//
// Created by Piotr Moszkowicz on 2019-03-18.
//

#pragma once

#include <array>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "colors.h"

class Circle {
public:
    Circle(float x, float y, float r) : m_circle(new sf::CircleShape), m_texture(new sf::Texture),
                                        m_pixels(new sf::Uint8[250000]), m_beforeL(0.51f) {
        m_circle->setPosition(x, y);
        m_circle->setRadius(r);
        m_circle->setOutlineThickness(5);
    }

    virtual ~Circle() {
        delete m_circle;
        delete m_texture;
        delete[] m_pixels;
    }

    sf::CircleShape &operator()() {
        return *m_circle;
    }

    void update(const float &l) {
        if (std::fabs(m_beforeL - l) < 0.05f) {
            return;
        }

        m_beforeL = l;

        this->fill(l);

        m_texture->update(m_pixels);
    }

protected:
    void create() {
        m_texture->create(250, 250);
        this->make();
        m_texture->update(m_pixels);
        m_circle->setTexture(m_texture);
    }
    virtual void make() = 0;
    virtual void fill(const float &l) = 0;

    sf::CircleShape *m_circle;
    sf::Texture *m_texture;
    sf::Uint8 *m_pixels;

    float m_beforeL;
};

class HslCircle : public Circle {
public:
    HslCircle(float x, float y, float r) : Circle(x, y, r) {
        this->create();
    }
private:
    void make() override {
        unsigned int index = 0;

        float h, r;
        HSL c{};

        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                r = std::sqrt(static_cast<float>(i * i + j * j));
                h = std::fmodf(
                        std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(M_PI) +
                        180.0f, 360.0f);

                if (r < 125.0f) {
                    c.H = h;
                    c.S = r * 0.008f;
                    c.L = m_beforeL;

                    m_cache[index++] = c;
                    draw_to_color_pixels(125 - i, 125 + j, convert(c), m_pixels);
                }
            }
        }
    }
    void fill(const float& l) override {
        unsigned int index = 0;

        float r,h;

        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                if (j * j + i * i < 15625) {
                    m_cache.at(index++).L = l;
                    draw_to_color_pixels(125 - i, 125 + j, convert(m_cache.at(index - 1)), m_pixels);
                }
            }
        }
    }

    std::array<HSL, 49075> m_cache{};
};

class HsvCircle : public Circle {
public:
    HsvCircle(float x, float y, float r) : Circle(x, y, r) {
        this->create();
    }
private:
    void make() override {
        float h, r;
        HSV c{};
        unsigned int index = 0;

        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                r = std::sqrt(static_cast<float>(i * i + j * j));
                h = std::fmodf(
                        std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(M_PI) +
                        180.0f, 360.0f);

                if (r <= 125.0f) {
                    c.H = h / 360.0f;
                    c.S = r * 0.008f;
                    c.V = m_beforeL;

                    m_cache[index++] = c;
                    draw_to_color_pixels(125 - i, 125 + j, convert(c), m_pixels);
                }
            }
        }
    }

    void fill(const float& l) override {
        unsigned int index = 0;

        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                if (i * i + j * j <= 15625) {
                    m_cache.at(index++).V = l;
                    draw_to_color_pixels(125 - i, 125 + j, convert(m_cache.at(index - 1)), m_pixels);
                }
            }
        }
    }

    std::array<HSV, 49075> m_cache{};
};

class CmyCircle : public Circle {
public:
    CmyCircle(float x, float y, float r) : Circle(x, y, r) {
        this->create();
    }

private:
    void make() override {
        float r, h;
        CMY c{};
        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                r = std::sqrt(static_cast<float>(i * i + j * j));
                h = std::fmodf(
                        std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(M_PI) +
                        180.0f, 360.0f);

                if (r <= 125.0f) {
                    c = CMY{
                            r * 0.008f,
                            h / 360.0f,
                            Circle::m_beforeL
                    };

                    draw_to_color_pixels(125 - i, 125 + j, convert(c), m_pixels);
                }
            }
        }
    }

    void fill(const float &l) override {
        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                if (i * i + j * j <= 15625) {
                    m_pixels[4 * ((j + 125) * 250 + 125 - i) + 2] = static_cast<sf::Uint8>((1.0f - m_beforeL) * 255.0f);
                }
            }
        }
    }
};

class RgbCircle : public Circle {
public:
    RgbCircle(float x, float y, float r) : Circle(x, y, r) {
        this->create();
    }

private:
    void make() override {
        RGB c{};
        float r, h;
        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                r = std::sqrt(static_cast<float>(i * i + j * j));
                h = std::fmodf(
                        std::atan2f(static_cast<float>(j), static_cast<float>(i)) * 180.0f / static_cast<float>(M_PI) +
                        180.0f, 360.0f);
                if (r <= 125.0f) {
                    c = RGB{
                            r * 0.008f * 255.0f,
                            h / 360.0f * 255.0f,
                            m_beforeL * 255.0f
                    };
                    draw_to_color_pixels(125 - i, 125 + j, c, m_pixels);
                }
            }
        }
    }

    void fill(const float &l) override {
        for (int i = -125; i < 125; i++) {
            for (int j = -125; j < 125; j++) {
                if (i * i + j * j <= 15625) {
                    m_pixels[4 * ((j + 125) * 250 + 125 - i) + 2] = static_cast<sf::Uint8>(m_beforeL * 255.0f);
                }
            }
        }
    }
};

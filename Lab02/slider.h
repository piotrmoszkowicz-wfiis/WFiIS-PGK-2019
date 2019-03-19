//
// Created by Piotr Moszkowicz on 2019-03-18.
//

#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "colors.h"

class Slider {
public:
    Slider() : m_slider(new sf::RectangleShape), m_texture(new sf::Texture),
               m_pixels(new sf::Uint8[250000]) {
        m_slider->setPosition(660, 20);
        m_slider->setSize(sf::Vector2f(38.0f, 256.0f));
        m_slider->setOutlineColor(sf::Color::Black);
        m_slider->setOutlineThickness(1.0f);

        RGB c{};

        for (int i = 0; i < 250; i++) {
            for (int j = 0; j < 250; j++) {
                c.R = static_cast<float>(j);
                c.G = static_cast<float>(j);
                c.B = static_cast<float>(j);
                draw_to_color_pixels(i, j, c, m_pixels);
            }
        }

        m_texture->create(250, 250);
        m_texture->update(m_pixels);
        m_slider->setTexture(m_texture);

        m_bars[0] = new sf::VertexArray(sf::Lines, 2);
        m_bars[1] = new sf::VertexArray(sf::Lines, 2);

        (*m_bars[0])[0].color = (*m_bars[0])[1].color = (*m_bars[1])[0].color = (*m_bars[1])[1].color = sf::Color::Black;

        const float pos = 137.7f;

        this->updatePos(pos);
    }

    ~Slider() {
        delete m_slider;
        delete m_texture;
        delete[] m_pixels;

        for (auto v : m_bars) {
            delete v;
        }
    }

    sf::RectangleShape &operator()() {
        return *m_slider;
    }

    std::array<sf::VertexArray *, 2> &getBars() {
        return m_bars;
    }

    float updatePos(const float &pos) {
        m_currentPos = pos;
        (*m_bars[0])[0].position = sf::Vector2f(645.0f, m_currentPos);
        (*m_bars[0])[1].position = sf::Vector2f(655.0f, m_currentPos);

        (*m_bars[1])[0].position = sf::Vector2f(703.0f, m_currentPos);
        (*m_bars[1])[1].position = sf::Vector2f(713.0f, m_currentPos);

        return (m_currentPos - 20.0f) / 250.0f;
    }

private:
    sf::RectangleShape *m_slider;
    sf::Texture *m_texture;
    sf::Uint8 *m_pixels;
    std::array<sf::VertexArray *, 2> m_bars{};

    float m_currentPos = 137.7f;
};

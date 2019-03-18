//
// Created by Piotr Moszkowicz on 2019-03-18.
//

#pragma once

#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "font.h"

class Menu : public sf::Drawable {
public:
    Menu() : m_fps("0"), m_yValue("0"), m_bValue("0"), m_lValue("0.0") {
        m_font.loadFromMemory(font_data, font_data_size);
        m_text = new sf::Text;
        m_text->setFont(m_font);
        m_text->setCharacterSize(12);
        m_text->setFillColor(sf::Color::Black);
    }

    ~Menu() override {
        delete m_text;
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        outstringxy(target, 650, 280, m_fps + " FPS");
        outstringxy(target, 40, 40, "HSL");
        outstringxy(target, 290, 290, "L = " + m_lValue);
        outstringxy(target, 350, 40, "HSV");
        outstringxy(target, 600, 290, "V = " + m_lValue);
        outstringxy(target, 50, 320, "CMY");
        outstringxy(target, 300, 570, "Y = " + m_yValue + " %");
        outstringxy(target, 350, 320, "RGB");
        outstringxy(target, 600, 570, "B = " + m_bValue);
    }

    void setFps(unsigned int& fps) {
        m_fps = std::to_string(fps);
    }

    void setColors(const float& l) {
        m_lValue = std::to_string(l).substr(0, 5);
        m_yValue = std::to_string(static_cast<unsigned int>(l * 100));
        m_bValue = std::to_string(static_cast<unsigned int>(l * 255));
    }

private:
    void outstringxy(sf::RenderTarget &target, float x, float y, const std::string &s) const {
        m_text->setPosition(x, y);
        m_text->setString(s);
        target.draw(*m_text);
    }

    sf::Font m_font;
    sf::Text *m_text;

    std::string m_fps, m_yValue, m_bValue, m_lValue;
};

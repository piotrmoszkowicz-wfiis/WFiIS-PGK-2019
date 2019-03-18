//
// Created by Piotr Moszkowicz on 2019-03-18.
//

#pragma once

#include <array>
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "circle.h"
#include "menu.h"
#include "slider.h"

class Window {
public:
    Window() : m_renderWindow(sf::VideoMode(800, 650), "GFK Lab 02", sf::Style::Titlebar | sf::Style::Close),
               m_frameCounter(0),
               m_fps(0),
               m_menu(Menu()),
               m_slider(Slider()) {
        m_circlesToDraw = {
                new HslCircle(40, 40, 125),
                new HsvCircle(350, 40, 125),
                new CmyCircle(50, 320, 125),
                new RgbCircle(350, 320, 125)
        };

        this->setColors(m_color);
    }

    ~Window() {
        for (auto c : m_circlesToDraw) {
            delete c;
        }
    }

    void render() {
        sf::Event e{};
        this->clear();
        while (m_renderWindow.pollEvent(e)) this->handleEvent(e);
        this->drawMenu();
        this->drawCircles();
        this->drawSlider();
        this->printFps();
        this->display();
    }

    bool isOpen() const {
        return m_renderWindow.isOpen();
    }

    void setColors(const float &c) {
        m_color = c;
        m_menu.setColors(m_color);
    }

private:
    void clear() {
        m_renderWindow.clear(sf::Color::White);
    }

    void display() {
        m_renderWindow.display();
    }

    void drawMenu() {
        m_menu.setFps(m_fps);
        m_renderWindow.draw(m_menu);
    }

    void drawCircles() {
        for (auto c : m_circlesToDraw) {
            c->update(m_color);
            m_renderWindow.draw((*c)());
        }
    }

    void drawSlider() {
        auto bars = m_slider.getBars();

        for (auto v : bars) {
            m_renderWindow.draw(*v);
        }

        m_renderWindow.draw(m_slider());
    }

    void handleEvent(sf::Event &e) {
        switch (e.type) {
            case sf::Event::Closed: {
                m_renderWindow.close();
                break;
            }
            case sf::Event::MouseMoved: {
                this->handleMouseMove(e);
                break;
            }
            case sf::Event::MouseButtonPressed: {
                this->handleMousePressed(e);
                break;
            }
            case sf::Event::MouseButtonReleased: {
                this->handleMouseReleased();
                break;
            }
            default:
                break;
        }
    }

    void handleMouseMove(sf::Event &e) {
        if (m_buttonHold && this->isMouseOnBar(e.mouseMove.x, e.mouseMove.y)) {
            float newL = m_slider.updatePos(e.mouseMove.y);

            if (newL > 1.0f) {
                newL = 1.0f;
            }

            for (auto c : m_circlesToDraw) {
                c->update(newL);
            }
            this->setColors(newL);
        }
    }

    void handleMousePressed(sf::Event &e) {
        if (e.mouseButton.button == 0 && this->isMouseOnBar(e.mouseButton.x, e.mouseButton.y)) {
            float newL = m_slider.updatePos(e.mouseButton.y);

            if (newL > 1.0f) {
                newL = 1.0f;
            }

            for (auto c : m_circlesToDraw) {
                c->update(newL);
            }
            this->setColors(newL);
            m_buttonHold = true;
        }
    }

    void handleMouseReleased() {
        m_buttonHold = false;
    }

    inline bool isMouseOnBar(int &x, int &y) {
        return (x > 660 && x < 698) && (y > 20 && y < 276);
    }

    void printFps() {
        if (m_clock.getElapsedTime().asSeconds() >= 1.0f) {
            m_fps = (unsigned int) ((float) m_frameCounter / m_clock.getElapsedTime().asSeconds());
            m_clock.restart();
            m_frameCounter = 0;
        }
        m_frameCounter++;
    }

    sf::RenderWindow m_renderWindow;
    sf::Clock m_clock;

    Menu m_menu;
    Slider m_slider;

    std::array<Circle *, 4> m_circlesToDraw{};

    unsigned int m_frameCounter;
    unsigned int m_fps;

    float m_color = 0.51f;

    bool m_buttonHold = false;
};
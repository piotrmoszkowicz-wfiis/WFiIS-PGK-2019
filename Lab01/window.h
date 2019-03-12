//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#pragma once

#include <iostream>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "shapes.h"

enum class AppState {
    None = 0,
    ChooseDrawingColor = 1,
    ChooseFillingColor = 2,
    DrawLine = 3,
    DrawRect = 4,
    DrawFilledRect = 5,
    DrawCircle = 6
};

class Window {
public:
    Window() : m_renderWindow(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close),
               m_windowMenu(Menu()), m_state(AppState::None),
               m_shapes(std::vector<sf::Drawable *>()) {
        m_renderWindow.setFramerateLimit(60);
        m_renderTexture.create(794, 534);
        m_renderTexture.clear(sf::Color::Black);
    }

    ~Window() {
        this->clearVector();
        delete m_currentlyDrawn;
    }

    void render() {
        sf::Event e;
        this->clear();
        while (m_renderWindow.pollEvent(e)) this->handleEvent(e);
        this->drawMenu();
        this->drawPaintedItems();
        this->drawCurrentlyPaintingItem();
        this->display();
        this->drawTexture();
    }

    bool isOpen() const {
        return m_renderWindow.isOpen();
    }

private:
    void clear() {
        m_renderWindow.clear(sf::Color::Black);
    }

    void clearVector() {
        for (auto shape : m_shapes) {
            delete shape;
        }
        m_shapes.clear();
    }

    void close() {
        m_renderWindow.close();
    }

    void display() {
        m_renderTexture.display();
    }

    void drawMenu() {
        m_renderWindow.draw(m_windowMenu);
    }

    void drawCurrentlyPaintingItem() {
        if (m_currentlyDrawn != nullptr) {
            m_renderTexture.draw(*m_currentlyDrawn);
        }
    }

    void drawPaintedItems() {
        for (auto item : m_shapes) {
            m_renderTexture.draw(*item);
        }
    }

    void drawTexture() {
        sf::Sprite sprite(m_renderTexture.getTexture());
        sprite.setPosition(4.0f, 64.0f);
        m_renderWindow.draw(sprite);
        m_renderWindow.display();
    }

    void handleEvent(sf::Event e) {
        if (e.type == sf::Event::Closed) this->close();
        else if (e.type == sf::Event::KeyPressed) this->handleKeyboard(e);
        else if (e.type == sf::Event::MouseButtonPressed) this->handleClick(e);
        else if (e.type == sf::Event::MouseButtonReleased) this->handleRelease(e);
        else if (e.type == sf::Event::MouseMoved) this->handleMouseMove(e);
    }

    void handleClick(sf::Event e) {
#ifdef DEBUG
        std::cout << "Clicked mouse: " << e.mouseButton.button << std::endl;
#endif

        if (e.mouseButton.button == 0) {
            if (e.mouseButton.y < 62 && e.mouseButton.x < 765) {
                if (m_state == AppState::ChooseDrawingColor) {
                    m_windowMenu.setDrawingColor(e.mouseButton.x, e.mouseButton.y);
                } else if (m_state == AppState::ChooseFillingColor) {
                    m_windowMenu.setFillingColor(e.mouseButton.x, e.mouseButton.y);
                }
            }
            if ((e.mouseButton.x > 2 && e.mouseButton.x < 798) && (e.mouseButton.y > 62 && e.mouseButton.y < 598)) {
#ifdef DEBUG
                std::cout << "x: " << e.mouseButton.x << " y: " << e.mouseButton.y << std::endl;
#endif

                auto x = fixXCoordinate(e.mouseButton.x);
                auto y = fixYCoordinate(e.mouseButton.y);

                switch (m_state) {
                    case AppState::DrawCircle:
                        m_currentlyDrawn = createCircle(x, y, m_windowMenu.drawing_color);
                        break;
                    case AppState::DrawFilledRect:
                        m_currentlyDrawn = createRect(x, y, m_windowMenu.drawing_color,
                                                      m_windowMenu.filling_color);
                        break;
                    case AppState::DrawLine:
                        m_currentlyDrawn = createLine(x, y, m_windowMenu.drawing_color);
                        break;
                    case AppState::DrawRect:
                        m_currentlyDrawn = createRect(x, y, m_windowMenu.drawing_color);
                        break;
                    default:
                        return;
                }
                m_isDrawing = true;
            }
        }
    }

    void handleKeyboard(sf::Event e) {
#ifdef DEBUG
        std::cout << "Clicked key: " << e.key.code << std::endl;
#endif

        AppState stateToSet = AppState::None;
        std::string charStateToSet;

        switch (e.key.code) {
            case 5:
                stateToSet = AppState::ChooseDrawingColor;
                charStateToSet = "f";
                break;
            case 1:
                stateToSet = AppState::ChooseFillingColor;
                charStateToSet = "b";
                break;
            case 11:
                stateToSet = AppState::DrawLine;
                charStateToSet = "l";
                break;
            case 17:
                stateToSet = AppState::DrawRect;
                charStateToSet = "r";
                break;
            case 0:
                stateToSet = AppState::DrawFilledRect;
                charStateToSet = "a";
                break;
            case 2:
                stateToSet = AppState::DrawCircle;
                charStateToSet = "c";
                break;
            case 22:
                this->saveToFile();
                break;
            case 14:
                this->openFile();
                break;
            case 36:
                this->close();
                return;
            default:
                return;
        }

        this->setState(stateToSet, charStateToSet);
    }

    void handleMouseMove(sf::Event e) {
#ifdef DEBUG
        std::cout << "Moved mouse -> x:" << e.mouseMove.x << " y: " << e.mouseMove.y << std::endl;
#endif
        if (e.mouseMove.y < 62 || e.mouseMove.y > 592 || e.mouseMove.x < 4 || e.mouseMove.x > 794) {
            return;
        }

        auto x = fixXCoordinate(e.mouseMove.x);
        auto y = fixYCoordinate(e.mouseMove.y);
#ifdef DEBUG
        std::cout << "Normalized -> x: " << x << " y: " << y << std::endl;
#endif

        if (m_isDrawing) {
            m_renderTexture.clear(sf::Color::Black);
            switch (m_state) {
                case AppState::DrawCircle:
                    updateDrawingCircle(dynamic_cast<sf::CircleShape *>(m_currentlyDrawn), x, y);
                    break;
                case AppState::DrawFilledRect:
                case AppState::DrawRect:
                    updateDrawingRect(dynamic_cast<sf::RectangleShape *>(m_currentlyDrawn), x, y);
                    break;
                case AppState::DrawLine:
                    updateDrawingLine(dynamic_cast<sf::VertexArray *>(m_currentlyDrawn), x, y);
                    break;
                default:
                    return;
            }
        }
    }

    void handleRelease(sf::Event e) {
#ifdef DEBUG
        std::cout << "Mouse released " << e.mouseButton.button << " -> x:" << e.mouseButton.x << " y: "
                  << e.mouseButton.y << std::endl;
#endif
        if (m_isDrawing) {
            if (e.mouseButton.y < 62 || e.mouseButton.y > 592 || e.mouseButton.x < 4 || e.mouseButton.x > 794) {
                return;
            }

            auto x = fixXCoordinate(e.mouseButton.x);
            auto y = fixYCoordinate(e.mouseButton.y);

#ifdef DEBUG
            std::cout << "Normalized -> x: " << x << " y: " << y << std::endl;
#endif

            switch (m_state) {
                case AppState::DrawCircle:
                    updateDrawingCircle(dynamic_cast<sf::CircleShape *>(m_currentlyDrawn), x, y);
                    this->pushToDrawn();
                    break;
                case AppState::DrawFilledRect:
                case AppState::DrawRect:
                    updateDrawingRect(dynamic_cast<sf::RectangleShape *>(m_currentlyDrawn), x, y);
                    this->pushToDrawn();
                    break;
                case AppState::DrawLine:
                    updateDrawingLine(dynamic_cast<sf::VertexArray *>(m_currentlyDrawn), x, y);
                    this->pushToDrawn();
                    break;
                default:
                    return;
            }
        }
    }

    void openFile() {
        this->clearVector();
        m_renderTexture.clear(sf::Color::Black);

        m_fileTexture.loadFromFile("result.png");
        auto fileSprite = new sf::Sprite(m_fileTexture);

        this->pushItemToDrawn(fileSprite);
    }

    void pushItemToDrawn(sf::Drawable *item) {
        m_shapes.push_back(item);
    }

    void pushToDrawn() {
        this->pushItemToDrawn(m_currentlyDrawn);
        m_currentlyDrawn = nullptr;
        m_isDrawing = false;
    }

    void saveToFile() {
        m_renderTexture.getTexture().copyToImage().saveToFile("result.png");
    };

    void setState(AppState s, const std::string &c) noexcept {
        m_state = s;
        m_windowMenu.setStateChar(c);
    }

    sf::RenderWindow m_renderWindow;
    sf::RenderTexture m_renderTexture;
    Menu m_windowMenu;
    AppState m_state;

    std::vector<sf::Drawable *> m_shapes;
    bool m_isDrawing = false;
    sf::Drawable *m_currentlyDrawn = nullptr;
    sf::Texture m_fileTexture;
};

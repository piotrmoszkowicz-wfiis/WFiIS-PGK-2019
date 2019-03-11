//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#pragma once

#include <iostream>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "font.h"

class Menu : public sf::Drawable {
private:
    sf::Font font;
    sf::Text *text;
    sf::RectangleShape *rectangle;

    sf::RectangleShape *rectangle_drawing_color;
    sf::RectangleShape *rectangle_filling_color;

    sf::Texture *colors_texture;
    sf::Sprite *colors_sprite;
    sf::Uint8 *colors_pixels;
    const unsigned int colors_size_x = 765;
    const unsigned int colors_size_y = 60;

    std::string state_char = "";

    inline void
    draw_to_color_pixels(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
        colors_pixels[4 * (y * colors_size_x + x) + 0] = r;
        colors_pixels[4 * (y * colors_size_x + x) + 1] = g;
        colors_pixels[4 * (y * colors_size_x + x) + 2] = b;
        colors_pixels[4 * (y * colors_size_x + x) + 3] = 255;
    }

    inline sf::Color colorFromClick(int x, int y) const {
        const int index = (y * colors_size_x + x) * 4;
        sf::Uint8 r = colors_pixels[index + 0];
        sf::Uint8 g = colors_pixels[index + 1];
        sf::Uint8 b = colors_pixels[index + 2];

        return sf::Color(r, g, b);
    }

public:
    Menu() {
        font.loadFromMemory(font_data, font_data_size);
        text = new sf::Text;
        text->setFont(font);
        text->setCharacterSize(12);
        text->setFillColor(sf::Color::White);

        rectangle = new sf::RectangleShape(sf::Vector2f(796, 536));
        rectangle->setFillColor(sf::Color::Transparent);
        rectangle->setOutlineColor(sf::Color::White);
        rectangle->setOutlineThickness(1.0f);
        rectangle->setPosition(2, 62);

        unsigned int x, y;
        colors_pixels = new sf::Uint8[colors_size_x * colors_size_y * 4];
        for (x = 0; x < 255; x++)
            for (y = 0; y < 30; y++) {
                draw_to_color_pixels(x, y, x, 255, 0);
                draw_to_color_pixels(x + 255, y, 255, 255 - x, 0);
                draw_to_color_pixels(x + 510, y, 255, 0, x);
                draw_to_color_pixels(254 - x, y + 30, 0, 255, 255 - x);
                draw_to_color_pixels(509 - x, y + 30, 0, x, 255);
                draw_to_color_pixels(764 - x, y + 30, 255 - x, 0, 255);
            }

        colors_texture = new sf::Texture();
        colors_texture->create(colors_size_x, colors_size_y);
        colors_texture->update(colors_pixels);

        colors_sprite = new sf::Sprite();
        colors_sprite->setTexture(*colors_texture);
        colors_sprite->setPosition(1, 1);

        rectangle_drawing_color = new sf::RectangleShape(sf::Vector2f(30, 30));
        rectangle_drawing_color->setFillColor(drawing_color);
        rectangle_drawing_color->setOutlineColor(drawing_color);
        rectangle_drawing_color->setPosition(768.0f, 0.0f);

        rectangle_filling_color = new sf::RectangleShape(sf::Vector2f(30, 30));
        rectangle_filling_color->setFillColor(filling_color);
        rectangle_filling_color->setOutlineColor(filling_color);
        rectangle_filling_color->setPosition(768.0f, 31.0f);
    }

    ~Menu() override {
        delete text;
        delete rectangle;
        delete colors_pixels;
        delete colors_texture;
        delete colors_sprite;
        delete rectangle_drawing_color;
        delete rectangle_filling_color;
    }

    void outtextxy(sf::RenderTarget &target, float x, float y, wchar_t *str) const {
        text->setPosition(x, y);
        text->setString(str);
        target.draw(*text);
    }

    void outcharxy(sf::RenderTarget &target, float x, float y, const std::string &s) const {
        text->setPosition(x, y);
        text->setString(s);
        target.draw(*text);
    }

    void setStateChar(const std::string &c) noexcept {
        state_char = c;
    }

    void setDrawingColor(int x, int y) {
        drawing_color = colorFromClick(x, y);
        rectangle_drawing_color->setFillColor(drawing_color);
        rectangle_drawing_color->setOutlineColor(drawing_color);
    }

    void setFillingColor(int x, int y) {
        filling_color = colorFromClick(x, y);
        rectangle_filling_color->setFillColor(filling_color);
        rectangle_filling_color->setOutlineColor(filling_color);
    }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        std::string s = "a";
        outtextxy(target, 5, 600, const_cast<wchar_t*>(L"f - wybór koloru rysowania"));
        outtextxy(target, 5, 615, const_cast<wchar_t*>(L"b - wybór koloru wypełniania"));
        outtextxy(target, 5, 630, const_cast<wchar_t*>(L"l - rysowanie linii"));

        outtextxy(target, 200, 600, const_cast<wchar_t *>(L"r - rysowanie prostokąta"));
        outtextxy(target, 200, 615, const_cast<wchar_t *>(L"a - rysowanie wypełnionego prostokąta"));
        outtextxy(target, 200, 630, const_cast<wchar_t *>(L"c - rysowanie okręgu"));

        outtextxy(target, 470, 600, const_cast<wchar_t *>(L"w - zapis do pliku"));
        outtextxy(target, 470, 615, const_cast<wchar_t *>(L"o - odczyt z pliku"));
        outtextxy(target, 470, 630, const_cast<wchar_t *>(L"esc - wyjście"));

        outtextxy(target, 650, 615, const_cast<wchar_t *>(L"Aktualne:"));

        outcharxy(target, 720, 615, state_char);

        target.draw(*rectangle);
        target.draw(*rectangle_drawing_color);
        target.draw(*rectangle_filling_color);
        target.draw(*colors_sprite);
    }

    sf::Color drawing_color = sf::Color::Transparent;
    sf::Color filling_color = sf::Color::Transparent;
};
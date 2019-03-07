//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#pragma once

#include <iostream>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

float fixXCoordinate(int x) {
    return static_cast<float>(x) - 3.0f;
}

float fixYCoordinate(int y) {
    return static_cast<float>(y) - 60.0f;
}

sf::CircleShape *createCircle(float x, float y, sf::Color drawingColor) {
    auto circle = new sf::CircleShape;
    circle->setPosition(x, y);
    circle->setRadius(0.0f);
    circle->setOutlineColor(drawingColor);
    circle->setOutlineThickness(2.0f);
    circle->setFillColor(sf::Color::Transparent);
    return circle;
}

sf::RectangleShape *
createRect(float x, float y, sf::Color drawingColor, sf::Color fillingColor = sf::Color::Transparent) {
    auto rect = new sf::RectangleShape;
    rect->setPosition(x, y);
    rect->setSize(sf::Vector2f(0, 0));
    rect->setOutlineColor(drawingColor);
    rect->setOutlineThickness(2.0f);
    rect->setFillColor(fillingColor);
    return rect;
}

sf::VertexArray *createLine(float x, float y, sf::Color drawingColor) {
    auto line = new sf::VertexArray(sf::Lines, 2);
    (*line)[0].position = sf::Vector2f(x, y);
    (*line)[0].color = drawingColor;
    (*line)[1].position = sf::Vector2f(x, y);
    (*line)[1].color = drawingColor;
    return line;
}

inline float countDistance(float x, float y, float x2, float y2) {
    float distX = x2 - x;
    float distY = y2 - y;
    return sqrt((distX * distX) + (distY * distY));
}

void updateDrawingCircle(sf::CircleShape *circle, float x, float y) {
    sf::Vector2f pos = circle->getPosition();

    auto radius = countDistance(pos.x, pos.y, x, y) / 2;

    if (x > 700 && pos.x + 2 * radius > 794.0f) {
        radius = (792.0f - pos.x) / 2.0f;
    }

    if (x < 100 && pos.x - 2 * radius < 2.0f) {
        radius = (pos.x - 2.0f) / 2.0f;
    }

    if (y > 450 && pos.y + 2 * radius > 534.0f) {
        radius = (532.0f - pos.y) / 2.0f;
    }

    if (y < 100 && pos.y - 2 * radius < 2.0f) {
        radius = (pos.y - 2.0f) / 2.0f;
    }

    if (pos.x - x > 0 || pos.y - y > 0) {
        radius *= -1.0f;
    }

    circle->setRadius(radius);

#ifdef DEBUG
    std::cout << "x: " << pos.x << " y: " << pos.y << " r: " << radius << std::endl;
    std::cout << "Max-Left: " << pos.x - radius << " Max-Right: " << pos.x + radius << std::endl;
    std::cout << "Max-Up: " << pos.y - 63.0f - radius << " Max-Bottom: " << pos.y + 63.0f + radius << std::endl;
#endif
}

void updateDrawingRect(sf::RectangleShape *rect, float x, float y) {
    auto newScaleX = 1.0f;
    auto newScaleY = 1.0f;

    sf::Vector2f pos = rect->getPosition();
    sf::Vector2f size = rect->getSize();
    size.x = abs(pos.x - x);
    size.y = abs(pos.y - y);

    if (pos.x - x > 0) {
        newScaleX = -1.0f;
    }

    if (pos.y - y > 0) {
        newScaleY = -1.0f;
    }

    rect->setScale(newScaleX, newScaleY);
    rect->setSize(size);
}

void updateDrawingLine(sf::VertexArray *line, float x, float y) {
    (*line)[1].position = sf::Vector2f(x, y);
}

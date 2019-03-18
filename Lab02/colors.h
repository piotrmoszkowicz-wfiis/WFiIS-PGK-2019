//
// Created by Piotr Moszkowicz on 2019-03-18.
//

#pragma once

#include <SFML/Graphics.hpp>

struct HSL {
    float H;
    float S;
    float L;
};

struct HSV {
    float H;
    float S;
    float V;
};

struct CMY {
    float C;
    float M;
    float Y;
};

struct RGB {
    float R;
    float G;
    float B;
};

RGB convert(const HSL &c) {
    float z = (1.0f - std::fabsf(2.0f * c.L - 1.0f)) * c.S;
    float x = z * (1.0f - std::fabsf(std::fmodf(c.H * 0.016666f, 2.0f) - 1.0f));
    float m = c.L - z / 2.0f;

    RGB result = {};

    if (c.H < 60.0f) {
        result.R = z + m;
        result.G = x + m;
        result.B = m;
    } else if (c.H < 120.0f) {
        result.R = x + m;
        result.G = z + m;
        result.B = m;
    } else if (c.H < 180.0f) {
        result.R = m;
        result.G = z + m;
        result.B = x + m;
    } else if (c.H < 240.0f) {
        result.R = m;
        result.G = x + m;
        result.B = z + m;
    } else if (c.H < 300.0f) {
        result.R = x + m;
        result.G = m;
        result.B = z + m;
    } else {
        result.R = z + m;
        result.G = m;
        result.B = x + m;
    }

    result.R *= 255.0f;
    result.G *= 255.0f;
    result.B *= 255.0f;

    return result;
}

RGB convert(const HSV &c) {
    if (c.S == 0) {
        return RGB{
                c.V * 255.0f,
                c.V * 255.0f,
                c.V * 255.0f
        };
    }

    RGB result = {};

    float h = c.H * 6.0f;

    if (h == 6.0f) {
        h = 0.0f;
    }

    auto i = static_cast<int>(h);

    auto x = c.V * (1.0f - c.S);
    auto y = c.V * (1.0f - c.S * (h - i));
    auto z = c.V * (1.0f - c.S * (1.0f - (h - i)));

    if (i == 0) {
        result.R = c.V;
        result.G = z;
        result.B = x;
    } else if (i == 1) {
        result.R = y;
        result.G = c.V;
        result.B = x;
    } else if (i == 2) {
        result.R = x;
        result.G = c.V;
        result.B = z;
    } else if (i == 3) {
        result.R = x;
        result.G = y;
        result.B = c.V;
    } else if (i == 4) {
        result.R = z;
        result.G = x;
        result.B = c.V;
    } else {
        result.R = c.V;
        result.G = x;
        result.B = y;
    }

    result.R *= 255.0f;
    result.G *= 255.0f;
    result.B *= 255.0f;

    return result;
}

RGB convert(const CMY &c) {
    return RGB{
            (1.0f - c.C) * 255.0f,
            (1.0f - c.M) * 255.0f,
            (1.0f - c.Y) * 255.0f
    };
}

inline void draw_to_color_pixels(int x, int y, RGB c, sf::Uint8 *colors_pixels) {
    colors_pixels[4 * (y * 250 + x) + 0] = static_cast<sf::Uint8>(c.R);
    colors_pixels[4 * (y * 250 + x) + 1] = static_cast<sf::Uint8>(c.G);
    colors_pixels[4 * (y * 250 + x) + 2] = static_cast<sf::Uint8>(c.B);
    colors_pixels[4 * (y * 250 + x) + 3] = static_cast<sf::Uint8>(255);

    // std::cout << 4 * (y * 250 + x) + 3 << std::endl;
}
#pragma once
#include <cstdio>

class Vector4 {
public:
    double data[4];

    Vector4();

    void Print();

    void Set(double d1, double d2, double d3);

    double GetX();

    double GetY();

    double GetZ();

    Vector4 operator-(const Vector4 &);

    friend Vector4 operator*(const Vector4 &, double);
};

class Matrix4 {
public:
    double data[4][4];

    Matrix4();

    void Print();

    Matrix4 operator*(const Matrix4);
    Matrix4 operator*(const Matrix4) const;

    friend Vector4 operator*(const Matrix4, const Vector4);
};
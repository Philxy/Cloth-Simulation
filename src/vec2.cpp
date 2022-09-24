#include "../include/vec2.h"

Vec2::Vec2(double X, double Y)
{
    x = X;
    y = Y;
}

Vec2::Vec2()
{
}

Vec2::Vec2(const Vec2 &rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
}

Vec2 operator+(const Vec2 &left, const Vec2 &right)
{
    return Vec2(left.x + right.x, left.y + right.y);
}

Vec2 operator-(const Vec2 &left, const Vec2 &right)
{
    return Vec2(left.x - right.x, left.y - right.y);
}

Vec2 operator-(const Vec2 &v)
{
    return Vec2(-v.x, -v.y);
}

Vec2 operator+(const Vec2 &v)
{
    return Vec2(v.x, v.y);
}

Vec2 operator*(const Vec2 &left, double c)
{
    return Vec2(c * left.x, c * left.y);
}

Vec2 operator*(double c, const Vec2 &right)
{
    return Vec2(c * right.x, c * right.y);
}

Vec2 operator+=(const Vec2 &left, const Vec2 &right)
{
    return Vec2(left.x + right.x, left.y + right.y);
}

Vec2 operator-=(const Vec2 &left, const Vec2 &right)
{
    return Vec2(left.x - right.x, left.y - right.y);
}

double operator*=(const Vec2 &left, const Vec2 &right)
{
    return left.x * right.x + left.y * right.y;
}

double operator*(const Vec2 &left, const Vec2 &right)
{
    return left.x * right.x + left.y * right.y;
}
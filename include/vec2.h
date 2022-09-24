#pragma once

struct Vec2
{
public:
   double x;
   double y;

   Vec2();
   Vec2(double X, double Y);
   Vec2(const Vec2& rhs);

   friend Vec2 operator+(const Vec2 &left, const Vec2 &right);
   friend Vec2 operator-(const Vec2 &left, const Vec2 &right);
   friend Vec2 operator+(const Vec2 &v);
   friend Vec2 operator-(const Vec2 &v);
   friend Vec2 operator+=(const Vec2 &left, const Vec2 &right);
   friend Vec2 operator-=(const Vec2 &left, const Vec2 &right);
   friend double operator*=(const Vec2 &left, const Vec2 &right);
   friend double operator*(const Vec2 &left, const Vec2 &right);
   friend Vec2 operator*(const Vec2 &left, double c);
   friend Vec2 operator*(double c, const Vec2 &right);
};

Vec2 operator+(const Vec2 &left, const Vec2 &right);
Vec2 operator-(const Vec2 &left, const Vec2 &right);
Vec2 operator+(const Vec2 &v);
Vec2 operator-(const Vec2 &v);
Vec2 operator+=(const Vec2 &left, const Vec2 &right);
Vec2 operator-=(const Vec2 &left, const Vec2 &right);
double operator*=(const Vec2 &left, const Vec2 &right);
double operator*(const Vec2 &left, const Vec2 &right);
Vec2 operator*(const Vec2 &left, double c);
Vec2 operator*(double c, const Vec2 &right);

/*
Vec2 operator+(Vec2 &left, Vec2 &right)
{
   return Vec2(left.x + right.x, left.x + right.y);
}

Vec2 operator-(Vec2 &left, Vec2 &right)
{
   return Vec2(left.x - right.x, left.x - right.y);
}


Vec2 operator*(Vec2 &left, double &right)
{
   return Vec2(left.x * right, left.y * right);
};

Vec2 operator*(double &left, Vec2 &right)
{
   return Vec2(left * right.x, left * right.y);
};

Vec2 operator/(Vec2 &left, double &right)
{
   return Vec2(left.x / right, left.y / right);
};

Vec2 operator/(double &left, Vec2 &right)
{
   return Vec2(left / right.x, left / right.y);
};


double operator*(Vec2 &left, Vec2 &right)
{
   return left.x * right.x + left.x * right.y;
};

*/

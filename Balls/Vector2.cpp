#include "Vector2.h"

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float _a, float _b) 
{
	x = _a;
	y = _b;
}
	
Vector2::Vector2(const Vector2& other) 
{
	x = other.x;
	y = other.y;
}

Vector2& Vector2::operator=(const Vector2& v) {
	x = v.x;
	y = v.y;
	return *this;
}

Vector2 Vector2::operator+(const Vector2& v) const 
{
	return Vector2(x + v.x, y + v.y);
}

Vector2& Vector2::operator+=(const Vector2& v) 
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2 Vector2::operator-(const Vector2& v) const 
{
	return Vector2(x - v.x, y - v.y);
}

Vector2& Vector2::operator-=(const Vector2& v) 
{
	x -= v.x;
	y -= v.y;
	return *this;
}

float Vector2::len() 
{
	return sqrt(x * x + y * y);
}

float Vector2::operator*(const Vector2& v) const 
{
	return x * v.x + y * v.y;
}

float Vector2::operator^(const Vector2& v) const 
{
	return x * v.y - y * v.x;
}

Vector2 operator*(float k, const Vector2& v)
{
	return Vector2(v.x * k, v.y * k);
}

Vector2 Vector2::operator*(float k) const
{
	return Vector2(x * k, y * k);
}

Vector2& Vector2::operator*=(float k) 
{
	x *= k;
	y *= k;
	return *this;
}

Vector2 Vector2::operator/(float k) const
{
	return Vector2(x / k, y / k);
}

Vector2& Vector2::operator/=(float k) 
{
	x /= k;
	y /= k;
	return *this;
}

Vector2 Vector2::norm() const 
{
	Vector2 v(x, y);
	return v / v.len();
}

Vector2 Vector2::ort() const 
{
	Vector2 v(0 - y, x);
	return v / v.len();
}

Vector2 Vector2::operator-() const
{
	return Vector2(0 - x, 0 - y);
}

int Vector2::operator==(const Vector2& v) const
{
	return x == v.x && y == v.y;
}

int Vector2::operator!=(const Vector2& v) const 
{
	return x != v.x || y != v.y;
}

int Vector2::operator||(const Vector2& v) const 
{
	return !(x * v.y - y * v.x);
}


std::ostream& operator<<(std::ostream& stream, const Vector2& v)
{
	stream << v.x << " " << v.y;
	return stream;
}

std::istream& operator>>(std::istream& stream, Vector2& v) 
{
	stream >> v.x >> v.y;
	return stream;
}

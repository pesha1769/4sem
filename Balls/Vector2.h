#pragma once
#include <iostream>

struct Vector2 
{
	float x, y;

	Vector2();
	Vector2(float, float);
	Vector2(const Vector2&);

	Vector2& operator=(const Vector2&);
	Vector2 operator+(const Vector2&) const;	
	Vector2& operator+=(const Vector2&);
	Vector2 operator-(const Vector2&) const;	
	Vector2& operator-=(const Vector2&);	

	float len();	
	float operator*(const Vector2&) const;	// (a, b)
	float operator^(const Vector2&) const;	// [a, b] 

	Vector2 operator*(float) const;		// b = a * k
	Vector2& operator*=(float);		// b *= k
	Vector2 operator/(float) const;	
	Vector2& operator/=(float);		

	Vector2 norm() const;		// a/|a|
	Vector2 ort() const;		// n _|_ a, |n| = 1
	Vector2 operator-() const;	// b = -a

	int operator==(const Vector2&) const;	// a == b
	int operator!=(const Vector2&) const;	// a != b
	int operator||(const Vector2&) const;	// a || b 
};
std::ostream& operator<<(std::ostream&, const Vector2&);	
std::istream& operator>>(std::istream&, Vector2&);		
Vector2 operator*(float, const Vector2&);	// b = k * a

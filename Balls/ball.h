#pragma once
#include "Vector2.h"

class MaterialPoint
{
public:
	float mass;
	Vector2 position;
	Vector2 velocity;

	MaterialPoint();

	void UpdatePosition(float dt);
};

class Ball : public MaterialPoint 
{
public:
	float radius;
	int type;

	Ball();
};

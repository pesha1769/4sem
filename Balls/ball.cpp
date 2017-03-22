#include <iostream>
#include "ball.h"

MaterialPoint::MaterialPoint() 
{
	mass = (rand() % 5) * 5;
	velocity = Vector2(rand() % 150 - 75, rand() % 150 - 75);
	position = Vector2(0, 0);
}

void MaterialPoint::UpdatePosition(float dt) 
{
	position += velocity * dt;
}


Ball::Ball() 
{
	radius = (rand() % 5) * 5;
	type = (rand() % 5) * 5;

}
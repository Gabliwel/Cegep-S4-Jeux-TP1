#include "CollisionCircle.h"

CollisionCircle::CollisionCircle()
{
	this->radius = 1.0f;
	this->x = 0.0f;
	this->y = 0.0f;
}

CollisionCircle::CollisionCircle(const float radius, const float x, const float y)
{
	this->radius = radius;
	this->x = x;
	this->y = y;
}

bool CollisionCircle::checkCollision(const CollisionCircle& otherCircle) const
{
	float lineX = this->x - otherCircle.x;
	float lineY = this->y - otherCircle.y;

	float distance = lineX * lineX + lineY * lineY;
	float totalRadius = this->radius + otherCircle.radius;

	//À la place de faire la racine carré de la distance, on met la somme des rayons au carré; plus économe.
	totalRadius *= totalRadius;

	//Deux cercles qui se touchent sont considérées en collision
	if (distance <= totalRadius) return true;

	return false;
}

float CollisionCircle::getRadius() const
{
	return radius;
}

float CollisionCircle::getX() const
{
	return x;
}

float CollisionCircle::getY() const
{
	return y;
}

void CollisionCircle::setPosition(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

void CollisionCircle::setRadius(const float radius)
{
	this->radius = radius;
}
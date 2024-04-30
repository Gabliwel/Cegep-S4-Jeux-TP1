#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CollisionCircle.h"

using namespace sf;

class GameObject : public Sprite
{
public:
	GameObject();

	void initialize(const Texture& texture, const Vector2f initialPosition, const int worldWidth, const int worldHeight);

	void activate();
	void deactivate();
	bool isActive() const;

	float getRotationRadians() const;
	float getRotationRadianInDegrees() const;
	void setRotationRadians(const float angle);
	void rotateInRadians(const float angle);

	const CollisionCircle& getCollisionCircle() const;
	bool isColliding(const GameObject& other) const;
	float getCollisionRadius() const;
	void setCollisionRadius(const float radius);

	void setPosition(float x, float y);
	void setPosition(const Vector2f& position);

	void move(float offsetX, float offsetY);
	void move(const Vector2f& offset);
	void draw(RenderWindow& renderWindow);

protected:
	static const float RADIANS_TO_DEGREE;
	CollisionCircle collisionCircle;

private:
	bool active;
	float rotationRadians;
};


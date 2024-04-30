#include "GameObject.h"

const float GameObject::RADIANS_TO_DEGREE = 180.0f / M_PI; //57.295779513f;

GameObject::GameObject()
{
	active = false;
	rotationRadians = 0.0f;
}

void GameObject::initialize(const Texture& texture, const Vector2f initialPosition, const int worldWidth, const int worldHeight)
{
	setTexture(texture);
	setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
	setCollisionRadius(texture.getSize().x / 2.0f);
	setPosition(initialPosition);
}

void GameObject::activate()
{
	active = true;
}

void GameObject::deactivate()
{
	active = false;
}

bool GameObject::isActive() const
{
	return active;
}

float GameObject::getRotationRadians() const
{
	return rotationRadians;
}

float GameObject::getRotationRadianInDegrees() const
{
	return rotationRadians * RADIANS_TO_DEGREE;
}

void GameObject::setRotationRadians(const float angle)
{
	rotationRadians = angle;
}
void GameObject::rotateInRadians(const float angle)
{
	rotationRadians += angle;
}

const CollisionCircle& GameObject::getCollisionCircle() const
{
	return collisionCircle;
}

bool GameObject::isColliding(const GameObject& other) const
{
	return this->getCollisionCircle().checkCollision(other.getCollisionCircle());
}

float GameObject::getCollisionRadius() const
{
	return collisionCircle.getRadius();
}

void GameObject::setCollisionRadius(const float radius)
{
	collisionCircle.setRadius(radius);
}

void GameObject::setPosition(const float x, const float y)
{
	Sprite::setPosition(x, y);
	collisionCircle.setPosition(x, y);
}

void GameObject::setPosition(const Vector2f& position)
{
	Sprite::setPosition(position);
	collisionCircle.setPosition(position.x, position.y);
}

void GameObject::move(float offsetX, float offsetY)
{
	Sprite::move(offsetX, offsetY);
	collisionCircle.setPosition(getPosition().x, getPosition().y);
}

void GameObject::move(const Vector2f& offset)
{
	Sprite::move(offset);
	collisionCircle.setPosition(getPosition().x, getPosition().y);
}

void GameObject::draw(RenderWindow& renderWindow)
{
	if (active) renderWindow.draw(*this);
}
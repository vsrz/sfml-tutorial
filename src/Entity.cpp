#include "Entity.h"



void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;

}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}


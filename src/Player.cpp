#include "Player.h"
#include "Aircraft.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy) {}

	void operator() (SceneNode& node, sf::Time) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	
}
void Player::handleEvent(const sf::Event& event, CommandQueue& commands
{

}

void Player::handleRealtimeInput(CommandQueue& commands)
{

}




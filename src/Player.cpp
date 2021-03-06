#include "Player.h"
#include "Aircraft.h"
#include "Glob.h"

#include <iostream>

struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy) {}

	void operator() (Aircraft& aircraft, sf::Time) const
	{
		aircraft.accelerate(velocity);
	}


	sf::Vector2f velocity;
};

Player::Player() 
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	initializeActions();
	for (auto& pair : mActionBinding)
	{
		pair.second.category = Category::PlayerAircraft;
	}
}
void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
	}

	// LMB is pressed, set the destination coordinates
	/*
	else if (event.type == sf::Event::MouseButtonPressed &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mPlayerDestination.x = sf::Mouse::getPosition().x;
		mPlayerDestination.y = sf::Mouse::getPosition().y;

		std::cout 
			<< toString(mPlayerDestination.x) 
			<< ", " 
			<< toString(mPlayerDestination.y) 
			<< std::endl;

	}
	*/
}

void Player::initializeActions()
{
	const float playerSpeed = 250.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
	//mActionBinding[MoveToLocation].action = derivedAction<Aircraft>(
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) &&
			isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case Action::MoveDown:
	case Action::MoveUp:
	case Action::MoveLeft:
	case Action::MoveRight:
	case Action::MoveToLocation:
		return true;
	default:
		return false;

	}

}





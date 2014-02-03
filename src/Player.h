#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SFML/Window.hpp>
#include <map>
#include "CommandQueue.h"

class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		MoveToLocation,
		ActionCount,
	};

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	Player(sf::RenderWindow& window);
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

private:
	static bool isRealtimeAction(Action action);
	
	sf::RenderWindow& mWindow;
	sf::Vector2i mPlayerDestination;
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action,Command> mActionBinding;
	void initializeActions();
};

#endif

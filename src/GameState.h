#ifndef GAMESTATE_H
#define GAMESTATE_H

#pragma once

#include "State.h"
#include "World.h"

class GameState
	: public State
{
public:
	GameState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	World mWorld;
	Player& mPlayer;

	bool mDebugOverlay;

};

#endif

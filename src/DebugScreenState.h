#ifndef DEBUGSCREENSTATE_H
#define DEBUGSCREENSTATE_H

#pragma once

#include "State.h"
#include "StateStack.h"
#include <SFML/Graphics.hpp>

class DebugScreenState :
	public State
{
public:
	DebugScreenState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Time mDebugTime;
	std::size_t mDebugFps;
	sf::Text mFps;
	sf::Text mTps;

	void updateDebugText(sf::Time dt);
};

#endif
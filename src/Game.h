#ifndef GAME_H
#define GAME_H
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "World.h"
#include "Glob.h"

class Game
	: private sf::NonCopyable
{
public:
	Game(void);	
	~Game(void);

	void run();

private:
	void processEvents();
	void update(sf::Time);
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool);

private:
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;	
	World mWorld;

	sf::Text mDebugText;
	sf::Font mFont;
	sf::Time mDebugTime;
	std::size_t mDebugFps;

	void updateDebugText(sf::Time);

};

#endif

#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "World.h"
#include "Player.h"
#include "Glob.h"
#include "StateStack.h"

class Application
	: private sf::NonCopyable
{
public:
	Application(void);	
	~Application(void);

	void run();

private:
	void processEvents();
	void update(sf::Time);
	void render();
	void processInput();

	void registerStates();
	
	static const sf::Time TimePerFrame;

	sf::RenderWindow mWindow;	

	TextureHolder mTextures;
	FontHolder mFonts;
	Player mPlayer;
	StateStack mStateStack;

};

#endif

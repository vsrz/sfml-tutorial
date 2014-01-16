#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(void) 
	: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
	, mWorld(mWindow)
	, mFont()
	, mDebugText()
	, mDebugFps(0)
	, mDebugTime()
{
	mFont.loadFromFile("res/Sansation.ttf");
	mDebugText.setFont(mFont);
	mDebugText.setPosition(5.f, 5.f);
	mDebugText.setCharacterSize(12);
	mDebugText.setString("Frames / Second : 0 fps\nTime / Update : 0 us");

}


Game::~Game(void)
{

}

void Game::run(void)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{	
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		updateDebugText(elapsedTime);
		render();
	}
}

void Game::processEvents(void)
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
		}
		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
}

void Game::update(sf::Time elapsedTime)
{
	mWorld.update(elapsedTime);
}

void Game::render(void)
{
	mWindow.clear();
	mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mDebugText);
	mWindow.display();
}

void Game::updateDebugText(sf::Time dt)
{
	mDebugTime += dt;
	mDebugFps += 1;
	if (mDebugTime >= sf::seconds(1.0f))
	{
		mDebugText.setString(
				"Frames / Second : " + toString(mDebugFps) + " fps\n" +
				"Time / Update : " + toString(mDebugTime.asMicroseconds() / mDebugFps) + " us");
                                                         
		mDebugTime -= sf::seconds(1.0f);
		mDebugFps = 0;
	}
}
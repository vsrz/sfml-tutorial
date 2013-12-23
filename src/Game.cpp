#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(void) : 
	mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close),
	mPlayer(),
	mIsMovingUp(false),
	mIsMovingDown(false),
	mIsMovingLeft(false),
	mIsMovingRight(false)
{
	if (!mTexture.loadFromFile("res/Eagle.png"))
	{
		mPlayer.setTexture(mTexture);
		mPlayer.setPosition(100.f, 100.f);

	}

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
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
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
	if (key == sf::Keyboard::W)
	{
		mIsMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		mIsMovingLeft = isPressed;
	} 
	else if (key == sf::Keyboard::S)
	{
		mIsMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		mIsMovingRight = isPressed;
	}

}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if(mIsMovingUp)
	{
		movement.y -= 1.f;
	}
	if(mIsMovingLeft)
	{
		movement.x -= 1.f;
	}
	if(mIsMovingDown)
	{
		movement.y += 1.f;
	}
	if(mIsMovingRight)
	{
		movement.x += 1.f;
	}

	mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render(void)
{
	sf::Sprite sprite(mTexture);
	sprite.setPosition(mPlayer.getPosition());
	mWindow.clear();
	mWindow.draw(sprite);
	mWindow.display();
}

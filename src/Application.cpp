#include "Application.h"
#include "TitleState.h"
#include "MenuState.h"
#include "GameState.h"
#include "PauseState.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(void) 
	: mWindow(sf::VideoMode(640, 480), "SFML Tutorial", sf::Style::Close)
	, mFonts()
	, mPlayer()
	, mTextures()
	, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
	, mDebugText()
	, mDebugFps(0)
	, mDebugTime()
{
	mWindow.setKeyRepeatEnabled(false);
	mFonts.load(Fonts::Default, "res/Sansation.ttf");
	mTextures.load(Textures::TitleScreen, "res/TitleScreen.png");

	mDebugText.setFont(mFonts.get(Fonts::Default));
	mDebugText.setPosition(5.f, 5.f);
	mDebugText.setCharacterSize(10u);
	mDebugText.setString("0 fps\n0 tps");

	registerStates();
	mStateStack.pushState(States::Title);

}


Application::~Application(void)
{

}

void Application::run(void)
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
			processInput();
			update(TimePerFrame);

			if (mStateStack.isEmpty())
			{
				mWindow.close();
			}
		}
		updateDebugText(elapsedTime);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}	

void Application::update(sf::Time elapsedTime)
{
	mStateStack.update(elapsedTime);
}

void Application::render(void)
{
	mWindow.clear();
	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mDebugText);
	mWindow.display();
}

void Application::updateDebugText(sf::Time dt)
{
	mDebugTime += dt;
	mDebugFps += 1;
	if (mDebugTime >= sf::seconds(1.0f))
	{
		mDebugText.setString(
				toString(mDebugFps) + " fps\n" +
				toString(mDebugTime.asMicroseconds() / mDebugFps) + " tps");
                                                         
		mDebugTime -= sf::seconds(1.0f);
		mDebugFps = 0;
	}
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(States::Title);
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GameState>(States::Menu);
	mStateStack.registerState<PauseState>(States::Pause);
}


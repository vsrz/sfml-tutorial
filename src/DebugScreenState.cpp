
#include "DebugScreenState.h"
#include "ResourceHolder.h"
#include "Glob.h"

DebugScreenState::DebugScreenState(StateStack& stack, Context context)
	: State(stack, context)
	, mDebugFps(0)
	, mDebugTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Default);
	
	mFps.setFont(font);
	mFps.setCharacterSize(10);
	mFps.setColor(sf::Color::White);
	mFps.setPosition(5.f, 5.f);
	mFps.setString("0 fps");

	mTps.setFont(font);
	mTps.setCharacterSize(10);
	mTps.setPosition(5.f, 15.f);
	mTps.setColor(sf::Color::White);
	mTps.setString("0 tps");

}

void DebugScreenState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	window.draw(mFps);
	window.draw(mTps);
}

bool DebugScreenState::update(sf::Time dt)
{
	updateDebugText(dt);
	return true;

}

bool DebugScreenState::handleEvent(const sf::Event& event)
{
	return true;
}
void DebugScreenState::updateDebugText(sf::Time dt)
{
	mDebugTime += dt;
	mDebugFps += 1;
	if (mDebugTime >= sf::seconds(1.0f))
	{
		mFps.setString(toString(mDebugFps) + " fps");
		mTps.setString(toString(mDebugTime.asMicroseconds() / mDebugFps) + " tps");
		
		mDebugTime -= sf::seconds(1.0f);
		mDebugFps = 0;
	}
}



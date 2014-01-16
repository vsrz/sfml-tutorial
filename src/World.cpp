#include "World.h"
#include <iostream>

World::World(sf::RenderWindow& window)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 5000.f)
	, mSpawnPosition(
		mWorldView.getSize().x / 2.f, 
		mWorldBounds.height - mWorldView.getSize().y
		)
	, mScrollSpeed(-50.f)
	, mPlayerAircraft(nullptr)
	, mSceneLayers()
	, mSceneGraph()
	 	  
{
	loadTextures();
	buildScene();

	mWorldView.setCenter(mSpawnPosition);

}

void World::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}
void World::update(sf::Time dt)
{
	// Move the background texture
	mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());
	
	sf::Vector2f position = mPlayerAircraft->getPosition();
	sf::Vector2f velocity = mPlayerAircraft->getVelocity();

	// Bounce the planes in the other direction of they have reached the edge of the screen
	if(position.x <= mWorldBounds.left + 150 
		|| position.x >= mWorldBounds.left + mWorldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		mPlayerAircraft->setVelocity(velocity);
	}

	mSceneGraph.update(dt);
}

void World::loadTextures()
{
	mTextures.load(Textures::Eagle, "res/Eagle.png");
	mTextures.load(Textures::Raptor, "res/Raptor.png");
	mTextures.load(Textures::Desert, "res/Desert.png");

}

void World::buildScene()
{
	/**
	 * Initialize the scene layer by iterating through the
	 * layer nodes then attaching the new node to the scene graph
	 **/
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		
		// Return the raw pointer to this stored object
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));

	}

	// Configure the desert texture to repeat itself
	sf::Texture& texture = mTextures.get(Textures::Desert);
	sf::IntRect textureRect(mWorldBounds);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add the airplanes to the scene
	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
	mPlayerAircraft = leader.get();
	mPlayerAircraft->setPosition(mSpawnPosition);
	mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	// Give the leader two escorts
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
	leftEscort->setPosition(-80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
	rightEscort->setPosition(80.f, 50.f);
	mPlayerAircraft->attachChild(std::move(rightEscort));



}
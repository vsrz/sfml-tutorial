#ifndef SCENENODE_H
#define SCENENODE_H
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>

class SceneNode : 
	public sf::Transformable, 
	public sf::Drawable, 
	private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	
	SceneNode(void);
	
	void attachChild(Ptr child);
	Ptr detachChild(const SceneNode& node);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	std::vector<Ptr> mChildren;
	SceneNode*	mParent;
};

#endif


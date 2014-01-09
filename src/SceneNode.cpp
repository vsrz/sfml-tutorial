#include "SceneNode.h"

SceneNode::SceneNode(void)
{
	mParent = nullptr;
}

void SceneNode::attachChild(Ptr child)
{
	// attach this node to the current parent node
	child->mParent = this;

	// uses move to avoid the copy constructor?
	mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
	// Search for the specified node in the container
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&node] (Ptr& p) -> bool { return p.get() == &node; });
	assert(found != mChildren.end());

	/* move the found node out of the container into result */
	Ptr result = std::move(*found);
	
	// set the parent node to point to nullptr
	result->mParent = nullptr;

	// erase the empty element from the Children container
	mChildren.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// the absolute transform of the current node (where the scene node is placed)
	states.transform *= getTransform();

	// Draw the derived object
	drawCurrent(target, states);

	// Draw all the child nodes using range based for C++11 syntax
	for (const Ptr& child : mChildren)
	{
		// dereference the iterator and call draw on its object
		child->draw(target, states);
	}
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}




#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H
#pragma once

namespace sf
{
	class Texture;
}

namespace Textures
{
	enum ID
	{
		Eagle,
		Raptor,
		Desert,
	};

}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Font::ID> FontHolder;

#endif
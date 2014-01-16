
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tests.h"

int main()
{
    try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

    return 0;
}


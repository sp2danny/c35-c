
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define SFML_STATIC

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void Main([[maybe_unused]] const std::vector<std::string>& args)
{

	sf::RenderWindow window(sf::VideoMode(640, 480), "C35");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				/**/ if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear();
		window.display();
	}

	std::cout << "\ndone.\n";
}

std::vector<std::string> split(const std::string& s, char delim)
{
	std::vector<std::string> result;
	std::stringstream        ss{s};
	std::string              item;

	while (std::getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return result;
}

#ifndef CONSOLE
int __cdecl WinMain(void*, void*, char* cargs, int)
{
	Main(split(cargs, ' '));
	return 0;
}
#else
int main(int argc, char* argv[])
{
	std::vector<std::string> args;
	for (int i = 1; i < argc; ++i)
		args.push_back(argv[i]);
	Main(args);
}
#endif

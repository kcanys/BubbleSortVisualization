#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

class sort
{
private:
	//private variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Clock *clock;
	sf::Time elapsed;
	
	
	//Window background and text
	sf::Color *color;
	sf::Text* noO;
	sf::Font font;

	//variables for data
	int dataSize;
	int randomN = 0;
	int i, j, tempPos;
	bool sortLoop;
	int comparisons;
	int switches;
	int w, h;

	//sort objects
	std::vector<sf::RectangleShape> shapes;

	//private functions 
	void initVariables();
	void initWindow();
	void initData();

public:
	//Constructor | destructor
	sort();
	~sort();

	//Accessors
	const bool running() const;

	//public functions
	void pollEvents();
	void update();
	void render();
	void text(std::string t, int x, int y, int size);
	void timeHandling();
	void drawData();
	int randomNumberGenerator(int f, int c);
	void sortLogic();
	std::string timePassedText();
	std::string comparisonsText();
	std::string switchesText();
	std::string finalString();
	std::string closingTime();
	void quit();
};


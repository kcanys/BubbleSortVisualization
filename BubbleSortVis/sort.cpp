#include "sort.h"

//Constructor
sort::sort()
{
	this->initVariables();
	this->initWindow();
	this->dataSize = 200;
	this->initData();
	
}

//Destructor
sort::~sort()
{
	delete this->window;
}

//Returns true if window is still running
const bool sort::running() const
{
	return this->window->isOpen();
}

//Inits variables and window
void sort::initVariables()
{
	this->window = nullptr;
	this->color = new sf::Color(123, 123, 123, 255);
	if (!this->font.loadFromFile("BRLNSR.TTF"))
		printf("Error while loading font..");
	this->clock = new sf::Clock();
	this->i = 0;
	this->j = 0;
	this->sortLoop = true;
	this->switches = 0;
	this->comparisons = 0;
}

void sort::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1202;

	this->window = new sf::RenderWindow(this->videoMode, "Bubble Sort", sf::Style::Titlebar | sf::Style::Close);
}

void sort::initData()
{
	for (int i = 1; i <= this->dataSize; i++)
	{
		this->shapes.push_back(sf::RectangleShape(sf::Vector2f(5, randomNumberGenerator(1, 700))));
		this->shapes.back().setPosition(sf::Vector2f(1+i*6, 800));
		this->shapes.back().setFillColor(sf::Color(i%255, 0, i%255, 100));
		this->shapes.back().rotate(180);
	}
	printf("\nData initialized. Initialized rectangles: %d", dataSize);
}

//checking for events
void sort::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

//Window drawing and updating - put pollEvents in update to always check for events
void sort::update()
{
	this->pollEvents();
	this->timeHandling();
}

void sort::render()
{
	this->window->clear(*(this->color));
	this->text(this->timePassedText(), 0, 0, 25);
	this->text(this->comparisonsText(), 0, 30, 25);
	this->text(this->switchesText(), 0, 60, 25);
	this->text("O(N^2)", 0, 90, 25);
	this->drawData();
	this->text("Bubble Sort Visualization", 410, 0, 30);
	if (sortLoop)
		this->sortLogic();
	else
	{
		this->text(this->finalString(), 320, 350, 40);
		this->text(this->closingTime(), 450, 380, 40);
	}
	this->window->display();
}

void sort::text(std::string t, int x, int y, int size = 25)
{
	this->noO = new sf::Text(t, this->font, size);
	noO->setPosition(sf::Vector2f(x, y));
	this->window->draw(*noO);
}

void sort::timeHandling()
{
	if(this->sortLoop)
		this->elapsed = this->clock->getElapsedTime();
}

void sort::drawData()
{
	for (int i = 0; i < this->dataSize; i++)
	{
		this->window->draw(this->shapes[i]);
	}
	this->sortLogic();
}

int sort::randomNumberGenerator(int f, int c)
{
	this->randomN = rand() % (c + 1) + f;
	printf("Data: %d\n", randomN);
	return randomN;
}

void sort::sortLogic()
{
	if (this->i > this->dataSize)
		return;
	this->comparisons++;
	if (this->j >= this->dataSize - i - 1)
	{
		this->i++;

		if (i < this->dataSize)
			this->shapes[this->dataSize - i].setFillColor(sf::Color(this->shapes[this->dataSize - i].getFillColor().r, this->shapes[this->dataSize - i].getFillColor().g, this->shapes[this->dataSize - i].getFillColor().b, 255));

		this->j = 0;
	}

	if (this->shapes[this->j].getSize().y > this->shapes[this->j + 1].getSize().y)
	{
		tempPos = this->shapes[this->j].getSize().y;
		this->shapes[this->j].setSize(sf::Vector2f(this->shapes[this->j].getSize().x, this->shapes[this->j + 1].getSize().y));
		this->shapes[this->j + 1].setSize(sf::Vector2f(this->shapes[this->j + 1].getSize().x, tempPos));
		this->switches++;
	}
	//printf("i=%d j=%d\n", this->i, this->j);
	this->j++;

	if (this->i > this->dataSize)
	{
		this->clock->restart();
		this->sortLoop = false;
	}
}

std::string sort::timePassedText()
{
	std::string returnValue = "Time passed: " + std::to_string(this->elapsed.asSeconds());
	return returnValue;
}

std::string sort::comparisonsText()
{
	std::string returnValue = "Comparisons done: " + std::to_string(this->comparisons);
	return returnValue;
}

std::string sort::switchesText()
{
	std::string returnValue = "Switches done: " + std::to_string(this->switches);
	return returnValue;
}

std::string sort::finalString()
{
	std::string returnValue = std::to_string(this->dataSize) + " elements sorted in " + std::to_string(this->elapsed.asSeconds()) + " seconds";
	return returnValue;
}

std::string sort::closingTime()
{
	int val = 5 - (int)this->clock->getElapsedTime().asSeconds();
	if (val == -1)
		this->quit();
	std::string returnValue = "Closing in " + std::to_string(val) + " seconds...";
	
	return returnValue;
}

void sort::quit()
{
	this->window->close();
}


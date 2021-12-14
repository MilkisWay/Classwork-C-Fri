#pragma once //ifndefendif
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>//
#include <ctime>//Converts given time since epoch to a calendar local time and then to a textual representation,
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Class that acts as the game engine.All functions of the game here
class Game
{
private:
	//variables
	//Window
	sf::RenderWindow* window;//want to delete when want so dinamical access
	sf::VideoMode videoMode;
	sf::Event ev;//has default initialization

	//Mouse positions
	sf::Vector2i mousePosWindow;//integer
	sf::Vector2f mousePosView;//float

	//Texture
	sf::Font font;

	//Text
	sf::Text allText;

	//Game logic
	bool endGame;
	unsigned points;//need only positive values
	unsigned health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private Functions
	void initializeVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void spawnEnemy();
	void pollEvents();
	void updateMousePositions();
	void updateText();
	void updateEnemies();
	void update();
	void renderText(sf::RenderTarget& target);//dont always have to render to main window. Some things are gone render to the view
	void renderEnemies(sf::RenderTarget& target);
	void render();
};


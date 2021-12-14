#include "Game.h"

//Privatefunctions
void Game::initializeVariables()
{
	this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points=0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer=this->enemySpawnTimerMax;
    this->maxEnemies = 7;
    this->mouseHeld = false;
    this->health = 100;
}
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}
void Game::initFonts()
{
    if (this->font.loadFromFile("Pacifico.ttf"))
    {
        std::cout << "Faillllled to load font!" <<std::endl;
    }
}

void Game::initText()
{
    this->allText.setFont(this->font);
    this->allText.setCharacterSize(30);
    this->allText.setFillColor(sf::Color(100, 118, 135, 255));
    this->allText.setString("MILANA");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f,10.f);//position in the world
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));//float vector is parm
    this->enemy.setFillColor(sf::Color(255, 102, 0, 255));

}
//Constructors
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
	delete this-> window;//memory
}
//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

//Functions

void Game::spawnEnemy()
/*spawns enemiesand control their color and positions
position is random 
Enemies are added to the vector
*/
{
    this->enemy.setPosition(
        static_cast<float>(rand()%static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),//first convert into integer than random and then covert into float
        0.f);
    //Random enemy type
    int type = rand() % 5;//for 0 to 4
    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color(164, 196, 0, 255));
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(20.f, 20.f));
        this->enemy.setFillColor(sf::Color(240, 163, 10, 255));
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color(129, 110, 191, 255));
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(40.f, 40.f));
        this->enemy.setFillColor(sf::Color(28, 95, 68, 255));
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color(255, 102, 0, 255));
        break;
    default:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color(255, 255, 255, 255));
        break;
    }

    //Spawn an enemy
    this->enemies.push_back(this->enemy);
    //Remove enemies at the end of screen
}

void Game::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->ev)) //while getting events from the window
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

void Game::updateMousePositions()
//updates timer and spawn enemies, when total amount is less than max
{
    //updates the mouse posiont relative to window with vector of two integer
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss; //creates a string with mixed types
    ss << "Points: " << this->points << std::endl
        << "Health: " << this->health << std::endl;
    this->allText.setString(ss.str());
}

void Game::updateEnemies()
{
    //updating timer for enemy spawning; moves the enemies downwards and removes from the edge of the screen
    if (this->enemies.size() < this->maxEnemies) //while we have less enemies 
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //spawn enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }
    //Move the enemies referance e &e and updating checking if enemy below the screen and delete this enemy
    for (int i=0;i<this->enemies.size();i++)
    {
        bool deleted = false;
        this->enemies[i].move(0.f,3.f);
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
            std::cout << "Health:" << this->health << std::endl;
        }
       
    }
    //Check if cliked on enemies. If check delete and add points
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true; //will check what enemy I cliked on
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))//it takes floar so that is the reason why needed mousePos to be float
                {
                    //Gain points
                    if (this->enemies[i].getFillColor() == sf::Color(164, 196, 0, 255))
                        this->points += 200;
                    else if (this->enemies[i].getFillColor() == sf::Color(240, 163, 10, 255))
                        this->points += 50;
                    else if (this->enemies[i].getFillColor() == sf::Color(129, 110, 191, 255))
                        this->points += 30;
                    else if (this->enemies[i].getFillColor() == sf::Color(28, 95, 68, 255))
                        this->points += 20;
                    else if (this->enemies[i].getFillColor() == sf::Color(255, 102, 0, 255))
                        this->points += 10;
                    std::cout << "Points:" <<this->points << std::endl;

                    //Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }

            }
        }
    }
    else
    {
        this->mouseHeld = false;
        //If not holding a mouse will set false, so we can start the loop from the begining
    }  
}

void Game::update()
{
    this->pollEvents();//calling it
    if (!this->endGame)
    {
        this->updateMousePositions();
        //Update mouse position
        // reference to window *this->window
        //std::cout << "Mouse pos:" << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
        this->updateText();
        this->updateEnemies();
    }
    //Condition to end the game
    if (this->health <= 0)
        this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->allText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all the enemies
    for (auto& e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::render()
{
    /*Renders the game objects
    clear old frame
    render objects
    display frame in window*/
    this->window->clear(sf::Color(204, 255, 204, 240));

    //Draw game objects
    this->renderEnemies(*this->window);//reference
    this->renderText(*this->window);
    this->window->display();

}

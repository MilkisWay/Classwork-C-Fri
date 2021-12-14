#include <iostream>
#include "Game.h"

int main()
{
    //Init srand
    /*Converts between types using a combination of implicitand user - defined conversions.
    Syntax : static_cast <new_type> (expression)*/

    std::srand(static_cast<unsigned>(time(NULL)));//srand(time(NULL)) is to set current time, but it is used to generate random numbers

    //Init Class game object as Game engine
     Game game;

    //Game loop
    while (game.running()&& !game.getEndGame())
    {   
        //Update
        game.update();
        //Render
        game.render();

    }
    //End of application
    //print end of the game and score
    return 0;
}

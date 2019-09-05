#include <iostream>
#include <curses.h>
#include <signal.h>
#include "GameWindow.h"
#include "Border.h"
#include "Game.h"
int main() {

    Game game;
    game.menuHandler();
    game.createObjects();
    game.gameLoop();
    game.closeGame();
    return 0;
}

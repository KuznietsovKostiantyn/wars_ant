//
// Created by Kostiantyn on 08.05.2019.
//

#ifndef SEMESTRALWORK_GAME_H
#define SEMESTRALWORK_GAME_H

#include <list>
#include <map>
#include <set>
#include "GameWindow.h"
#include "Attack.h"
#include "Menu.h"

enum TURN {START, WAIT_CLICK, MOUSE1, COUNT, MOUSE2, WIN, AUTO_TURN};

class Game
{

    Menu m_menu;
    GameWindow m_window;
    vector<AntClan*> m_clans;
    TURN m_turn;
    map<string, Attack> m_attack;
    vector<Barier> m_bariers;

public:
    void menuHandler();
    void createObjects();
    void gameLoop();
    void closeGame();
    void createAntClans();
    int readAntsCount();
    void update();
    void gameStage();
    void attackResult(Attack &attack);
    void checkCollision ();
    void loadMap(std::string map_name);
    void checkErr(ifstream & file);
    void saveGame();
    void loadGame();
    void gameLoopAI();
    void attackHandler();
    AntClan* getClanWhichCouldBeAttacked( AntClan *& me);
    ~Game();
};
#endif //SEMESTRALWORK_GAME_H

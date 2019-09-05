//
// Created by Kostiantyn on 07.05.2019.
//
#ifndef SEMESTRALWORK_GAMEWINDOW_H
#define SEMESTRALWORK_GAMEWINDOW_H
#include <iostream>
#include <vector>
#include <signal.h>
#include "Border.h"
#include "AntClan.h"

using namespace std;

class GameWindow{


    int m_width;
    int m_height;
    Border m_borders;
    WINDOW * new_window;
    MEVENT event;

public:
    void createWindow();
    void deleteWindow();
    void createBorders();
    static void resizeHandler(int sig);
    WINDOW *& getWindow ();
    MEVENT & getEvent ();
    AntClan * mouseClickHandler(vector<AntClan*> &  m_clans);
    bool collision(vector<Coord> & home);
    void drawBariers(vector<Barier> & bariers);
};
#endif //SEMESTRALWORK_GAMEWINDOW_H

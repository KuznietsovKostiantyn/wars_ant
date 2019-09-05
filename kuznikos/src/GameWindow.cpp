//
// Created by Kostiantyn on 07.05.2019.
//
#include "GameWindow.h"
#include "AntHome.h"
#include "AntClan.h"
#include <curses.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <math.h>
#include <stack>
#include <set>
#include <map>
#include <list>

void GameWindow::createWindow(){
    initscr();
    ///set game field size.
    m_height = 25;
    m_width = 100;
    ///set window size.
    new_window = newwin(27,100,0,0);
    start_color();
    keypad(new_window, TRUE);
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_CYAN);
    init_pair(5, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(6, COLOR_WHITE, COLOR_YELLOW);
    noecho();
    curs_set(0);
    raw(); //mouse
    refresh();
}
void GameWindow::deleteWindow() {
    endwin();
}
void GameWindow::resizeHandler(int sig){
    if(sig)
        resize_term(25,100);
    resize_term(25,100);
}
void GameWindow::createBorders() {
    m_borders.Draw(m_height, m_width, new_window);
}
WINDOW *& GameWindow::getWindow() {
    return new_window;
}

MEVENT &GameWindow::getEvent() {
    return event;
}

AntClan * GameWindow::mouseClickHandler(vector<AntClan*> & m_clans) {
    for (auto x: m_clans){
        if (collision(x->getHome()->getHomeBorders()))
            return x;
    }
    return nullptr;
}

bool GameWindow::collision(vector<Coord> & home) {

    return event.x > home.at(0).m_x && event.x < home.at(3).m_x &&
        event.y > home.at(0).m_y && event.y < home.at(3).m_y;

}
void GameWindow::drawBariers(vector<Barier> & bariers){

    for ( auto & x: bariers){
        x.DrawBarier(new_window);
    }
}


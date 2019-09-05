//
// Created by kuznikos on 5/7/19.
//

#include "Coord.h"
#include <iostream>
#include "AntHome.h"
#include "Ant.h"

AntHome::AntHome (const Coord & coord, const int & hp){

    m_hp = hp;
    m_home_center = Coord((coord.m_x+coord.m_x+7)/2, (coord.m_y+coord.m_y+5)/2);
    m_home_borders.push_back(coord);
    m_home_borders.emplace_back(Coord(coord.m_x,coord.m_y+5));
    m_home_borders.emplace_back(Coord(coord.m_x+7,coord.m_y));
    m_home_borders.emplace_back(Coord(coord.m_x+7,coord.m_y+5));
}
void FirstTypeHome::Draw(WINDOW *& window){
    wattron(window,COLOR_PAIR(1));
    for (int i = 0; i < (m_home_borders.at(2).m_x-m_home_borders.at(0).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(0).m_y, m_home_borders.at(0).m_x+i);
        wprintw(window,"+");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(1).m_y-m_home_borders.at(0).m_y); i++ ){
        wmove(window, m_home_borders.at(0).m_y+i+1, m_home_borders.at(0).m_x);
        wprintw(window,"|");
        wrefresh(window);
    }
    for (int i = 0; i < m_home_borders.at(3).m_y-m_home_borders.at(2).m_y; i++ ){
        wmove(window, m_home_borders.at(2).m_y+i+1, m_home_borders.at(3).m_x);
        wprintw(window, "|");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(3).m_x-m_home_borders.at(1).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(3).m_y, m_home_borders.at(1).m_x+i);
        wprintw(window, "+");
        wrefresh(window);
    }
    wattroff(window,COLOR_PAIR(1));
    wrefresh(window);
}
/**
 * Create ant: default or boss for this house
 **/
Ant * FirstTypeHome::createAnt(std::string &attacker_name) {

    int roll = rand() % 20;
    if (roll < 10)
        return new BossAnt1(m_home_center, 30, 30, attacker_name);
    else
        return new StandardAnt(m_home_center, 20, 20, attacker_name);
}

int FirstTypeHome::getHouseType() {
    return 1;
}

std::vector<Coord> &AntHome::getHomeBorders() {
    return m_home_borders;
}

Coord &AntHome::getHomeCenter() {
    return m_home_center;
}

int & AntHome::getHp() {
    return m_hp;
}

void SecondTypeHome::Draw(WINDOW *& window){

    wattron(window,COLOR_PAIR(2));
    for (int i = 0; i < (m_home_borders.at(2).m_x-m_home_borders.at(0).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(0).m_y, m_home_borders.at(0).m_x+i);
        wprintw(window,"+");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(1).m_y-m_home_borders.at(0).m_y); i++ ){
        wmove(window, m_home_borders.at(0).m_y+i+1, m_home_borders.at(0).m_x);
        wprintw(window,"|");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(3).m_y-m_home_borders.at(2).m_y); i++ ){
        wmove(window, m_home_borders.at(2).m_y+i+1, m_home_borders.at(3).m_x);
        wprintw(window, "|");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(3).m_x-m_home_borders.at(1).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(3).m_y, m_home_borders.at(1).m_x+i);
        wprintw(window, "+");
        wrefresh(window);
    }
    wattroff(window, COLOR_PAIR(2));
}

Ant *SecondTypeHome::createAnt(std::string &attacker_name) {
    int roll = rand() % 20;
    if (roll < 10)
        return new BossAnt2(m_home_center, 25, 25, attacker_name);
    else
        return new StandardAnt(m_home_center, 20, 20, attacker_name);
}

int SecondTypeHome::getHouseType() {
    return 2;
}

void ThirdTypeHome::Draw(WINDOW *&window) {

    wattron(window,COLOR_PAIR(3));
    for (int i = 0; i < (m_home_borders.at(2).m_x-m_home_borders.at(0).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(0).m_y, m_home_borders.at(0).m_x+i);
        wprintw(window,"+");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(1).m_y-m_home_borders.at(0).m_y); i++ ){
        wmove(window, m_home_borders.at(0).m_y+i+1, m_home_borders.at(0).m_x);
        wprintw(window,"|");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(3).m_y-m_home_borders.at(2).m_y); i++ ){
        wmove(window, m_home_borders.at(2).m_y+i+1, m_home_borders.at(3).m_x);
        wprintw(window, "|");
        wrefresh(window);
    }
    for (int i = 0; i < (m_home_borders.at(3).m_x-m_home_borders.at(1).m_x)+1; i++ ){
        wmove(window, m_home_borders.at(3).m_y, m_home_borders.at(1).m_x+i);
        wprintw(window, "+");
        wrefresh(window);
    }
    wattroff(window, COLOR_PAIR(3));
}

Ant *ThirdTypeHome::createAnt(std::string &attacker_name) {

    int roll = rand() % 20;
    if (roll < 10)
        return new BossAnt3(m_home_center, 25, 25, attacker_name);
    else
        return new StandardAnt(m_home_center, 20, 20, attacker_name);

}

int ThirdTypeHome::getHouseType() {
    return 3;
}


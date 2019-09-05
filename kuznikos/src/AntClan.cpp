//
// Created by kuznikos on 5/12/19.
//
#include "AntHome.h"
#include "Ant.h"
#include "AntClan.h"
#include <unistd.h>
#include <iostream>

AntClan::AntClan(){}

AntClan::AntClan (const int & type, const Coord & coord, const unsigned & ants_count, const std::string & name, const int & color) {

    m_ants_count = ants_count;
    m_name = name;
    m_color = color;
    switch(type){
        case 1:
            m_ant_home = new FirstTypeHome(coord);
            break;
        case 2:
            m_ant_home = new SecondTypeHome(coord);
            break;
        case 3:
            m_ant_home = new ThirdTypeHome(coord);
            break;
    }
}
AntHome *& AntClan::getHome() {
    return m_ant_home;
}

std::map<Coord, SearchRoute> & AntClan::getSearchRoute() {
    return m_route_to_enemies;
}

unsigned int &AntClan::getAntsCount() {
    return m_ants_count;
}

void AntClan::Draw(WINDOW *&window) {
    m_ant_home->Draw(window);
    mvwprintw(window, m_ant_home->getHomeCenter().m_y, m_ant_home->getHomeCenter().m_x, "   ");
    mvwprintw(window, m_ant_home->getHomeCenter().m_y, m_ant_home->getHomeCenter().m_x-1, "%c", m_name[0]);
    mvwprintw(window, m_ant_home->getHomeCenter().m_y, m_ant_home->getHomeCenter().m_x, ":%d", m_ants_count);
    mvwprintw(window, (m_ant_home->getHomeCenter().m_y+1), m_ant_home->getHomeCenter().m_x-2, "      ");
    mvwprintw(window, (m_ant_home->getHomeCenter().m_y+1), m_ant_home->getHomeCenter().m_x-2, "HP:%d",  m_ant_home->getHp());
    wrefresh(window);
}

std::string &AntClan::getName() {
    return m_name;
}

int &AntClan::getColor() {
    return m_color;
}

bool AntClan::operator==(const AntClan &rhs) const {
    return m_name == rhs.m_name;
}

bool AntClan::operator!=(const AntClan &rhs) const {
    return !(rhs == *this);
}

AntClan::~AntClan() {
    delete m_ant_home;
}

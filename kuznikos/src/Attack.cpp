//
// Created by kuznikos on 5/10/19.
//
#include "Attack.h"
#include "Ant.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>

Attack::Attack ():is_attacker(false), is_defender(false), is_count(false){}
Attack::~Attack() {
    is_count = false;
    is_attacker = false;
    is_defender = false;
    for (auto x: army){
        delete x;
    }
}
AntClan *& Attack::getAttacker(){ return  m_attacker;}
AntClan *& Attack::getDefender(){ return  m_defender;}
void Attack::setAttacker(AntClan *a){

    m_attacker = a;
    is_attacker = true;
}
void Attack::setDefender(AntClan * a){

    m_defender = a;
    is_defender = true;
}
void Attack::setCount(int c){

    m_count = c;
    is_count = true;
}
bool Attack::canAttack (){
    if (!(is_attacker && is_defender && is_count))
        return false;
    return !(m_attacker == m_defender || m_attacker->getAntsCount() < m_count);
}
/**
 * Change ant coordninate to the next on the way
 * */
void Attack::moveToDestination(std::list<Coord> & route) {

    auto x = army.begin();
    while (x != army.end() && !army.empty()) {
        auto it = find(route.begin(), route.end(), (*x)->getCoord());
        if (next(it, 1) != route.end()) {
            (*x)->Move(*next(it, 1));
        }
        x++;
    }
}
/**
 * Remove ants from the window
 * */
void Attack::clearAnts(WINDOW *&window, std::vector<Ant *> &ants) {
    for (Ant* & x: ants ) {
        if (checkDraw(*x))
            mvwprintw(window, x->getCoord().m_y, x->getCoord().m_x, " ");
    }
    wrefresh(window);
}
/**
 * Check if ant is in the home
 * */
bool Attack::checkDraw(Ant &ant) {
    return !(IsInHome(ant.getCoord(), m_attacker->getHome()->getHomeBorders()) || IsInHome(ant.getCoord(), m_defender->getHome()->getHomeBorders()));
}

bool Attack::IsInHome(Coord &coord, std::vector<Coord> &pHome) {
    return coord.m_x >= pHome.at(0).m_x && coord.m_x <= pHome.at(3).m_x &&
    coord.m_y >= pHome.at(0).m_y && coord.m_y <= pHome.at(3).m_y;

}
bool Attack::isDead (Ant * ant) {
    return ant->getHp() <= 0;
}
/**
 * Search the way to the defender and move to him
 * */
bool Attack::attackEnemy(WINDOW *&window, int count) {
    std::list<Coord> way = (*m_attacker->getSearchRoute().find(m_defender->getHome()->getHomeCenter())).second.getList();
    if(count <= m_count) addAnt();

    attackClear(window);
    moveToDestination(way);
    for (Ant* & x: army ) {
        if (checkDraw(*x))
            x->Draw(window);
    }
    wrefresh(window);
    return army.size() == (unsigned)count_if(army.begin(), army.end(), [&](Ant * ant ){ return ant->getCoord() == *(--way.end());});
}



void Attack::attackClear(WINDOW *&window) {
    clearAnts(window, army);
}
long & Attack::getAntsCount() {
    return m_count;
}

std::vector<Ant *> & Attack::getArmy() {
    return army;
}
/**
 * Check if ants are in the same coordinate.
 * If they are, they take damage to each other and if someone die - remove from vector of ants.
 * */
void Attack::checkCollision(Attack &attack) {

    auto x = army.begin();
    while ( x != army.end()) {
        int dead = 0;
        auto it1 = find_if(attack.getArmy().begin(), attack.getArmy().end(), [&](Ant *ant) -> bool {
            return (*x)->getCoord() == ant->getCoord() && (*x)->getClanName() != ant->getClanName();
        });
        if (it1 != attack.getArmy().end()) {
            (*x)->getHp() -= (*it1)->getDamage();
            (*it1)->getHp()-= (*x)->getDamage();
            if (isDead(*x)) {
                Ant * toDel = *x;
                x = army.erase(x);
                delete toDel;
                dead = 1;
                m_count--;
                usleep(200000);
            }
            if (isDead(*it1)){
                Ant * toDel = *it1;

               attack.getArmy().erase(it1);
               delete toDel;
               attack.m_count--;
            }
        }
       if (!dead){
            if (x != army.end())
                x++;
        }
    }
}
void Attack::addAnt(){

    std::string name = m_attacker->getName();
    army.push_back(m_attacker->getHome()->createAnt(name));
}

void Attack::clearAnts(WINDOW *&window) {
    for(auto x : army){
        if (checkDraw(*x))
            mvwprintw(window, x->getCoord().m_y, x->getCoord().m_x, " ");
        delete x;
    }
    army.clear();

}


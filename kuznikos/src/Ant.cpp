//
// Created by kuznikos on 5/12/19.
//

#include "Ant.h"

void StandardAnt::Draw(WINDOW *&window) {
    mvwprintw(window, m_coord.m_y, m_coord.m_x, "%c", tolower(m_clan_name[0]));
    wrefresh(window);
}

Ant::Ant (const Coord & c, const int & hp, const unsigned & damage, const std::string & name){
    m_coord.m_x = c.m_x;
    m_coord.m_y = c.m_y;
    m_hp = hp;
    m_damage = damage;
    m_clan_name = name;
}
void Ant::Move( Coord & dest) {
    m_coord = dest;
}

Coord &Ant::getCoord() {
    return m_coord;
}

unsigned &StandardAnt::getDamage() {
    return m_damage;
}

std::string &Ant::getClanName() {
    return m_clan_name;
}

int &StandardAnt::getHp() {
    return m_hp;
}

StandardAnt::~StandardAnt() {}

void BossAnt1::Draw(WINDOW *&window) {
    wattron(window, COLOR_PAIR(4));
    mvwprintw(window, m_coord.m_y, m_coord.m_x, "%c", tolower(m_clan_name[0]));
    wrefresh(window);
    wattroff(window, COLOR_PAIR(4));
}
unsigned & BossAnt1::getDamage() {
    return m_damage;
}

int &BossAnt1::getHp() {
    return m_hp;
}

void BossAnt2::Draw(WINDOW *&window) {
    wattron(window, COLOR_PAIR(5));
    mvwprintw(window, m_coord.m_y, m_coord.m_x, "%c", tolower(m_clan_name[0]));
    wrefresh(window);
    wattroff(window, COLOR_PAIR(5));
}
unsigned & BossAnt2::getDamage() {
    return m_damage;
}

int &BossAnt2::getHp() {
    return m_hp;
}

void BossAnt3::Draw(WINDOW *&window) {
    wattron(window, COLOR_PAIR(6));
    mvwprintw(window, m_coord.m_y, m_coord.m_x, "%c", tolower(m_clan_name[0]));
    wrefresh(window);
    wattroff(window, COLOR_PAIR(6));

}
unsigned & BossAnt3::getDamage() {
    return m_damage;
}

int &BossAnt3::getHp() {
    return m_hp;
}

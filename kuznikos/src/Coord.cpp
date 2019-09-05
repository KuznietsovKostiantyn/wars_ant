//
// Created by kuznikos on 6/5/19.
//
#include "Coord.h"

Coord::Coord(){m_x = -1; m_y = -1;}
Coord::Coord(const int & x, const int & y):m_x(x), m_y(y){}
Coord::Coord(const Coord & src){
    m_x = src.m_x;
    m_y = src.m_y;
}
bool Coord::operator ==(const Coord &a) {
    return a.m_x == this->m_x && a.m_y == this->m_y;
}
bool Coord::operator <(const Coord &a) {
    return a.m_x < this->m_x || (a.m_x == this->m_x && a.m_y < this->m_y);
}
bool Coord::operator !=(const Coord &a) {
    return a.m_x != this->m_x || a.m_y != this->m_y;
}
bool operator<(const Coord &a, const Coord &b) {
    return a.m_x < b.m_x || (a.m_x == b.m_x && a.m_y < b.m_y);
}

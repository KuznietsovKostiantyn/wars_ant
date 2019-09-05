//
// Created by Kostiantyn on 07.05.2019.
//

#include <curses.h>
#include <iostream>
#include "Border.h"

void Border::Draw(const int & height, const int & width, WINDOW *& window) {

    for (int i = 1; i < width; i++ ){
        wmove(window, 0, i);
        wprintw(window, "#");
        wrefresh(window);
    }
    for (int i = 0; i < height; i++ ){
        wmove(window, i, 0);
        wprintw(window, "#");
        wrefresh(window);
    }

    for (int i = 0; i < width; i++ ){
        wmove(window, height-1, i);
        wprintw(window, "#");
        wrefresh(window);
    }
    for (int i = 0; i < height; i++ ){
        wmove(window, i, width-1);
        wprintw(window, "#");
        wrefresh(window);
    }
}

void Barier::DrawBarier(WINDOW *&window) {

    if (m_start_point.m_x == m_end_point.m_x){
        for (int i = m_start_point.m_y; i < m_end_point.m_y; i++ )
            mvwprintw(window, i, m_start_point.m_x, "#");
    }
    else {
        for (int i = m_start_point.m_x; i < m_end_point.m_x; i++)
            mvwprintw(window, i, m_start_point.m_y, "#");
    }
    wrefresh(window);
}

Barier::Barier(const Coord &start, const Coord &end) {

    m_start_point = start;
    m_end_point = end;
}

Coord &Barier::getStartPoint() {
    return m_start_point;
}
Coord &Barier::getEndPoint() {
    return m_end_point;
}
bool Barier::detectIntersect(Coord &start, Coord &end) {
    int ax = m_end_point.m_x - m_start_point.m_x;
    int ay = m_end_point.m_y - m_start_point.m_y;

    int bx = end.m_x - start.m_x;
    int by = end.m_y - start.m_y;

    int dx = end.m_x - m_start_point.m_x;
    int dy = end.m_y - m_start_point.m_y;

    int det = ax * by - ay * bx;

    if (det == 0) return false;

    int r = (dx * by - dy * bx) / det;
    int s = (ax * dy - ay * dx) / det;

    return !(r < 0 || r > 1 || s < 0 || s > 1);
}
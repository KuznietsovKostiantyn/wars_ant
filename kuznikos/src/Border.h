//
// Created by Kostiantyn on 07.05.2019.
//

#ifndef SEMESTRALWORK_BORDER_H
#define SEMESTRALWORK_BORDER_H

#include "curses.h"
#include "Coord.h"

class Border{
public:
    void Draw(const int & height, const int & width, WINDOW *& window );
};
class Barier : public Border{

    Coord m_start_point;
    Coord m_end_point;

public:
    Barier(const Coord & start, const Coord & end );
    void DrawBarier(WINDOW *& window);
    Coord & getStartPoint();
    Coord & getEndPoint();
    bool detectIntersect( Coord & start, Coord & end );
};
#endif //SEMESTRALWORK_BORDER_H

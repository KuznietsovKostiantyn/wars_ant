//
// Created by kuznikos on 5/7/19.
//

#ifndef SEMESTRALWORK_COORD_H
#define SEMESTRALWORK_COORD_H
class Coord{

public:

    int m_x;
    int m_y;

    Coord();
    Coord(const int & x, const int & y);
    Coord(const Coord & src);
    ~Coord() = default;
    bool operator ==(const Coord &a);
    bool operator <(const Coord &a);
    friend bool operator <(const Coord &a, const Coord & b);
    bool operator !=(const Coord &a);

};
#endif //SEMESTRALWORK_COORD_H

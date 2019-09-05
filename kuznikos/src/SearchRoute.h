//
// Created by kuznikos on 5/12/19.
//

#ifndef SEMESTRALWORK_SEARCHROUTE_H
#define SEMESTRALWORK_SEARCHROUTE_H

#include <list>
#include "Coord.h"
#include "Border.h"
#include <map>
#include <vector>

class SearchRoute{

    std::list <Coord> m_route;
    Coord m_start_point;
    Coord m_dest_point;
    std::vector<std::vector<Coord>> m_house_borders;
public:
    SearchRoute(const Coord & start, const Coord & dest, std::vector<std::vector<Coord>> & borders);
    bool checkCollision(int & new_x, int & new_y, std::vector<Barier> & bariers);
    void FindShortRoute(std::vector<Barier> & bariers);
    bool liesOnLine(Coord & tmp, Barier & b);
    std::list<Coord> & getList();
    void AddToList(std::map<Coord,Coord> &road_map);
    static bool compare(const Coord & a, const Coord &b);
    friend bool operator < (const Coord & a, const Coord & b);
};
#endif //SEMESTRALWORK_SEARCHROUTE_H

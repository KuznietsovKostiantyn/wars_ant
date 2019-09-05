//
// Created by kuznikos on 5/12/19.
//

#include "SearchRoute.h"
#include "Attack.h"
#include "Border.h"
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iostream>

bool SearchRoute::compare(const Coord &a, const Coord &b) {
    return a.m_x == b.m_x && a.m_y == b.m_y;
}
SearchRoute::SearchRoute(const Coord &start, const Coord & dest, std::vector<std::vector<Coord>> & borders) {

    m_start_point = start;
    m_dest_point = dest;
    for(auto &x: borders)
        m_house_borders.push_back(x);

}
/**
 * BFS searching algorithm.
 */
void SearchRoute::FindShortRoute(std::vector<Barier> & bariers) {
    std::set<Coord> visited;
    std::queue<Coord> queue;
    queue.push(m_start_point);
    std::map<Coord,Coord> road_map;
    std::vector<int> coordX{0, 1, -1, 0};
    std::vector<int> coordY{-1, 0, 0, 1};
    while (!queue.empty()){
        Coord tmp = queue.front();
        queue.pop();
        if (visited.find(tmp) != visited.end())
            continue;
        visited.insert(tmp);
        for (unsigned i = 0; i < 4; i++){
            int new_x = tmp.m_x+coordX.at(i);
            int new_y = tmp.m_y+coordY.at(i);
            if (new_x < 0 || new_y  < 0 || new_x > 100 || new_y  > 25) {
                continue;
            }
            Coord new_coord = Coord(new_x, new_y);
            auto it1 = visited.find(new_coord);
            if (it1 == visited.end()){
                if (new_x > 0 && new_y > 0 && !checkCollision(new_x, new_y, bariers) ){
                    road_map.insert(std::make_pair(new_coord, tmp));
                    queue.push(new_coord);
                    if (compare(new_coord,m_dest_point)) {
                        AddToList(road_map);
                        return;
                    }
                }
            }
        }
    }
    return;

}
void SearchRoute::AddToList(std::map<Coord, Coord> &road_map) {

    m_route.insert(m_route.begin(), m_dest_point);
    Coord tmp;
    auto it = road_map.find(m_dest_point);
    while(it->second != m_start_point){
        tmp = it->second;
        m_route.insert(m_route.begin(),it->second);
        it = road_map.find(tmp);
    }
    m_route.insert(m_route.begin(),m_start_point);
}

std::list<Coord> &SearchRoute::getList() {
    return m_route;
}
/**
 * Check if searching point isn't in home, or isn't on border.
 * */
bool SearchRoute::checkCollision(int & new_x, int & new_y, std::vector<Barier> & bariers) {

    Coord tmp(new_x, new_y);
    Coord center;
    for (auto &x: bariers){
        if (liesOnLine(tmp, x)){
            return true;
        }
    }
    for (unsigned i = 0; i < m_house_borders.size(); i++){
        center = Coord((m_house_borders[i].at(0).m_x+m_house_borders[i].at(0).m_x+7)/2, (m_house_borders[i].at(0).m_y+m_house_borders[i].at(0).m_y+5)/2);
        if (center == m_start_point || center == m_dest_point )
            continue;
        if (Attack::IsInHome(tmp, m_house_borders[i])){
            return true;
        }
    }
    return false;
}
/**
 * Check if point is on barier.
 * */
bool SearchRoute::liesOnLine(Coord & tmp, Barier & b){

    int dxc = tmp.m_x - b.getStartPoint().m_x;
    int dyc = tmp.m_y - b.getStartPoint().m_y;

    int dxl = b.getEndPoint().m_x - b.getStartPoint().m_x;
    int dyl = b.getEndPoint().m_y - b.getStartPoint().m_y;

    int cross = dxc * dyl - dyc * dxl;

        if (cross != 0 )
        return false;
    if (abs(dxl) >= abs(dyl))
        return dxl > 0 ?
               b.getStartPoint().m_x <= tmp.m_x && tmp.m_x <= b.getEndPoint().m_x :
               b.getEndPoint().m_x <= tmp.m_x && tmp.m_x <= b.getStartPoint().m_x;
    else
        return dyl > 0 ?
               b.getStartPoint().m_y <= tmp.m_y && tmp.m_y <= b.getEndPoint().m_y :
               b.getEndPoint().m_y <= tmp.m_y && tmp.m_y <= b.getStartPoint().m_y;
}

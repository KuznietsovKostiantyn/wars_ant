//
// Created by kuznikos on 5/7/19.
//

#ifndef SEMESTRALWORK_ANTCLAN_H
#define SEMESTRALWORK_ANTCLAN_H

#include "AntHome.h"
#include "Ant.h"
#include <memory>

class AntClan{

    unsigned int m_ants_count;
    AntHome * m_ant_home;
    std::string m_name;
    std::map<Coord,SearchRoute> m_route_to_enemies;
    int m_color;

public:
    AntClan();
    ~AntClan();
    AntClan (const int & type, const Coord & coord, const unsigned int & ants_count, const std::string & name, const int & color);
    AntHome *& getHome();
    std::map<Coord, SearchRoute> & getSearchRoute();
    unsigned int & getAntsCount();
    std::string & getName();
    int & getColor();
    void Draw(WINDOW *& window);
    bool operator==(const AntClan &rhs) const;
    bool operator!=(const AntClan &rhs) const;

};
#endif //SEMESTRALWORK_ANTCLAN_H

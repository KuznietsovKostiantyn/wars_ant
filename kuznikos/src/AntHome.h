//
// Created by kuznikos on 5/7/19.
//

#ifndef SEMESTRALWORK_ANTHOME_H
#define SEMESTRALWORK_ANTHOME_H

#include "Coord.h"
#include "SearchRoute.h"
#include <curses.h>
#include <string>
#include <vector>

class Ant;

class AntHome{

protected:
    Coord m_home_center;
    int m_hp;
    std::vector<Coord> m_home_borders;

public:
    virtual void Draw(WINDOW *& window) = 0;
    virtual ~AntHome() = default;
    virtual Ant * createAnt(std::string & attacker_name) = 0;
    virtual int getHouseType () = 0;
    AntHome (const Coord & coord, const int & hp);
    std::vector<Coord> & getHomeBorders();
    Coord & getHomeCenter();
    int & getHp();

};
class FirstTypeHome : public AntHome{

public:
    explicit FirstTypeHome (const Coord & coord, const int & hp = 100): AntHome(coord, hp){}
    void Draw(WINDOW *& window) override;
    ~FirstTypeHome() override = default;
    int getHouseType () override;
    Ant * createAnt(std::string & attacker_name) override;
};
class SecondTypeHome : public AntHome{

public:
    explicit SecondTypeHome (const Coord & coord, const int & hp = 200): AntHome(coord, hp){}
    void Draw(WINDOW *& window) override;
    ~SecondTypeHome() override = default;
    int getHouseType () override;
    Ant * createAnt(std::string & attacker_name) override;
};
class ThirdTypeHome : public AntHome{

public:
    explicit ThirdTypeHome (const Coord & coord, const int & hp = 150): AntHome(coord, hp){}
    void Draw(WINDOW *& window) override;
    ~ThirdTypeHome() override = default;
    int getHouseType () override;
    Ant * createAnt(std::string & attacker_name) override;
};
#endif //SEMESTRALWORK_ANTHOME_H

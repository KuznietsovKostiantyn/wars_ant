//
// Created by kuznikos on 5/10/19.
//

#ifndef SEMESTRALWORK_ANT_H
#define SEMESTRALWORK_ANT_H

#include "Coord.h"
#include "AntHome.h"
#include <curses.h>
#include <list>
#include <string>
#include <vector>

class Ant
{

protected:
    Coord m_coord;
    int m_hp;
    unsigned m_damage;
    std::string m_clan_name;

public:
    Ant (const Coord & c, const int & hp, const unsigned & damage, const std::string & name);
    virtual void Draw ( WINDOW *& window) = 0 ;
    void Move ( Coord & dest);
    virtual unsigned & getDamage() = 0;
    virtual int & getHp() = 0;
    Coord & getCoord();
    std::string & getClanName();
    virtual ~Ant() = default;
};
class StandardAnt : public Ant
{

public:
    StandardAnt(const Coord & c, const int & hp, const unsigned & damage, const std::string & name): Ant(c, hp, damage, name){}
    void Draw ( WINDOW *& window) override;
    unsigned & getDamage() override;
    int & getHp() override;
    ~StandardAnt() override;

};
class BossAnt1: public Ant{

public:
    BossAnt1(const Coord & c, const int & hp, const unsigned & damage, const std::string & name): Ant(c, hp, damage, name){}
    void Draw ( WINDOW *& window) override;
    unsigned & getDamage() override;
    int & getHp() override;
    ~BossAnt1() override = default;
};
class BossAnt2: public Ant {

public:
    BossAnt2(const Coord & c, const int & hp, const unsigned & damage, const std::string & name): Ant(c, hp, damage, name){}
    void Draw ( WINDOW *& window) override;
    unsigned & getDamage() override;
    int & getHp() override;
    ~BossAnt2() override = default;
};
class BossAnt3: public Ant {

public:
    BossAnt3(const Coord & c, const int & hp, const unsigned & damage, const std::string & name): Ant(c, hp, damage, name){}
    void Draw ( WINDOW *& window) override;
    unsigned & getDamage() override;
    int & getHp() override;
    ~BossAnt3() override = default;
};
#endif //SEMESTRALWORK_ANT_H

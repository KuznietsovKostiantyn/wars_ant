//
// Created by kuznikos on 5/10/19.
//

#ifndef SEMESTRALWORK_ATTACK_H
#define SEMESTRALWORK_ATTACK_H

#include "AntClan.h"
#include <vector>
class Attack
{

    AntClan * m_attacker;
    AntClan * m_defender;
    std::vector<Ant*> army;
    long m_count;
    bool is_attacker;
    bool is_defender;
    bool is_count;

public:
    Attack ();
    ~Attack();
    void setAttacker(AntClan * a);
    AntClan *& getAttacker();
    AntClan *& getDefender();
    long & getAntsCount();
    void setDefender(AntClan * a);
    void setCount(int c);
    bool canAttack ();
    bool attackEnemy(WINDOW *&window, int count);
    void moveToDestination(std::list<Coord> & route );
    void clearAnts(WINDOW *& window, std::vector<Ant*> & ants);
    bool checkDraw( Ant & ant);
    static bool IsInHome(Coord &coord, std::vector<Coord> &pHome);
    void attackClear(WINDOW *& window);
    bool isDead (Ant * ant);
    std::vector<Ant*> & getArmy();
    void checkCollision(Attack &attack);
    void addAnt();
    void clearAnts(WINDOW *&window);
};
#endif //SEMESTRALWORK_ATTACK_H

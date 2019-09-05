//
// Created by Kostiantyn on 08.05.2019.
//
#include "Game.h"
#include "GameWindow.h"
#include <iostream>
#include <algorithm>
#include <curses.h>
#include <list>
#include <signal.h>
#include <set>
#include <unistd.h>
#include <queue>
#include <map>
#include <fstream>
#include "GameWindow.h"
#include "Border.h"
#include "Attack.h"

enum m_choices{PLAYER_VS_COMPUTER, PLAYER_VS_PLAYER, LOAD, QUIT };
enum m_map_choices{MAP_1, MAP_2};
/**
 * Initialize and draw main game objects.
 **/
void Game::createObjects()
{
    if(m_menu.getChoice() == QUIT)
        return;
    srand((unsigned) time(NULL));
    m_window.createWindow();
    signal(SIGWINCH, GameWindow::resizeHandler);
    m_window.createBorders();
    m_window.drawBariers(m_bariers);
    createAntClans();
    m_turn = START;

}
void Game::closeGame()
{
    m_window.deleteWindow();
}
/**
 * Main game method. Handle mouse and keyboard clicks.
 * Collect all attacks and call appropriate metod for handle attack.
 * */
void Game::gameLoop()
{
    int ch;
    if (m_menu.getChoice() == QUIT)
        return;
    if (m_turn != WIN)
        m_turn = WAIT_CLICK;
    AntClan * tmp;
    Attack attack;
    mousemask(ALL_MOUSE_EVENTS  | REPORT_MOUSE_POSITION, NULL);
    if (m_menu.getChoice() == PLAYER_VS_COMPUTER){
        gameLoopAI();
        return;
    }
    while(1){
        gameStage();
        ch = wgetch(m_window.getWindow());
        /// Check if mouse button clicked and set attacker
        if (ch == KEY_MOUSE && m_turn == WAIT_CLICK){
            if (getmouse(&m_window.getEvent()) == OK){
                if (m_window.getEvent().bstate == BUTTON1_CLICKED || BUTTON1_DOUBLE_CLICKED){
                    tmp = m_window.mouseClickHandler(m_clans);
                    if (tmp != nullptr){
                        attack.setAttacker(m_window.mouseClickHandler(m_clans));
                        m_turn = MOUSE1;
                        gameStage();
                    }
                }
            }
        }
        /// Read ants count for attack
        if (m_turn == MOUSE1){
            attack.setCount(readAntsCount());
            m_turn = COUNT;
        }
        if (ch == KEY_MOUSE && m_turn == COUNT){
            if (getmouse(&m_window.getEvent()) == OK){
                if (m_window.getEvent().bstate == BUTTON1_CLICKED || BUTTON1_DOUBLE_CLICKED){
                    tmp = m_window.mouseClickHandler(m_clans);
                    if (tmp != nullptr){
                        attack.setDefender(m_window.mouseClickHandler(m_clans));
                        m_turn = MOUSE2;
                        gameStage();
                    }
                }
            }
        }
        /// Check if mouse button clicked and set defender
        if (m_turn == MOUSE2){

            if (!attack.canAttack()
                || attack.getAttacker()->getAntsCount() < attack.getAntsCount()
                || !m_attack.insert(make_pair(attack.getAttacker()->getName(), attack)).second){

                mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
                mvwprintw(m_window.getWindow(), 26, 40, "CAN'T ATTACK");
                wrefresh(m_window.getWindow());
                usleep(500000);
            }
            else
                attack.getAttacker()->getAntsCount() -= attack.getAntsCount();
            m_turn = WAIT_CLICK;
        }
        /// If button "ENTER" clicked - start attack. After attack - handle result.
        if (ch == 10 && !m_attack.empty()){
            mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
            mvwprintw(m_window.getWindow(), 26, 40, "ATTACK");
            attackHandler();
            update();
            m_attack.clear();
            if (m_clans.size() == 1 )
                m_turn = WIN;
            else
                m_turn = WAIT_CLICK;
            gameStage();
        }
        /// if button "q" clicked - exit game.
        if ( ch == 'q' && m_turn != MOUSE1){
            return;
        }
        ///if button "w" clicked - save game.
        if (ch == 'w' && m_turn == WAIT_CLICK){
            saveGame();
            createObjects();
            gameLoop();
        }
        if(m_turn == WIN) {
            wattron(m_window.getWindow(), COLOR_PAIR(m_clans.at(0)->getColor()));
            wmove(m_window.getWindow(), 26, 0);
            wclrtoeol(m_window.getWindow());
            mvwprintw(m_window.getWindow(), 26, 40, "CLAN %c WIN", m_clans.at(0)->getName()[0]);
            wrefresh(m_window.getWindow());
            usleep(2000000);
            wattroff(m_window.getWindow(), COLOR_PAIR(m_clans.at(0)->getColor()));
            m_turn = WIN;
            return;
        }
        wrefresh(m_window.getWindow());
    }
}
/**
 * Initialize ant clans and set routes to enemies
 */
void Game::createAntClans() {
    vector<vector<Coord>> home_borders;
    for (auto x: m_clans)
        x->Draw(m_window.getWindow());
    for (unsigned i = 0; i < m_clans.size(); i++){
        home_borders.push_back(m_clans.at(i)->getHome()->getHomeBorders());
    }
    for(unsigned i = 0; i < m_clans.size(); i++){
        for(unsigned j = 0; j < m_clans.size(); j++) {
            if(i == j) continue;
            m_clans.at(i)->getSearchRoute().emplace(
                    m_clans.at(j)->getHome()->getHomeCenter(),
                    SearchRoute(m_clans.at(i)->getHome()->getHomeCenter(),
                            m_clans.at(j)->getHome()->getHomeCenter(),
                            home_borders) );
            m_clans.at(i)->getSearchRoute().find(m_clans.at(j)->getHome()->getHomeCenter() )->second.FindShortRoute(m_bariers);
        }
    }
}

int Game::readAntsCount() {
    int ch;
    while(1){
        ch = wgetch(m_window.getWindow());
        switch (ch){
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
        }
    }

}
/**
 * Update map.
 */
void Game::update() {

    wclear(m_window.getWindow());
    m_window.createBorders();
    m_window.drawBariers(m_bariers);
    for(auto &x: m_clans ){
            x->Draw(m_window.getWindow());
    }
}
/**
 * Handle attack result.
 */
void Game::attackResult (Attack & attack){

    if (!attack.getArmy().empty()){

        for (int i = 0; i < attack.getAntsCount(); i++){

            if (!attack.getArmy().empty()) {
                attack.getDefender()->getHome()->getHp() -= attack.getArmy().at(0)->getDamage();
            }

        }
    }
}
/**
 * Check if any attack collide with another.
 */
void Game::checkCollision (){
    for(auto &x: m_attack ){
        for(auto &y: m_attack ){
            x.second.checkCollision(y.second);
        }
    }
}
/**
 * Print text depends on game stage.
 */
void Game::gameStage() {

    mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
    switch(m_turn){
        case WAIT_CLICK:
            mvwprintw(m_window.getWindow(), 26, 40, "CHOOSE ATTACKER");
            break;
        case MOUSE1:
            mvwprintw(m_window.getWindow(), 26, 40, "CHOOSE COUNT OF ANTS");
            break;
        case COUNT:
            mvwprintw(m_window.getWindow(), 26, 40, "CHOOSE ENEMY");
            break;
        default:
            break;
    }

}

void Game::menuHandler() {

    m_menu.switchSections();

    if (m_menu.getChoice() == PLAYER_VS_PLAYER ){
        m_menu.mapMenu();
        if (m_menu.getChoosingMap() == MAP_1){
            loadMap("examples/map1.txt");
        }
        if (m_menu.getChoosingMap() == MAP_2){
            loadMap("examples/map2.txt");
        }
    }
    if (m_menu.getChoice() == LOAD )
        loadGame();
    if (m_menu.getChoice() == PLAYER_VS_COMPUTER){
        m_menu.mapMenu();
        if (m_menu.getChoosingMap() == MAP_1){
            loadMap("examples/map1.txt");
        }
        if (m_menu.getChoosingMap() == MAP_2){
            loadMap("examples/map2.txt");
        }
    }
}

void Game::loadMap(std::string map_name) {

    std::ifstream file(map_name.c_str());
    if(!file.is_open()){
        m_menu.erorDetected();
        return;
    }
    char delim;
    unsigned count;
    int coord_y;
    int coord_y1;
    int coord_x;
    int coord_x1;
    string clan_name;
    unsigned house_type;
    unsigned count_ants;
    unsigned hp;
    unsigned color;
    /// read barirers count
    file >> count;

    for (unsigned i = 0 ; i < count; i++){

        file >> coord_x;
        checkErr(file);
        file >> coord_y;
        checkErr(file);
        file >> delim;
        checkErr(file);
        file >> coord_x1;
        checkErr(file);
        file >> coord_y1;
        checkErr(file);

        if(coord_x >= 100 || coord_y >= 25 || coord_x1 >= 100 || coord_y >= 25
            || coord_x == 0 || coord_x1 == 0 || coord_y == 0 || coord_y1 == 0
            || coord_y == coord_y1){
            file.close();
            m_menu.erorDetected();
            return;
        }
        ///check if bariers intersect
        if (m_bariers.empty())
            m_bariers.emplace_back(Coord(coord_x, coord_y), Coord(coord_x1, coord_y1));
        else {
            Coord start(coord_x, coord_y);
            Coord end(coord_x1, coord_y1);
            for (auto &x: m_bariers) {
                if (x.detectIntersect(start, end) || (start == x.getStartPoint() && end == x.getEndPoint())) {
                    m_menu.erorDetected();
                    file.close();
                    return;
                }
            }
            if (start.m_x == end.m_x && start.m_y > end.m_y)
                swap(start, end);
            m_bariers.emplace_back(start, end);
        }
    }
    file >> delim;
    checkErr(file);
    file >> count;
    /// read ant clans and input validating.
    for (unsigned i = 0 ; i < count; i++){
        file >> clan_name;
        if (clan_name.size() != 1){
            file.close();
            m_menu.erorDetected();
            return;
        }
        checkErr(file);
        file >> house_type;
        checkErr(file);
        file >> coord_x;
        checkErr(file);
        file >> coord_y;
        checkErr(file);
        if (coord_x >= 100 || coord_y >= 25 || coord_x == 0 || coord_y == 0){
            file.close();
            m_menu.erorDetected();
            return;
        }
        file >> count_ants;
        checkErr(file);
        file >> hp;
        checkErr(file);
        file >> color;
        checkErr(file);
        file >> delim;
        checkErr(file);
        Coord coord(coord_x, coord_y);
        if (house_type > 3){
            m_menu.erorDetected();
            file.close();
            return;
        }
        m_clans.push_back(new AntClan(house_type, coord, count_ants, clan_name, color));
    }
    file >> delim;
    if (!file.eof()){
        file.close();
        m_menu.erorDetected();
        return;
    }
    /// Validate if ant's home doesn't collide with another.
    for (auto it = m_clans.begin(); it !=m_clans.end(); it++){
        for (auto it1 = m_clans.begin(); it1 != m_clans.end(); it1++){
            if ((*it)->getHome() != (*it1)->getHome() && Attack::IsInHome((*it)->getHome()->getHomeBorders().at(0), (*it1)->getHome()->getHomeBorders())){
                m_menu.erorDetected();
                return;
            }
        }
    }
    file.close();

}
void Game::checkErr(ifstream & file){
    if (!file.good() || file.eof() )
        m_menu.erorDetected();
}

Game::~Game() {

    while (!m_clans.empty()) {
        auto day = m_clans.back();
        m_clans.pop_back();
        delete day;
    }
}

void Game::saveGame() {

    std::string file_name = "";
    m_menu.readSaveFile(file_name);
    if (file_name.empty()){
        m_menu.erorDetected();
    }
    file_name = "examples/" + file_name;
    ofstream out_file;
    out_file.open(file_name);
    out_file << m_bariers.size() << "\n";
    for (auto &x: m_bariers){
        out_file << x.getStartPoint().m_x << " " << x.getStartPoint().m_y << " - "
                 << x.getEndPoint().m_x << " " << x.getEndPoint().m_y << "\n";
    }
    out_file << "-\n";
    out_file << m_clans.size();
    for (auto &x: m_clans){
        out_file << "\n" << x->getName() << "\n" << x->getHome()->getHouseType() << "\n"
                 << x->getHome()->getHomeBorders().at(0).m_x << " " << x->getHome()->getHomeBorders().at(0).m_y << "\n"
                 << x->getAntsCount() << "\n" << x->getHome()->getHp() << "\n" << x->getColor() << "\n" << "-";
    }

}

void Game::loadGame() {
    std::string file_name = "";
    m_menu.readSaveFile(file_name);
    file_name = "examples/" + file_name;
    loadMap(file_name);
}
/// Main method for AI.
void Game::gameLoopAI() {

    int ch;
    AntClan * tmp;
    Attack attack;
    mousemask(ALL_MOUSE_EVENTS  | REPORT_MOUSE_POSITION, NULL);
    while(1){
        gameStage();
        ch = wgetch(m_window.getWindow());
        if (ch == KEY_MOUSE && m_turn == WAIT_CLICK){
            if (getmouse(&m_window.getEvent()) == OK){
                if (m_window.getEvent().bstate == BUTTON1_CLICKED || BUTTON1_DOUBLE_CLICKED){
                    tmp = m_window.mouseClickHandler(m_clans);
                    if (tmp != nullptr){
                        /// check if mouse click was on playing home.
                        if ( tmp->getName() == "A"){
                            attack.setAttacker(m_window.mouseClickHandler(m_clans));
                            m_turn = MOUSE1;
                            gameStage();
                        }
                        else{
                            mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
                            mvwprintw(m_window.getWindow(), 26, 40, "CHOOSE HOUSE A");
                            wrefresh(m_window.getWindow());
                            usleep(500000);
                            m_turn = WAIT_CLICK;
                        }
                    }
                }
            }
        }
        if (m_turn == MOUSE1){
            attack.setCount(readAntsCount());
            m_turn = COUNT;
        }
        if (ch == KEY_MOUSE && m_turn == COUNT){
            if (getmouse(&m_window.getEvent()) == OK){
                if (m_window.getEvent().bstate == BUTTON1_CLICKED || BUTTON1_DOUBLE_CLICKED){
                    tmp = m_window.mouseClickHandler(m_clans);
                    if (tmp != nullptr){
                        attack.setDefender(m_window.mouseClickHandler(m_clans));
                        m_turn = MOUSE2;
                        gameStage();
                    }
                }
            }
        }
        if (m_turn == MOUSE2){

            if (!attack.canAttack()
                || attack.getAttacker()->getAntsCount() < attack.getAntsCount()
                || !m_attack.insert(make_pair(attack.getAttacker()->getName(), attack)).second){

                mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
                mvwprintw(m_window.getWindow(), 26, 40, "CAN'T ATTACK");
                wrefresh(m_window.getWindow());
                usleep(500000);
                m_turn = WAIT_CLICK;
            }
            else{
                attack.getAttacker()->getAntsCount() -= attack.getAntsCount();
                m_turn = AUTO_TURN;
            }
        }
        if(m_turn == AUTO_TURN){
            if (m_attack.empty()){
                mvwprintw(m_window.getWindow(), 26, 40, "                                 ");
                mvwprintw(m_window.getWindow(), 26, 40, "EMPTY");
                wrefresh(m_window.getWindow());
                usleep(500000);
            }
            /// set another attacks
            for (auto x: m_clans){
                if (m_attack.begin()->second.getAttacker() != x){

                    attack.setAttacker(x);
                    attack.setDefender(getClanWhichCouldBeAttacked(x));
                    attack.setCount(rand()% (attack.getAttacker()->getAntsCount() <= 5 ? attack.getAttacker()->getAntsCount() : 5 ));
                    m_attack.insert(make_pair(attack.getAttacker()->getName(), attack));
                    attack.getAttacker()->getAntsCount() -= attack.getAntsCount();
                }
            }
            attackHandler();
            update();
            m_attack.clear();
            /// check if our clan is dead
            auto it = find_if(m_clans.begin(), m_clans.end(), [&] (AntClan * a){ return a->getName() == "A";});
            if (it == m_clans.end()){
                wattron(m_window.getWindow(), COLOR_PAIR(5));
                wmove(m_window.getWindow(), 26, 0);
                wclrtoeol(m_window.getWindow());
                mvwprintw(m_window.getWindow(), 26, 40, "YOU LOSE");
                wrefresh(m_window.getWindow());
                usleep(2000000);
                wattroff(m_window.getWindow(), COLOR_PAIR(5));
                return;
            }
            if (m_clans.size() == 1 )
                m_turn = WIN;
            else
                m_turn = WAIT_CLICK;
            gameStage();
        }
        if ( ch == 'q' && m_turn != MOUSE1){
            return;
        }
        if (ch == 'w' && m_turn == WAIT_CLICK){
            saveGame();
            createObjects();
            gameLoop();
        }
        if(m_turn == WIN) {
            wattron(m_window.getWindow(), COLOR_PAIR(m_clans.at(0)->getColor()));
            wmove(m_window.getWindow(), 26, 0);
            wclrtoeol(m_window.getWindow());
            mvwprintw(m_window.getWindow(), 26, 40, "CLAN %c WIN", m_clans.at(0)->getName()[0]);
            wrefresh(m_window.getWindow());
            usleep(2000000);
            wattroff(m_window.getWindow(), COLOR_PAIR(m_clans.at(0)->getColor()));
            m_turn = WIN;
            return;
        }
        wrefresh(m_window.getWindow());
    }
}
/// Choose clan which could be attacked
AntClan *Game::getClanWhichCouldBeAttacked(AntClan *&me) {
     unsigned num = rand() % m_clans.size();
     if(m_clans[num]->getName() == me->getName()) return getClanWhichCouldBeAttacked(me);
     return m_clans[num];
}

void Game::attackHandler() {
    unsigned finished_attacks = 0;
    vector<map<string, Attack>::iterator> attack_it;
    vector<vector<AntClan>::iterator> clan_it;
    vector<AntClan *> inc_attack_it;
    int cnt = 0;
    int iterate_control = 0;
    /// add 1 ant to attack participants.
    for (auto &x: m_attack){
        if(inc_attack_it.empty()) {
            x.second.getAttacker()->getAntsCount()++;
            x.second.getDefender()->getAntsCount()++;
            inc_attack_it.push_back(x.second.getAttacker());
            inc_attack_it.push_back(x.second.getDefender());
        }
        else{
            auto it = find_if(inc_attack_it.begin(), inc_attack_it.end(), [&] (AntClan * a) {return x.second.getAttacker() == a;});
            auto it1 = find_if(inc_attack_it.begin(), inc_attack_it.end(), [&] (AntClan * a) {return x.second.getDefender() == a;});
            if (it == inc_attack_it.end()) x.second.getAttacker()->getAntsCount()++;
            if (it1 == inc_attack_it.end()) x.second.getDefender()->getAntsCount()++;
        }
    }

    inc_attack_it.clear();
    while(!(m_attack.empty())){
        cnt++;

        vector<string> attacks_toDelete;
        for (auto &x: m_attack) {

            /// if all ants reached defender's house.
            if(x.second.attackEnemy(m_window.getWindow(), cnt)) {
                finished_attacks++;

                attackResult(x.second);
                x.second.clearAnts(m_window.getWindow());
                attacks_toDelete.push_back(x.first);
            }
            if (m_attack.size() > 1 && iterate_control )
                checkCollision();
            iterate_control = 1;
        }
        ///delete all attacks
        for(auto &x: attacks_toDelete){
            m_attack.erase(m_attack.find(x));
        }

        usleep(100000);
    }
    /// detect if some clan defeated and remove him.
    vector<AntClan *> clansToDelete;
    for(auto x : m_clans){
        if(x->getHome()->getHp() <= 0 ) clansToDelete.push_back(x);
    }

    for(auto x : clansToDelete){
        auto it = find_if(m_clans.begin(), m_clans.end(), [&](AntClan * clan){ return *x == *clan;});
        delete x;
        m_clans.erase(it);
    }

}
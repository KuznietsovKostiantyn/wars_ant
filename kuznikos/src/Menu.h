//
// Created by Kostiantyn on 02.06.2019.
//

#ifndef SEMESTRALWORK_MENU_H
#define SEMESTRALWORK_MENU_H

#include <curses.h>
#include <string>

class Menu {

    WINDOW * m_window;
    int m_choice;
    int m_choosing_map;
public:
    Menu();
    ~Menu() = default;

    void switchSections();
    int getChoice() const;
    void mapMenu();
    void switchMap();
    void printBorders();
    int getChoosingMap() const;
    void erorDetected();
    std::string & readSaveFile(std::string & file_name);
};
#endif //SEMESTRALWORK_MENU_H

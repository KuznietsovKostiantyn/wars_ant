//
// Created by Kostiantyn on 02.06.2019.
//

#include <string>
#include <fstream>
#include "Menu.h"
#include <unistd.h>

enum m_choices{PLAYER_VS_COMPUTER, PLAYER_VS_PLAYER, LOAD, QUIT};
enum m_map_choices{MAP_1, MAP_2};

Menu::Menu() {

    initscr();
    m_window = newwin(27, 100, 0, 0);
    printBorders();
    keypad(m_window, true);
    raw();
    noecho();
    curs_set(0);
}
/**
 * Main menu handler. Print menu fields and handle switching between them.
 * */
void Menu::switchSections() {

    int underline_index = 8;
    int prevUnderline_index = 8;
    int input_tmp;
    std::string choices[6] = {"PLAYER VS COMPUTER", "PLAYER VS PLAYER", "LOAD", "QUIT"};
    wattron(m_window, A_REVERSE);
    mvwprintw(m_window, 10 , 35, choices[0].c_str());
    wattroff(m_window, A_REVERSE);
    int cnt = 9;
    for ( int i = 1; i < 4; i++ ) {
        mvwprintw(m_window, cnt+2 , 35 ,choices[i].c_str());
        cnt++;
    }
    wrefresh(m_window);
    while ( 1 ) {
        input_tmp = wgetch(m_window);
        prevUnderline_index = underline_index;
        if ( input_tmp == KEY_UP ) {
            underline_index--;
        } else if ( input_tmp == KEY_DOWN ) {
            underline_index++;
        } else if ( input_tmp == 10 ) {
            m_choice = underline_index-8;
            wclear(m_window);
            wrefresh(m_window);
            endwin();
            break;
        } else {
            continue;
        }
        if ( underline_index > 11 ) {
            underline_index = 8;
        } else if ( underline_index < 8 ) {
            underline_index = 11;
        }
        mvwprintw(m_window, prevUnderline_index+2 , 35 ,choices[prevUnderline_index-8].c_str());
        wattron(m_window, A_REVERSE);
        mvwprintw(m_window, underline_index+2 , 35 ,choices[underline_index-8].c_str());
        wattroff(m_window, A_REVERSE);
        wrefresh(m_window);
    }
    wclear(m_window);
    wrefresh(m_window);
    endwin();

}
int Menu::getChoice() const {
    return m_choice;
}

void Menu::mapMenu() {
    initscr();
    m_window = newwin(27,100,0,0);
    printBorders();
    noecho();
    curs_set(0);
    keypad(m_window, true);
    raw();
    wrefresh(m_window);
    switchMap();
}
/**
 * Map menu handler. Print menu fields and handle switching between them.
 * */
void Menu::switchMap() {

    int underline_index = 8;
    int prevUnderline_index = 8;
    int input_tmp;
    std::string choices[3] = {"1 MAP", "2 MAP"};
    wattron(m_window, A_REVERSE);
    mvwprintw(m_window, 10 , 35 , choices[0].c_str());
    wattroff(m_window, A_REVERSE);
    int cnt = 9;
    for ( int i = 1; i < 2; i++ ) {
        mvwprintw(m_window, cnt+2 , 35 ,choices[i].c_str());
    }
    wrefresh(m_window);
    while ( 1 ) {
        input_tmp = wgetch(m_window);
        prevUnderline_index = underline_index;
        if ( input_tmp == KEY_UP ) {
            underline_index--;
        } else if ( input_tmp == KEY_DOWN ) {
            underline_index++;
        } else if ( input_tmp == 10 ) {
            m_choosing_map = underline_index-8;
            wclear(m_window);
            wrefresh(m_window);
            endwin();
            break;
        } else {
            continue;
        }
        if ( underline_index > 9 ) {
            underline_index = 8;
        } else if ( underline_index < 8 ) {
            underline_index = 9;
        }
        mvwprintw(m_window, prevUnderline_index+2 , 35 ,choices[prevUnderline_index-8].c_str());
        wattron(m_window, A_REVERSE);
        mvwprintw(m_window, underline_index+2 , 35 ,choices[underline_index-8].c_str());
        wattroff(m_window, A_REVERSE);
        wrefresh(m_window);
    }
    wclear(m_window);
    wrefresh(m_window);
    endwin();
}
void Menu::printBorders() {
    for (int i = 1; i < 100; i++ ){
        wmove(m_window, 0, i);
        wprintw(m_window, "#");
        wrefresh(m_window);
    }
    for (int i = 0; i < 25; i++ ){
        wmove(m_window, i, 0);
        wprintw(m_window, "#");
        wrefresh(m_window);
    }

    for (int i = 0; i < 100; i++ ){
        wmove(m_window, 24, i);
        wprintw(m_window, "#");
        wrefresh(m_window);
    }
    for (int i = 0; i < 25; i++ ){
        wmove(m_window, i, 99);
        wprintw(m_window, "#");
        wrefresh(m_window);
    }
    wrefresh(m_window);
}

int Menu::getChoosingMap() const {
    return m_choosing_map;
}

void Menu::erorDetected() {
    wclear(m_window);
    wrefresh(m_window);
    mvwprintw(m_window, 10 , 35 , "CAN'T LOAD FILE");
    wrefresh(m_window);
    usleep(1000000);
    endwin();
    m_choice = 3;
}
/**
 * Reading file name and handle input.
 */
std::string &Menu::readSaveFile(std::string & file_name) {

    initscr();
    m_window = newwin(27,100,0,0);
    noecho();
    keypad(m_window, true);
    raw(); //mouse
    char ch;
    while (1){
        mvwprintw(m_window, 12, 35, "WRITE FILE NAME");
        wrefresh(m_window);
        if(file_name.empty())
            usleep(2000000);
        if((ch = getch()) == 10)
            break;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '1' && ch <= '9'))
            file_name+=ch;
        if (ch == 127){
            if (!file_name.empty())
                file_name.resize(file_name.size()-1);
        }
        wmove(m_window, 13, 0);
        wclrtoeol(m_window);
        mvwprintw(m_window, 13, 35, file_name.c_str());
        wrefresh(m_window);
    }
    endwin();
    return file_name;
}

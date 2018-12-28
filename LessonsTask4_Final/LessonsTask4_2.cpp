//
//  LessonsTask4_2.cpp
//  
//
//  Created by Hayden Martz on 5/17/18.
//
//

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "Textline.hpp"

int main(){
    initscr();
    cbreak();
    noecho();
    curs_set(1);
    keypad(stdscr, TRUE);
    
    Textline first;
    
    int input;
    
    while(input != 10){ //press enter to exit
        first.update();
        input = getch();
        clear();
        switch(input){
            case KEY_LEFT : first.decrementCursor();
                break;
            case KEY_RIGHT : first.incrementCursor();
                break;
            case 127 : first.backspace();
                break;
            case 330 : first.fDelete();
                break;
            default : if(32<=input && input <=126
                         && first.getCursorPos()<first.getLength())
                first.typeChar(input);
        }
    }
    endwin();
    return 0;
}
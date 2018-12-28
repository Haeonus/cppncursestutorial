//
//  LessonsTask5.cpp
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

    //Get window size
    int rows, columns;
    getmaxyx(stdscr, rows, columns);
    
    
    //Declare an array of Textlines to model the system
    Textline *fields[rows];
    for(int i=0; i<rows; i++){
        fields[i] = new Textline(0, i, columns, false, false);
    }
    
    //Setup operating variables
    int cursorx = 0;
    int cursory = 0;
    
    int input;
    while(input != 9){ //press escape to exit
        //Update screen
        for(int i=0; i<rows; i++){
            fields[i]->update();
        }
        move(cursory, cursorx);
        
        input = getch();
        clear();
        
        switch(input){
            case KEY_LEFT : if(0<cursorx) cursorx--;
                break;
            case KEY_RIGHT : if(cursorx<columns) cursorx++;
                break;
            case KEY_UP : if(0<cursory) cursory--;
                break;
            case KEY_DOWN : if(cursory<rows) cursory++;
                break;
            case 10 : //Let enter go to beginning of next line
                        if(cursorx==rows) break;
                        cursorx = 0; cursory++;
                        break;
            case 127 : fields[cursory]->setCursorPos(cursorx);
                       fields[cursory]->backspace();
                       cursorx = fields[cursory]->getCursorPos();
                break;
            case 330 : fields[cursory]->setCursorPos(cursorx);
                       fields[cursory]->fDelete();
                       cursorx = fields[cursory]->getCursorPos();
                break;
            default : if(32<=input && input <=126 && cursorx < columns){
                            fields[cursory]->setCursorPos(cursorx);
                            fields[cursory]->typeChar(input);
                            cursorx = fields[cursory]->getCursorPos();
                      }
        }
    }
    
    //Make sure to delete the the pointer array
    for(int i=0; i<rows; i++){
        delete fields[i];
    }
    endwin();
    return 0;
}

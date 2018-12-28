//
//  LessonsTask3.cpp
//  
//
//  Created by Hayden Martz on 5/16/18.
//
//

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
    //get the parameters
    int xpos = 0;
    int ypos = 0;
    int length = 0;
    
    cout << "Please enter the x-position and y-position as (x, y): ";
    scanf("(%d, %d", &xpos, &ypos);
    while((getchar()) != '\n'); //clear buffer
        //Or: cin.ignor(numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter the length (characters): ";
    scanf("%d", &length);
    while((getchar()) != '\n');
    cout << endl;
    
    printf("(%d, %d) length: %d\n", xpos, ypos, length);
    cout << "Beginning ncurses..." << endl;
    
    //start of the ncurses implementation
    int input;
    int cursorPos = 0;
    int entryField[length];
    for(int i=0; i<length; i++) entryField[i] = ' '; //blankfill entry
    
    initscr();
    cbreak();
    noecho();
    curs_set(1); //1 here, so cursor is visible
    keypad(stdscr, TRUE);
    
    while(input != 10){ //10 is enter key
        mvprintw(0, 0, "Press Enter to Exit");
        for(int i=0; i<length; i++){
            mvprintw(ypos, xpos+i, "%c", entryField[i]);
        }
        mvchgat(ypos, xpos, length, A_UNDERLINE, 1, NULL);
        move(ypos, xpos+cursorPos);
        
        input = getch();
        clear();
        mvprintw(1,0,"%d", input);
        //Handle all the user typing.
        if(input == KEY_LEFT && cursorPos > 0) cursorPos--;
        if(input == KEY_RIGHT && cursorPos < length-1) cursorPos++;
        if(32 <= input && input <= 126 && cursorPos<length){
            //Move text to right
            for(int i=length-1; i>cursorPos; i--)
                entryField[i+1] = entryField[i];
            //Enter character
            entryField[cursorPos] = input;
            cursorPos++;
        }
        //Delete: write a space and decrement cursorPos
        if((input == 127 || input ==330) && cursorPos>-1){
            if(input == 127){
                if(cursorPos!=0) cursorPos--;
                entryField[cursorPos] = 32;
            }
            //Move rest of text to left
            for(int i=cursorPos; i<length; i++)
                entryField[i] = entryField[i+1];
            entryField[length-1] = 32; //To avoid artifacts
        }

    }
    endwin();
}
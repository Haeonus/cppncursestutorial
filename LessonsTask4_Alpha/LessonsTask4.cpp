//
//  LessonsTask4.cpp
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

class Textline {
    //Variables
    int xpos, ypos, length, cursorPos;
    int* field;
    bool highlighted, underlined;
    
public:
    //Constructors/Desctructor
    Textline();
    Textline(int, int, int);
    Textline(int, int, int, bool, bool);
    ~Textline();
    
    //Mutators
    void setPos(int, int);
    void setX(int);
    void setY(int);
    void setLength(int);
    void setFormatting(bool, bool);
    void decrementCursor();
    void incrementCursor();
        //For Text Handling
    void backspace();
    void fDelete();
    void typeChar(int);
    void typeString(int[]);
    
    //Accessors
    int getXPos();
    int getYPos();
    int getLength();
    int getCursorPos();
    bool getHighlighted();
    bool getUnderlined();
        //Display the Information
    void update();
};

//Constructors
Textline::Textline(){
    xpos = 0; ypos = 0; length = 15;
    cursorPos = 0; highlighted = false; underlined = true;
    field = new int[length];
}
Textline::Textline(int x, int y, int l){
    xpos = x; ypos = y; length = l;
    cursorPos = 0; highlighted = false; underlined = true;
    field = new int[length];
}
Textline::Textline(int x, int y, int l, bool h, bool u){
    xpos = x; ypos = y; length = l;
    cursorPos = 0; highlighted = h; underlined = u;
    field = new int[length];
}

//Destructor
Textline::~Textline(){
    delete [] field;
}

//Mutators
void Textline::setPos(int x, int y){ xpos = x; ypos = y; }
void Textline::setX(int x){ xpos = x; }
void Textline::setY(int y){ ypos = y; }
void Textline::setLength(int l){ length = l; }
void Textline::decrementCursor(){ if(cursorPos > 0) cursorPos--;}
void Textline::incrementCursor(){ if(cursorPos < length) cursorPos++;}
    //For Text Handling
void Textline::backspace(){
    if(cursorPos!=0) cursorPos--;
    field[cursorPos] = 3;
    fDelete();
}
void Textline::fDelete(){
    for(int i=cursorPos; i<length; i++)
        field[i] = field[i+1];
    field[length-1] = 32; //To avoid artifacts
}
void Textline::typeChar(int ch){
    //Move text to right
    for(int i=length-1; i>cursorPos; i--)
        field[i+1] = field[i];
    //Enter character
    field[cursorPos] = ch;
    cursorPos++;
}
void Textline::typeString(int ch[]){
    for(int i=0; i<length; i++){
        field[i] = ch[i];
        cursorPos++;
    }
}

//Accessors
int Textline::getXPos(){ return xpos; }
int Textline::getYPos(){ return ypos; }
int Textline::getLength(){ return length; }
int Textline::getCursorPos(){ return cursorPos;}
bool Textline::getHighlighted(){ return highlighted; }
bool Textline::getUnderlined(){ return underlined; }
    //Display the Information
void Textline::update(){
    for(int i=0; i<length; i++){
        mvprintw(ypos, xpos+i, "%c", field[i]);
    }
    if(underlined == true) mvchgat(ypos, xpos, length, A_UNDERLINE, 1, NULL);
    if(highlighted == true) mvchgat(ypos, xpos, length, A_STANDOUT, 1, NULL);
    move(ypos, xpos+cursorPos);
}


g++ -lncurses -o LessonsTask4_2 LessonsTask4_2.cpp Textline.cpp
//MAIN==============================================================
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
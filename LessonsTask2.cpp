//
//  LessonsTask2.cpp
//  
//
//  Created by Hayden Martz on 5/15/18.
//
//

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

int main(){
    
    //Setup input file
    ifstream menuFile;
    menuFile.open("MenuOptions.txt");
    if(!menuFile){
        cout << "Unable to Open MenuOptions.txt" <<endl;
        exit(1);
    }
    //Get number of file options
    int count = 0;
    int maxOptionLength = 0;
    string menuOption;
    while(getline(menuFile, menuOption)){
        count++;
        if(menuOption.length() > maxOptionLength)
            maxOptionLength = menuOption.length();
    }
    

    //Reset File Pointer back to beginning of file
    menuFile.clear();
    menuFile.seekg(0, ios::beg);
    
    //Put menu options in array
    string *menuOptions = new string[count];
    for(int i=0; i<count; i++){
        getline(menuFile, menuOption);
        menuOptions[i] = menuOption;
    }
    //Setup ncurses screen
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE); //Lets for using arrow keys and keypad
    
    //Open interactive menu
    int selected = 0;
    int input = 0;
    while(input!='q'){
        //print menu options
        clear();
        for(int i=0; i<count; i++){
            mvprintw(i, 15, menuOptions[i].c_str());
            if(i == selected) mvchgat(i, 15, maxOptionLength, A_STANDOUT, 1, NULL);
        }
        refresh();
        input = getch();
        //Change selected option; Note: (0, 0) is at the top left.
        if(input == KEY_DOWN && selected < (count-1)) selected++;
        if(input == KEY_UP && selected > 0 ) selected--;
    }
    endwin();
    delete [] menuOptions;
}
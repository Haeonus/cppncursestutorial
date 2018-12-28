//
//  Textline.hpp
//  
//
//  Created by Hayden Martz on 5/17/18.
//
//

#ifndef Textline_hpp
#define Textline_hpp

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
    void setCursorPos(int);
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
#endif /* Textline_hpp */

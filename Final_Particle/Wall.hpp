/*
This file defines a wall object, which is
used a bounds for the edges of the screen.
 
Author: Miguel Donado, Dimitrios Chavouzis
 
*/

#ifndef Wall_hpp
#define Wall_hpp

#include <stdio.h>

class Wall{
private:
    float* m_pos;
    bool m_orientation; //true if horizontal, false if vertical
    
public:
    Wall(float*, bool);
    ~Wall();
    float* get_pos();
    bool get_orientation();
};

#endif /* Wall_hpp */

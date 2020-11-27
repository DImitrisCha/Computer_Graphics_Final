//
//  Wall.hpp
//  Homework 2
//
//  Created by Miguel Donado on 11/27/20.
//  Copyright © 2020 Miguel Donado. All rights reserved.
//

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

//
//  Box.hpp
//  PlayTime
//
//  Created by Dimitrios Chavouzis on 12/2/20.
//  Copyright © 2020 Dimitrios Chavouzis. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp
#include <set>
#include <map>
#include <iostream>
#include <stdio.h>
#include "Particle.hpp"

class Box {
private:
    float m_x_left;
    float m_x_right;
    float m_y_bottom;
    float m_y_top;
    
    std::set<Particle*> m_included;
    
public:
    Box(float, float, float, float, std::set<Particle*>);
    
    bool in_bounds(float,float);
};
#endif /* Box_hpp */

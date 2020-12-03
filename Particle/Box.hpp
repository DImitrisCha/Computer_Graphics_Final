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
#include <iostream>
#include <stdio.h>
#include "Particle.hpp"

class Box {
private:
    float m_x_left;
    float m_x_right;
    float m_y_bottom;
    float m_y_top;
    int m_index;
    std::set<Particle*> m_included;
    bool in_bounds(float,float);
    
public:
    Box(float, float, float, float, int);
    bool in_bounds(Particle*);
    void update_box(Particle* particle);
    std::set<Particle*> get_included();
    int get_region();
};
#endif /* Box_hpp */

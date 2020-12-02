//
//  Box.cpp
//  PlayTime
//
//  Created by Dimitrios Chavouzis on 12/2/20.
//  Copyright © 2020 Dimitrios Chavouzis. All rights reserved.
//

#include "Box.hpp"
#include <iostream>

using namespace std;


Box::Box(float x_left, float x_right, float y_bottom, float y_top, set<Particle*> included){
    m_x_left = x_left;
    m_x_right = x_right;
    m_y_bottom = y_bottom;
    m_y_top = y_top;
    
    m_included = included;
}

bool Box::in_bounds(float loc_x, float loc_y){
    
    if (loc_x > this->m_x_left and loc_x < this->m_x_right and loc_y > this->m_y_bottom and loc_y < this->m_y_top){
        //If in bounds then add it to the set
        return true;
    }
    
    return false;
}

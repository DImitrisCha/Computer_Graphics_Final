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

/* Constructor
 *
 * float x_left, x_right - x-axis edges of the box
 * float y_bottom, y_top - y-axis edges of the box
 * int index - arbitrary index to keep track of individual regions
 *
 */
Box::Box(float x_left, float x_right, float y_bottom, float y_top, int index){
    m_x_left = x_left;
    m_x_right = x_right;
    m_y_bottom = y_bottom;
    m_y_top = y_top;
    m_index = index;
}

/* Standard accessors for private instance variables */
std::set<Particle*> Box::get_included(){
    return m_included;
}
int Box::get_region(){
    return m_index;
}

/* Determines if a point x,y is within this Box
 *
 * float loc_x, loc_y - x,y coordinates of the point being analyzed
 *
 */
bool Box::in_bounds(float loc_x, float loc_y){
    return (loc_x >= m_x_left and loc_x < m_x_right and loc_y >= m_y_bottom and loc_y < m_y_top);
}

/* Determines if a Particle is within this Box
 *
 * Particle* particle - address of Particle being analyzed
 *
 */
bool Box::in_bounds(Particle* particle){
    float* location = particle->get_position();
    return in_bounds(location[0], location[1]);
}

/* Determines if a Particle is within this Box, if it is currently in a different box
 * removes it from current Box
 *
 * Particle* particle - address of Particle being analyzed
 *
 */
void Box::update_box(Particle* particle){
    if(in_bounds(particle)){
        m_included.insert(particle);
        particle->set_region(m_index);
    }
    else{
        if(particle->get_prev_region() == m_index) // if Particle was in this Box previously
            m_included.erase(particle);
    }
}

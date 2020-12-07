/*
Object that represents a part of our screen. Implemented
for efficiency to only check for collisions inside
the given onject.
 
Author: Miguel Donado, Dimitrios Chavouzis
 
*/

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

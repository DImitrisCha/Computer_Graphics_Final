/*
This file defines a wall object, which is
used a bounds for the edges of the screen.
 
Author: Miguel Donado, Dimitrios Chavouzis
 
*/

#include "Wall.hpp"

Wall::Wall(float* pos, bool orientation)
{
    m_pos = pos;
    m_orientation = orientation;
}
Wall::~Wall(){
    delete[] m_pos;
}
bool Wall::get_orientation(){
    return m_orientation;
}
float* Wall::get_pos(){
    return m_pos;
}

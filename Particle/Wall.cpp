//
//  Wall.cpp
//  Homework 2
//
//  Created by Miguel Donado on 11/27/20.
//  Copyright © 2020 Miguel Donado. All rights reserved.
//

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

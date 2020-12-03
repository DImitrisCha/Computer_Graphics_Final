/*
This file defines the Particle class.
 
Author: Miguel Donado
Date: October 12, 2020
 
*/

#ifndef Particle_hpp
#define Particle_hpp
#include <stdio.h>
#include <cmath>
#include "Wall.hpp"

class Particle{
private:
    float m_radius;
    float m_gravity;
    float* m_pos;
    float* m_vel;
    float* m_color;
    float m_start_time;
    bool m_moving;
    void check_moving();
public:
    Particle();
    Particle(float*, float*, float, float*, float);
    ~Particle();
    float* move();
    float* get_color();
    float get_radius();
    float* get_vel();
    float* get_position();
    void calculate_vel(Particle &two);
    void set_vel(float, float);
    void set_gravity(float);
    bool checkCollision(Particle &);
    bool checkCollision(Wall &);
};

#endif /* Particle_hpp */

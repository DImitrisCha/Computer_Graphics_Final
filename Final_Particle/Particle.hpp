/*
This file defines the Particle class.
 
Author: Miguel Donado, Dimitrios Chavouzis
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
    float m_friction;
    float* m_pos;
    float* m_vel;
    float* m_color;
    int m_region;
    int m_prev_region;
    bool check_moving();
public:
    Particle();
    Particle(float*, float*, float, float*, float);
    ~Particle();
    float* move();
    float get_radius();
    float* get_position();
    float* get_vel();
    float* get_color();
    int get_region();
    int get_prev_region();
    void set_vel(float, float);
    void set_region(int);
    void calculate_vel(Particle &two);
    bool checkCollision(Particle &);
    bool checkCollision(Wall &);
};

#endif /* Particle_hpp */

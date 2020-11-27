/*
This file defines the Particle class.
 
Author: Miguel Donado
Date: October 12, 2020
 
*/

#ifndef Particle_hpp
#define Particle_hpp
#include <stdio.h>
#include <cmath>

class Particle{
private:
    float time;
    float m_radius;
    float* m_pos;
    float* m_vel;
    float* m_acc;
    float* m_color;
    float m_init_h;
    float m_start_time;
public:
    Particle();
    Particle(float*, float*, float*, float*, float);
    ~Particle();
    float* move();
    float* get_color();
    float get_radius();
    float get_start_time();
    void set_start_time(float);
    bool checkParticleCollision(Particle &);
};

#endif /* Particle_hpp */

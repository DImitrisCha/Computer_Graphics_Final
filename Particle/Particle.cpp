/*
This file defines the Particle class.
 
Author: Miguel Donado
Date: October 12, 2020
 
*/

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#endif

#include "Particle.hpp"
#include <cmath>

Particle::Particle()
{
    float randVal = (float)rand() / (float)RAND_MAX;
    m_radius = .15 + randVal * 0.2;
    m_start_time = 0;
    
    // assigns random values to (x,y,z) and (r,g,b)
    m_pos = new float[3];
    m_vel = new float[3];
    m_acc = new float[3];
    m_color = new float[3];
    for(int i = 0; i < 3; i++){
        m_pos[i] = randVal - 0.5;
        m_color[i] = 0.0;
        m_vel[i] = 0.0;
        m_acc[i] = 0.0;
    }
//    m_pos[0] *= 18; // spreads out the randomly generated x value
    m_vel[0] = -0.05f + 0.1f * randVal;
    m_vel[1] = 0.1f + 0.1f * randVal;
    m_acc[1] = -0.001f;
    
    // stores initial y value
    m_init_h = m_pos[1];
}
Particle::Particle(float t)
{
    float randVal = (float)rand() / (float)RAND_MAX;
    m_radius = .15 + randVal * 0.2;
    m_start_time = t;
    
    // assigns random values to (x,y,z) and (r,g,b)
    m_pos = new float[3];
    m_vel = new float[3];
    m_acc = new float[3];
    m_color = new float[3];
    for(int i = 0; i < 3; i++){
        m_pos[i] = randVal - 0.5;
        m_color[i] = 0.0;
        m_vel[i] = 0.0;
        m_acc[i] = 0.0;
    }
//    m_pos[0] *= 18; // spreads out the randomly generated x value
    m_vel[0] = -0.05f + 0.1f * randVal;
    m_vel[1] = 0.1f + 0.1f * randVal;
    m_acc[1] = -0.01f;
    m_color[2] = randVal;
    
    // stores initial y value
    m_init_h = m_pos[1];
}
Particle::~Particle()
{
    delete[] m_pos;
    delete[] m_vel;
    delete[] m_acc;
    delete[] m_color;
}
float* Particle::move(void){
    m_vel[0] += m_acc[0];
    m_vel[1] += m_acc[1];
    
    m_pos[0] += m_vel[0];
    m_pos[1] += m_vel[1];
    
    return m_pos;
}
float* Particle::get_color(){
    return m_color;
}
float Particle::get_radius(){
    return m_radius;
}
float Particle::get_start_time(){
    return m_start_time;
}
void Particle::set_start_time(float t){
    m_start_time = t;
}

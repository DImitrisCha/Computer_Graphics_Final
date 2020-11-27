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
    m_pos = new float[3];
    m_vel = new float[3];
    m_acc = new float[3];
    m_color = new float[3];
    m_radius = 1;
    m_init_h = m_pos[1];
    m_start_time = 0;
}
Particle::Particle(float* pos, float* vel, float* acc, float* color, float r)
{
    m_pos = pos;
    m_vel = vel;
    m_acc = acc;
    m_color = color;
    m_radius = r;
    m_init_h = pos[1];
    m_start_time = 0;
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
bool Particle::checkCollision(Particle &two){
    
    float left = pow((this -> m_pos[0] - two.m_pos[0]),2) + pow((this -> m_pos[1] - two.m_pos[1]),2) + pow((this -> m_pos[2] - two.m_pos[2]),2);
    
    float right = pow((this->get_radius() + two.get_radius()),2);
    
    if (left > right){
        return false;
    }
    else{
        return true;
    }
}
bool Particle::checkCollision(Wall &two){
    bool collision = false;
    float* wall = two.get_pos();
    
    if(two.get_orientation()){
        //checks diff in y values for a horizontal wall
        if(abs(wall[1] - m_pos[1]) < m_radius){
            collision = true;
            
            m_vel[1] = m_vel[1] * -1;
            move();
        }
    }
    else{
        //checks diff in x values for a vertical wall
        if(abs(wall[0] - m_pos[0]) < m_radius){
            collision = true;
            
            m_vel[0] = m_vel[0] * -1;
            move();
        }
    }
    
    return collision;
}

float Particle::checkParticleBoarderCollision(){
  if (this->m_pos[0] <= -40){
    //add code to manipulate its direction, velocity etc
    return 0.0;
  }
  else if (this->m_pos[1] <= -40){
    //add code to manipulate its direction, velocity etc
    return 1.0;
  }
  else if (this->m_pos[0] >= 90){
    //add code to manipulate its direction, velocity etc
    return 2.0;
  }
  else if (this->m_pos[1] >= 90){
    //add code to manipulate its direction, velocity etc
    return 3.0;
  }
  else{
    return 4.0;
  }
}

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
    float randMax =  1 / (float)RAND_MAX;
    m_radius = .2 + randMax * (float)rand() * 0.2;
    m_start_time = 0;
    
    // assigns random values to (x,y,z) and (r,g,b)
    m_pos = new float[3];
    m_vel = new float[3];
    m_color = new float[3];
    for(int i = 0; i < 3; i++){
        m_pos[i] = (float)rand() * randMax - 0.5;
        m_color[i] = (float)rand() * randMax;
        m_vel[i] = 0.0f;
    }
    m_pos[0] *= 18; // spreads out the randomly generated x value
    m_vel[0] = -0.1f + 0.2f * (float)rand() * randMax;
    m_vel[1] = 0.1f + 0.2f * (float)rand() * randMax;
    m_gravity = -0.01f;
}
Particle::Particle(float* pos, float* vel, float g, float* color, float r)
{
    m_pos = pos;
    m_vel = vel;
    m_gravity = g;
    m_color = color;
    m_radius = r;
}
Particle::~Particle()
{
    delete[] m_pos;
    delete[] m_vel;
    delete[] m_color;
}
float* Particle::move(void){
    m_vel[1] += m_gravity;
    
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
float* Particle::get_position(){
    return m_pos;
}
void Particle::set_vel(float vel_x, float vel_y){
    m_vel[0] = vel_x; m_vel[1] = vel_y;
}
void Particle::calculate_vel(Particle &two){
    float m_1 = m_radius; float m_2 = two.get_radius();
    
    float vel_x = ((m_1 - m_2) * this->m_vel[0] + 2 * m_2 * two.m_vel[0])/(m_1+m_2);
    float vel_y = ((m_1 - m_2) * this->m_vel[1] + 2 * m_2 * two.m_vel[1])/(m_1+m_2);
    
    float other_vel_x =((m_2 - m_1) * two.m_vel[0] + 2 * m_1 * this->m_vel[0])/(m_1+m_2);
    float other_vel_y =((m_2 - m_1) * two.m_vel[1] + 2 * m_1 * this->m_vel[1])/(m_1+m_2);
    
    set_vel(vel_x, vel_y);
    two.set_vel(other_vel_x, other_vel_y);
}
bool Particle::checkCollision(Particle &two){
    float left = pow((this -> m_pos[0] - two.m_pos[0]),2) + pow((this -> m_pos[1] - two.m_pos[1]),2) + pow((this -> m_pos[2] - two.m_pos[2]),2);
    
    float right = pow((this->get_radius() + two.get_radius()),2);
    
    if (left > right){
        return false;
    }
    else{
        calculate_vel(two);
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
            if(abs(m_vel[1]) > abs(m_gravity)){
                m_vel[0] = m_vel[0] * 0.9;
                m_vel[1] = m_vel[1] * -1;
                move();
            }
            else{
                m_vel[1] = 0;
                m_gravity = 0;
            }
        }
    }
    else{
        //checks diff in x values for a vertical wall
        if(abs(wall[0] - m_pos[0]) < m_radius){
            collision = true;
            if(abs(m_vel[0]) > abs(m_gravity)){
                m_vel[0] = m_vel[0] * -1;
                move();
            }
            else{
                m_vel[0] = 0; //deaccelerate function?
            }
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

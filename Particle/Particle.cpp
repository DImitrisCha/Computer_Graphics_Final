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

/* Randomized constructor */
Particle::Particle()
{
    float randMax =  1 / (float)RAND_MAX;
    m_radius = .3 + randMax * (float)rand() * 0.2;
    
    // assigns random values to (x,y,z) and (r,g,b)
    m_pos = new float[3];
    m_vel = new float[3];
    m_color = new float[3];
    
    for(int i = 0; i < 3; i++){
        m_color[i] = (float)rand() * randMax;
        m_pos[i] = (float)rand() * randMax * 18;
        m_vel[i] = -0.05f + 0.05f * (float)rand() * randMax;
    }
    
    // assigns 0 to the z-values
    m_pos[2] = 0.0f;
    m_vel[2] = 0.0f;
    
    // sets arbitrary gravity, friction, and region values
    m_gravity = -0.01f;
    m_friction = 1 + m_gravity;
    m_region = -1; m_prev_region = -1;
}

/* Specific constructor based on input arguments
 *
 * float* pos = float[3] containing x,y,z coordinates
 * float* vel = float[3] containing x,y,z velocities
 * float g = float defining gravity for the system
 * float* color = float[3] containing r,g,b values
 * float r = particle size/mass
 */
Particle::Particle(float* pos, float* vel, float g, float* color, float r)
{
    m_pos = pos;
    m_vel = vel;
    m_gravity = g;
    m_friction = 1 + m_gravity;
    m_color = color;
    m_radius = r;
    m_region = -1; m_prev_region = -1;
}

/* Particle Destructor */
Particle::~Particle()
{
    delete[] m_pos;
    delete[] m_vel;
    delete[] m_color;
}

/* Standard accessors for private instance variables */
float* Particle::get_color(){
    return m_color;
}
float* Particle::get_vel(){
    return m_vel;
}
float Particle::get_radius(){
    return m_radius;
}
float* Particle::get_position(){
    return m_pos;
}
int Particle::get_region(){
    return m_region;
}
int Particle::get_prev_region(){
    return m_prev_region;
}

/* Methods to manually update instance variables */
void Particle::set_region(int region){
    m_prev_region = m_region;
    m_region = region;
}
void Particle::set_vel(float vel_x, float vel_y){
    m_vel[0] = vel_x; m_vel[1] = vel_y;
}

/* Updates x,y coordinates based on x,y velocities*/
float* Particle::move(void){
    // accelerates particle if it's moving
    if(check_moving())
        m_vel[1] += m_gravity;
    
    // adds velocity on both axis
    m_pos[1] += m_vel[1];
    m_pos[0] += m_vel[0];
    
    // renders particle on screen if a few pixels off
    if(m_pos[1] < m_radius)
        m_pos[1] = m_radius;
    
    if(m_pos[0] < m_radius)
        m_pos[0] = m_radius;
    else if(m_pos[0] > 20)
        m_pos[0] = 20 - m_radius;
    
    return m_pos;
}

/* Checks if a particle has stopped or is still in motion */
bool Particle::check_moving(){
    if(abs(m_vel[0]) < abs(m_gravity) and abs(m_vel[1]) < abs(m_gravity) and m_pos[1] == m_radius){
        m_vel[0] = 0.0f; m_vel[1] = 0.0f; return false; }
    else
        return true;
}

/* Calculates x,y velocities for two particles after collision
 *
 * Particle &two - address to second particle this collised with
 *
 */
void Particle::calculate_vel(Particle &two){
    float m_1 = m_radius; float m_2 = two.get_radius(); //uses radius as mass
    
    //Performs 1d collision equations on x,y velocities
    float vel_x = ((m_1 - m_2) * this->m_vel[0] + 2 * m_2 * two.m_vel[0])/(m_1+m_2);
    float vel_y = ((m_1 - m_2) * this->m_vel[1] + 2 * m_2 * two.m_vel[1])/(m_1+m_2);
    
    float other_vel_x =((m_2 - m_1) * two.m_vel[0] + 2 * m_1 * this->m_vel[0])/(m_1+m_2);
    float other_vel_y =((m_2 - m_1) * two.m_vel[1] + 2 * m_1 * this->m_vel[1])/(m_1+m_2);
    
    //Updates velocities on both Particles
    set_vel(vel_x, vel_y);
    two.set_vel(other_vel_x, other_vel_y);
}

/* Checks collision between this and other Particle
 *
 * Particle &two - address to second particle to check for collision
 *
 */
bool Particle::checkCollision(Particle &two){
    float dist_center = sqrt(pow((m_pos[0] - two.m_pos[0] + m_vel[0]),2) + pow((m_pos[1] - two.m_pos[1] + m_vel[1]),2));
    float sum_radius = (m_radius + two.get_radius());
    
    if (dist_center <= sum_radius){
        // calculates velocity after collision for both particles and updates second particle
        calculate_vel(two); two.move();
        return true;
    }
    else{
        return false;
    }
}

/* Checks collision between this and wall
 *
 * Wall &two - address to Wall object to check for collision
 *
 */
bool Particle::checkCollision(Wall &two){
    bool collision = false;
    float* wall = two.get_pos();
    
    // differentiates between wall orientations and calculates accordingly
    if(two.get_orientation()){ // true for horizontal
        if(abs(wall[1] - m_pos[1]) <= m_radius){
            collision = true;
            m_vel[1] = (m_vel[1] * -1); // inverts direction of y-speed
            m_vel[0] = m_vel[0] * m_friction; // simulates friction by reducing x-speed
        }
    }
    else{
        if(abs(wall[0] - m_pos[0]) <= m_radius){ // false for vertical
            collision = true;
            m_vel[0] = m_vel[0] * -1.0f; // inverts direction of x-speed
        }
    }
    
    return collision;
}

/*
 This file simulates the movement of particles over time and their
 interactions with each other and with their environment.
 
 Author: Miguel Donado & Dimitrios Chavouzis
 Date: December 8, 2020
 
*/

#include <stdio.h>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include "Box.hpp"
#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

// Globals
float win_width = 512;
float win_height = 512;
int avg_fps = 60; float fps = 0; int frames = 0;
float gravity = -0.01f;
float delta_time;
vector<Particle*> particles;
vector<Wall*> walls;
vector<Box*> regions;
GLUquadricObj *disk = gluNewQuadric();

// Initialization
void init(void) {
    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

// Converts the amounts of ms it takes to draw a frame into how many frames per second are drawn
void calculateFPS(){
    fps += 1000/delta_time;
    frames ++;
    // Averages out FPS for the last 30 frames
    if(frames == 30){
        avg_fps = fps/frames;
        fps = 0; frames = 0;
        //std::cout << "FPS: " << avg_fps << "  Particles: " << particles.size() << "\n";
    }
}

// Creates n amount of particles and adds them particles vector
void createParticles(int n){
    for(int i = 0; i < n; i++){
        particles.push_back(new Particle()); //add new particle to the vector
    }
}

// Drawing routine
void drawScene(void)
{
    float time_init = glutGet(GLUT_ELAPSED_TIME); //records Time Elapsed at beginning of frame
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 20, 0, 20, .1f, 500.0f);
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_LINE, GL_FILL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for (int i = 0; i < particles.size(); i++) {
        // Cycles through available regions to determine what region this Particle belongs to
        for(int j = 0; j < regions.size(); j++){
            regions[j]->update_box(particles[i]);
        }
        
        // Gets set of all Particles in this Particle's region and checks for collision
        int region = particles[i]->get_region();
        set<Particle*> close_particles = regions[region]->get_included();
        for (auto particle: close_particles){
            if(particles[i] != particle)
                particles[i]->checkCollision(*particle);
        }
        
        // Cycles through walls and checks for collision
        for (int j = 0; j < walls.size(); j++) {
            particles[i]->checkCollision(*walls[j]);
        }
        
        // Updates particle position and gets x,y,z coordinates
        float* curr_location = particles[i]->move();
        float* curr_color = particles[i]->get_color();
        
        glPushMatrix();
            
        // renders the particle according to its instance variables
        glColor3f(curr_color[0], curr_color[1], curr_color[2]);
        glTranslatef(curr_location[0], curr_location[1], curr_location[2]);
        gluDisk(disk, 0.0, particles[i]->get_radius(), 20, 20);
            
        glPopMatrix();
    }
    
    glutSwapBuffers();
    
    float time_final = glutGet(GLUT_ELAPSED_TIME); //records Time Elapsed at end of frame
    delta_time = time_final - time_init; //calculates how long it takes to draw a frame
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;
    glViewport(0, 0, w, h);
    glutPostRedisplay();
}

void idle() {
    calculateFPS();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Escape key
            exit(0); break;
        case 'a':
            //Adds 5 new randomly generated particles
            createParticles(5);
        case 'f':
            //Assigns random velocity to each particle
            float randSpeed =  (float)rand() / (float)RAND_MAX;
            for (int i = 0; i < particles.size(); i++) {
                particles[i]->set_vel(randSpeed - 0.5f, randSpeed - 0.2f);
            }
    }
    
    glutPostRedisplay();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(win_width, win_height);

    glutCreateWindow("ParticleSimulator");
    
    init();
    
    // Set up regions, dividing the scene roughly into quarters that overlap
    regions.push_back(new Box(0.0, 12.0, 8.0, 20.0, 0)); //top-left
    regions.push_back(new Box(8.0, 20.0, 8.0, 20.0, 1)); //top-right
    regions.push_back(new Box(0.0, 12.0, 0.0, 12.0, 2)); //bot-left
    regions.push_back(new Box(8.0, 20.0, 0.0, 12.0, 3)); //bot-right
    
    // Set up walls around the scene
    walls.push_back(new Wall((float[3]) {20.0f, 0.0f, 0.0f}, false)); //right
    walls.push_back(new Wall((float[3]) {0.0f, 0.0f, 0.0f}, true)); //bottm
    walls.push_back(new Wall((float[3]) {0.0f, 0.0f, 0.0f}, false)); //left
    
    // Set up two initial red and blue particles
    float pos_1[3] = {1.0f, 5.0f, 0.0f};
    float vel_1[3] = {0.1f, 0.0f, 0.0f};
    float color_1[3] = {0, 0, 1};
    float r_1 = 0.5f;
    particles.push_back(new Particle(pos_1, vel_1, gravity, color_1, r_1));
    float pos_2[3] = {19.0f, 5.0f, 0.0f};
    float vel_2[3] = {-0.1f, 0.0f, 0.0f};
    float color_2[3] = {1, 0, 0};
    float r_2 = 0.6f;
    particles.push_back(new Particle(pos_2, vel_2, gravity, color_2, r_2));
    
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return 0;
}

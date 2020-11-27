/*
This file simulates the movement of particles over time.
 
Author: Miguel Donado
Date: October 12, 2020
Time spent: 8 hours
Collaborators: Ariel Chung, Nic Dillon, Katie Turner
Feedback: There was a lot of self-teaching and trial and error which was fun but made
          me feel lost at certain points. For me, the hardest part was to get started
          but after that most of the document made sense. The part on finding the FPS
          and 'resetting' the particles wasn't super clear right away but that might
          be me not reading the hand out carefully.
 
*/

#include <stdio.h>

#include "Particle.hpp"
#include <vector>
w
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

// Globals
float win_width = 512;
float win_height = 512;
int avg_fps = 60; float fps = 0; int frames = 0;
float t = 0;
float delta_time;
vector<Particle*> particles;
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
    // averages out FPS for the last 30 frames
    if(frames == 30){
        avg_fps = fps/frames;
        fps = 0; frames = 0;
        std::cout << "FPS: " << avg_fps << "  Particles: " << particles.size() << "\n";
    }
}

// Drawing routine
void drawScene(void)
{
    float time_init = glutGet(GLUT_ELAPSED_TIME); //records Time Elapsed at beginning of frame
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, win_width / win_height, .1f, 500.f);
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_LINE, GL_FILL);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    for (int i = 0; i < particles.size(); i++) {
        float* curr_location = particles[i]->move();
        float* curr_color = particles[i]->get_color();
            
        glPushMatrix();
            
        // renders the particle according to its instance variables
        glColor3f(curr_color[0], curr_color[1], curr_color[2]);
        glTranslatef(curr_location[0], curr_location[1], curr_location[2]);
        gluDisk(disk, 0.0, particles[i]->get_radius(), 20, 20);
            
        glPopMatrix();
    }
    
    for(int j = 0; j < particles.size(); j++){
        for (int k = 0; k < particles.size(); k++){
            if (j == k){
                continue;
            }
            else{
                if(particles[j]->checkParticleCollision(*particles[k])) std::cout<<particles[j]->checkParticleCollision(*particles[k])<<"\n";
            }
        }
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
    t += 0.1;
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: // Escape key
        exit(0); break;
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
    
    float pos_1[3] = {-10.0f, 0.0f, 0.0f};
    float vel_1[3] = {0.3f, 0.0f, 0.0f};
    float acc_1[3] = {0.0f, -0.01f, 0.0f};
    float color_1[3] = {0, 0, 1};
    float r_1 = 0.5f;
    particles.push_back(new Particle(pos_1, vel_1, acc_1, color_1, r_1));
    
    float pos_2[3] = {10.0f, 0.0f, 0.0f};
    float vel_2[3] = {-0.3f, 0.0f, 0.0f};
    float acc_2[3] = {0.0f, -0.01f, 0.0f};
    float color_2[3] = {1, 0, 0};
    float r_2 = 0.5f;
    particles.push_back(new Particle(pos_2, vel_2, acc_2, color_2, r_2));
    
    glutDisplayFunc(drawScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}


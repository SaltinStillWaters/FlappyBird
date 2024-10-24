#include "collision.h"
#include "birdHitbox.h"
#include <GL/freeglut.h>
#include <cstdlib>
#include <iostream>
#include <deque>

//NOTE: SAMPLE CODE TO TEST HITBOXES.

void display();
void createTimer(int value);
void updateTimer(int value);
void keyBoardCheck(unsigned char key, int x, int y);

BirdHitbox birdHitbox = BirdHitbox(Dimension(0.1, 0.2, 0.1, 0.0), -0.005);
Collision collision;


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("test");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyBoardCheck);
    glutTimerFunc(0, createTimer, 0);
    glutTimerFunc(0, updateTimer, 0);
    glutMainLoop();

    return 0;
}

void keyBoardCheck(unsigned char key, int x, int y) {
    std::cout << "Key Pressed: " << key << '\n';

    birdHitbox.jump(0.08);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);

        glVertex2f(birdHitbox.dimension.xLeft, birdHitbox.dimension.yTop);
        glVertex2f(birdHitbox.dimension.xLeft, birdHitbox.dimension.yBot);
        glVertex2f(birdHitbox.dimension.xRight, birdHitbox.dimension.yBot);
        glVertex2f(birdHitbox.dimension.xRight, birdHitbox.dimension.yTop);

        
        glColor3ub(255, 255, 255);
        
        std::deque<Dimension*> pipes = collision.pipes;
        for (int x = 0; x < pipes.size(); ++x) {
            Dimension* pipe = pipes[x];

            glVertex2f(pipe->xLeft, pipe->yTop);
            glVertex2f(pipe->xLeft, pipe->yBot);
            glVertex2f(pipe->xRight, pipe->yBot);
            glVertex2f(pipe->xRight, pipe->yTop);
        }

    glEnd();
    glFlush();
}

void createTimer(int value) {
    float lowerY = (std::rand() % 101) / 100.0f;
    collision.createPipe(lowerY, 0.3);
    glutTimerFunc(3000, createTimer, 0);
}

void updateTimer(int value) {
    collision.update(birdHitbox.dimension, -0.01f);
    
    if (collision.checkCollision(birdHitbox.dimension)) {
        std::cout << "COLLISION!\n";
    }
    birdHitbox.update();
    
    glutPostRedisplay();
    glutTimerFunc(50, updateTimer, 0);
}
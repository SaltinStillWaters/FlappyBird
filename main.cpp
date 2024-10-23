#include "collision.h"
#include <GL/freeglut.h>
#include <cstdlib>
#include <iostream>
#include <deque>


void display();
void createTimer(int value);
void updateTimer(int value);

Dimension bird = Dimension(0.1, 0.2, 0.1, 0.0);
Collide collision;


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("test");
    glutDisplayFunc(display);
    glutTimerFunc(0, createTimer, 0);
    glutTimerFunc(0, updateTimer, 0);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3ub(255, 0, 0);

        glVertex2f(bird.xLeft, bird.yTop);
        glVertex2f(bird.xLeft, bird.yBot);
        glVertex2f(bird.xRight, bird.yBot);
        glVertex2f(bird.xRight, bird.yTop);

        
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
    collision.update(bird);
    
    if (collision.checkCollision(bird)) {
        std::cout << "COLLISION!\n";
    }

    glutPostRedisplay();
    glutTimerFunc(50, updateTimer, 0);
}
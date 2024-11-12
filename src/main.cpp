//this is your original main()
#include "GL/glew.h"
#include "GL/glut.h"
#include "Bird.h"
#include <iostream>

void display();
void init();
void idle();
void cleanup();
void jump(int key, int state, int x, int y);

ArrayBuffer* buffer;
Bird* bird;

int main(int argcp, char **argv) {
    glutInit(&argcp, argv);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Window");

    if (glewInit() != GLEW_OK) {
        std::cout << "Cannot initialize GLEW." << std::endl;
    }

    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMouseFunc(jump);
    glutMainLoop();
    cleanup();
    return 0;
}

void init() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    AttribFormat* attribFormat = new AttribFormat();
    attribFormat->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
    attribFormat->addAttrib<GLfloat>(4, GL_COLOR_ARRAY);

    buffer = new ArrayBuffer("bird.data", attribFormat);
    bird = new Bird(GL_QUADS, buffer);
    bird->setScale(0.15f);

    //Lalabas yung bird pag tina
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
    // glMatrixMode(GL_MODELVIEW);
    // DrawableObj::updateScreenDimens(900.0f, 900.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    bird->draw(); 
    glutSwapBuffers();
}

void idle() {
    bird->update(); 
    glutPostRedisplay();
}

void jump(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bird->jump();
    }
}

void cleanup() {
    delete buffer;
    delete bird;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
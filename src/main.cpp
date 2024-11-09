#include "GL/glew.h"
#include "GL/glut.h"

#include "DrawableObj.h"

#include <iostream>

void display();
void init();
void idle();
void cleanup();

ArrayBuffer *buffer;
IndexBuffer *ibuffer;
DrawableObj *obj;
AttribFormat *attribFormat;

GLfloat rotate = 0.f;

int main(int argcp, char **argv) {
    glutInit(&argcp, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Window");

    if (glewInit() != GLEW_OK) {
        std::cout << "Cannot initialize GLEW." << std::endl;
    }

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    cleanup();
    return 0;
}

void init() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    attribFormat = new AttribFormat();
    attribFormat->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
    attribFormat->addAttrib<GLubyte>(3, GL_COLOR_ARRAY);

    buffer = new ArrayBuffer("vertices.data", attribFormat);
    ibuffer = new IndexBuffer("indices.data");

    obj = new DrawableObj(GL_QUADS, buffer, ibuffer);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    obj->draw();

    glFlush();
}

void idle() {
    obj->setRotation(rotate);
    rotate += rotate >= 360.f ? -rotate : 1.f;
    Sleep(1000 / 60);
    glutPostRedisplay();
}

void cleanup() {
    delete buffer;
    delete ibuffer;
    delete obj;
    delete attribFormat;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
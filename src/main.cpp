#include "GL/glew.h"
#include "GL/glut.h"

#include "DrawableObj.h"

#include <iostream>

void display();
void init();
void idle();
void reshape(int width, int height);
void cleanup();

ArrayBuffer *buffer;
ArrayBuffer *buffer2;
IndexBuffer *ibuffer;
DrawableObj *obj;
DrawableObj *bg;
AttribFormat *attribFormat;
AttribFormat *attribFormat2;

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
    glutReshapeFunc(reshape);
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

    attribFormat2 = new AttribFormat();
    attribFormat2->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);

    buffer = new ArrayBuffer("vertices.data", attribFormat);
    ibuffer = new IndexBuffer("indices.data");
    buffer2 = new ArrayBuffer("bg.data", attribFormat2);

    obj = new DrawableObj(GL_QUADS, buffer, ibuffer, true);
    bg = new DrawableObj(GL_QUADS, buffer2);
    bg->setPlainColor(ColorUByte({128, 0, 128, 255}));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    bg->draw();
    obj->draw();

    glFlush();
}

void idle() {
    obj->setRotation(rotate);
    rotate += rotate >= 360.f ? -rotate : 1.f;
    Sleep(1000 / 60);
    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    DrawableObj::updateScreenDimens(width, height);
}

void cleanup() {
    delete buffer;
    delete buffer2;
    delete ibuffer;
    delete obj;
    delete attribFormat;
    delete attribFormat2;
    delete bg;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
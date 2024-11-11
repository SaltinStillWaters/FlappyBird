#include "GL/glew.h"
#include "GL/glut.h"

#include "DrawableObj.h"

#include <iostream>

void display();
void init();
void idle();
void cleanup();
void jump(int key, int state, int x, int y);

ArrayBuffer *buffer;
IndexBuffer *ibuffer;
DrawableObj *obj;
AttribFormat *attribFormat;

GLfloat rotate = 0.f;
GLfloat yOffSet = 0.f; 
GLfloat fly = 0.f;
bool isFlying = false;
const GLfloat MAX_FLIGHT_HEIGHT = 1.85f;
const GLfloat MIN_FLIGHT_HEIGHT = -0.95f;
const GLfloat GRAVITY = 9.81f;


int main(int argcp, char **argv) {
    glutInit(&argcp, argv);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Window");

    if (glewInit() != GLEW_OK) {
        std::cout << "Cannot initialize GLEW." << std::endl;
    }

    init();
    //glutFullScreen(); 
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

    attribFormat = new AttribFormat();
    attribFormat->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
    attribFormat->addAttrib<GLfloat>(4, GL_COLOR_ARRAY);

    buffer = new ArrayBuffer("bird.data", attribFormat);
    // ibuffer = new IndexBuffer("indices.data");

    obj = new DrawableObj(GL_QUADS, buffer);
    obj->setScale(0.15f, 0.15f);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    obj->draw();

    glFlush();
}

void idle() {
    obj->setRotation(rotate);
    obj->setOffset(-0.5, yOffSet);

    if (fly >= 0.35f) {
            isFlying = false;
            fly = 0;
    }

    if (isFlying) {
        if(yOffSet < MAX_FLIGHT_HEIGHT -1.0f){
            rotate += rotate >= 45.f ? 0 : 3.f;
            yOffSet += 0.0015f * GRAVITY;
        }
        fly += 0.01f;
    } else {                       
        if(yOffSet > MIN_FLIGHT_HEIGHT){
            Sleep(1000 / 60);
            rotate -= rotate <= -45.f ? 0 : 3.f;
            yOffSet -= 0.005 * GRAVITY;
        }
    }
    
    Sleep(1000 / 60);
    glutPostRedisplay();
}



void jump(int key, int state, int x, int y){
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
        isFlying = true;
    }
}


void cleanup() {
    delete buffer;
    //delete ibuffer;
    delete obj;
    delete attribFormat;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Resettable.h"
#include "Bird.h"
#include "Pipes.h"
#include "DrawableObj.h"
#include "Pipes.h"
#include "SkyHelpers.h"
#include "GameController.h"

#include <iostream>


DrawableObj *sky;
Pipes* pipes;
Bird* bird;
GameController* controller;
DrawableObj *sunAndMoon;

void display();
void init();
void idle();
void reshape(int width, int height);
void scroll(int button, int dir, int x, int y);
void jump(int key, int state, int x, int y);
void cleanup();
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam);

int main(int argcp, char **argv) {
    // Reference for sound. Don't delete yet ty
    // LPCWSTR str = L"C:\\Users\\Salti\\Downloads\\bg.wav";
    // PlaySoundW(str, 0, SND_FILENAME | SND_ASYNC);

    glutInit(&argcp, argv);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Window");

    if (glewInit() != GLEW_OK) {
        std::cout << "Cannot initialize GLEW." << std::endl;
    }

    glDebugMessageCallback(MessageCallback, 0);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseWheelFunc(scroll);
    glutIdleFunc(idle);
    glutMouseFunc(jump);

    glutMainLoop();

    cleanup();
    return 0;
}

void init() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    DrawableObj::type("square", GL_QUADS, "vertices.data",
                      &DrawableObj::formatVertexColor);
    DrawableObj::type("sky", GL_QUADS, "skyVertices.data",
                      &DrawableObj::formatVertexColor, false);
    DrawableObj::type("sunAndMoon", GL_QUADS, "sunAndMoon.data",
                      &DrawableObj::formatVertexColor);

    sky = DrawableObj::create("sky");
    sunAndMoon = DrawableObj::create("sunAndMoon");

    controller = GameController::getInstance();

    bird = Bird::getInstance("bird.data", controller);
    controller->addResettable(bird);

    pipes = Pipes::getInstance(controller, bird->getHitbox(), 
                               "topPipe.data", "botPipe.data",
                               -0.015f, 1.f);
    controller->addResettable (pipes);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    sky->draw();
    sunAndMoon->draw();
    pipes->draw();
    bird->draw();
    
    glFlush();
}

void idle() {
    bird->update();
    pipes->update();

    Sleep(1000 / 60);
    glutPostRedisplay();
}

void reshape(int width, int height) {
    GLfloat w = width;
    GLfloat h = height;

    if (w / h > 16.f / 9.f)
        w = h * 16.f / 9.f;
    else if (w / h < 16.f / 9.f)
        h = w * 9.f / 16.f;

    glViewport(((GLfloat)width - w) / 2.f, ((GLfloat)height - h) / 2.f, w, h);
    DrawableObj::updateScreenDimens(w, h);
}


void scroll(int button, int dir, int x, int y) {
    updateSkyColors(sky->getVertexBuffer());
}

void jump(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bird->jump();
        controller->clickHandler();
    }
}


void cleanup() {
    delete sky;
    delete bird;
    delete sunAndMoon;
    delete pipes;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
}

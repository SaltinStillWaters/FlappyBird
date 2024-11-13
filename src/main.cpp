#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

#include "Pipes.h"
#include "DrawableObj.h"
#include "SkyHelpers.h"
#include "GameController.h"

DrawableObj *sky;
Pipes* pipes;
GameController* controller;

void display();
void init();
void idle();
void reshape(int width, int height);
void scroll(int button, int dir, int x, int y);
void cleanup();
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam);

int main(int argcp, char **argv) {
    // LPCWSTR str = L"C:\\Users\\Salti\\Downloads\\bg.wav";
    // PlaySoundW(str, 0, SND_FILENAME | SND_ASYNC);

    glutInit(&argcp, argv);
    glutInitWindowSize(400, 400);
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

    controller = GameController::getInstance();
    pipes = Pipes::getInstance(controller, "topPipe.data", "botPipe.data", -0.01);
    sky = DrawableObj::create("sky");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    sky->draw();
    pipes->draw();

    glFlush();
}

void idle() {
    pipes->createPipe();
    pipes->updatePipes();
    pipes->checkCollision();
    
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
    glViewport(((GLfloat) width - w) / 2.f, ((GLfloat) height - h) / 2.f, w, h);
    DrawableObj::updateScreenDimens(w, h);
}

void scroll(int button, int dir, int x, int y) {
    updateSkyColors(sky->getVertexBuffer());
}

void cleanup() {
    delete sky;
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
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Bird.h"
#include "Pipes.h"
#include "SkyHelpers.h"
#include <iostream>

DrawableObj *sky;
DrawableObj *box;
DrawableObj *box2;
Pipes* pipes;
Bird* bird;

GLfloat rotate = 0.f;
ArrayBuffer* buffer;

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


void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
    fprintf(stderr,
            "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
            severity, message);
}


void init() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    DrawableObj::type("square", GL_QUADS, "vertices.data", &DrawableObj::formatVertexColor);
    DrawableObj::type("sky", GL_QUADS, "skyVertices.data", &DrawableObj::formatVertexColor, false);

    pipes = new Pipes("topPipe.data", "botPipe.data", -0.01f);
    pipes->createPipe();
    
    box = DrawableObj::create("square");
    box2 = DrawableObj::create("square");
    sky = DrawableObj::create("sky");
    box2->setScale(0.5);
    box2->setOffset(0.5, 0.5);

    bird = new Bird("bird2.data");
    bird->setSize(0.15f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    sky->draw();
    box->draw();
    box2->draw();
    pipes->draw();
    bird->draw();
    //bird->draw();
    glutSwapBuffers();
}

void idle() {
    pipes->createPipe();
    pipes->updatePipes();
    pipes->checkCollision();

    rotate += 1.f;
    if (rotate >= 360.f)
        rotate = 0.f;

    box->setRotation(rotate);
    box2->setRotation(rotate);

    bird->update();

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

void jump(int key, int state, int x, int y) {
    if (key == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bird->jump();
    }
}


void cleanup() {
    delete sky;
    delete box;
    delete box2;
    delete pipes;
    delete bird;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

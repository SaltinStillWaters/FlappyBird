#include <GL/glew.h>

#include <GL/freeglut.h>
#include <iostream>

#include "DrawableObj.h"
#include "Pipes.h"
#include "SkyHelpers.h"

std::vector<std::pair<DrawableObj *, GLfloat>> stars;
DrawableObj *sky;
DrawableObj *sunAndMoon;
Pipes *pipes;

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

    DrawableObj::type("sky", GL_QUADS, "skyVertices.data",
                      &DrawableObj::formatVertexColor, false);
    DrawableObj::type("sunAndMoon", GL_QUADS, "sunAndMoon.data",
                      &DrawableObj::formatVertexColor);
    DrawableObj::type("star", GL_POLYGON, "star.data",
                      &DrawableObj::formatVertexColor);

    // Generating stars with random positions.
    srand(time(0));
    for (int i = 0; i < STAR_COUNT; i++) {
        GLfloat x = (rand() % 100) / 50.f - 1.f;
        GLfloat y = (rand() % 100) / 50.f - 1.f;
        GLfloat starScale = (rand() % 100) / 200.f;
        stars.push_back({DrawableObj::create("star"), starScale});
        stars[i].first->setOffset(x, y);
        stars[i].first->setScale(0.f);
    }

    sky = DrawableObj::create("sky");
    sunAndMoon = DrawableObj::create("sunAndMoon");
    sunAndMoon->setOffset(0.f, -1.5f);
    sunAndMoon->setScale(1.25f);

    pipes = new Pipes("topPipe.data", "botPipe.data", -0.01);
    pipes->createPipe();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    sky->draw();

    for (const std::pair<DrawableObj *, GLfloat> &star : stars)
        star.first->draw();

    sunAndMoon->draw();

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
    glViewport(((GLfloat)width - w) / 2.f, ((GLfloat)height - h) / 2.f, w, h);
    DrawableObj::updateScreenDimens(w, h);
}

void scroll(int button, int dir, int x, int y) {
    scrollCounter = ((scrollCounter + dir * 1) % ((GLint)SKY_CHANGE_DURATION) +
                     ((GLint)SKY_CHANGE_DURATION)) %
                    ((GLint)SKY_CHANGE_DURATION);

    updateSky(sky->getVertexBuffer(), dir);
    sunAndMoon->setRotation(celestialRotation);
    sunAndMoon->setScale(celestialScale);

    for (const std::pair<DrawableObj *, GLfloat> &star : stars) {
        star.first->setScale(star.second * starMult);
    }
}

void cleanup() {
    delete sky;
    delete sunAndMoon;
    delete pipes;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
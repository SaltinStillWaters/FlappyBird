// #include <GL/glew.h>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// using namespace std;

// int main() {
//     string line;
//     ifstream in("data/sunAndMoon.data");
//     ofstream out("data/sunAndMoonFinal.data");
//     out << fixed;
//     GLfloat a;
//     while(getline(in, line)) {
//         stringstream ss(line);
//         ss >> a;
//         out << (a * 3.f / 4.f) << ' ';
//         ss >> a;
//         out << (a * 3.f / 4.f) - 1.5 << ' ';
//         ss >> a;
//         out << (int) a << ' ';
//         ss >> a;
//         out << (int) a << ' ';
//         ss >> a;
//         out << (int) a << '\n';
//     }
// }

#include <GL/glew.h>

#include <GL/freeglut.h>
#include <iostream>

#include "DrawableObj.h"
#include "Pipes.h"
#include "SkyHelpers.h"

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

    DrawableObj::type("square", GL_QUADS, "vertices.data",
                      &DrawableObj::formatVertexColor);
    DrawableObj::type("sky", GL_QUADS, "skyVertices.data",
                      &DrawableObj::formatVertexColor, false);
    DrawableObj::type("sunAndMoon", GL_QUADS, "sunAndMoonFinal.data",
                      &DrawableObj::formatVertexColor);

    sky = DrawableObj::create("sky");
    sunAndMoon = DrawableObj::create("sunAndMoon");
    sunAndMoon->setOffset(0.f, -1.5f);

    pipes = new Pipes("topPipe.data", "botPipe.data", -0.01);
    pipes->createPipe();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    sky->draw();
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
    updateSkyColors(sky->getVertexBuffer());
    celestialRotation += fmodf(SUN_MOON_CHANGE_DEG, 360);
    sunAndMoon->setRotation(celestialRotation);
    
    celestialScale += celestialCoefficient * SUN_MOON_SCALE_DELTA;
    sunAndMoon->setScale(celestialScale);
}

void cleanup() {
    delete sky;
    delete sunAndMoon;
    delete pipes;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
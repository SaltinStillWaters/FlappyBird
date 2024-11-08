#include "GL/glew.h"
#include "GL/freeglut.h"
#include "BufferObj.h"
#include "ArrayBuffer.h"
#include <iostream>

void display();
void init();

int main(int argcp, char** argv) {
    glutInit(&argcp, argv);
    glutCreateWindow("Window");

    if(glewInit() != GLEW_OK) {
        std::cout << "Error iniitalizing glew";
    }

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

unsigned int vao;

void init() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    ArrayBuffer birdBuffer("data/test.txt", GL_STATIC_DRAW);
    birdBuffer.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);
    birdBuffer.unbind();

    /*
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    BufferObj birdBuffer(vertices, sizeof(vertices), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    birdBuffer.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);
    birdBuffer.unbind();
    */
}

void display() {
    std::cout << "Hello World";
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}
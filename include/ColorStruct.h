#ifndef COLORSTRUCT_H
#define COLORSTRUCT_H

#include <GL/glew.h>

struct ColorUByte {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a;
};

struct ColorFloat {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif
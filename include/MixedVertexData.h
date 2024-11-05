#ifndef MIXEDVERTEXDATA_H
#define MIXEDVERTEXDATA_H

#include <GL/glew.h>

struct MixedVertexData {
    GLfloat x, y; // Vertex pos
    GLubyte r, g, b, a; // Vertex colors
};

#endif
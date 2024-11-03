#ifndef ATTRIBFORMAT_H
#define ATTRIBFORMAT_H

#include <GL/glew.h>
#include <vector>

struct Attrib {
    GLint count;
    GLenum type;
    GLboolean normalized;
    GLsizei size;
};

class AttribFormat {
  protected:
    GLsizei stride = 0;
    std::vector<Attrib> attribs;

  public:
    template <typename T> void addAttrib(GLint count) { static_assert(false); }
    void removeAttrib(unsigned int index);
    GLsizei getStride();
    std::vector<Attrib> getAttribs();
};

template <> inline void AttribFormat::addAttrib<GLfloat>(GLint count) {
    stride += count * sizeof(GLfloat);
    attribs.push_back({count, GL_FLOAT, GL_FALSE, sizeof(GLfloat)});
}

template <> inline void AttribFormat::addAttrib<GLubyte>(GLint count) {
    stride += count * sizeof(GLfloat);
    attribs.push_back({count, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLubyte)});
}

#endif
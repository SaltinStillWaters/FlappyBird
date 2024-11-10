#ifndef ATTRIBFORMAT_H
#define ATTRIBFORMAT_H

#include <GL/glew.h>
#include <stdexcept>
#include <unordered_map>
#include <vector>

struct Attrib {
    GLint count;
    GLenum type;
    GLboolean normalized;
    GLsizei size;
    GLsizei offset;
};

class AttribFormat {
  protected:
    GLsizei stride = 0;
    std::unordered_map<GLenum, Attrib> attribs;
    std::vector<GLenum> attribsOrdered;

  public:
    template <typename T> void addAttrib(GLint count, GLenum attribName) {
        throw std::runtime_error("Attrib type not supported.");
    }
    GLsizei getStride() const;
    Attrib getAttribute(GLenum attribName);
    bool enabledAttribute(GLenum attribName) const;
    std::vector<GLenum> getAttributeOrder();
};

template <>
inline void AttribFormat::addAttrib<GLfloat>(GLint count, GLenum attribName) {
    attribs[attribName] = {count, GL_FLOAT, GL_FALSE, sizeof(GLfloat), stride};
    attribsOrdered.push_back(attribName);
    stride += count * sizeof(GLfloat);
}

template <>
inline void AttribFormat::addAttrib<GLubyte>(GLint count, GLenum attribName) {
    attribs[attribName] = {count, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(GLubyte),
                           stride};
    attribsOrdered.push_back(attribName);
    stride += count * sizeof(GLubyte);
}

#endif
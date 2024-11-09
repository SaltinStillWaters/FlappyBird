#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include <string>

#include "AttribFormat.h"
#include "BufferObj.h"

class ArrayBuffer : public BufferObj {
  protected:
    AttribFormat *format;

  public:
    ArrayBuffer(const std::string &filename, AttribFormat *format,
                GLenum usage = GL_STATIC_DRAW);
    ArrayBuffer(const void *data, GLsizeiptr size, GLuint count, GLenum usage)
        : BufferObj(data, size, GL_ARRAY_BUFFER, count, usage) {}
    AttribFormat *getFormat();
};

#endif
#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include "BufferObj.h"

class ArrayBuffer : public BufferObj {
  public:
    ArrayBuffer(const void *data, GLsizeiptr size,
                GLenum usage = GL_STATIC_DRAW)
        : BufferObj(data, size, GL_ARRAY_BUFFER, usage) {}
};

#endif
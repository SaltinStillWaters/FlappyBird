#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "BufferObj.h"

class IndexBuffer : public BufferObj {
  public:
    IndexBuffer(const void *data, GLsizeiptr size,
                GLenum usage = GL_STATIC_DRAW)
        : BufferObj(data, size, GL_ELEMENT_ARRAY_BUFFER, usage) {}
};

#endif
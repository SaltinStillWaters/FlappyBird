#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <string>

#include "BufferObj.h"

class IndexBuffer : public BufferObj {
  public:
    IndexBuffer(std::string filename, GLenum usage = GL_STATIC_DRAW);
};

#endif
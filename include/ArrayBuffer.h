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
    AttribFormat *getFormat();
};

#endif
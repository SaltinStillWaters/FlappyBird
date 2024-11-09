#ifndef BUFFEROBJ_H
#define BUFFEROBJ_H

#include <GL/glew.h>

class BufferObj {
  protected:
    GLuint id;
    GLenum target;
    GLenum usage;
    GLuint count = 0;

  public:
    BufferObj(GLenum target, GLenum usage);
    ~BufferObj();
    GLuint getCount() const;
    void bind() const;
    void unbind() const;
};

#endif
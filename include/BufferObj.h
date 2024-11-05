#ifndef BUFFEROBJ_H
#define BUFFEROBJ_H

#include <GL/glew.h>

class BufferObj {
    protected:
        GLuint id;
        GLenum target;
    public:
        BufferObj(const void *data, GLsizeiptr size, GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
        ~BufferObj();
        void bind() const;
        void unbind() const;
};

#endif
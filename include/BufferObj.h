#ifndef BUFFEROBJ_H
#define BUFFEROBJ_H

#include <GL/glew.h>

class BufferObj {
    protected:
        GLuint id;
        GLenum target;
        GLenum usage;
    public:
        BufferObj(GLenum target, GLenum usage);
        BufferObj(const void *data, GLsizeiptr size, GLenum target, GLenum usage);
        ~BufferObj();
        void bind() const;
        void unbind() const;
};

#endif
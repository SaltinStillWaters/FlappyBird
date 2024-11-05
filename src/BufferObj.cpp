#include <GL/glew.h>

#include "BufferObj.h"

BufferObj::BufferObj(GLenum target, GLenum usage)
{
    BufferObj::target = target;
    BufferObj::usage = usage;
    glGenBuffers(1, &id);
}

BufferObj::BufferObj(const void *data, GLsizeiptr size, GLenum target,
                     GLenum usage)
{
    BufferObj::target = target;
    BufferObj::usage = usage;
    glGenBuffers(1, &id);
    glBindBuffer(BufferObj::target, id);
    glBufferData(BufferObj::target, size, data, usage);
}

BufferObj::~BufferObj() { glDeleteBuffers(1, &id); }

void BufferObj::bind() const { glBindBuffer(target, id); }

void BufferObj::unbind() const { glBindBuffer(target, 0); }

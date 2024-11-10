#include "BufferObj.h"

BufferObj::BufferObj(GLenum target, GLenum usage) {
    BufferObj::target = target;
    BufferObj::usage = usage;
    glGenBuffers(1, &id);
}

BufferObj::~BufferObj() { glDeleteBuffers(1, &id); }

GLuint BufferObj::getCount() const { return count; }

void BufferObj::bind() const { glBindBuffer(target, id); }

void BufferObj::unbind() const { glBindBuffer(target, 0); }

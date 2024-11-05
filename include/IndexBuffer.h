#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <string>

#include "BufferObj.h"

// TODO:
// Read indices from a file. Using vectors and vector.data(), you can get the array equivalent of the array
// Implementation for overloaded constructor for filenames.
// indexCount must be updated.

class IndexBuffer : public BufferObj {
    protected:
        GLsizei indexCount = 0;
    public:
        IndexBuffer(const void *data, GLsizeiptr size,
                    GLenum usage)
            : BufferObj(data, size, GL_ELEMENT_ARRAY_BUFFER, usage) {}
        IndexBuffer(std::string filename, GLenum usage = GL_STATIC_DRAW);
        GLsizei getIndexCount();
};

#endif
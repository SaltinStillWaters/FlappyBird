#ifndef ARRAYBUFFER_H
#define ARRAYBUFFER_H

#include <string>

#include "BufferObj.h"

// TODO:
// Read vertex data from a file. Using vectors and vector.data(), you can get the array equivalent of the array
// Check if vertex data from file is mixed (position & color) [can be possible by counting no. of spaces?]
// Implementation for overloaded constructor for filenames.
// If mixed, use the struct MixedVertexData as the data type for the vector.
// NOTE: If struct is not contiguous, a VertexArrayObj::setAsMixedVertexData() can be used on a VAO for proper mapping.

class ArrayBuffer : public BufferObj {
    public:
        ArrayBuffer(const void *data, GLsizeiptr size,
                    GLenum usage)
            : BufferObj(data, size, GL_ARRAY_BUFFER, usage) {}
        ArrayBuffer(std::string filename, GLenum usage = GL_STATIC_DRAW);
};

#endif
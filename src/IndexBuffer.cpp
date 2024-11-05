#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::string filename, GLenum usage)
    : BufferObj(GL_ELEMENT_ARRAY_BUFFER, usage) {
        
}

GLsizei IndexBuffer::getIndexCount() { return indexCount; }
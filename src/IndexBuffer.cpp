#include <fstream>
#include <iostream>
#include <vector>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::string filename, GLenum usage)
    : BufferObj(GL_ELEMENT_ARRAY_BUFFER, usage) {
    std::ifstream fileReader;
    fileReader.open("data/" + filename);
    if (!fileReader)
        throw std::runtime_error("Vertex file not found");

    std::vector<GLuint> bufferData;
    GLuint input;

    while (fileReader >> input) {
        bufferData.push_back(input);
    }

    count = bufferData.size();
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint),
                 bufferData.data(), usage);
}
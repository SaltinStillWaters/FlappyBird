#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "ArrayBuffer.h"

ArrayBuffer::ArrayBuffer(const std::string &filename, AttribFormat *format,
                         GLenum usage)
    : BufferObj(GL_ARRAY_BUFFER, usage) {

    ArrayBuffer::format = format;

    std::ifstream fileReader;
    fileReader.open("data/" + filename);
    if (!fileReader)
        throw std::runtime_error("Vertex file not found");

    std::vector<uint8_t> bufferData;
    std::string line;
    std::stringstream vertexStream;
    std::vector<GLenum> attribs = format->getAttributeOrder();

    while (getline(fileReader, line)) {
        vertexStream << line;
        GLuint offset = 0;
        uint8_t arr[format->getStride()] = {0};

        for (GLenum attribName : attribs) {
            Attrib attrib = format->getAttribute(attribName);
            for (GLint i = 0; i < attrib.count; i++) {
                if (attrib.type == GL_FLOAT) {
                    GLfloat input;
                    vertexStream >> input;
                    memcpy(arr + offset, &input, sizeof(GLfloat));
                } else if (attrib.type == GL_UNSIGNED_BYTE) {
                    GLint temp;
                    vertexStream >> temp;
                    GLubyte input = (GLubyte)temp;
                    memcpy(arr + offset, &input, sizeof(GLubyte));
                } else
                    std::runtime_error("Unsupported type.");
                offset += attrib.size;
            }
        }
        bufferData.insert(bufferData.end(), arr, arr + format->getStride());
        vertexStream.clear();
        count++;
    }

    bind();
    glBufferData(GL_ARRAY_BUFFER, bufferData.size(), bufferData.data(), usage);
}

AttribFormat *ArrayBuffer::getFormat() { return format; }
#include "VertexArrayObj.h"
#include "AttribFormat.h"

#include <vector>

VertexArrayObj::VertexArrayObj() { glGenVertexArrays(1, &id); }

VertexArrayObj::~VertexArrayObj() { glDeleteVertexArrays(1, &id); }

void VertexArrayObj::bind() const { glBindVertexArray(id); }

void VertexArrayObj::unbind() const { glBindVertexArray(0); }

void VertexArrayObj::setAttribFormats(AttribFormat format) {
    bind();
    std::vector<Attrib> attribs = format.getAttribs();
    GLuint offset = 0;
    for (GLuint i = 0; i < attribs.size(); i++) {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, attribs[i].count, attribs[i].type,
                              attribs[i].normalized, format.getStride(),
                              (const void *) offset);
        offset += attribs[i].count * attribs[i].size;
    }
}

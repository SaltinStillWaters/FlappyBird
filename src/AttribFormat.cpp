#include "AttribFormat.h"
#include <typeinfo>

void AttribFormat::removeAttrib(unsigned int index) {
    if (index >= attribs.size())
        return;
    stride -= attribs[index].count * attribs[index].size;
    attribs.erase(attribs.begin() + index);
}

GLsizei AttribFormat::getStride() { return stride; }

std::vector<Attrib> AttribFormat::getAttribs() { return attribs; }

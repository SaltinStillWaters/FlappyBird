#include <stdexcept>

#include "AttribFormat.h"

GLsizei AttribFormat::getStride() const { return stride; }

Attrib AttribFormat::getAttribute(GLenum attribName) {
    if (enabledAttribute(attribName))
        return attribs[attribName];
    throw std::runtime_error("Attribute name (" + std::to_string(attribName) +
                             ") not found");
}

bool AttribFormat::enabledAttribute(GLenum attribName) const {
    return attribs.find(attribName) != attribs.end();
}

std::vector<GLenum> AttribFormat::getAttributeOrder() { return attribsOrdered; }

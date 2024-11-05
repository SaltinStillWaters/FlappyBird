#ifndef VERTEXARRAYOBJ_H
#define VERTEXARRAYOBJ_H

#include <GL/glew.h>
#include "AttribFormat.h"

class VertexArrayObj {
    protected:
        GLuint id;
    public:
        VertexArrayObj();
        ~VertexArrayObj();
        void bind() const;
        void unbind() const;
        void setAttribFormats(AttribFormat format);
        void setAsMixedVertexData();
};

#endif
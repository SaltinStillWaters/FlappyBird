#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H

#include <string>
#include <GL/glew.h>

#include "Shader.h"
#include "ArrayBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObj.h"

// NOTES:
// Shaders and VAOs will STILL be used outside of this class. This class only
// attempts to hide ArrayBuffers.
// The code in main function will declare its own VAOs and shaders that are considered defaults.


// Use this struct to get input
struct MixedVertexData {
    GLfloat x, y; // Vertex pos
    GLubyte r, g, b, a; // Vertex colors
};

class DrawableObj {
    protected:
        GLfloat rotation = 0.f;
        GLfloat scale = 0.f;
        GLfloat xOffset = 0.f;
        GLfloat yOffset = 0.f;
        GLsizei vertexCount = 0;
        ArrayBuffer *vertexBuffer;

        // Not required:
        IndexBuffer *indexBuffer;
        Shader *shader;
        VertexArrayObj *vao;

        // TODO:
        // CollisionObj *collisionData;

    public:
        // setVertexBuffer automatically.
        DrawableObj(ArrayBuffer *vertexBuffer);
        
        // NOTE: Do NOT delete pointer data. These may be used by other DrawableObjs.
        ~DrawableObj();
        
        // Do NOT construct ArrayBuffer here. ArrayBuffer must already be an object.
        // Will only link ArrayBuffer address.
        void setVertexBuffer(ArrayBuffer *vertexBuffer);

        // Do NOT construct IndexBuffer here. IndexBuffer must already be an object.
        // Will only link IndexBuffer address.
        void setIndexBuffer(IndexBuffer *indexBuffer);

        // Do NOT construct shader here. Shader must already be an object.
        // Will only link shader address.
        void setShader(Shader *shader);
        
        // Do NOT construct VertexArrayObj here. VertexArrayObj must already be an object.
        // Will only link VertexArrayObj address.
        void setVAO(VertexArrayObj *vao);
        
        // TODO:
        // Check if IndexBuffer, VAO and/or Shader is nullptr.
        // Apply IndexBuffer/Shader/VAO if not null.
        // Reapply previous shader if object-specific shader was applied.
        // Reapply using glGetIntegerv(GL_CURRENT_PROGRAM, &currentShaderProgram)
        // Reapply previous VAO if object-specific VAO was applied.
        // Reapply using glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO)
        // Apply transformation and rotation if applicable.
        void draw();

};

#endif
#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H

#include "ArrayBuffer.h"
#include "ColorStruct.h"
#include "IndexBuffer.h"

class DrawableObj {
  protected:
    static GLfloat screenWidth;
    static GLfloat screenHeight;
    GLfloat rotation = 0.f;
    GLfloat xScale = 1.f;
    GLfloat yScale = 1.f;
    GLfloat xOffset = 0.f;
    GLfloat yOffset = 0.f;
    GLsizei vertexCount = 0;
    ArrayBuffer *vertexBuffer = nullptr;
    IndexBuffer *indexBuffer = nullptr;
    ColorFloat plainColor = {0.f, 0.f, 0.f, 0.f};
    GLenum drawMode;
    bool fixedScale = false;
    bool plainColored = false;

    // TODO:
    // CollisionObj *collisionData;

  public:
    DrawableObj(GLenum drawMode, ArrayBuffer *vertices, bool fixed = false);
    DrawableObj(GLenum drawMode, ArrayBuffer *vertices, IndexBuffer *indices,
                bool fixed = false);
    ~DrawableObj();
    void setIndexBuffer(IndexBuffer *indices);
    void removeIndexBuffer();
    void setPlainColor(ColorUByte color);
    void setPlainColor(ColorFloat color);
    void removePlainColor();
    void setOffset(GLfloat x, GLfloat y);
    void setRotation(GLfloat angle);
    void setScale(GLfloat xScale, GLfloat yScale);
    void setFixed();
    void setUnfixed();
    static void updateScreenDimens(GLfloat width, GLfloat height);
    void draw();
};

#endif
#ifndef DRAWABLEOBJ_H
#define DRAWABLEOBJ_H

#include "ArrayBuffer.h"
#include "ColorStruct.h"
#include "IndexBuffer.h"

class DrawableObj {
  protected:
    struct DrawableObjTemplate;
    static std::unordered_map<std::string, DrawableObjTemplate> typeTemplates;

    static GLfloat screenWidth;
    static GLfloat screenHeight;
    GLfloat rotation = 0.f;
    GLfloat scale = 1.f;
    GLfloat xOffset = 0.f;
    GLfloat yOffset = 0.f;

  public:
    ArrayBuffer *vertexBuffer = nullptr;

  protected:
    IndexBuffer *indexBuffer = nullptr;
    ColorFloat plainColor = {0.f, 0.f, 0.f, 0.f};
    GLenum drawMode;
    bool normalizedCoords = true;
    bool plainColored = false;
    DrawableObj(GLenum drawMode, ArrayBuffer *vertices, IndexBuffer *indices,
                bool normalized = true);

  private:
    static bool initialized;
    class DrawableObjInit {
      public:
        DrawableObjInit() { DrawableObj::init(); }
        ~DrawableObjInit() { DrawableObj::cleanup(); }
    };
    static DrawableObjInit initDrawableObj;

  public:
    static AttribFormat formatVertexOnly;
    static AttribFormat formatVertexColor;
    static void init();
    static void cleanup();
    static void type(std::string name, GLenum drawMode,
                     std::string vertexFilename, AttribFormat *attribFormat,
                     bool normalizedCoords = true,
                     GLenum vertexUsage = GL_STATIC_DRAW);
    static void type(std::string name, GLenum drawMode,
                     std::string vertexFilename, AttribFormat *attribFormat,
                     std::string indexFilename, bool normalizedCoords = true,
                     GLenum vertexUsage = GL_STATIC_DRAW,
                     GLenum indexUsage = GL_STATIC_DRAW);
    static DrawableObj *create(std::string name);
    static void updateScreenDimens(GLfloat width, GLfloat height);
    void setIndexBuffer(IndexBuffer *indices);
    void removeIndexBuffer();
    void setPlainColor(ColorUByte color);
    void setPlainColor(ColorFloat color);
    void removePlainColor();
    void setOffset(GLfloat x, GLfloat y);
    void setRotation(GLfloat angle);
    void setScale(GLfloat scale);
    GLfloat getXOffset();
    GLfloat getYOffset();
    void setFixed();
    void setUnfixed();
    void draw();
};

#endif
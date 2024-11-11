#include "DrawableObj.h"
#include <iostream>

struct DrawableObj::DrawableObjTemplate {
    ArrayBuffer *vertices;
    IndexBuffer *indices;
    GLenum drawMode;
    bool normalizedCoords = true;
};

std::unordered_map<std::string, DrawableObj::DrawableObjTemplate>
    DrawableObj::typeTemplates;

GLfloat DrawableObj::screenWidth;
GLfloat DrawableObj::screenHeight;

bool DrawableObj::initialized = false;

AttribFormat DrawableObj::formatVertexOnly;
AttribFormat DrawableObj::formatVertexColor;

DrawableObj::DrawableObjInit DrawableObj::initDrawableObj;

DrawableObj::DrawableObj(GLenum drawMode, ArrayBuffer *vertices,
                         IndexBuffer *indices, bool normalized) {
    DrawableObj::drawMode = drawMode;
    vertexBuffer = vertices;
    indexBuffer = indices;
    normalizedCoords = normalized;
}

void DrawableObj::init() {
    if (!initialized) {
        DrawableObj::formatVertexColor.addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
        DrawableObj::formatVertexColor.addAttrib<GLubyte>(3, GL_COLOR_ARRAY);
        DrawableObj::formatVertexOnly.addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
        DrawableObj::initialized = true;
    }
}

void DrawableObj::cleanup() {
    for (auto &element : DrawableObj::typeTemplates) {
        std::cout << "Deleting " << element.first << '\n';
        delete element.second.vertices;
        element.second.vertices = nullptr;
        delete element.second.indices;
        element.second.indices = nullptr;
    }
}

void DrawableObj::type(std::string name, GLenum drawMode,
                       std::string vertexFilename, AttribFormat *attribFormat,
                       bool normalizedCoords, GLenum vertexUsage) {
    DrawableObj::typeTemplates[name] = {
        new ArrayBuffer(vertexFilename, attribFormat, vertexUsage), nullptr,
        drawMode, normalizedCoords};
}

void DrawableObj::type(std::string name, GLenum drawMode,
                       std::string vertexFilename, AttribFormat *attribFormat,
                       std::string indexFilename, bool normalizedCoords,
                       GLenum vertexUsage, GLenum indexUsage) {
    DrawableObj::typeTemplates[name] = {
        new ArrayBuffer(vertexFilename, attribFormat, vertexUsage),
        new IndexBuffer(indexFilename, indexUsage), drawMode, normalizedCoords};
}

DrawableObj *DrawableObj::create(std::string name) {
    if (DrawableObj::typeTemplates.find(name) ==
        DrawableObj::typeTemplates.end())
        return nullptr;

    DrawableObj::DrawableObjTemplate *typeData =
        &DrawableObj::typeTemplates[name];
    return new DrawableObj(typeData->drawMode, typeData->vertices,
                           typeData->indices, typeData->normalizedCoords);
}

void DrawableObj::setIndexBuffer(IndexBuffer *indices) {
    indexBuffer = indices;
}

void DrawableObj::removeIndexBuffer() { indexBuffer = nullptr; }

void DrawableObj::setPlainColor(ColorUByte color) {
    plainColored = true;
    plainColor = {((GLfloat)color.r) / 255.f, ((GLfloat)color.g) / 255.f,
                  ((GLfloat)color.b) / 255.f, ((GLfloat)color.a) / 255.f};
}

void DrawableObj::setPlainColor(ColorFloat color) {
    plainColored = true;
    plainColor = color;
}

void DrawableObj::removePlainColor() {
    plainColored = false;
    plainColor = {0.f, 0.f, 0.f, 0.f};
}

void DrawableObj::setOffset(GLfloat x, GLfloat y) {
    xOffset = x;
    yOffset = y;
}

void DrawableObj::setRotation(GLfloat angle) { rotation = angle; }

void DrawableObj::setScale(GLfloat scale) { DrawableObj::scale = scale; }

void DrawableObj::setFixed() { normalizedCoords = true; }

void DrawableObj::setUnfixed() { normalizedCoords = false; }

void DrawableObj::updateScreenDimens(GLfloat width, GLfloat height) {
    screenWidth = width;
    screenHeight = height;
}

void DrawableObj::draw() {
    vertexBuffer->bind();
    AttribFormat *attribs = vertexBuffer->getFormat();
    Attrib vertexFormat = attribs->getAttribute(GL_VERTEX_ARRAY);

    glVertexPointer(vertexFormat.count, vertexFormat.type, attribs->getStride(),
                    (void *)(intptr_t)(0 + vertexFormat.offset));

    if (attribs->enabledAttribute(GL_COLOR_ARRAY)) {
        Attrib colorFormat = attribs->getAttribute(GL_COLOR_ARRAY);
        glColorPointer(colorFormat.count, colorFormat.type,
                       attribs->getStride(),
                       (void *)(intptr_t)(0 + colorFormat.offset));
    }

    if (plainColored) {
        glDisableClientState(GL_COLOR_ARRAY);
        glColor4f(plainColor.r, plainColor.g, plainColor.b, plainColor.a);
    }

    glLoadIdentity();

    if (normalizedCoords) {
        GLfloat minDimens = std::min(screenWidth, screenHeight);
        glScalef(minDimens / screenWidth, minDimens / screenHeight, 1.f);
    }

    glTranslatef(xOffset, yOffset, 0.f);
    glScalef(scale, scale, 1.f);
    glRotatef(rotation, 0.f, 0.f, 1.f);

    if (indexBuffer != nullptr) {
        indexBuffer->bind();
        glDrawElements(drawMode, indexBuffer->getCount(), GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(drawMode, 0, vertexBuffer->getCount());
    }

    if (plainColored) {
        glEnableClientState(GL_COLOR_ARRAY);
    }
}

#include <algorithm>
#include <iostream>

#include "DrawableObj.h"

GLfloat DrawableObj::screenWidth;
GLfloat DrawableObj::screenHeight;

DrawableObj::DrawableObj(GLenum drawMode, ArrayBuffer *vertices, bool fixed) {
    DrawableObj::drawMode = drawMode;
    vertexBuffer = vertices;
    fixedAspectRatio = fixed;
}

DrawableObj::DrawableObj(GLenum drawMode, ArrayBuffer *vertices,
                         IndexBuffer *indices, bool fixed) {
    DrawableObj::drawMode = drawMode;
    vertexBuffer = vertices;
    indexBuffer = indices;
    fixedAspectRatio = fixed;
}

DrawableObj::~DrawableObj() {}

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

void DrawableObj::setScale(GLfloat scale) {
    DrawableObj::scale = scale;
}

void DrawableObj::setFixed() {
    fixedAspectRatio = true;
}

void DrawableObj::setUnfixed() {
    fixedAspectRatio = false;
}

void DrawableObj::updateScreenDimens(GLfloat width, GLfloat height) {
    screenWidth = width;
    screenHeight = height;
    // std:: cout << width << ' ' << height << '\n';
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


    if(fixedAspectRatio) {
        GLfloat minDimens = std::min(screenWidth, screenHeight);
        glScalef(minDimens/screenWidth, minDimens/screenHeight, 1.f);
    }

    glScalef(scale, scale, 1.f);
    glRotatef(rotation, 0.f, 0.f, 1.f);
    glTranslatef(xOffset, yOffset, 0.f);

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

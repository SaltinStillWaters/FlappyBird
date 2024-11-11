#ifndef SKYHELPERS_H
#define SKYHELPERS_H

#include "ColorStruct.h"
#include "DrawableObj.h"

ColorFloat calcDeltaColor(ColorFloat color1, ColorFloat color2) {
    GLfloat r = (color2.r - color1.r) / COLOR_CHANGE_DURATION;
    GLfloat g = (color2.g - color1.g) / COLOR_CHANGE_DURATION;
    GLfloat b = (color2.b - color1.b) / COLOR_CHANGE_DURATION;
    GLfloat a = (color2.a - color1.a) / COLOR_CHANGE_DURATION;
    return {r, g, b, a};
}

GLuint skyColorCounter = 0;

const GLuint SKY_COLORS_COUNT = 4;
ColorFloat skyColors[SKY_COLORS_COUNT][2] = {
    {{28.f / 255.f, 162.f / 255.f, 250.f / 255.f},
     {20.f / 255.f, 80.f / 255.f, 163.f / 255.f}},
    {{109.f / 255.f, 66.f / 255.f, 93.f / 255.f},
     {255.f / 255.f, 205.f / 255.f, 146.f / 255.f}},
    {{25.f / 255.f, 16.f / 255.f, 20.f / 255.f},
     {30.f / 255.f, 10.f / 255.f, 30.f / 255.f}},
    {{234.f / 255.f, 227.f / 255.f, 200.f / 255.f},
     {113.f / 255.f, 156.f / 255.f, 188.f / 255.f}}};

GLuint skyIndex1 = 0, skyIndex2 = 1;
ColorFloat deltaSkyColor[2] = {
    calcDeltaColor(skyColors[skyIndex1][0], skyColors[skyIndex2][0]),
    calcDeltaColor(skyColors[skyIndex1][1], skyColors[skyIndex2][1]),
};

void updateSkyColors(ArrayBuffer *skyVertexBuffer) {
    skyVertexBuffer->bind();

    uint8_t *skyVertexPtr =
        (uint8_t *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    AttribFormat *format = skyVertexBuffer->getFormat();
    GLsizei colorOffset = format->getAttribute(GL_COLOR_ARRAY).offset;
    GLsizei stride = format->getStride();
    GLint vertexCount = skyVertexBuffer->getCount();

    bool targetColorMatch = true;

    for (GLuint i = 0, j = 0; i < vertexCount * stride; i += stride, j++) {
        GLubyte r = skyVertexPtr[i + colorOffset];
        GLubyte g = skyVertexPtr[i + colorOffset + 1];
        GLubyte b = skyVertexPtr[i + colorOffset + 2];

        ColorFloat curColor = Color::convertUB2F({r, g, b});
        ColorFloat targetColor = skyColors[skyIndex2][j / 2];

        bool rMatch = std::fabs(curColor.r - targetColor.r) <
                      std::fabs(deltaSkyColor[j / 2].r);
        bool gMatch = std::fabs(curColor.g - targetColor.g) <
                      std::fabs(deltaSkyColor[j / 2].g);
        bool bMatch = std::fabs(curColor.b - targetColor.b) <
                      std::fabs(deltaSkyColor[j / 2].b);

        if (rMatch) {
            curColor.r = targetColor.r;
        } else {
            curColor.r = curColor.r + deltaSkyColor[j / 2].r;
        }

        if (gMatch) {
            curColor.g = targetColor.g;
        } else {
            curColor.g = curColor.g + deltaSkyColor[j / 2].g;
        }

        if (bMatch) {
            curColor.b = targetColor.b;
        } else {
            curColor.b = curColor.b + deltaSkyColor[j / 2].b;
        }

        ColorUByte convertedColor = Color::convertF2UB(curColor);
        skyVertexPtr[i + colorOffset] = convertedColor.r;
        skyVertexPtr[i + colorOffset + 1] = convertedColor.g;
        skyVertexPtr[i + colorOffset + 2] = convertedColor.b;

        if (!rMatch || !gMatch || !bMatch) {
            targetColorMatch = false;
        }
    }

    if (targetColorMatch) {
        skyIndex1 = (skyIndex1 + 1) % SKY_COLORS_COUNT;
        skyIndex2 = (skyIndex2 + 1) % SKY_COLORS_COUNT;

        deltaSkyColor[0] =
            calcDeltaColor(skyColors[skyIndex1][0], skyColors[skyIndex2][0]);
        deltaSkyColor[1] =
            calcDeltaColor(skyColors[skyIndex1][1], skyColors[skyIndex2][1]);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    skyVertexBuffer->unbind();
}

#endif
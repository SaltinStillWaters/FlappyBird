#ifndef SKYHELPERS_H
#define SKYHELPERS_H

#include "ColorStruct.h"
#include "DrawableObj.h"
#include <iostream>

const GLuint STAR_COUNT = 25;
const GLfloat SKY_CHANGE_DURATION = 50.f;
const GLfloat SUN_MOON_CHANGE_DEG = 180.f / (SKY_CHANGE_DURATION * 2.f);
const GLfloat SUN_MOON_SCALE_MAX = 1.25f;
const GLfloat SUN_MOON_SCALE_MIN = 0.25f;
const GLfloat STAR_MULT_MAX = 1.f;
const GLfloat STAR_MULT_MIN = 0.f;
const GLfloat STAR_MULT_DIFF = STAR_MULT_MAX - STAR_MULT_MIN;
const GLfloat STAR_MULT_DELTA = STAR_MULT_DIFF / SKY_CHANGE_DURATION;
const GLfloat SUN_MOON_SCALE_TOTAL_DIFF =
    SUN_MOON_SCALE_MAX - SUN_MOON_SCALE_MIN;
const GLfloat SUN_MOON_SCALE_DELTA =
    SUN_MOON_SCALE_TOTAL_DIFF / SKY_CHANGE_DURATION;

ColorFloat calcDeltaColor(ColorFloat color1, ColorFloat color2) {
    GLfloat r = (color2.r - color1.r) / SKY_CHANGE_DURATION;
    GLfloat g = (color2.g - color1.g) / SKY_CHANGE_DURATION;
    GLfloat b = (color2.b - color1.b) / SKY_CHANGE_DURATION;
    GLfloat a = (color2.a - color1.a) / SKY_CHANGE_DURATION;
    return {r, g, b, a};
}

GLfloat celestialRotation = 0.f;
GLfloat celestialScale = 1.25f;
GLfloat starMult = 0.f;
GLfloat celestialCoefficient = -1.f;
GLint scrollCounter = 0;
int lastDir = 1;

const GLuint SKY_COLORS_COUNT = 4;
ColorFloat skyColors[SKY_COLORS_COUNT][2] = {
    {{28.f / 255.f, 162.f / 255.f, 250.f / 255.f},
     {20.f / 255.f, 80.f / 255.f, 163.f / 255.f}},
    {{109.f / 255.f, 66.f / 255.f, 93.f / 255.f},
     {255.f / 255.f, 205.f / 255.f, 146.f / 255.f}},
    {{0.f / 255.f, 0.f / 255.f, 0.f / 255.f},
     {30.f / 255.f, 10.f / 255.f, 30.f / 255.f}},
    {{234.f / 255.f, 227.f / 255.f, 200.f / 255.f},
     {113.f / 255.f, 156.f / 255.f, 188.f / 255.f}}};

GLuint skyIndex1 = 0, skyIndex2 = 1;
ColorFloat deltaSkyColor[2] = {
    calcDeltaColor(skyColors[skyIndex1][0], skyColors[skyIndex2][0]),
    calcDeltaColor(skyColors[skyIndex1][1], skyColors[skyIndex2][1]),
};

GLfloat clamp(GLfloat value, GLfloat minVal, GLfloat maxVal) {
    if (value < minVal)
        return minVal;
    if (value > maxVal)
        return maxVal;
    return value;
}

void updateSky(ArrayBuffer *skyVertexBuffer, int dir) {
    if (dir != lastDir) {
        if (scrollCounter == 49 && dir == -1) {
            skyIndex2 =
                (((skyIndex1 - 1) % SKY_COLORS_COUNT) + SKY_COLORS_COUNT) %
                SKY_COLORS_COUNT;
            celestialCoefficient *= -1;
        } else if (scrollCounter == 1 && dir == 1) {
            skyIndex2 =
                (((skyIndex1 + 1) % SKY_COLORS_COUNT) + SKY_COLORS_COUNT) %
                SKY_COLORS_COUNT;
            celestialCoefficient *= -1;
        } else
            std::swap(skyIndex1, skyIndex2);
            
        deltaSkyColor[0] =
            calcDeltaColor(skyColors[skyIndex1][0], skyColors[skyIndex2][0]);
        deltaSkyColor[1] =
            calcDeltaColor(skyColors[skyIndex1][1], skyColors[skyIndex2][1]);

        lastDir = dir;
    }

    celestialRotation =
        fmodf(celestialRotation + dir * SUN_MOON_CHANGE_DEG, 360.f);

    celestialScale += dir * celestialCoefficient * SUN_MOON_SCALE_DELTA;
    if (scrollCounter == 0) {
        celestialCoefficient *= -1;
        if (celestialCoefficient * dir == -1) {
            celestialScale = 1.25f;
        }
    }

    skyVertexBuffer->bind();

    uint8_t *skyVertexPtr =
        (uint8_t *)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
    AttribFormat *format = skyVertexBuffer->getFormat();
    GLsizei colorOffset = format->getAttribute(GL_COLOR_ARRAY).offset;
    GLsizei stride = format->getStride();
    GLint vertexCount = skyVertexBuffer->getCount();

    for (GLuint i = 0, j = 0; i < vertexCount * stride; i += stride, j++) {
        GLubyte r = skyVertexPtr[i + colorOffset];
        GLubyte g = skyVertexPtr[i + colorOffset + 1];
        GLubyte b = skyVertexPtr[i + colorOffset + 2];

        ColorFloat curColor = Color::convertUB2F({r, g, b});
        ColorFloat targetColor = skyColors[skyIndex2][j / 2];

        if (scrollCounter == 0) {
            curColor.r = targetColor.r;
            curColor.g = targetColor.g;
            curColor.b = targetColor.b;
        } else {
            curColor.r = clamp(curColor.r + deltaSkyColor[j / 2].r, 0.0f, 1.0f);
            curColor.g = clamp(curColor.g + deltaSkyColor[j / 2].g, 0.0f, 1.0f);
            curColor.b = clamp(curColor.b + deltaSkyColor[j / 2].b, 0.0f, 1.0f);
        }

        ColorUByte convertedColor = Color::convertF2UB(curColor);
        skyVertexPtr[i + colorOffset] = convertedColor.r;
        skyVertexPtr[i + colorOffset + 1] = convertedColor.g;
        skyVertexPtr[i + colorOffset + 2] = convertedColor.b;
    }

    if (scrollCounter == 0) {
        skyIndex1 =
            (((skyIndex1 + dir * 1) % SKY_COLORS_COUNT) + SKY_COLORS_COUNT) %
            SKY_COLORS_COUNT;
        skyIndex2 =
            (((skyIndex2 + dir * 1) % SKY_COLORS_COUNT) + SKY_COLORS_COUNT) %
            SKY_COLORS_COUNT;

        deltaSkyColor[0] =
            calcDeltaColor(skyColors[skyIndex1][0], skyColors[skyIndex2][0]);
        deltaSkyColor[1] =
            calcDeltaColor(skyColors[skyIndex1][1], skyColors[skyIndex2][1]);

        if (skyIndex1 == 0) {
            celestialRotation = 0.f;
        }

        if (skyIndex1 == 2) {
            celestialRotation = 180.f;
            starMult = STAR_MULT_MAX;
        }

        if (skyIndex1 == 1 || skyIndex1 == 3) {
            starMult = STAR_MULT_MIN;
        }
    }

    if (skyIndex2 == 2) {
        starMult += STAR_MULT_DELTA;
    }

    if (skyIndex1 == 2 && scrollCounter != 0) {
        starMult -= STAR_MULT_DELTA;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    skyVertexBuffer->unbind();
}

#endif
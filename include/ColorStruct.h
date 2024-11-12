#ifndef COLORSTRUCT_H
#define COLORSTRUCT_H

#include <GL/glew.h>
#include <cmath>

const GLfloat COLOR_CHANGE_DURATION = 50.f;

struct ColorUByte {
    GLubyte r;
    GLubyte g;
    GLubyte b;
    GLubyte a = 255;
};

struct ColorFloat {
    float r;
    float g;
    float b;
    float a = 1.0f;
};

class Color {
public:
    static bool checkColorEquality(ColorFloat color1, ColorFloat color2) {
        return color1.r == color2.r && color1.g == color2.g &&
               color1.b == color2.b && color1.a == color2.a;
    }

    static bool checkColorEquality(ColorUByte color1, ColorUByte color2) {
        return color1.r == color2.r && color1.g == color2.g &&
               color1.b == color2.b && color1.a == color2.a;
    }

    static ColorFloat convertUB2F(ColorUByte color) {
        return {
            ((GLfloat)color.r) / 255.f,
            ((GLfloat)color.g) / 255.f,
            ((GLfloat)color.b) / 255.f,
            ((GLfloat)color.a) / 255.f,
        };
    }

    static ColorUByte convertF2UB(ColorFloat color) {
        return {
            (GLubyte)(color.r * 255.f),
            (GLubyte)(color.g * 255.f),
            (GLubyte)(color.b * 255.f),
            (GLubyte)(color.a * 255.f),
        };
    }
};

#endif
#include <iostream>
#include "SkyObj.h"

ArrayBuffer *SkyObj::skyVertices = nullptr;
SkyObj::SkyObjInit SkyObj::initSkyObj;

SkyObj::SkyObj() : DrawableObj() {
    drawMode = GL_QUADS;
    vertexBuffer = skyVertices;
}

void SkyObj::init() {
    if (!skyVertices) {
        DrawableObj::init();
        SkyObj::skyVertices = new ArrayBuffer("skyVertices.data",
                                      DrawableObj::formatVertexColor);
    }
}

void SkyObj::cleanup() {
    if (skyVertices) {
        delete SkyObj::skyVertices;
        SkyObj::skyVertices = nullptr;
    }
}
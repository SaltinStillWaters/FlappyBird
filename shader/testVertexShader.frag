#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 vertexColor;

out vec4 fragmentColor;

void main() {
    gl_Position = position;
    fragmentColor = vertexColor;
}
#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const std::string &vertexShaderFilename,
               const std::string &fragmentShaderFilename) {
    ShaderFile vertexShader = readShaderFile(vertexShaderFilename);
    ShaderFile fragmentShader = readShaderFile(fragmentShaderFilename);
    constructShader(vertexShader, fragmentShader);
}

Shader::~Shader() { glDeleteProgram(id); }

void Shader::setUniform3f(const std::string &name, GLfloat f0, GLfloat f1,
                          GLfloat f2) {
    glUniform3f(getUniformLocation(name), f0, f1, f2);
}

void Shader::setUniform4f(const std::string &name, GLfloat f0, GLfloat f1,
                          GLfloat f2, GLfloat f3) {
    glUniform4f(getUniformLocation(name), f0, f1, f2, f3);
}

void Shader::bind() const { glUseProgram(id); }

void Shader::unbind() const { glUseProgram(0); }

GLint Shader::getUniformLocation(const std::string &name) {
    if (uniformLocationMap.find(name) != uniformLocationMap.end())
        return uniformLocationMap[name];

    GLint location = glGetUniformLocation(id, name.c_str());
    uniformLocationMap[name] = location;

    if (location == -1)
        std::cout << "Cannot find uniform " << name << std::endl;

    return location;
}

void Shader::constructShader(ShaderFile vertexShader,
                             ShaderFile fragmentShader) {
    id = glCreateProgram();
    GLuint vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glLinkProgram(id);
    glValidateProgram(id);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

GLuint Shader::compileShader(GLenum shaderType, ShaderFile shaderFile) {
    GLuint shaderId = glCreateShader(shaderType);
    const char *shaderSrcPtr = shaderFile.src.c_str();
    glShaderSource(shaderId, 1, &shaderSrcPtr, nullptr);
    glCompileShader(shaderId);

    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint msgLen;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLen);
        char msg[msgLen];
        glGetShaderInfoLog(shaderId, msgLen, &msgLen, msg);
        std::cout << shaderFile.filename
                  << " compilation failed: " << std::endl;
        std::cout << msg << std::endl;
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

ShaderFile Shader::readShaderFile(const std::string &filename) {
    std::ifstream fileReader;
    fileReader.open("shader/" + filename);

    if (!fileReader)
        throw std::runtime_error("Shader file not found");

    std::string input;
    std::stringstream codeStream;
    while (getline(fileReader, input)) {
        codeStream << input << "\n";
    }

    fileReader.close();

    return {filename, codeStream.str()};
}

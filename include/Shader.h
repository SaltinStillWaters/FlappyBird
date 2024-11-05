#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>

struct ShaderFile {
    std::string filename;
    std::string src;
};

class Shader {
    protected:
        GLuint id;
        std::string vertexShaderFilePath;
        std::string fragmentShaderFilePath;
        std::unordered_map<std::string, GLint> uniformLocationMap;
    public:
        Shader(const std::string &vertexShaderFilePath,
            const std::string &fragmentShaderFilePath);
        ~Shader();
        void setUniform3f(const std::string &name, GLfloat f0, GLfloat f1,
                        GLfloat f2);
        void setUniform4f(const std::string &name, GLfloat f0, GLfloat f1,
                        GLfloat f2, GLfloat f3);
        void bind() const;
        void unbind() const;

    protected:
        GLint getUniformLocation(const std::string &name);
        void constructShader(ShaderFile vertexShader, ShaderFile fragmentShader);
        GLuint compileShader(GLenum shaderType, ShaderFile shaderFile);
        ShaderFile readShaderFile(const std::string &filename);
};

#endif
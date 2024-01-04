#ifndef SHADER_H
#define SHADER_H

#include "opengl.hpp"
#include "shader_file.hpp"
#include "shader_exception.hpp"

class Shader {
public:
    Shader() {

    }

    Shader(opengl::ShaderType type, ShaderFile file) :
        file(file) {

        if(file.getFileName().empty()) {
            throw new ShaderException("no file specified");
        }

        if(file.getShaderCode().empty()) {
            throw new ShaderException("provided shader empty file: " + file.getFileName());
        }

        shaderId = opengl::createShader(type);
        if(shaderId == 0) {
            throw new ShaderException("shader creation failed");
        }

        opengl::compileShader(shaderId, file.getShaderCode());
    }

    opengl::ShaderID getID() {
        return shaderId;
    }

private:
    ShaderFile file;
    opengl::ShaderID shaderId; 
};

#endif //SHADER_H
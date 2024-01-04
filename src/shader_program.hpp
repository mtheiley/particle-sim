#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>

#include "opengl.hpp"
#include "shader_exception.hpp"

class ShaderProgram {
public:
    ShaderProgram(std::vector<opengl::ShaderID> shaderIdList) {
        programId = opengl::createShaderProgram();
        if(programId == 0) {
            throw new ShaderException("unable to create shader program");
        }
        
        for(opengl::ShaderID shaderId : shaderIdList) {
            opengl::attachShader(programId, shaderId);
        }

        opengl::linkShader(programId);
    }

    void selectShaderProgram() {
        opengl::selectShaderProgram(programId);
    }

private:
    opengl::ShaderProgramID programId;
};

#endif //SHADER_PROGRAM_H
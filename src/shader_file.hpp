#ifndef SHADER_FILE_H
#define SHADER_FILE_H

#include <string>
#include <fstream>

class ShaderFile {
public:
    ShaderFile() {
            
    }

    ShaderFile(std::string fileName) :
        fileName(fileName) {

        std::ifstream infile(fileName);
        std::string line;
        while (std::getline(infile, line)) {
            shaderCode += line + LINE_ENDING;
            //std::cout << line << std::endl;
        }
    }

    std::string getShaderCode() {
        return shaderCode;
    }

    std::string getFileName() {
        return fileName;
    }

private:
    const std::string LINE_ENDING = "\n";
    std::string fileName = "";
    std::string shaderCode = "";
};

#endif //SHADER_FILE_H
#ifndef SHADER_EXCEPTION_H
#define SHADER_EXCEPTION_H

#include <exception>
#include <string>
#include <cstring>

class ShaderException : public std::exception {
public:
    ShaderException(std::string message) {
        this->message = new char[message.length()];
        strcpy(this->message, message.c_str());
    }

    char* what() {
        return message;
    }

    ~ShaderException() {
        delete[] this->message;
    }

private:
    char* message;
};

#endif //SHADER_EXCEPTION_H
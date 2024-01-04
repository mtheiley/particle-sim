#ifndef WINDOW_EXCEPTION_H
#define WINDOW_EXCEPTION_H

#include <exception>
#include <string>
#include <cstring>

class WindowException : public std::exception {
public:
    WindowException(std::string message) {
        this->message = new char[message.length()];
        strcpy(this->message, message.c_str());
    }

    char* what() {
        return message;
    }

    ~WindowException() {
        delete[] this->message;
    }

private:
    char* message;
};

#endif //SHADER_EXCEPTION_H
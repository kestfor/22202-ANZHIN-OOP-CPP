#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>
#include <utility>

class BasicException : public std::exception {
protected:
    const std::string message;
    int codeError;
public:

    enum errorCodes {
        UNEXPECTED_TYPE = 1,
        UNSUPPORTED_TYPE,
        INCOMPATIBLE_AMOUNT
    };

    BasicException(std::string  message, const int codeError) : message{std::move(message)}, codeError(codeError) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

    int code() const {
        return codeError;
    }
};




#endif //EXCEPTIONS_H

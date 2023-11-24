#ifndef SOUNDEXCEPTION_H
#define SOUNDEXCEPTION_H
#include <stdexcept>
#include <utility>

class BasicException : public std::exception {
protected:
    const std::string message;
    int codeError;
public:

    enum errorCodes {
        INVALID_FILE_NAME = 1,
        BAD_FORMAT,
        FILE_ERROR,
        INVALID_NAME,
        EMPTY_COMMAND,
        INVALID_COMMAND_NAME,
        INVALID_AMOUNT_PARAMS,
        INVALID_PARAM,
        INVALID_OPTION
    };

    BasicException(std::string  message, const int codeError) : message{std::move(message)}, codeError(codeError) {}

    const char *what() const noexcept override {
        return message.c_str();
    }

    int code() const {
        return codeError;
    }
};

class WAVException final : public BasicException {
public:

    enum errorCodes {
        INVALID_FILE_NAME = BasicException::INVALID_FILE_NAME,
        BAD_FORMAT = BasicException::BAD_FORMAT,
        FILE_ERROR = BasicException::FILE_ERROR,
    };

    WAVException(const std::string &message, const int codeError) : BasicException(message, codeError) {}
};

class FactoryException final : public BasicException {
public:

    enum errorCodes {
        INVALID_NAME = BasicException::INVALID_NAME,
    };

    FactoryException(const std::string &message, const int codeError) : BasicException(message, codeError) {}
};

class InstructionException final : public BasicException {
public:

    enum errorCodes {
        EMPTY_COMMAND = BasicException::EMPTY_COMMAND,
        INVALID_COMMAND_NAME = BasicException::INVALID_COMMAND_NAME,
        INVALID_PARAM = BasicException::INVALID_PARAM,
    };

    InstructionException(const std::string &message, const int codeError) : BasicException(message, codeError) {}
};

class ConfigException final : public BasicException {
public:

    enum errorCodes {
        INVALID_FILE_NAME = BasicException::INVALID_FILE_NAME,
    };

    ConfigException(const std::string &message, const int codeError) : BasicException(message, codeError) {}
};

class ConverterException final : public BasicException {
public:

    enum errorCodes {
        INVALID_AMOUNT_PARAMS = BasicException::INVALID_AMOUNT_PARAMS,
        INVALID_PARAM = BasicException::INVALID_PARAM,
    };

    ConverterException(const std::string &message, const int codeError) : BasicException(message, codeError) {}
};


#endif //SOUNDEXCEPTION_H

#include "ConfigsReader.h"


string ConfigsReader::readline() const {
    string line;
    bool isComment = true;
    while (isComment) {
        if (!file->eof()) {
            std::getline(*file, line);
        } else {
            break;
        }
        if (!line.starts_with("#")) {
            isComment = false;
        }
    }
    return line;
}

Instruction ConfigsReader::readInsruction() const {
    const string line = readline();
    return {line, factory};
}

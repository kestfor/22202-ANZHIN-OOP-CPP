#include "ConfigsReader.h"


string ConfigsReader::readline() {
    string line;
    bool isComment = true;
    while (isComment) {
        if (!file->eof()) {
            std::getline(*file, line);
            currLine += 1;
        } else {
            break;
        }
        if (!line.starts_with("#") && !line.empty()) {
            isComment = false;
        }
    }
    if (file->eof() && isComment) {
        line = "";
    }
    return line;
}

Instruction ConfigsReader::readInsruction() {
    const string line = readline();
    return {line, factory};
}

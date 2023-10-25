#include "CommandArgumentService.h"

void CommandArgumentService::handleWrongArguments() {
    string error = "invalid argument(s), game has 3 optional argument: \n"
                   "1. --file or -f in short'\n"
                   "2. --iterations or -i in short\n"
                   "3. --output or -o in short\n"
                   "for example:\n"
                   "'-i 2 -o res.txt' or '--iterations=2 --output=res.txt' "
                   "will calculate universe after 2 ticks and save to the file(offline mode)\n"
                   "starting without 2 or 3 argument turn on online mode\n"
                   "'file' argument - path to the file of saved universe to start with";
    throw std::runtime_error(error);
}

CommandArgumentService::CommandArgumentService(int args, char **argv) {
    for (int i = 1; i < args; i++) {
        string argName = string(argv[i]);
        if (argName.starts_with("--")) {
            string value = argName.substr(argName.find('=') + 1);
            argName = argName.substr(0, argName.find('=') + 1);
            if (allowedArgs.contains(argName)) {
                allowedArgs[argName] = value;
                string shortName = argName.substr(1, 2);
                if (!allowedArgs[shortName].empty()) {
                    handleWrongArguments();
                } else {
                    allowedArgs[shortName] = value;
                }
            } else {
                handleWrongArguments();
            }
        } else if (argName.starts_with('-') && argName.size() == 2) {
            if (i + 1 >= args) {
                handleWrongArguments();
            } else {
                i++;
                string value = string(argv[i]);
                if (allowedArgs.contains(argName)) {
                    allowedArgs[argName] = value;
                } else {
                    handleWrongArguments();
                }
            }
        } else {
            handleWrongArguments();
        }
    }
}

const string &CommandArgumentService::getArgument(const string &name) {
    if (allowedArgs.contains(name)) {
        return allowedArgs[name];
    } else {
        throw std::runtime_error("wrong argument");
    }
}

const string &CommandArgumentService::operator[](const string &name) {
    return getArgument(name);
}

bool CommandArgumentService::contains(const string &name) {
    const string arg = this->getArgument(name);
    if (arg.empty()) {
        return false;
    } else {
        return true;
    }
}

vector<string> CommandArgumentService::parseCommand(const string &line) {
    vector<string> result;
    if (line.empty()) {
        return result;
    }
    size_t startInd = 0;
    size_t endInd = line.size() - 1;
    while (startInd <= endInd) {
        while (startInd <= endInd && line[startInd] == ' ') {
            startInd++;
        }
        for (size_t i = startInd; i <= endInd; i++) {
            if (line[i] == ' ') {
                result.push_back(line.substr(startInd, i - startInd));
                startInd = i + 1;
                break;
            } else if (i == endInd && (line[i] != ' ')) {
                result.push_back(line.substr(startInd, i - startInd + 1));
                startInd = i + 1;
            }
        }
    }
    return result;
}

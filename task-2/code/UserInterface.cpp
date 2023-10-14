#include "UserInterface.h"

void UserInterface::handleWrongArguments() {
    string error = "invalid argument(s), game has 3 optional argument: \n"
                   "1. --file or -f in short'\n"
                   "2. --iterations or -i in short\n"
                   "3. --output or -o in short\n"
                   "for example:\n"
                   "'-i 2 -o res.txt' or '--iterations=2 --output=res.txt' "
                   "will calculate universe after 2 ticks and save to the file(offline mode)\n"
                   "starting without 2 or 3 argument turn on online mode\n"
                   "'file' argument - path to the file of saved universe to start with";
    throw runtime_error(error);
}

UserInterface::UserInterface(int args, char *argv[]) {
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
    if (!allowedArgs["-i"].empty() && !allowedArgs["-o"].empty()) {
        this->mode = offline;
    } else {
        this->mode = online;
    }
}

void UserInterface::gameInit() {
    if (allowedArgs["-f"].empty()) {
        game = new Life();
    } else {
        game = new Life(allowedArgs["-f"]);
    }
    if (mode == offline) {
        int n = stoi(allowedArgs["-i"]);
        cout << "calculating...\n";
        for (int i = 0; i < n; i++) {
            game->nextGeneration();
        }
        this->dumpToFile(allowedArgs["-o"], false);
        this->exit();
    } else {
        this->getTick(0);
    }
}

void UserInterface::handleWrongCommand(const string &cmd) {
    cout << '"' << cmd << '"' <<  " is not a proper command, type 'help' to learn more\n";
}

void UserInterface::waitForCommand() {
    string cmd;
    getline(cin, cmd);
    string cmdName = cmd.substr(0, cmd.find(' '));
    if (find(allowedCmds.begin(), allowedCmds.end(), cmdName) == allowedCmds.end()) {
        handleWrongCommand(cmdName);
    } else {
        if (cmdName == "dump") {
            string cmdArg = cmd.substr(cmd.find(' ') + 1);
            dumpToFile(cmdArg);
        } else if (cmdName == "tick" or cmdName == "t") {
            if (cmd.find(' ') != -1) {
                int tickNumber = stoi(cmd.substr(cmd.find(' ') + 1));
                getTick(tickNumber);
            } else {
                getTick();
            }
        } else if (cmdName == "help") {
            help();
        } else if (cmdName == "exit"){
            exit();
        } else {
            string cmdArg = cmd.substr(cmd.find(' ') + 1);
            try {
                int arg = stoi(cmdArg);
                live(arg);
            } catch (const invalid_argument &err) {
                live();
            }
        }
    }
}

void UserInterface::dumpToFile(const string &fileName, bool waitForCommand) {
    ofstream file(fileName);
    file << "#Life 1.06\n";
    file << "#N " + game->getUniverseName() + '\n';
    file << "#R " + game->getBirthSurviveRules() + '\n';
    auto coords = game->getLiveCoords();
    for (const auto &item : coords) {
        file << item.first << ' ' << item.second << endl;
    }
    file.close();
    cout << "universe was successfully saved\n";
    if (waitForCommand) {
        this->waitForCommand();
    }
}

void UserInterface::getTick(int n, bool waitForCommand) {
    cout << "calculating...\n";
    for (int i = 0; i < n; i++) {
        game->nextGeneration();
    }
    system("cls");
    cout << game->getUniverseName() << endl;
    cout << game->getBirthSurviveRules() << endl;
    cout << "current gen: " << game->getGenNumber() << endl;
    game->show();
    if (waitForCommand) {
        this->waitForCommand();
    }
}

void UserInterface::help(bool waitForCommand) {
    string line = "after start there are 5 commands that you can use:\n"
                  "1. dump <filename> - save current universe in file with name filename\n"
                  "2. tick <n=1> or in short t <n=1> for example: 'tick 2' command will show you your universe after 2 generations\n"
                  "3. exit - close the game, all progress will be lost\n"
                  "4. live <n=50> - run simulation in real time for n iterations\n"
                  "4. help - get info about commands\n";
    system("cls");
    cout << line;
    if (waitForCommand) {
        this->waitForCommand();
    }
}

void UserInterface::exit() {
    std::exit(EXIT_SUCCESS);
}

void UserInterface::showWarning(const string &msg) {
    cout << msg << endl;
}

void UserInterface::stop() {
    exit();
}

void UserInterface::live(int n) {
    system("cls");
    cout << game->getUniverseName() << endl;
    cout << game->getBirthSurviveRules() << endl;
    vector<int> lastTen(10, 0);
    COORD coord;
    for (int i = 0; i < n; i++) {
        coord.Y = 2;
        coord.X = 0;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        game->nextGeneration();
        cout << "current gen: " << game->getGenNumber() << endl;
        game->show();
        Sleep(50);
        lastTen[i % 10] = game->getAmountAlive();
        if (i % 10 == 0 && i != 0) {
            bool test = false;
            for (int j = 0; j < 9; j++) {
                if (lastTen[j] != lastTen[j + 1]) {
                    test = true;
                    break;
                }
            }
            if (!test) {
                break;
            }
        }
    }
    waitForCommand();
}


//#include "Command.h"
//
//
//void Command::dumpToFileCmd(const string &fileName) {
//    std::ofstream file(fileName);
//    file << "#Life 1.06\n";
//    file << "#N " + game->getUniverseName() + '\n';
//    file << "#R " + game->getBirthSurviveRules() + '\n';
//    auto coords = game->getLiveCoords();
//    for (const auto &item : coords) {
//        file << item.first << ' ' << item.second << std::endl;
//    }
//    file.close();
//    std::cout << "universe was successfully saved\n";
//}
//
//void Command::getTickCmd(int n) {
//    if (n >= 1000) {
//        std::cout << "calculating...\n";
//    }
//    for (int i = 0; i < n; i++) {
//        game->nextGeneration();
//    }
//    system("cls");
//    std::cout << game->getUniverseName() << std::endl;
//    std::cout << game->getBirthSurviveRules() << std::endl;
//    std::cout << "current gen: " << game->getGenNumber() << std::endl;
//    game->show();
//}
//
//void Command::helpCmd() {
//    string line = "after start there are 5 commands that you can use:\n"
//                  "1. dump <filename> - save current universe in file with name filename\n"
//                  "2. tick <n=1> or in short t <n=1> for example: 'tick 2' command will show you your universe after 2 generations\n"
//                  "3. exit - close the game, all progress will be lost\n"
//                  "4. live <n=50> - run simulation in real time for n iterations\n"
//                  "5. help - get info about commands\n";
//    system("cls");
//    std::cout << line;
//}
//
//void Command::liveCmd(int n) {
//    system("cls");
//    std::cout << game->getUniverseName() << std::endl;
//    std::cout << game->getBirthSurviveRules() << std::endl;
//    COORD coord;
//    for (int i = 0; i < n; i++) {
//        coord.Y = 2;
//        coord.X = 0;
//        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//        game->nextGeneration();
//        std::cout << "current gen: " << game->getGenNumber() << std::endl;
//        game->show();
//        Sleep(50);
//        if (game->getAmountAlive() == 0) {
//            break;
//        }
//    }
//}
//
//void Command::exitCmd() {
//    std::exit(EXIT_SUCCESS);
//}
//
//void Command::execute(vector<string> &arguments) {
//    if (!allowedCmdsMap.contains(arguments[0])) {
//        std::cout << '"' << arguments[0] << '"' <<  " is not a proper command, type 'help' to learn more\n";
//        return;
//    }
//    switch (allowedCmdsMap[arguments[0]]) {
//        case tick: {
//            if (arguments.size() > 1) {
//                getTickCmd(stoi(arguments[1]));
//            } else {
//                getTickCmd();
//            }
//            break;
//        }
//        case t: {
//            if (arguments.size() > 1) {
//                getTickCmd(stoi(arguments[1]));
//            } else {
//                getTickCmd();
//            }
//            break;
//        }
//        case dump: {
//            dumpToFileCmd(arguments[1]);
//            break;
//        }
//        case help: {
//            helpCmd();
//            break;
//        }
//        case live: {
//            if (arguments.size() > 1) {
//                liveCmd(stoi(arguments[1]));
//            } else {
//                liveCmd();
//            }
//            break;
//        }
//        case exit: {
//            exitCmd();
//            break;
//        }
//    }
//}

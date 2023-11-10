#include "GameController.h"
#include "CommandArgumentService.h"
#include "LifeSettings.h"
#include "FileReader.h"

const int AMOUNT_PRESETS = 5;

string getPresetName() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,AMOUNT_PRESETS);
    string presetName = std::filesystem::current_path().string() + "\\..\\presets\\" + std::to_string(dist(gen)) + ".life";
    return presetName;
}

int main(int args, char *argv[]) {
    system("cls");
    map<string, string> arguments;
    try {
        arguments = CommandArgumentService::parseArguments(args, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what();
        return 0;
    }
    string fileName;
    if (arguments.contains("-f")) {
        fileName = arguments["-f"];
    } else {
        fileName = getPresetName();
    }
    FileReader reader(fileName);
    LifeSettings settings;
    try {
        settings.setName(reader.getUniverseName());
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
    try {
        settings.setBirthSurviveRules(reader.getBirthSurviveRules());
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
    try {
        settings.setStartCoords(reader.readCoords());
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << std::endl;
    }
    GameController controller(settings);
    if (arguments.contains("-i") && arguments.contains("-o")) {
        controller.runGame(arguments["-i"], arguments["-o"]);
    } else {
        controller.runGame();
    }
}
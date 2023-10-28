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
    try {
        system("cls");
        CommandArgumentService argumentService(args, argv);
        string fileName = argumentService.contains("-f") ? argumentService.getArgument("-f") : getPresetName();
        FileReader reader(fileName);
        LifeSettings settings;
        settings.setName(reader.getUniverseName());
        settings.setBirthSurviveRules(reader.getBirthSurviveRules());
        settings.setStartCoords(reader.readCoords());
        GameController controller(settings);
        if (argumentService.contains("-i") && argumentService.contains("-o")) {
            controller.runGame(argumentService.getArgument("-i"), argumentService.getArgument("-o"));
        } else {
            controller.runGame();
        }
    } catch (const std::runtime_error &err) {
        system("cls");
        std::cout << err.what();
    }
}
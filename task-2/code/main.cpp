#include "GameController.h"

int main(int args, char *argv[]) {
    try {
        system("cls");
        GameController controller(args, argv);
        while (true) {
            controller.waitForCommand();
        }
    } catch (const std::runtime_error &err) {
        system("cls");
        std::cout << err.what();
    }
}
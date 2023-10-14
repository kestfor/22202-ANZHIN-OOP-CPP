#include "UserInterface.h"
using namespace std;



int main(int argc, char *argv[]) {
    try {
        UserInterface userInterface(argc, argv);
        userInterface.gameInit();
        while (true) {
            userInterface.waitForCommand();
        }
    } catch (const runtime_error &err) {
        system("cls");
        cout << err.what();
    }
}
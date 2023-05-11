#include <iostream>
#include "include/Controller.hpp"
int main(int argc, char** argv) { 
    Controller mazeController(argc, argv);

    while (mazeController.isWindowOpen()) {
        mazeController.update();
        mazeController.render();
    }
    return 0; 
}

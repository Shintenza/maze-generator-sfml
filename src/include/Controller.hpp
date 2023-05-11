#pragma once
#include "MazeState.hpp"
#include "MenuState.hpp"
#include "State.hpp"

#include <SFML/Graphics.hpp>
#include <stack>

class Controller {
private:
    sf::RenderWindow *window;
    sf::VideoMode videoMode;
    sf::Event event;

    int argc;
    char **argv;

    int mazeWidth;
    int mazeHeight;
    int cellWidth;
    int wallWidth;
    int borderWidth;

    std::stack<State *> states;

    std::string getAssetsPath();

    void initWindow();
    void initDefaults();
    void updatePollEvents();
    void statesUpdateHandler();
    void handleInput();

public:
    Controller(int arg_count, char **args);
    ~Controller();
    bool isWindowOpen();

    void update();
    void render();
};

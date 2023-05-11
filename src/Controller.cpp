#include "include/Controller.hpp"

Controller::Controller(int arg_count, char **args) : argc(arg_count), argv(args) {
    initDefaults();
    initWindow();
}

Controller::~Controller() {
    delete window;
}

std::string Controller::getAssetsPath() {
    std::string path = argv[0];
    std::string assetsFolderName = "assets";
    if (path.find("bin") != std::string::npos) {
        return "./" + assetsFolderName + "/";
    }
    return "../" + assetsFolderName + "/";
}

void Controller::initWindow() {
    int windowSizeX = 2 * borderWidth + cellWidth * mazeWidth + wallWidth * mazeWidth - wallWidth;
    int windowSizeY = 2 * borderWidth + cellWidth * mazeHeight + wallWidth * mazeHeight - wallWidth;

    videoMode = sf::VideoMode(windowSizeX, windowSizeY);
    window = new sf::RenderWindow(videoMode, "Maze generator", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(false);
    states.push(new MenuState(window, getAssetsPath(), states, &mazeWidth, &mazeHeight, &cellWidth, &wallWidth, &borderWidth));
}

void Controller::initDefaults() {
    cellWidth = 14;
    wallWidth = 5;
    mazeWidth = 30;
    mazeHeight = 25;
    borderWidth = 5;

}

void Controller::updatePollEvents() {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window->setView(sf::View(visibleArea));
        }
    }
}

void Controller::statesUpdateHandler() {
    if (states.empty()) {
        window->close();
        return;
    }
    if (states.top()->getState()) {
        states.top()->update();
    } else {
        delete states.top();
        states.pop();
    }
}

void Controller::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->close();
    }
}

bool Controller::isWindowOpen() {
    return window->isOpen();
}

void Controller::update() {
    updatePollEvents();
    handleInput();
    statesUpdateHandler();
}

void Controller::render() {
    window->clear();
    if (!states.empty())
        states.top()->render();
    window->display();
}

#pragma once
#include <SFML/Graphics.hpp>

class State {
protected:
    sf::RenderWindow *window;
    std::string assetsPath;

private:
    std::string stateName;
    bool isActive;

public:
    State(sf::RenderWindow *target, std::string state_name) : window(target), stateName(state_name), isActive(true){};
    State(sf::RenderWindow *target, std::string assets_path, std::string state_name)
        : window(target), assetsPath(assets_path), stateName(state_name), isActive(true){};
    virtual ~State(){};
    void endState() { isActive = false; };
    bool getState() { return isActive; };

    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

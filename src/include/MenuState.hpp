#pragma once
#include "State.hpp"
#include "MazeState.hpp"
#include <iostream>
#include <stack>

class MenuState : public State {
private:
    sf::Font roboto_font;
    sf::Font chopsic_font;

    sf::Vector2i mousePosInt;
    sf::Vector2f mousePos;

    sf::RectangleShape buttonShape;
    sf::RectangleShape quitButtonShape;
    sf::RectangleShape wAddButtion;
    sf::RectangleShape wMinusButtion;
    sf::RectangleShape hAddButtion;
    sf::RectangleShape hMinusButtion;

    sf::Text optionWidth;
    sf::Text currentWidth;
    sf::Text wPlusSign;
    sf::Text wMinusSign;

    sf::Text optionHeight;
    sf::Text currentHeight;
    sf::Text hPlusSign;
    sf::Text hMinusSign;

    sf::Text start;
    sf::Text quit;

    sf::Text title;

    std::stack<State *> &states;
    int *mazeWidth;
    int *mazeHeight;
    int *cellWidth;
    int *wallWidth;
    int *borderWidth;

    bool isHeld;

    void loadAssets();
    void initOptions();
    void initText();
    void updateMousePos();

public:
    MenuState(sf::RenderWindow *window, std::string assets_path, std::stack<State *> &states_stack, int *mW, int *mH, int *cW, int *wW, int *bW);
    void handleInput() override;
    void update() override;
    void render() override;
};

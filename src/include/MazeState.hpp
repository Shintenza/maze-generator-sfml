#pragma once

#include "Cell.hpp"
#include "State.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <ctime>

class MazeState : public State {
private:
    sf::RectangleShape entry;
    sf::RectangleShape exit;

    sf::Vector2u defaultWinSize;

    bool isPaused;
    
    int mazeWidth;
    int mazeHeight;
    int cellWidth;
    int wallWidth;
    int borderWidth;

    Cell *cells;

    int visitedCells;

    std::stack<std::pair<int, int>> mazeStack;


    void handleInput();

    void updateWindow();
    void genEntry();
    void genExit();
    void mazeGenerator();
    void drawMaze();

public:
    MazeState(sf::RenderWindow *window, int mW, int mH, int cW, int wW, int bW);
    ~MazeState();

    void update();
    void render();
};

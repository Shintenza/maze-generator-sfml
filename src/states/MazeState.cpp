#include "../include/MazeState.hpp"

MazeState::MazeState(sf::RenderWindow *window, int mW, int mH, int cW, int wW, int bW) : State(window, "maze_state"){
    mazeWidth = mW;
    mazeHeight = mH;
    cellWidth = cW;
    wallWidth = wW;
    borderWidth = bW;
    updateWindow();

    std::cout<<mazeWidth<<" "<< mazeHeight<<" "<< cellWidth<<" "<< wallWidth<< " "<< borderWidth<<std::endl;

    isPaused = false;
    
    cells = new Cell[mazeWidth * mazeHeight]();

    genEntry();
    genExit();
}

MazeState::~MazeState() {
    delete[] cells;
}


void MazeState::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        window->setSize(defaultWinSize);
        endState();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        isPaused = !isPaused;
    }
}

void MazeState::updateWindow() {
    int windowSizeX = 2 * borderWidth + cellWidth * mazeWidth + wallWidth * mazeWidth - wallWidth;
    int windowSizeY = 2 * borderWidth + cellWidth * mazeHeight + wallWidth * mazeHeight - wallWidth;
    defaultWinSize = window->getSize();
    window->setSize(sf::Vector2u(windowSizeX, windowSizeY));
    window->clear();
}

void MazeState::genEntry() {
    srand(std::time(0));
    int yEntry = rand() % mazeHeight;

    mazeStack.push(std::make_pair(0, yEntry));
    cells[yEntry*mazeWidth].isVisited = true;
    visitedCells = 1;

    entry.setPosition(0, borderWidth + yEntry * cellWidth + yEntry * wallWidth);
    entry.setFillColor(sf::Color::White);
    entry.setSize(sf::Vector2f(borderWidth, cellWidth));
}

void MazeState::genExit() {
    int yExit = rand() % mazeHeight;
    exit.setPosition(sf::Vector2f(borderWidth + mazeWidth * cellWidth + (mazeWidth - 1) * wallWidth, borderWidth + yExit * cellWidth + yExit * wallWidth));
    exit.setFillColor(sf::Color::White);
    exit.setSize(sf::Vector2f(borderWidth, cellWidth));
}

void MazeState::mazeGenerator() {
    if (isPaused) return;
    if (visitedCells >= mazeWidth * mazeHeight)
        return;

    auto index = [&](int x, int y) {
        return ((mazeStack.top().second + y) * mazeWidth + (mazeStack.top().first + x));
    };

    enum directions {
        NORTH,
        EAST,
        SOUTH,
        WEST,
    };

    std::vector<int> possibleNeigbours;
    if (mazeStack.top().second > 0 && !cells[index(0, -1)].isVisited) {
        possibleNeigbours.push_back(NORTH);
    }
    if (mazeStack.top().first < mazeWidth - 1 && !cells[index(1, 0)].isVisited) {
        possibleNeigbours.push_back(EAST);
    }
    if (mazeStack.top().second < mazeHeight - 1 && !cells[index(0, 1)].isVisited) {
        possibleNeigbours.push_back(SOUTH);
    }
    if (mazeStack.top().first > 0 && !cells[index(-1, 0)].isVisited) {
        possibleNeigbours.push_back(WEST);
    }

    if (!possibleNeigbours.empty()) {
        int nextDirection = possibleNeigbours[rand() % possibleNeigbours.size()];

        switch (nextDirection) {
        case NORTH:
            cells[index(0, -1)].isVisited = true;
            cells[index(0, -1)].hasSouthNeighbour = true;
            cells[index(0, 0)].hasNorthNeighbour = true;
            mazeStack.push(std::make_pair(mazeStack.top().first, mazeStack.top().second - 1));
            break;
        case EAST:
            cells[index(1, 0)].isVisited = true;
            cells[index(1, 0)].hasWestNeighbour = true;
            cells[index(0, 0)].hasEastNeighbour = true;
            mazeStack.push(std::make_pair(mazeStack.top().first + 1, mazeStack.top().second));
            break;
        case SOUTH:
            cells[index(0, 1)].isVisited = true;
            cells[index(0, 1)].hasNorthNeighbour = true;
            cells[index(0, 0)].hasSouthNeighbour = true;
            mazeStack.push(std::make_pair(mazeStack.top().first, mazeStack.top().second + 1));
            break;
        case WEST:
            cells[index(-1, 0)].isVisited = true;
            cells[index(-1, 0)].hasEastNeighbour = true;
            cells[index(0, 0)].hasWestNeighbour = true;
            mazeStack.push(std::make_pair(mazeStack.top().first - 1, mazeStack.top().second));
            break;
        }
        visitedCells++;
    } else {
        mazeStack.pop();
    }
}

void MazeState::drawMaze() {
    window->draw(entry);
    for (int x = 0; x < mazeWidth; x++) {
        for (int y = 0; y < mazeHeight; y++) {
            sf::RectangleShape rect;
            rect.setSize(sf::Vector2f(cellWidth, cellWidth));
            rect.setPosition( borderWidth + x * cellWidth + x * wallWidth, borderWidth + y * cellWidth + y * wallWidth);
            if (!cells[y * mazeWidth + x].isVisited) {
                rect.setFillColor(sf::Color::Blue);
            } else {
                rect.setFillColor(sf::Color::White);
            }
            if (cells[y * mazeWidth + x].hasEastNeighbour) {
                sf::RectangleShape pass;
                pass.setSize(sf::Vector2f(wallWidth, cellWidth));
                pass.setFillColor(sf::Color::White);
                pass.setPosition(sf::Vector2f(borderWidth + x * cellWidth + cellWidth + x * wallWidth, borderWidth +y * cellWidth + y * wallWidth));
                window->draw(pass);
            }
            if (cells[y * mazeWidth + x].hasSouthNeighbour) {
                sf::RectangleShape pass;
                pass.setSize(sf::Vector2f(cellWidth, wallWidth));
                pass.setFillColor(sf::Color::White);
                pass.setPosition(sf::Vector2f(borderWidth + x * cellWidth + x * wallWidth, borderWidth + y * cellWidth + cellWidth + y * wallWidth));
                window->draw(pass);
            }
            window->draw(rect);
        }
    }
    if (visitedCells == mazeWidth * mazeHeight) {
        window->draw(exit);
    }
}

void MazeState::update() {
    handleInput();
    mazeGenerator();
}

void MazeState::render() {
    window->clear(sf::Color::Black);
    drawMaze();
    window->display();
}

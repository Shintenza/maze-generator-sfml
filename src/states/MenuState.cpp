#include "../include/MenuState.hpp"

MenuState::MenuState(sf::RenderWindow *window, std::string assets_path, std::stack<State *> &states_stack, int *mW, int *mH, int *cW, int *wW, int *bW)
    : states(states_stack), State(window, assets_path, "menu_state") {
    isHeld = false;

    mazeWidth = mW;
    mazeHeight = mH;
    cellWidth = cW;
    wallWidth = wW;
    borderWidth = bW;
    loadAssets();
    initText();
    initOptions();
}

void MenuState::loadAssets() {
    if (!roboto_font.loadFromFile(assetsPath + "roboto.ttf")) {
        throw "Failed to load roboto.ttf";
        exit(1);
    }
    if (!chopsic_font.loadFromFile(assetsPath + "chopsic.otf")) {
        throw "Failed to load chopsic.otf";
        exit(1);
    }
}

void MenuState::initOptions() {
    optionWidth.setFont(roboto_font);
    optionWidth.setString("Maze width: ");
    optionWidth.setCharacterSize(25);
    optionWidth.setFillColor(sf::Color::Black);
    optionWidth.setPosition(title.getPosition().x, 100);

    wAddButtion.setSize(sf::Vector2f(30, 30));
    wAddButtion.setFillColor(sf::Color::Black);
    int wAddButtionX = title.getPosition().x + title.getGlobalBounds().width - wAddButtion.getSize().x;
    int wAddButtionY = 100;
    wAddButtion.setPosition(sf::Vector2f(wAddButtionX, wAddButtionY));

    wPlusSign.setCharacterSize(20);
    wPlusSign.setFont(chopsic_font);
    wPlusSign.setString("+");
    int wPlusSignX = wAddButtion.getPosition().x + wAddButtion.getSize().x * .5f - wPlusSign.getGlobalBounds().width * .5f;
    int wPlusSignY = wAddButtion.getPosition().y + wAddButtion.getSize().y * .5f - wPlusSign.getGlobalBounds().height;
    wPlusSign.setPosition(sf::Vector2f(wPlusSignX, wPlusSignY));

    currentWidth.setFont(roboto_font);
    currentWidth.setString(std::to_string(*mazeWidth));
    currentWidth.setCharacterSize(25);
    currentWidth.setPosition(wAddButtion.getPosition().x - currentWidth.getGlobalBounds().width - 20, 100);
    currentWidth.setFillColor(sf::Color::Black);

    wMinusButtion.setSize(sf::Vector2f(30, 30));
    wMinusButtion.setFillColor(sf::Color::Black);
    wMinusButtion.setPosition(sf::Vector2f(currentWidth.getPosition().x - 20 - wMinusButtion.getSize().x, 100));

    wMinusSign.setCharacterSize(20);
    wMinusSign.setFont(chopsic_font);
    wMinusSign.setString("-");
    int wMinusSignX = wMinusButtion.getPosition().x + wMinusButtion.getSize().x * .5f - wMinusSign.getGlobalBounds().width * .5f;
    int wMinusSignY = wMinusButtion.getPosition().y + wMinusButtion.getSize().y * .5f - wMinusSign.getGlobalBounds().height * 3;
    wMinusSign.setPosition(sf::Vector2f(wMinusSignX, wMinusSignY));

    optionHeight.setString("Maze height:");
    optionHeight.setCharacterSize(25);
    optionHeight.setFont(roboto_font);
    optionHeight.setPosition(sf::Vector2f(optionWidth.getPosition().x, optionWidth.getPosition().y + optionWidth.getGlobalBounds().height + 40));
    optionHeight.setFillColor(sf::Color::Black);

    hAddButtion.setSize(sf::Vector2f(30, 30));
    hAddButtion.setFillColor(sf::Color::Black);
    int hAddButtionX = title.getPosition().x + title.getGlobalBounds().width - hAddButtion.getSize().x;
    int hAddButtionY = optionHeight.getPosition().y;
    hAddButtion.setPosition(sf::Vector2f(hAddButtionX, hAddButtionY));

    hPlusSign.setCharacterSize(20);
    hPlusSign.setFont(chopsic_font);
    hPlusSign.setString("+");
    int hPlusSignX = hAddButtion.getPosition().x + hAddButtion.getSize().x * .5f - hPlusSign.getGlobalBounds().width * .5f;
    int hPlusSignY = hAddButtion.getPosition().y + hAddButtion.getSize().y * .5f - hPlusSign.getGlobalBounds().height;
    hPlusSign.setPosition(sf::Vector2f(hPlusSignX, hPlusSignY));

    currentHeight.setFont(roboto_font);
    currentHeight.setString(std::to_string(*mazeHeight));
    currentHeight.setCharacterSize(25);
    currentHeight.setPosition(hAddButtion.getPosition().x - currentHeight.getGlobalBounds().width - 20, optionHeight.getPosition().y);
    currentHeight.setFillColor(sf::Color::Black);

    hMinusButtion.setSize(sf::Vector2f(30, 30));
    hMinusButtion.setFillColor(sf::Color::Black);
    hMinusButtion.setPosition(sf::Vector2f(currentHeight.getPosition().x - 20 - hMinusButtion.getSize().x, optionHeight.getPosition().y));

    hMinusSign.setCharacterSize(20);
    hMinusSign.setFont(chopsic_font);
    hMinusSign.setString("-");
    int hMinusSignX = hMinusButtion.getPosition().x + hMinusButtion.getSize().x * .5f - hMinusSign.getGlobalBounds().width * .5f;
    int hMinusSignY = hMinusButtion.getPosition().y + hMinusButtion.getSize().y * .5f - hMinusSign.getGlobalBounds().height * 3;
    hMinusSign.setPosition(sf::Vector2f(hMinusSignX, hMinusSignY));
}

void MenuState::initText() {
    sf::Vector2u winSize = window->getSize();

    title.setFont(chopsic_font);
    title.setString("Maze Generator");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Black);

    title.setPosition(sf::Vector2f(winSize.x * .5f - title.getGlobalBounds().width * .5f, 0));

    buttonShape.setSize(sf::Vector2f(200, 50));
    buttonShape.setFillColor(sf::Color::Black);
    buttonShape.setPosition(sf::Vector2f(winSize.x * .5f - buttonShape.getSize().x * .5f, winSize.y - 2 * buttonShape.getSize().y - 30));

    quitButtonShape.setSize(sf::Vector2f(200, 50));
    quitButtonShape.setFillColor(sf::Color::Black);
    quitButtonShape.setPosition(sf::Vector2f(winSize.x * .5f - quitButtonShape.getSize().x * .5f, winSize.y - quitButtonShape.getSize().y - 20));

    start.setFont(chopsic_font);
    start.setString("Start");
    start.setCharacterSize(20);
    start.setFillColor(sf::Color::White);
    int startButtonX = buttonShape.getPosition().x + buttonShape.getSize().x * .5f - start.getGlobalBounds().width * .5f;
    int startButtonY = buttonShape.getPosition().y + buttonShape.getSize().y * .5f - start.getGlobalBounds().height * .75f;
    start.setPosition(sf::Vector2f(startButtonX, startButtonY));

    quit.setFont(chopsic_font);
    quit.setString("Quit");
    quit.setCharacterSize(20);
    quit.setFillColor(sf::Color::White);
    int quitButtonX = quitButtonShape.getPosition().x + quitButtonShape.getSize().x * .5f - quit.getGlobalBounds().width * .5f;
    int quitButtonY = quitButtonShape.getPosition().y + quitButtonShape.getSize().y * .5f - quit.getGlobalBounds().height * .75f;
    quit.setPosition(sf::Vector2f(quitButtonX, quitButtonY));
}

void MenuState::updateMousePos() {
    mousePosInt = sf::Mouse::getPosition(*window);
    mousePos = window->mapPixelToCoords(mousePosInt);
}

void MenuState::handleInput() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (!isHeld) {
            isHeld = true;
            if (buttonShape.getGlobalBounds().contains(mousePos)) {
                states.push(new MazeState(window, *mazeWidth, *mazeHeight, *cellWidth, *wallWidth, *borderWidth));
            }

            if (quitButtonShape.getGlobalBounds().contains(mousePos)) {
                states.pop();
            }

            if (wAddButtion.getGlobalBounds().contains(mousePos)) {
                if (*mazeWidth >= 50) return;
                *mazeWidth +=1;
                currentWidth.setString(std::to_string(*mazeWidth));
            }
            if (wMinusButtion.getGlobalBounds().contains(mousePos)) {
                if (*mazeWidth <= 5) return;
                *mazeWidth -=1;
                currentWidth.setString(std::to_string(*mazeWidth));
            }

            if (hAddButtion.getGlobalBounds().contains(mousePos)) {
                if (*mazeHeight >= 40) return;
                *mazeHeight += 1;
                currentHeight.setString(std::to_string(*mazeHeight));
            }
            if (hMinusButtion.getGlobalBounds().contains(mousePos)) {
                if (*mazeHeight <= 5) return;
                *mazeHeight -= 1;
                currentHeight.setString(std::to_string(*mazeHeight));
            }

        }
    } else {
        isHeld = false;
    }
}

void MenuState::update() {
    updateMousePos();
    handleInput();
}

void MenuState::render() {
    window->clear(sf::Color::White);
    window->draw(title);
    window->draw(buttonShape);
    window->draw(start);
    window->draw(quitButtonShape);
    window->draw(quit);
    window->draw(optionWidth);
    window->draw(currentWidth);
    window->draw(wAddButtion);
    window->draw(wMinusButtion);
    window->draw(wPlusSign);
    window->draw(wMinusSign);
    window->draw(optionHeight);
    window->draw(hAddButtion);
    window->draw(hPlusSign);
    window->draw(currentHeight);
    window->draw(hMinusButtion);
    window->draw(hMinusSign);
}

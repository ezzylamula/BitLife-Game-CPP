#include "Game.h"

#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "Enter your character name: ";
    std::getline(std::cin, name);

    if (name.empty()) {
        name = "Alex";
    }

    LifeGame game(name);
    game.run();
    return 0;
}

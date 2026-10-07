#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <utility>

namespace {
const int kMinAge = 18;
const int kMaxAge = 80;
}

LifeGame::LifeGame(std::string playerName)
    : player_{std::move(playerName)} {
    initializeEvents();
}

void LifeGame::initializeEvents() {
    lifeEvents_ = {
        "A friend introduces you to a promising side hustle.",
        "Your family asks for help with rent this month.",
        "You meet someone special and your social life improves.",
        "A sudden illness leaves you exhausted for a few weeks.",
        "A scholarship opportunity opens up for higher education.",
        "Your boss notices your hard work and gives you a promotion.",
        "Your health improves after a period of careful habits.",
        "An old friend invites you to a big social event.",
        "You discover a new passion that lifts your mood.",
        "Unexpected expenses hit and your budget gets tighter."
    };
}

int LifeGame::randomInt(int min, int max) const {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void LifeGame::showHeader() const {
    std::cout << "\n========================================================\n";
    std::cout << "  BitLife-inspired Life Simulator  |  " << player_.name << "\n";
    std::cout << "========================================================\n";
}

void LifeGame::showStats() const {
    std::cout << "Age: " << player_.age << "\n";
    std::cout << "Month: " << player_.month << "\n";
    std::cout << "Money: $" << player_.money << "\n";
    std::cout << "Health: " << player_.health << "/100\n";
    std::cout << "Happiness: " << player_.happiness << "/100\n";
    std::cout << "Intelligence: " << player_.intelligence << "/100\n";
    std::cout << "Energy: " << player_.energy << "/100\n";
    std::cout << "Stress: " << player_.stress << "/100\n";
    std::cout << "Relationship: " << player_.relationship << "/100\n";
    std::cout << "Education: " << player_.education << "/10\n";
    std::cout << "Job: " << player_.job << "\n";
    std::cout << "Children: " << player_.children << "\n";
    std::cout << "========================================================\n";
}

void LifeGame::showMenu() const {
    std::cout << "1. Study\n";
    std::cout << "2. Work\n";
    std::cout << "3. Socialize\n";
    std::cout << "4. Rest\n";
    std::cout << "5. Health Check\n";
    std::cout << "6. Apply for Job\n";
    std::cout << "7. Life Summary\n";
    std::cout << "8. Quit Game\n";
    std::cout << "Choose an action: ";
}

void LifeGame::showLifeSummary() const {
    std::cout << "\n===== Life Summary =====\n";
    std::cout << player_.name << " is " << player_.age << " years old and works as " << player_.job << ".\n";
    std::cout << "Balance: $" << player_.money << "\n";
    std::cout << "Current mood: " << (player_.happiness > 70 ? "Thriving" : player_.happiness > 40 ? "Stable" : "Struggling") << "\n";
    std::cout << "Education level: " << player_.education << "/10\n";
    std::cout << "Relationship score: " << player_.relationship << "/100\n";
    std::cout << "Health status: " << (player_.health > 70 ? "Excellent" : player_.health > 40 ? "Fair" : "Critical") << "\n";
    std::cout << "========================\n";
}

void LifeGame::advanceMonth() {
    player_.month += 1;
    if (player_.month > 12) {
        player_.month = 1;
        player_.age += 1;
    }

    player_.energy = std::max(0, player_.energy - 5);
    player_.stress = std::min(100, player_.stress + 5);
    player_.health = std::max(0, player_.health - 2);

    if (player_.age >= kMaxAge) {
        player_.alive = false;
        std::cout << "You reached the end of a long life. The game is over.\n";
        return;
    }

    if (randomInt(0, 100) < 35) {
        handleRandomEvent();
    }

    if (player_.health <= 10) {
        std::cout << "Your health is critically low. Rest and see a doctor soon.\n";
    }

    if (player_.money < 0) {
        player_.debt += 200;
        player_.money += 200;
        std::cout << "You fell behind on bills and took on debt.\n";
    }
}

void LifeGame::handleRandomEvent() {
    const std::string event = lifeEvents_[randomInt(0, static_cast<int>(lifeEvents_.size()) - 1)];
    std::cout << "\nRandom event: " << event << "\n";

    switch (randomInt(1, 6)) {
        case 1:
            player_.money += 200;
            player_.happiness += 10;
            std::cout << "You turn the opportunity into a small win.\n";
            break;
        case 2:
            player_.money -= 150;
            player_.health -= 10;
            std::cout << "Unexpected costs hit your budget and your energy dips.\n";
            break;
        case 3:
            player_.relationship += 15;
            player_.happiness += 8;
            std::cout << "A meaningful connection makes your life brighter.\n";
            break;
        case 4:
            player_.health -= 15;
            player_.energy -= 10;
            std::cout << "A brief illness drains your strength.\n";
            break;
        case 5:
            player_.intelligence += 5;
            player_.education += 1;
            std::cout << "You learn something valuable that sticks with you.\n";
            break;
        case 6:
            if (player_.jobLevel > 0) {
                player_.money += 300;
                player_.happiness += 7;
                std::cout << "Your effort gets noticed and your performance pays off.\n";
            } else {
                player_.happiness -= 5;
                std::cout << "No major change, but life keeps moving.\n";
            }
            break;
        default:
            break;
    }

    player_.happiness = std::clamp(player_.happiness, 0, 100);
    player_.health = std::clamp(player_.health, 0, 100);
    player_.energy = std::clamp(player_.energy, 0, 100);
    player_.stress = std::clamp(player_.stress, 0, 100);
    player_.relationship = std::clamp(player_.relationship, 0, 100);
    player_.intelligence = std::clamp(player_.intelligence, 0, 100);
}

void LifeGame::study() {
    player_.intelligence += randomInt(2, 6);
    player_.energy -= randomInt(10, 20);
    player_.stress += randomInt(5, 15);
    player_.happiness -= randomInt(0, 5);
    player_.money -= 50;

    if (player_.intelligence >= 70 && player_.education < 10) {
        player_.education += 1;
        std::cout << "You became more educated and sharper than before.\n";
    }

    std::cout << "You studied hard and invested in your future.\n";
}

void LifeGame::work() {
    if (player_.jobLevel == 0) {
        std::cout << "You need a job before you can work. Try applying for one first.\n";
        return;
    }

    const int salaryMap[] = {0, 1200, 1800, 2600, 4200, 6500};
    const int salary = salaryMap[player_.jobLevel];

    player_.money += salary;
    player_.energy -= randomInt(15, 25);
    player_.stress += randomInt(5, 15);
    player_.happiness -= randomInt(0, 8);

    std::cout << "You worked a shift and earned $" << salary << ".\n";
}

void LifeGame::socialize() {
    player_.happiness += randomInt(8, 16);
    player_.relationship += randomInt(5, 12);
    player_.energy -= randomInt(5, 12);
    player_.stress -= randomInt(4, 10);
    std::cout << "You spent time with others and made memories.\n";
}

void LifeGame::rest() {
    player_.energy += randomInt(20, 35);
    player_.health += randomInt(5, 12);
    player_.stress -= randomInt(10, 20);
    player_.money -= 20;
    player_.happiness += randomInt(3, 8);
    std::cout << "You took time to recover and recharge.\n";
}

void LifeGame::healthCheck() {
    player_.health += randomInt(8, 15);
    player_.energy -= randomInt(5, 10);
    player_.money -= 80;
    player_.stress -= randomInt(5, 10);
    std::cout << "You took care of your body and mind.\n";
}

void LifeGame::applyForJob() {
    std::cout << "\nAvailable jobs:\n";
    std::cout << "1. Fast Food Crew (Pay: $1200)\n";
    std::cout << "2. Retail Associate (Pay: $1800)\n";
    std::cout << "3. Office Assistant (Pay: $2600)\n";
    std::cout << "4. Manager (Pay: $4200)\n";
    std::cout << "5. Startup Founder (Pay: $6500)\n";
    std::cout << "Choose a job or press 0 to cancel: ";

    int selection = 0;
    std::cin >> selection;

    if (selection == 0) {
        std::cout << "You decided to keep searching.\n";
        return;
    }

    if (selection < 1 || selection > 5) {
        std::cout << "Invalid job selection.\n";
        return;
    }

    const std::string jobs[] = {"Fast Food Crew", "Retail Associate", "Office Assistant", "Manager", "Startup Founder"};
    player_.job = jobs[selection - 1];
    player_.jobLevel = selection;
    player_.happiness += 5;

    std::cout << "You secured a new job: " << player_.job << "\n";
}

void LifeGame::endGame() {
    std::cout << "\nThanks for playing " << player_.name << "!\n";
    std::cout << "Final year summary: " << player_.age << " years old, " << player_.job << ", $" << player_.money << " in savings.\n";
}

bool LifeGame::chooseMenuAction(int choice) {
    switch (choice) {
        case 1:
            study();
            break;
        case 2:
            work();
            break;
        case 3:
            socialize();
            break;
        case 4:
            rest();
            break;
        case 5:
            healthCheck();
            break;
        case 6:
            applyForJob();
            break;
        case 7:
            showLifeSummary();
            break;
        case 8:
            endGame();
            return false;
        default:
            std::cout << "Invalid option. Try again.\n";
            return true;
    }

    player_.health = std::clamp(player_.health, 0, 100);
    player_.happiness = std::clamp(player_.happiness, 0, 100);
    player_.energy = std::clamp(player_.energy, 0, 100);
    player_.stress = std::clamp(player_.stress, 0, 100);
    player_.relationship = std::clamp(player_.relationship, 0, 100);
    player_.intelligence = std::clamp(player_.intelligence, 0, 100);

    if (player_.health <= 0) {
        std::cout << "Your health dropped to zero. You could not continue the game.\n";
        return false;
    }

    advanceMonth();

    if (!player_.alive) {
        endGame();
        return false;
    }

    return true;
}

void LifeGame::run() {
    std::cout << "Welcome to your life simulation, " << player_.name << "!\n";
    std::cout << "Play through the years, make choices, and build a life.\n";

    while (player_.alive) {
        showHeader();
        showStats();
        showMenu();

        int choice = 0;
        std::cin >> choice;

        if (!chooseMenuAction(choice)) {
            break;
        }

        std::cout << "\nPress Enter to continue...\n";
        std::cin.ignore();
        std::cin.get();
    }
}

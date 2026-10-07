#pragma once

#include <string>
#include <vector>

class LifeGame {
public:
    explicit LifeGame(std::string playerName);
    void run();

private:
    struct Player {
        std::string name;
        int age = 18;
        int month = 1;
        int money = 1200;
        int health = 75;
        int happiness = 70;
        int intelligence = 40;
        int energy = 100;
        int stress = 20;
        int relationship = 25;
        int education = 0;
        int debt = 0;
        std::string job = "Unemployed";
        int jobLevel = 0;
        int children = 0;
        bool alive = true;
    };

    Player player_;
    std::vector<std::string> lifeEvents_;

    void initializeEvents();
    void showHeader() const;
    void showMenu() const;
    void showStats() const;
    void showLifeSummary() const;
    void advanceMonth();
    void handleRandomEvent();
    void study();
    void work();
    void socialize();
    void rest();
    void healthCheck();
    void applyForJob();
    void endGame();
    bool chooseMenuAction(int choice);
    int randomInt(int min, int max) const;
};

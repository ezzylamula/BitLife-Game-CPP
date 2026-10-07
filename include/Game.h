#pragma once

#include <string>
#include <vector>

struct Property {
    std::string name;
    int value;
    int yearPurchased;
    bool isPrimary;
};

struct Vehicle {
    std::string model;
    int value;
    int yearPurchased;
    int maintenanceCost;
};

struct Company {
    std::string name;
    std::string type; // "Tech", "Motor Manufacturing", "Pharmacy"
    int value;
    int yearFounded;
    int monthlyRevenue;
    int monthlyExpense;
    float ownership; // percentage ownership
};

class LifeGame {
public:
    explicit LifeGame(std::string playerName);
    void run();

private:
    struct Player {
        std::string name;
        int age = 18;
        int month = 1;
        int year = 2026;
        int money = 5000;
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
        int reputation = 0;

        std::vector<Property> properties;
        std::vector<Vehicle> vehicles;
        std::vector<Company> companies;
        float netWorth = 5000.0f;
    };

    Player player_;
    std::vector<std::string> lifeEvents_;

    void initializeEvents();
    void showHeader() const;
    void showMenu() const;
    void showStats() const;
    void showLifeSummary() const;
    void showWealthSummary() const;
    void advanceMonth();
    void handleRandomEvent();
    void study();
    void work();
    void socialize();
    void rest();
    void healthCheck();
    void applyForJob();
    void buyProperty();
    void buyVehicle();
    void startCompany();
    void manageCompanies();
    void investInCompany();
    void sellProperty();
    void sellVehicle();
    void viewAssets();
    void endGame();
    bool chooseMenuAction(int choice);
    int randomInt(int min, int max) const;
    void calculateNetWorth();
    void handleCompanyOperations();
    void handlePropertyTaxes();
    void handleVehicleMaintenance();
};

#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

namespace {
const int kMinAge = 18;
const int kMaxAge = 90;
}

LifeGame::LifeGame(std::string playerName)
    : player_{std::move(playerName)} {
    initializeEvents();
}

void LifeGame::initializeEvents() {
    lifeEvents_ = {
        "A friend introduces you to a promising business idea.",
        "Your family asks for help with housing expenses this month.",
        "You meet someone special and your social life improves.",
        "A sudden illness leaves you exhausted for a few weeks.",
        "A scholarship opportunity opens up for higher education.",
        "Your boss notices your hard work and gives you a promotion.",
        "Your health improves after a period of careful habits.",
        "An old friend invites you to a major city event.",
        "You discover a new passion that lifts your mood.",
        "Unexpected expenses hit and your budget gets tighter.",
        "A commercial property in your city becomes available.",
        "A startup founder offers you an equity opportunity.",
        "The local government invites community leaders to a summit.",
        "A luxury vehicle dealer offers a tempting financing deal.",
        "Your investments generate new income this month."
    };
}

int LifeGame::randomInt(int min, int max) const {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void LifeGame::calculateNetWorth() {
    int propertyTotal = 0;
    for (const auto& property : player_.properties) {
        propertyTotal += property.value;
    }

    int vehicleTotal = 0;
    for (const auto& vehicle : player_.vehicles) {
        vehicleTotal += vehicle.value;
    }

    int companyTotal = 0;
    for (const auto& company : player_.companies) {
        companyTotal += static_cast<int>(company.value * (company.ownership / 100.0f));
    }

    const int totalAssets = player_.money + propertyTotal + vehicleTotal + companyTotal;
    const int liabilities = player_.debt;
    player_.netWorth = static_cast<float>(totalAssets - liabilities);
}

void LifeGame::showHeader() const {
    std::cout << "\n========================================================\n";
    std::cout << "  BitLife-inspired Empire Life Simulator  |  " << player_.name << "\n";
    std::cout << "========================================================\n";
}

void LifeGame::showStats() const {
    std::cout << "Age: " << player_.age << "\n";
    std::cout << "Year: " << player_.year << "\n";
    std::cout << "Month: " << player_.month << "\n";
    std::cout << "Cash: $" << player_.money << "\n";
    std::cout << "Net Worth: $" << static_cast<int>(player_.netWorth) << "\n";
    std::cout << "Health: " << player_.health << "/100\n";
    std::cout << "Happiness: " << player_.happiness << "/100\n";
    std::cout << "Intelligence: " << player_.intelligence << "/100\n";
    std::cout << "Energy: " << player_.energy << "/100\n";
    std::cout << "Stress: " << player_.stress << "/100\n";
    std::cout << "Relationship: " << player_.relationship << "/100\n";
    std::cout << "Education: " << player_.education << "/10\n";
    std::cout << "Job: " << player_.job << "\n";
    std::cout << "Reputation: " << player_.reputation << "\n";
    std::cout << "Children: " << player_.children << "\n";
    std::cout << "========================================================\n";
}

void LifeGame::showMenu() const {
    std::cout << "1. Study\n";
    std::cout << "2. Work\n";
    std::cout << "3. Socialize\n";
    std::cout << "4. Rest\n";
    std::cout << "5. Health Check\n";
    std::cout << "6. Apply for Job / Career\n";
    std::cout << "7. Life Summary\n";
    std::cout << "8. Buy Property\n";
    std::cout << "9. Buy Vehicle\n";
    std::cout << "10. Start Company\n";
    std::cout << "11. View Assets\n";
    std::cout << "12. Wealth Summary\n";
    std::cout << "13. Quit Game\n";
    std::cout << "Choose an action: ";
}

void LifeGame::showLifeSummary() const {
    std::cout << "\n===== Life Summary =====\n";
    std::cout << player_.name << " is " << player_.age << " years old and works as " << player_.job << ".\n";
    std::cout << "Cash: $" << player_.money << "\n";
    std::cout << "Net worth: $" << static_cast<int>(player_.netWorth) << "\n";
    std::cout << "Current mood: " << (player_.happiness > 70 ? "Thriving" : player_.happiness > 40 ? "Stable" : "Struggling") << "\n";
    std::cout << "Education level: " << player_.education << "/10\n";
    std::cout << "Relationship score: " << player_.relationship << "/100\n";
    std::cout << "Health status: " << (player_.health > 70 ? "Excellent" : player_.health > 40 ? "Fair" : "Critical") << "\n";
    std::cout << "Business assets: " << player_.companies.size() << " companies\n";
    std::cout << "Properties owned: " << player_.properties.size() << "\n";
    std::cout << "Vehicles owned: " << player_.vehicles.size() << "\n";
    std::cout << "========================\n";
}

void LifeGame::showWealthSummary() const {
    std::cout << "\n===== Wealth Summary =====\n";
    std::cout << "Cash: $" << player_.money << "\n";
    std::cout << "Properties:\n";
    if (player_.properties.empty()) {
        std::cout << "  No properties owned.\n";
    } else {
        for (size_t i = 0; i < player_.properties.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << player_.properties[i].name
                      << " - $" << player_.properties[i].value << "\n";
        }
    }

    std::cout << "Vehicles:\n";
    if (player_.vehicles.empty()) {
        std::cout << "  No vehicles owned.\n";
    } else {
        for (size_t i = 0; i < player_.vehicles.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << player_.vehicles[i].model
                      << " - $" << player_.vehicles[i].value << "\n";
        }
    }

    std::cout << "Companies:\n";
    if (player_.companies.empty()) {
        std::cout << "  No companies owned.\n";
    } else {
        for (size_t i = 0; i < player_.companies.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << player_.companies[i].name << " ("
                      << player_.companies[i].type << ") - Ownership: "
                      << player_.companies[i].ownership << "%\n";
        }
    }
    std::cout << "Net worth: $" << static_cast<int>(player_.netWorth) << "\n";
    std::cout << "========================\n";
}

void LifeGame::handlePropertyTaxes() {
    if (player_.properties.empty()) {
        return;
    }

    int taxes = 0;
    for (const auto& property : player_.properties) {
        taxes += static_cast<int>(property.value * 0.02f);
    }

    if (taxes > 0) {
        player_.money -= taxes;
        std::cout << "Property tax paid: $" << taxes << "\n";
    }
}

void LifeGame::handleVehicleMaintenance() {
    if (player_.vehicles.empty()) {
        return;
    }

    int maintenance = 0;
    for (const auto& vehicle : player_.vehicles) {
        maintenance += vehicle.maintenanceCost;
    }

    if (maintenance > 0) {
        player_.money -= maintenance;
        std::cout << "Vehicle maintenance cost: $" << maintenance << "\n";
    }
}

void LifeGame::handleCompanyOperations() {
    if (player_.companies.empty()) {
        return;
    }

    for (auto& company : player_.companies) {
        const int monthlyDelta = company.monthlyRevenue - company.monthlyExpense;
        if (monthlyDelta > 0) {
            player_.money += monthlyDelta;
            company.value += static_cast<int>(monthlyDelta * 0.15f);
            std::cout << "Company update: " << company.name << " earned $" << monthlyDelta << " this month.\n";
        } else {
            player_.money += monthlyDelta;
            company.value = std::max(10000, company.value + monthlyDelta / 10);
            std::cout << "Company update: " << company.name << " had a lean month with $" << monthlyDelta << " in net flow.\n";
        }
    }
}

void LifeGame::advanceMonth() {
    player_.month += 1;
    player_.year += (player_.month > 12 ? 1 : 0);

    if (player_.month > 12) {
        player_.month = 1;
        player_.age += 1;
    }

    player_.energy = std::max(0, player_.energy - 5);
    player_.stress = std::min(100, player_.stress + 5);
    player_.health = std::max(0, player_.health - 2);

    handlePropertyTaxes();
    handleVehicleMaintenance();
    handleCompanyOperations();

    if (player_.age >= kMaxAge) {
        player_.alive = false;
        std::cout << "You reached the end of a long and impactful life. The game is over.\n";
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

    calculateNetWorth();
}

void LifeGame::handleRandomEvent() {
    const std::string event = lifeEvents_[randomInt(0, static_cast<int>(lifeEvents_.size()) - 1)];
    std::cout << "\nRandom event: " << event << "\n";

    switch (randomInt(1, 8)) {
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
        case 7:
            if (!player_.properties.empty()) {
                player_.money += 500;
                player_.happiness += 4;
                std::cout << "Your property appreciates and adds value to your portfolio.\n";
            } else {
                std::cout << "You see a chance to build wealth, but you do not own property yet.\n";
            }
            break;
        case 8:
            if (player_.reputation > 50) {
                player_.reputation += 10;
                player_.money += 1000;
                std::cout << "Your public reputation opens a political or business opportunity.\n";
            } else {
                player_.reputation += 5;
                std::cout << "You are beginning to gain recognition in your community.\n";
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
    player_.reputation = std::clamp(player_.reputation, 0, 1000);
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

    if (player_.education >= 5 && player_.jobLevel == 0) {
        std::cout << "Your education puts you in a stronger position for future careers.\n";
    }

    std::cout << "You studied hard and invested in your future.\n";
}

void LifeGame::work() {
    if (player_.jobLevel == 0) {
        std::cout << "You need a job before you can work. Try applying for one first.\n";
        return;
    }

    int salary = 0;
    switch (player_.jobLevel) {
        case 1: salary = 1200; break;
        case 2: salary = 1800; break;
        case 3: salary = 2600; break;
        case 4: salary = 4200; break;
        case 5: salary = 7600; break;
        case 6: salary = 12000; break;
        case 7: salary = 28000; break;
        case 8: salary = 90000; break;
        case 9: salary = 220000; break;
        case 10: salary = 500000; break;
        default: salary = 1500; break;
    }

    player_.money += salary;
    player_.energy -= randomInt(15, 25);
    player_.stress += randomInt(5, 15);
    player_.happiness -= randomInt(0, 8);
    player_.reputation += player_.jobLevel >= 8 ? 15 : 5;

    std::cout << "You worked and earned $" << salary << ".\n";
    calculateNetWorth();
}

void LifeGame::socialize() {
    player_.happiness += randomInt(8, 16);
    player_.relationship += randomInt(5, 12);
    player_.energy -= randomInt(5, 12);
    player_.stress -= randomInt(4, 10);
    player_.reputation += randomInt(0, 5);
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
    std::cout << "\nAvailable careers:\n";
    std::cout << "1. Fast Food Crew (Pay: $1200)\n";
    std::cout << "2. Retail Associate (Pay: $1800)\n";
    std::cout << "3. Office Assistant (Pay: $2600)\n";
    std::cout << "4. Manager (Pay: $4200)\n";
    std::cout << "5. Tech Entrepreneur (Pay: $7600)\n";
    std::cout << "6. Industrial Executive (Pay: $12000)\n";
    std::cout << "7. Pharmacist (Pay: $28000)\n";
    std::cout << "8. Mayor (Pay: $90000)\n";
    std::cout << "9. CEO (Pay: $220000)\n";
    std::cout << "10. Global Business Tycoon (Pay: $500000)\n";
    std::cout << "Choose a career or press 0 to cancel: ";

    int selection = 0;
    std::cin >> selection;

    if (selection == 0) {
        std::cout << "You decided to keep exploring your options.\n";
        return;
    }

    if (selection < 1 || selection > 10) {
        std::cout << "Invalid career selection.\n";
        return;
    }

    const std::string jobs[] = {
        "Fast Food Crew",
        "Retail Associate",
        "Office Assistant",
        "Manager",
        "Tech Entrepreneur",
        "Industrial Executive",
        "Pharmacist",
        "Mayor",
        "CEO",
        "Global Business Tycoon"
    };

    player_.job = jobs[selection - 1];
    player_.jobLevel = selection;
    player_.happiness += 5;

    if (selection >= 8) {
        player_.reputation += 20;
    }

    std::cout << "You secured a new career: " << player_.job << "\n";
}

void LifeGame::buyProperty() {
    std::cout << "\nAvailable properties:\n";
    std::cout << "1. Small Apartment - $120000\n";
    std::cout << "2. Family House - $240000\n";
    std::cout << "3. Luxury Villa - $500000\n";
    std::cout << "4. Commercial Unit - $800000\n";
    std::cout << "5. City Block - $1500000\n";
    std::cout << "Choose a property or press 0 to cancel: ";

    int choice = 0;
    std::cin >> choice;
    if (choice == 0) {
        std::cout << "You decided not to buy a property.\n";
        return;
    }

    const int prices[] = {120000, 240000, 500000, 800000, 1500000};
    const std::string names[] = {"Small Apartment", "Family House", "Luxury Villa", "Commercial Unit", "City Block"};

    if (choice < 1 || choice > 5) {
        std::cout << "Invalid property choice.\n";
        return;
    }

    const int price = prices[choice - 1];
    if (player_.money < price) {
        std::cout << "You cannot afford this property right now.\n";
        return;
    }

    Property property;
    property.name = names[choice - 1];
    property.value = price;
    property.yearPurchased = player_.year;
    property.isPrimary = (choice == 2 || choice == 3);

    player_.money -= price;
    player_.properties.push_back(property);
    calculateNetWorth();
    std::cout << "You bought " << property.name << " for $" << price << ".\n";
}

void LifeGame::buyVehicle() {
    std::cout << "\nAvailable vehicles:\n";
    std::cout << "1. Sedan - $35000\n";
    std::cout << "2. SUV - $55000\n";
    std::cout << "3. Luxury Car - $120000\n";
    std::cout << "4. Sports Car - $180000\n";
    std::cout << "5. Truck - $95000\n";
    std::cout << "Choose a vehicle or press 0 to cancel: ";

    int choice = 0;
    std::cin >> choice;
    if (choice == 0) {
        std::cout << "You decided not to buy a vehicle.\n";
        return;
    }

    const int prices[] = {35000, 55000, 120000, 180000, 95000};
    const std::string models[] = {"Sedan", "SUV", "Luxury Car", "Sports Car", "Truck"};
    const int maintenance[] = {1200, 1800, 3500, 4200, 2600};

    if (choice < 1 || choice > 5) {
        std::cout << "Invalid vehicle choice.\n";
        return;
    }

    const int price = prices[choice - 1];
    if (player_.money < price) {
        std::cout << "You cannot afford this vehicle right now.\n";
        return;
    }

    Vehicle vehicle;
    vehicle.model = models[choice - 1];
    vehicle.value = price;
    vehicle.yearPurchased = player_.year;
    vehicle.maintenanceCost = maintenance[choice - 1];

    player_.money -= price;
    player_.vehicles.push_back(vehicle);
    calculateNetWorth();
    std::cout << "You bought a " << vehicle.model << " for $" << price << ".\n";
}

void LifeGame::startCompany() {
    std::cout << "\nCompany opportunities:\n";
    std::cout << "1. Tech Startup - $400000\n";
    std::cout << "2. Motor Manufacturing Plant - $900000\n";
    std::cout << "3. Pharmacy Chain - $700000\n";
    std::cout << "Choose a company or press 0 to cancel: ";

    int choice = 0;
    std::cin >> choice;
    if (choice == 0) {
        std::cout << "You decided not to start a company.\n";
        return;
    }

    const int costs[] = {400000, 900000, 700000};
    const std::string types[] = {"Tech", "Motor Manufacturing", "Pharmacy"};
    const std::string names[] = {"Northstar Tech", "VoltForge Motors", "MercyCare Pharma"};

    if (choice < 1 || choice > 3) {
        std::cout << "Invalid company selection.\n";
        return;
    }

    const int cost = costs[choice - 1];
    if (player_.money < cost) {
        std::cout << "You cannot afford to start this business.\n";
        return;
    }

    Company company;
    company.name = names[choice - 1];
    company.type = types[choice - 1];
    company.value = cost;
    company.yearFounded = player_.year;
    company.monthlyRevenue = (choice == 1) ? 120000 : (choice == 2) ? 180000 : 140000;
    company.monthlyExpense = (choice == 1) ? 70000 : (choice == 2) ? 110000 : 80000;
    company.ownership = 100.0f;

    player_.money -= cost;
    player_.companies.push_back(company);
    calculateNetWorth();
    std::cout << "You founded " << company.name << " and own a " << company.type << " company.\n";
}

void LifeGame::manageCompanies() {
    if (player_.companies.empty()) {
        std::cout << "You do not own any companies yet.\n";
        return;
    }

    std::cout << "\nYour companies:\n";
    for (size_t i = 0; i < player_.companies.size(); ++i) {
        std::cout << i + 1 << ". " << player_.companies[i].name
                  << " (" << player_.companies[i].type << ") - Value: $"
                  << player_.companies[i].value << "\n";
    }

    std::cout << "Press 0 to cancel or choose a company to review: ";
    int choice = 0;
    std::cin >> choice;

    if (choice == 0) {
        return;
    }

    if (choice < 1 || choice > static_cast<int>(player_.companies.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }

    Company& company = player_.companies[choice - 1];
    std::cout << "Company: " << company.name << "\n";
    std::cout << "Type: " << company.type << "\n";
    std::cout << "Value: $" << company.value << "\n";
    std::cout << "Monthly revenue: $" << company.monthlyRevenue << "\n";
    std::cout << "Monthly expense: $" << company.monthlyExpense << "\n";
    std::cout << "Ownership: " << company.ownership << "%\n";
}

void LifeGame::investInCompany() {
    if (player_.companies.empty()) {
        std::cout << "There are no companies in your portfolio to invest in.\n";
        return;
    }

    std::cout << "Choose a company to expand your ownership:\n";
    for (size_t i = 0; i < player_.companies.size(); ++i) {
        std::cout << i + 1 << ". " << player_.companies[i].name << "\n";
    }
    std::cout << "Press 0 to cancel: ";

    int index = 0;
    std::cin >> index;
    if (index == 0) {
        return;
    }

    if (index < 1 || index > static_cast<int>(player_.companies.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }

    Company& company = player_.companies[index - 1];
    const int investment = static_cast<int>(company.value * 0.10f);
    if (player_.money < investment) {
        std::cout << "You cannot afford to increase your ownership.\n";
        return;
    }

    player_.money -= investment;
    company.ownership = std::min(100.0f, company.ownership + 10.0f);
    company.value += investment;
    std::cout << "You invested $" << investment << " and increased ownership in " << company.name << " to "
              << company.ownership << "%.\n";
    calculateNetWorth();
}

void LifeGame::sellProperty() {
    if (player_.properties.empty()) {
        std::cout << "You do not own any property to sell.\n";
        return;
    }

    std::cout << "Properties available to sell:\n";
    for (size_t i = 0; i < player_.properties.size(); ++i) {
        std::cout << i + 1 << ". " << player_.properties[i].name << " - $" << player_.properties[i].value << "\n";
    }
    std::cout << "Choose a property to sell or press 0 to cancel: ";

    int selection = 0;
    std::cin >> selection;
    if (selection == 0) {
        return;
    }

    if (selection < 1 || selection > static_cast<int>(player_.properties.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }

    const int sellValue = static_cast<int>(player_.properties[selection - 1].value * 0.82f);
    std::cout << "You sold " << player_.properties[selection - 1].name << " for $" << sellValue << ".\n";
    player_.money += sellValue;
    player_.properties.erase(player_.properties.begin() + (selection - 1));
    calculateNetWorth();
}

void LifeGame::sellVehicle() {
    if (player_.vehicles.empty()) {
        std::cout << "You do not own any vehicles to sell.\n";
        return;
    }

    std::cout << "Vehicles available to sell:\n";
    for (size_t i = 0; i < player_.vehicles.size(); ++i) {
        std::cout << i + 1 << ". " << player_.vehicles[i].model << " - $" << player_.vehicles[i].value << "\n";
    }
    std::cout << "Choose a vehicle to sell or press 0 to cancel: ";

    int selection = 0;
    std::cin >> selection;
    if (selection == 0) {
        return;
    }

    if (selection < 1 || selection > static_cast<int>(player_.vehicles.size())) {
        std::cout << "Invalid selection.\n";
        return;
    }

    const int sellValue = static_cast<int>(player_.vehicles[selection - 1].value * 0.75f);
    std::cout << "You sold your " << player_.vehicles[selection - 1].model << " for $" << sellValue << ".\n";
    player_.money += sellValue;
    player_.vehicles.erase(player_.vehicles.begin() + (selection - 1));
    calculateNetWorth();
}

void LifeGame::viewAssets() {
    std::cout << "\n===== Assets =====\n";
    std::cout << "Properties:\n";
    if (player_.properties.empty()) {
        std::cout << "  None\n";
    } else {
        for (const auto& property : player_.properties) {
            std::cout << "  - " << property.name << " valued at $" << property.value << "\n";
        }
    }

    std::cout << "Vehicles:\n";
    if (player_.vehicles.empty()) {
        std::cout << "  None\n";
    } else {
        for (const auto& vehicle : player_.vehicles) {
            std::cout << "  - " << vehicle.model << " valued at $" << vehicle.value << "\n";
        }
    }

    std::cout << "Companies:\n";
    if (player_.companies.empty()) {
        std::cout << "  None\n";
    } else {
        for (const auto& company : player_.companies) {
            std::cout << "  - " << company.name << " (" << company.type << ") valued at $" << company.value << "\n";
        }
    }
    std::cout << "==================\n";
}

void LifeGame::endGame() {
    std::cout << "\nThanks for playing " << player_.name << "!\n";
    std::cout << "Final year summary: " << player_.age << " years old, " << player_.job << ", net worth: $"
              << static_cast<int>(player_.netWorth) << ".\n";
    std::cout << "You built a legacy with " << player_.properties.size() << " properties, "
              << player_.vehicles.size() << " vehicles, and " << player_.companies.size() << " companies.\n";
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
            buyProperty();
            break;
        case 9:
            buyVehicle();
            break;
        case 10:
            startCompany();
            break;
        case 11:
            viewAssets();
            break;
        case 12:
            showWealthSummary();
            break;
        case 13:
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
    player_.reputation = std::clamp(player_.reputation, 0, 1000);

    if (player_.health <= 0) {
        std::cout << "Your health dropped to zero. You could not continue the game.\n";
        return false;
    }

    if (choice != 8 && choice != 9 && choice != 10 && choice != 11 && choice != 12 && choice != 6 && choice != 7) {
        advanceMonth();
    }

    calculateNetWorth();

    if (!player_.alive) {
        endGame();
        return false;
    }

    return true;
}

void LifeGame::run() {
    std::cout << "Welcome to your life simulation, " << player_.name << "!\n";
    std::cout << "Play through the years, make choices, and build a legacy.\n";
    calculateNetWorth();

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

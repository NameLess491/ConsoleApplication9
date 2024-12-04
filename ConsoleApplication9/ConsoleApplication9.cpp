//Unit.h
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <utility>

class Unit {
private:
    std::string name;
    int health;
    std::pair<int, int> position;

public:
    Unit(const std::string& name, int health, int x, int y);

    std::string getName() const;
    int getHealth() const;
    std::pair<int, int> getPosition() const;

    void setName(const std::string& name);
    void setHealth(int health);
    void setPosition(int x, int y);

    void move(int dx, int dy);
};

#endif
//Unit.cpp
#include "Unit.h"

Unit::Unit(const std::string& name, int health, int x, int y)
    : name(name), health(health), position(x, y) {}

std::string Unit::getName() const {
    return name;
}

int Unit::getHealth() const {
    return health;
}

std::pair<int, int> Unit::getPosition() const {
    return position;
}

void Unit::setName(const std::string& name) {
    this->name = name;
}

void Unit::setHealth(int health) {
    this->health = health;
}

void Unit::setPosition(int x, int y) {
    position = { x, y };
}

void Unit::move(int dx, int dy) {
    position.first += dx;
    position.second += dy;
}
//Team.h
#ifndef TEAM_H
#define TEAM_H

#include "Unit.h"
#include <vector>

class Team {
private:
    std::string teamName;
    std::vector<Unit> members;

public:
    Team(const std::string& teamName);

    void addMember(const Unit& unit);
    void removeMember(const std::string& name);
    Unit* findMember(const std::string& name);

    void displayTeam() const;
};

#endif
//Team.cpp
#include "Team.h"
#include <iostream>

Team::Team(const std::string& teamName) : teamName(teamName) {}

void Team::addMember(const Unit& unit) {
    members.push_back(unit);
}

void Team::removeMember(const std::string& name) {
    members.erase(std::remove_if(members.begin(), members.end(),
        [&name](const Unit& unit) { return unit.getName() == name; }),
        members.end());
}

Unit* Team::findMember(const std::string& name) {
    for (auto& member : members) {
        if (member.getName() == name)
            return &member;
    }
    return nullptr;
}

void Team::displayTeam() const {
    std::cout << "Team: " << teamName << "\nMembers:\n";
    for (const auto& member : members) {
        auto [x, y] = member.getPosition();
        std::cout << "Name: " << member.getName()
            << ", Health: " << member.getHealth()
            << ", Position: (" << x << ", " << y << ")\n";
    }
}
//main.cpp
#include "Unit.h"
#include "Team.h"
#include <iostream>

int main() {
    Unit u1("Warrior", 100, 0, 0);
    Unit u2("Mage", 80, 1, 1);

    Team team("Alpha");
    team.addMember(u1);
    team.addMember(u2);

    team.displayTeam();

    Unit* found = team.findMember("Mage");
    if (found) {
        found->move(2, 2);
    }

    team.displayTeam();

    team.removeMember("Warrior");
    team.displayTeam();

    return 0;
}

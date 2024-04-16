/*
Author: Sean Lai Sheng Hong
Filename: noble.h
Purpose: Function Prototypes for the Noble class in namespace WarriorCraft

*/
#include<vector>
#include<iostream>
#include<string>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft{
    class Warrior;

    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
        public:
            // Constructor
            Noble(const std::string& name);
            // Battle another Noble
            void battle(Noble& otherNoble);
            // Check Name of the Noble
            bool checkName(const std::string& name) const;
            // Get the name of the Noble
            const std::string& getName() const;
            // Hire a warrior
            bool hire(Warrior& warrior);
            // Fire a warrior
            bool fire(Warrior& warrior);
            // Remove a specific warrior from the army (helper function)
            bool removeWarrior(Warrior& warrior);
    private:
        std::string name;
        double armyStrength;
        std::vector<Warrior*> army;
};
}
#endif
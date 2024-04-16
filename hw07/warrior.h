/*
Author: Sean Lai Sheng Hong
Filename: warrior.h
Purpose: Prototypes for the Warrior class in namespace WarriorCraft
*/
#include<iostream>
#include<string>

#ifndef WARRIOR_H
#define WARRIOR_H
namespace WarriorCraft{
    class Noble;
    // Warrior: Battles for a Noble
    class Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
        public:
            // Constructor
            Warrior(const std::string& name, double strength);
            // Get the strength of the warrior
            double getStrength() const;
            // Get the name of the warrior
            const std::string& getName() const;
            // Check name of the warrior
            bool checkName(const std::string& name) const;
            // Reduce the strength of the warrior
            void reduceStrength(double ratio);
            // Set the who Hired the warrior
            void setHired(Noble* master);
            // Check if the warrior is hired
            bool isHired() const;
            // Runaway from the noble
            bool runaway();
        private:
        // Data members
            std::string name;
            double strength;
            Noble* master;
    };

}
#endif
/*
Author: Sean Lai Sheng Hong
file: Protectors.h
Purpose: Prototype for the Protectors class and its children
*/
#include <iostream>
#include <string>

#ifndef PROTECTORS_H
#define PROTECTORS_H
namespace WarriorCraft{
    class Lord;
    class Protectors{
    friend std::ostream& operator<<(std::ostream& os, const Protectors& rhs);
    public:
        Protectors(const std::string& name, double strength);
        // Get the strength of the warrior
        double getStrength() const;
        // Get the name of the warrior
        const std::string& getName() const;
        // Check name of the warrior
        bool checkName(const std::string& name) const;
        // Reduce the strength of the warrior
        void reduceStrength(double ratio);
        // Set the who Hired the warrior
        void setHired(WarriorCraft::Lord* lord);
        // Check if the warrior is hired
        bool isHired() const;
        // Runaway from the noble
        bool runaway();
        // Enable poly non-member display, print the protector details
        virtual void battleCry() const = 0;
        
    protected:
        Lord* getLord() const;
    private:
        std::string name;
        double strength;
        Lord* lord;
    };

    class Warriors : public Protectors{
    public:
        using Protectors::Protectors;
        void battleCry() const override;
    };
    class Archer : public Warriors{
        public:
            using Warriors::Warriors;
            void battleCry() const override;
    };

    class Swordsman : public Warriors{
        public:
            using Warriors::Warriors;
            void battleCry() const override;
    };

    class Wizard : public Protectors{
    public:
        using Protectors::Protectors;
        void battleCry() const override;
    };

};
#endif
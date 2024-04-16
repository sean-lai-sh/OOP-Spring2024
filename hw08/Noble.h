/*
Author: Sean Lai Sheng Hong
file: Noble.h
Purpose: Prototype for the Noble class and its children
*/
#include <iostream>
#include <string>
#include <vector>

#ifndef NOBLE_H
#define NOBLE_H
namespace WarriorCraft{
    class Protectors;

    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
        public:
            Noble(const std::string& name, double strength);
            // Battle another Noble
            void battle(Noble& otherNoble);
            // BattleCall Display
            virtual void battleCall() const = 0;
            // Enabling polynon-member display
            virtual void display(std::ostream& os) const = 0;
            virtual void adjustStrength(double otherStrength) = 0;
            const std::string& getName() const;
        protected:
            void setStrength(double newStrength);
            double getStrength() const;
        private:
        std::string name;
        double strength;
    };
    class Lord : public Noble{
        public:
            Lord(const std::string& name);
            bool hires(Protectors& servant);
            bool fires(Protectors& servant);
            void battleCall() const override;
            void display(std::ostream& os) const override;
            void adjustStrength(double otherStrength) override;
            // remove a warrior from the army
            bool removeProtector(Protectors& protector);
        private:
            std::vector<Protectors*> army;
    };
    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void battleCall() const override;
        void display(std::ostream& os) const override;
        void adjustStrength(double otherStrength) override;
    };
};
#endif
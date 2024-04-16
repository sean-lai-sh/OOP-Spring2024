#include<iostream>
#include<string>

#ifndef PERSONWITHSTRENGTHTOFIGHT_H
#define PERSONWITHSTRENGTHTOFIGHT_H
namespace WarriorCraft{
    class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);
        void battleCall() const override;
        void display(std::ostream& os) const override;
        void adjustStrength(double otherStrength) override;
    }
};
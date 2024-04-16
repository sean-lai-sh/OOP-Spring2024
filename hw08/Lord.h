#include <iostream>
#include <string>
#include <vector>

#ifndef LORD_H
#define LORD_H
namespace WarriorCraft{
    class Protectors;
    class Noble;
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
    }   
};
#endif
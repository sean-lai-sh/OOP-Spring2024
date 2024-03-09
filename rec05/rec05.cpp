/*
  Sean Lai Sheng Hong
  Purpose: Learn Classes, Delgation, and Copy Control
  rec05.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;




class Section{
     class studentRecord{
          friend ostream& operator<<(ostream& os, const studentRecord& rhs){
               os <<"Name: " <<  rhs.name << " Grades: ";
               for(size_t i = 0; i < rhs.grades.size(); i++){
                    os << rhs.grades[i] << " ";
               }
               return os;
          }
          public:
               // Constructor initializes the name and the grades vector to size 14
               studentRecord(const string& name): name(name), grades(14, -1) {}

               // Get the name of the student
               const string& getName() const{
                    return name;
               }

               // Add a grade to the student
               bool addGrade(int grade, int week){
                    if(week < 1 || week > 14){
                         return false;
                    }
                    grades[week-1] = grade;
                    return true;
               }
          private:
               string name;
               vector<int> grades;
     };
     class TimeSlot{
          friend ostream& operator<<(ostream& os, const TimeSlot& rhs){
               if (rhs.time < 12){
                    os << "[Day: " << rhs.day << ", Start Time: " << rhs.time << "AM]";
               }else{
                    os << "[Day: " << rhs.day << ", Start Time: " << rhs.time - 12 << "PM]";
               }
               return os;
          }
          public:
               TimeSlot(const string& day, int time): day(day), time(time){}
          private:
               string day;
               int time;
     };
     friend ostream& operator<<(ostream& os, const Section& rhs){
          os << "Section: " << rhs.sectionName << ", " << rhs.slot << ", Students: ";
          if (rhs.students.size() == 0){
               os << "None";
          }
          for(size_t i = 0; i < rhs.students.size(); i++){
               os << "\n" <<  *rhs.students[i];
          }
          return os;
     }
     public:
          Section(const string& sectionName, const string& day, int time): 
          sectionName(sectionName), slot(day, time){}

          bool addStudent(const string& name){
               for(size_t i = 0; i < students.size(); i++){
                    if(students[i]->getName() == name){
                         return false;
                    }
               }
               studentRecord* newStudent = new studentRecord(name);
               students.push_back(newStudent);
               return true;
          }
          bool addGrade(const string& name, int grade, int week){
               for(size_t i = 0; i < students.size(); i++){
                    if(students[i]->getName() == name){
                         return students[i]->addGrade(grade, week);
                    }
               }
               return false;
          }
          ~Section(){
               cout << "Section " << sectionName << " is being deleted\n";
               for(size_t i = 0; i < students.size(); i++){
                    cout << "Deleting " << students[i]->getName() << "\n";
                    delete students[i];
                    students[i] = nullptr;
                    
               }
               students.clear(); // Extra but PLEASE DO outside of class
          }

          Section(const Section& rhs): sectionName(rhs.sectionName), slot(rhs.slot){
               for(size_t i = 0; i < rhs.students.size(); i++){
                    students.push_back(new studentRecord(*rhs.students[i]));
               }
          }

     private:
          string sectionName;
          TimeSlot slot;
          vector<studentRecord*> students;

};

class LabWorker{
     friend ostream& operator<<(ostream& os, const LabWorker& rhs){
          os << rhs.name;
          if(rhs.section != nullptr){
               os << " has " << *rhs.section;
          }else{
               os << " does not have a section";
          }
          return os;
     }
     public:
          LabWorker(const string& name): name(name), section(nullptr){}
          bool addSection(Section& newSection){
               section = &newSection;
               return true;
          }
          bool addGrade(const string& name, int grade, int week){
               bool added = false;
               if(section != nullptr){
                    added = section->addGrade(name, grade, week);
               }

               return added;
          }
     private:
          string name;
          Section* section;
};
// Test code
void doNothing(Section sec) { cout << sec << endl; }




int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    // cout << secA2 << endl;

} // main

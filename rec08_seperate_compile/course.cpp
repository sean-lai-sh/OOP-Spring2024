#include "student.h"
#include "course.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;
namespace BrooklynPoly {
    /// @brief  Course Code Implementation
    
    ostream& operator<<(ostream& os, const Course& rhs) {
        os << rhs.name << ": ";
        if (rhs.students.size() == 0) {
            os << "No Students" << endl;
        } else {
            for (size_t i = 0; i < rhs.students.size(); i++) {
                os << rhs.students[i]->getName();
            }
            os << endl;
        }
        return os;
    }

    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const {
        return name;
    }

    bool Course::addStudent(Student* student) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i] == student) {
                return false;
            }
        }
        students.push_back(student);
        return true;
    }

    void Course::removeStudentsFromCourse() {
        for (size_t i = 0; i < students.size(); i++) {
            students[i]->removedFromCourse(this);
        }
        students.clear();
    }

    void Course::removeStudentFromCourse(const string& studentName){ 
        for (size_t i = 0; i < students.size(); i++) {
            if(students[i]->getName() == studentName){
                students[i]->removedFromCourse(this);
                for(size_t j = i; j < students.size() - 1; j++){
                    students[j] = students[j + 1];
                }
                students.pop_back();
                return;
            }
            
        }
        students.clear();
    }
}
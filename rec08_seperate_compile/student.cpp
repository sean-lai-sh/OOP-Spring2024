#include "student.h"
#include "course.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

/// @brief  Student Code Implementation
namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Student& rhs) {
        os << rhs.name;
        os << ": ";
        if (rhs.courses.size() == 0) {
            os << "No Courses" << endl;
        } else {
            for (size_t i = 0; i < rhs.courses.size(); i++) {
                os << rhs.courses[i]->getName() << " ";
            }
            os << endl;
        }
        return os;
    }

    Student::Student(const string& name) : name(name) {}

    const string& Student::getName() const {
        return name;
    }

    bool Student::addCourse(Course* course) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i] == course) {
                return false;
            }
        }
        courses.push_back(course);
        return true;
    }

    void Student::removedFromCourse(Course* course) {
        /// IF order is not required
        // for (size_t i = 0; i < courses.size(); i++) {
        //     if (courses[i] == course) {
        //         courses[i] = courses[courses.size() - 1];
        //         courses.pop_back();
        //         return;
        //     }
        // }
        // IF order is required
        for(size_t i = 0; i < courses.size(); i++){
            if(courses[i] == course){
                for(size_t j = i; j < courses.size() - 1; j++){
                    courses[j] = courses[j + 1];
                }
                courses.pop_back();
                return;
            }
        }
    }

    bool Student::changeName(const string& newName){
        name = newName;
        return true;
    }
}
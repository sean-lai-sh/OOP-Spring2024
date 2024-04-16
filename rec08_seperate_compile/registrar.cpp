#include "student.h"
#include "course.h"
#include "registrar.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;
/// @brief  Registrar Code Implementation
namespace BrooklynPoly{
    ostream& operator<<(ostream& os, const Registrar& rhs) {
        os << "Registrar's Report" << endl;
        os << "Courses: " << endl;
        for (size_t i = 0; i < rhs.courses.size(); i++) {
            os << *rhs.courses[i];
        }
        os << "Students: " << endl;
        for (size_t i = 0; i < rhs.students.size(); i++) {
            os << *rhs.students[i];
        }
        return os;
    }

    Registrar::Registrar() : courses(0), students(0) {}

    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) == courses.size()) {
            courses.push_back(new Course(courseName));
            return true;
        }
        return false;
    }

    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) == students.size()) {
            students.push_back(new Student(studentName));
            return true;
        }
        return false;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName,
                                        const string& courseName) {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if (studentIndex == students.size() || courseIndex == courses.size()) {
            return false;
        }
        return students[studentIndex]->addCourse(courses[courseIndex]) &&
            courses[courseIndex]->addStudent(students[studentIndex]);
    }

    /// Optional Methods

    bool Registrar::changeStudentName(const string& oldName, const string& newName){
        size_t studentIndex = findStudent(oldName);
        if(studentIndex == students.size()){
            return false;
        }
        students[studentIndex]->changeName(newName);
        return true;
    }

    bool Registrar::dropStudentFromCourse(const string& studentName, const string& courseName){
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);
        if(studentIndex == students.size() || courseIndex == courses.size()){
            return false;
        }
        students[studentIndex]->removedFromCourse(courses[courseIndex]);
        courses[courseIndex]->removeStudentFromCourse(students[studentIndex]->getName());
        return true;
    }

    bool Registrar::removeStudent(const string& studentName){
        size_t studentIndex = findStudent(studentName);
        if(studentIndex == students.size()){
            return false;
        }
        /// Iterate through courses and remove current student from all courses
        
        delete students[studentIndex];
        for(size_t i = studentIndex; i < students.size() - 1; i++){
            students[i] = students[i + 1];
        }
        students.pop_back();
        return true;
    }
    ///Optional Methods End


    bool Registrar::cancelCourse(const string& courseName) {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == courses.size()) {
            return false;
        }
        courses[courseIndex]->removeStudentsFromCourse();
        delete courses[courseIndex];
        courses[courseIndex] = courses[courses.size() - 1];
        courses.pop_back();
        return true;
    }

    void Registrar::purge(){
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i]->removeStudentsFromCourse();
            delete courses[i];
        }
        for (size_t i = 0; i < students.size(); i++) {
            delete students[i];
        }
        courses.clear();
        students.clear();
    }



    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i]->getName() == studentName) {
                return i;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getName() == courseName) {
                return i;
            }
        }
        return courses.size();
    }
}
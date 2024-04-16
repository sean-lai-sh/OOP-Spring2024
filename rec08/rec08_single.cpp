/*
  Sean Lai Sheng Hong
  Date: March 15 2024
  rec08_single.cpp
  single file version of rec08
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse(); 

    // Remove a student from the course (For optional Method 2)
    void removeStudentFromCourse(const string& studentName);

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);
    bool changeName(const string& newName);
    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Change a given student's name if the student exists
    bool changeStudentName(const string& oldName, const string& newName);

    // Drop a student from a course if the student and course exists
    bool dropStudentFromCourse(const string& studentName,
                                 const string& courseName);
    // Remove a student from the registrar if the student exists
    bool removeStudent(const string& studentName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

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

/// @brief  Student Code Implementation

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


/// @brief  Registrar Code Implementation

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
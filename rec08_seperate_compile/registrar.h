#include<iostream>
#include<string>
#include<vector>

#ifndef REGISTRAR_H
#define REGISTRAR_H
namespace BrooklynPoly{
    class Course;
    class Student;
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();

        // Creates a new course, if none with that name
        bool addCourse(const std::string&);
        // Creates a new student, if none with that name
        bool addStudent(const std::string&);

        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName);

        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const std::string& courseName);

        // Change a given student's name if the student exists
        bool changeStudentName(const std::string& oldName, const std::string& newName);

        // Drop a student from a course if the student and course exists
        bool dropStudentFromCourse(const std::string& studentName,
                                    const std::string& courseName);
        // Remove a student from the registrar if the student exists
        bool removeStudent(const std::string& studentName);

        // Get rid of everything!!!
        void purge();

    private:
        size_t findStudent(const std::string&) const;
        size_t findCourse(const std::string&) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    };
}
#endif
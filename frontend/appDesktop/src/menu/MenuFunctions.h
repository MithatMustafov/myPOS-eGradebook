#pragma once
#include "../lib/httplib.h"
#include "Actions/StudentActions.h"
#include "Actions/SubjectActions.h"
#include "Actions/GradeActions.h"
#include "Actions/AnalyticsActions.h"

class MenuFunctions {
public:
    MenuFunctions();

    // Student Actions
    void addStudent() { studentOps.addStudent(); }
    void editStudent() { studentOps.editStudent(); }
    void deleteStudent() { studentOps.deleteStudent(); }
    void displayStudents() { studentOps.displayStudents(); }

    // Subject Actions
    void addSubject() { subjectOps.addSubject(); }
    void editSubject() { subjectOps.editSubject(); }
    void deleteSubject() { subjectOps.deleteSubject(); }
    void displaySubjects() { subjectOps.displaySubjects(); }

    // Grade Actions
    void addGrade() { gradeOps.addGrade(); }
    void editGrade() { gradeOps.editGrade(); }
    void deleteGrade() { gradeOps.deleteGrade(); }
    void displayGrades() { gradeOps.displayGrades(); }

    // Analytics Actions
    void calculateAverageInSubject() { analyticsOps.calculateAverageInSubject(); }
    void calculateAverageOverall() { analyticsOps.calculateAverageOverall(); }
    void displayTopStudents() { analyticsOps.displayTopStudents(); }
    void displayRemedialExamStudents() { analyticsOps.displayRemedialExamStudents(); }
    void displayLowGradeStudents() { analyticsOps.displayLowGradeStudents(); }
    void displayBirthdayToday() { analyticsOps.displayBirthdayToday(); }

private:
    httplib::Client cli;
    StudentActions studentOps;
    SubjectActions subjectOps;
    GradeActions gradeOps;
    AnalyticsActions analyticsOps;
}; 
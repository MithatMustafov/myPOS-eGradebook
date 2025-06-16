#pragma once
#include <string>
#include "../../lib/httplib.h"

class AnalyticsActions {
public:
    explicit AnalyticsActions(httplib::Client& client) : cli(client) {}
    
    void calculateAverageInSubject();
    void calculateAverageOverall();
    void displayTopStudents();
    void displayRemedialExamStudents();
    void displayLowGradeStudents();
    void displayBirthdayToday();

private:
    httplib::Client& cli;
}; 
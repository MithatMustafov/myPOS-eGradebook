#pragma once
#include <string>
#include "../../lib/httplib.h"

class GradeActions {
public:
    explicit GradeActions(httplib::Client& client) : cli(client) {}
    
    void addGrade();
    void editGrade();
    void deleteGrade();
    void displayGrades();

private:
    httplib::Client& cli;
}; 
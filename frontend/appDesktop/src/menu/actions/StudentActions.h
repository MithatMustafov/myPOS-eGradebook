#pragma once
#include <string>
#include "../../lib/httplib.h"

class StudentActions {
public:
    explicit StudentActions(httplib::Client& client) : cli(client) {}
    
    void addStudent();
    void editStudent();
    void deleteStudent();
    void displayStudents();

private:
    httplib::Client& cli;
}; 
#pragma once
#include <string>
#include "../../lib/httplib.h"

class SubjectActions {
public:
    explicit SubjectActions(httplib::Client& client) : cli(client) {}
    
    void addSubject();
    void editSubject();
    void deleteSubject();
    void displaySubjects();

private:
    httplib::Client& cli;
}; 
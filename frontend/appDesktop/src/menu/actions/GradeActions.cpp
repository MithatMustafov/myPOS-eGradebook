#include "GradeActions.h"
#include <iostream>
#include "../../utils/ConsoleUtils.h"
#include "../../utils/TableFormatter.h"
#include "../../utils/JsonParser.h"

void GradeActions::addGrade() {
    std::cout << "Enter student ID: ";
    int studentId;
    std::cin >> studentId;

    std::cout << "Enter subject ID: ";
    int subjectId;
    std::cin >> subjectId;

    std::cout << "Enter grade (2-6): ";
    int grade;
    std::cin >> grade;

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::string date;
    std::cin >> date;

    std::string body = "{\"student_id\":" + std::to_string(studentId) + 
                      ",\"subject_id\":" + std::to_string(subjectId) + 
                      ",\"grade\":" + std::to_string(grade) + 
                      ",\"date\":\"" + date + "\"}";

    auto res = cli.Post("/grades", body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Grade added successfully!" : "Failed to add grade.",
        res && res->status == 200
    );
}

void GradeActions::editGrade() {
    std::cout << "Enter grade ID to edit: ";
    int id;
    std::cin >> id;

    std::cout << "Enter new grade (2-6): ";
    int grade;
    std::cin >> grade;

    std::cout << "Enter new date (YYYY-MM-DD): ";
    std::string date;
    std::cin >> date;

    std::string body = "{\"grade\":" + std::to_string(grade) + 
                      ",\"date\":\"" + date + "\"}";

    auto res = cli.Put("/grades/" + std::to_string(id), body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Grade updated successfully!" : "Failed to update grade.",
        res && res->status == 200
    );
}

void GradeActions::deleteGrade() {
    std::cout << "Enter grade ID to delete: ";
    int id;
    std::cin >> id;

    auto res = cli.Delete("/grades/" + std::to_string(id));
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Grade deleted successfully!" : "Failed to delete grade.",
        res && res->status == 200
    );
}

void GradeActions::displayGrades() {
    auto res = cli.Get("/grades");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"ID", "Student", "Subject", "Grade", "Date"};
        auto rows = JsonParser::parseGrades(res->body);
        std::cout << "\n=== All Grades ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Grades retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch grades.", false);
    }
} 
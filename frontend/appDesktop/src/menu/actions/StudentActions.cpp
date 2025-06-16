#include "StudentActions.h"
#include <iostream>
#include "../../utils/ConsoleUtils.h"
#include "../../utils/TableFormatter.h"
#include "../../utils/JsonParser.h"

void StudentActions::addStudent() {
    std::cout << "Enter student full name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter date of birth (YYYY-MM-DD): ";
    std::string dob;
    std::cin >> dob;

    std::string body = "{\"full_name\":\"" + name + "\",\"date_of_birth\":\"" + dob + "\"}";

    auto res = cli.Post("/students", body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Student added successfully!" : "Failed to add student.",
        res && res->status == 200
    );
}

void StudentActions::editStudent() {
    std::cout << "Enter student ID to edit: ";
    int id;
    std::cin >> id;

    std::cout << "Enter new full name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter new date of birth (YYYY-MM-DD): ";
    std::string dob;
    std::cin >> dob;

    std::string body = "{\"full_name\":\"" + name + "\",\"date_of_birth\":\"" + dob + "\"}";

    auto res = cli.Put("/students/" + std::to_string(id), body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Student updated successfully!" : "Failed to update student.",
        res && res->status == 200
    );
}

void StudentActions::deleteStudent() {
    std::cout << "Enter student ID to delete: ";
    int id;
    std::cin >> id;

    auto res = cli.Delete("/students/" + std::to_string(id));
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Student deleted successfully!" : "Failed to delete student.",
        res && res->status == 200
    );
}

void StudentActions::displayStudents() {
    auto res = cli.Get("/students");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"ID", "Full Name", "Date of Birth"};
        auto rows = JsonParser::parseStudents(res->body);
        std::cout << "\n=== All Students ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Students retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch students.", false);
    }
} 
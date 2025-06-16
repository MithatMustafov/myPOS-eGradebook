#include "SubjectActions.h"
#include <iostream>
#include "../../utils/ConsoleUtils.h"
#include "../../utils/TableFormatter.h"
#include "../../utils/JsonParser.h"

void SubjectActions::addSubject() {
    std::cout << "Enter subject name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter teacher name: ";
    std::string teacher;
    std::getline(std::cin >> std::ws, teacher);

    std::cout << "Enter room number: ";
    std::string room;
    std::cin >> room;

    std::string body = "{\"name\":\"" + name + "\",\"teacher_name\":\"" + teacher + 
                      "\",\"room_number\":\"" + room + "\"}";

    auto res = cli.Post("/subjects", body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Subject added successfully!" : "Failed to add subject.",
        res && res->status == 200
    );
}

void SubjectActions::editSubject() {
    std::cout << "Enter subject ID to edit: ";
    int id;
    std::cin >> id;

    std::cout << "Enter new subject name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter new teacher name: ";
    std::string teacher;
    std::getline(std::cin >> std::ws, teacher);

    std::cout << "Enter new room number: ";
    std::string room;
    std::cin >> room;

    std::string body = "{\"name\":\"" + name + "\",\"teacher_name\":\"" + teacher + 
                      "\",\"room_number\":\"" + room + "\"}";

    auto res = cli.Put("/subjects/" + std::to_string(id), body, "application/json");
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Subject updated successfully!" : "Failed to update subject.",
        res && res->status == 200
    );
}

void SubjectActions::deleteSubject() {
    std::cout << "Enter subject ID to delete: ";
    int id;
    std::cin >> id;

    auto res = cli.Delete("/subjects/" + std::to_string(id));
    ConsoleUtils::printStatus(
        res && res->status == 200 ? "Subject deleted successfully!" : "Failed to delete subject.",
        res && res->status == 200
    );
}

void SubjectActions::displaySubjects() {
    auto res = cli.Get("/subjects");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"ID", "Subject Name", "Teacher", "Room"};
        auto rows = JsonParser::parseSubjects(res->body);
        std::cout << "\n=== All Subjects ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Subjects retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch subjects.", false);
    }
} 
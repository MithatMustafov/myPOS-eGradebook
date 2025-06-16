#include "AnalyticsActions.h"
#include <iostream>
#include "../../utils/ConsoleUtils.h"
#include "../../utils/TableFormatter.h"
#include "../../utils/JsonParser.h"

void AnalyticsActions::calculateAverageInSubject() {
    std::cout << "Enter student ID: ";
    int studentId;
    std::cin >> studentId;

    std::cout << "Enter subject ID: ";
    int subjectId;
    std::cin >> subjectId;

    auto res = cli.Get("/analytics/average/" + std::to_string(studentId) + "/" + std::to_string(subjectId));
    if (res && res->status == 200) {
        std::cout << "Average grade: " << res->body << "\n";
        ConsoleUtils::printStatus("Average calculated successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to calculate average.", false);
    }
}

void AnalyticsActions::calculateAverageOverall() {
    std::cout << "Enter student ID: ";
    int studentId;
    std::cin >> studentId;

    auto res = cli.Get("/analytics/average/" + std::to_string(studentId));
    if (res && res->status == 200) {
        std::cout << "Overall average: " << res->body << "\n";
        ConsoleUtils::printStatus("Overall average calculated successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to calculate overall average.", false);
    }
}

void AnalyticsActions::displayTopStudents() {
    auto res = cli.Get("/analytics/top-students");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"Student Name", "Average Grade"};
        auto rows = JsonParser::parseTopStudents(res->body);
        std::cout << "\n=== Top Students (Avg > 5.50) ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Top students retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch top students.", false);
    }
}

void AnalyticsActions::displayRemedialExamStudents() {
    auto res = cli.Get("/analytics/remedial-exam");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"Student Name", "Subject"};
        auto rows = JsonParser::parseRemedialExamStudents(res->body);
        std::cout << "\n=== Students for Remedial Exam ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Remedial exam students retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch remedial exam students.", false);
    }
}

void AnalyticsActions::displayLowGradeStudents() {
    auto res = cli.Get("/analytics/low-grades");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"Student Name", "Average Grade"};
        auto rows = JsonParser::parseLowGradeStudents(res->body);
        std::cout << "\n=== Students with Low Grades ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Low grade students retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch students with low grades.", false);
    }
}

void AnalyticsActions::displayBirthdayToday() {
    auto res = cli.Get("/analytics/birthdays-today");
    if (res && res->status == 200) {
        std::vector<std::string> headers = {"Student Name", "Date of Birth"};
        auto rows = JsonParser::parseBirthdayStudents(res->body);
        std::cout << "\n=== Students with Birthday Today ===\n";
        std::cout << TableFormatter::createTable(headers, rows);
        ConsoleUtils::printStatus("Birthday students retrieved successfully!", true);
    } else {
        ConsoleUtils::printStatus("Failed to fetch birthday students.", false);
    }
} 
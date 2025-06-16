#pragma once
#include <string>
#include <vector>
#include "../lib/nlohmann/json.hpp"

using json = nlohmann::json;

class JsonParser {
public:
    static std::vector<std::vector<std::string>> parseStudents(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& student : data["students"]) {
                rows.push_back({
                    std::to_string(student["id"].get<int>()),
                    student["full_name"],
                    student["date_of_birth"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseSubjects(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& subject : data["subjects"]) {
                rows.push_back({
                    std::to_string(subject["id"].get<int>()),
                    subject["name"],
                    subject["teacher_name"],
                    subject["room_number"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseGrades(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& grade : data["grades"]) {
                rows.push_back({
                    std::to_string(grade["id"].get<int>()),
                    grade["student_name"],
                    grade["subject_name"],
                    std::to_string(grade["grade"].get<int>()),
                    grade["date"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseTopStudents(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& student : data) {
                rows.push_back({
                    student["full_name"],
                    student["average_grade"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseRemedialExamStudents(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& student : data) {
                rows.push_back({
                    student["full_name"],
                    student["subject_name"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseLowGradeStudents(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& student : data) {
                rows.push_back({
                    student["full_name"],
                    student["average_grade"]
                });
            }
        } catch (...) {}
        return rows;
    }

    static std::vector<std::vector<std::string>> parseBirthdayStudents(const std::string& jsonStr) {
        std::vector<std::vector<std::string>> rows;
        try {
            json data = json::parse(jsonStr);
            for (const auto& student : data) {
                rows.push_back({
                    student["full_name"],
                    student["date_of_birth"]
                });
            }
        } catch (...) {}
        return rows;
    }
}; 
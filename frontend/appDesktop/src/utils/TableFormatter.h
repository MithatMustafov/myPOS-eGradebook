#pragma once
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class TableFormatter {
public:
    static std::string createTable(const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows) {
        std::vector<size_t> columnWidths(headers.size(), 0);
        
        // Calculate maximum width for each column including headers
        for (size_t i = 0; i < headers.size(); ++i) {
            columnWidths[i] = headers[i].length();
            for (const auto& row : rows) {
                if (i < row.size()) {
                    columnWidths[i] = std::max(columnWidths[i], row[i].length());
                }
            }
        }

        std::stringstream ss;
        
        // Print top border
        printBorder(ss, columnWidths);
        
        // Print headers
        ss << "| ";
        for (size_t i = 0; i < headers.size(); ++i) {
            ss << std::left << std::setw(columnWidths[i]) << headers[i] << " | ";
        }
        ss << "\n";
        
        // Print separator
        printSeparator(ss, columnWidths);
        
        // Print rows
        for (const auto& row : rows) {
            ss << "| ";
            for (size_t i = 0; i < headers.size(); ++i) {
                std::string value = i < row.size() ? row[i] : "";
                ss << std::left << std::setw(columnWidths[i]) << value << " | ";
            }
            ss << "\n";
        }
        
        // Print bottom border
        printBorder(ss, columnWidths);
        
        return ss.str();
    }

private:
    static void printBorder(std::stringstream& ss, const std::vector<size_t>& widths) {
        ss << "+";
        for (size_t width : widths) {
            ss << std::string(width + 2, '-') << "+";
        }
        ss.seekp(-1, std::ios_base::cur);
        ss << "+\n";
    }

    static void printSeparator(std::stringstream& ss, const std::vector<size_t>& widths) {
        ss << "+";
        for (size_t width : widths) {
            ss << std::string(width + 2, '-') << "+";
        }
        ss.seekp(-1, std::ios_base::cur);
        ss << "+\n";
    }
}; 
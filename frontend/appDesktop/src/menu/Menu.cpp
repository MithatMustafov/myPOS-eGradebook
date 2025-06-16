#include "Menu.h"
#include <iostream>
#include "../utils/ConsoleUtils.h"
#include "../asciiArt/asciiMyPOS.h"

Menu::Menu() {}

void Menu::displayMenu() {
    ConsoleUtils::clearScreen();
    printAsciiMyPOS();
    
    std::cout << "\n===== Student Management System =====" << std::endl;
    std::cout << "1. Add Student" << std::endl;
    std::cout << "2. Edit Student" << std::endl;
    std::cout << "3. Delete Student" << std::endl;
    std::cout << "4. Add Subject" << std::endl;
    std::cout << "5. Edit Subject" << std::endl;
    std::cout << "6. Delete Subject" << std::endl;
    std::cout << "7. Add Grade" << std::endl;
    std::cout << "8. Edit Grade" << std::endl;
    std::cout << "9. Delete Grade" << std::endl;
    std::cout << "10. Display All Students" << std::endl;
    std::cout << "11. Display All Subjects" << std::endl;
    std::cout << "12. Display All Grades" << std::endl;
    std::cout << "13. Calculate Student's Average in a Subject" << std::endl;
    std::cout << "14. Calculate Student's Overall Average" << std::endl;
    std::cout << "15. Display Top Students (Avg > 5.50)" << std::endl;
    std::cout << "16. Display Students for Remedial Exam" << std::endl;
    std::cout << "17. Display Students with < 3.00 in 3+ Subjects" << std::endl;
    std::cout << "18. Display Birthdays Today" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Menu::run() {
    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        // Clear screen before executing the action
        ConsoleUtils::clearScreen();
        
        switch (choice) {
            case 1:
                functions.addStudent();
                break;
            case 2:
                functions.editStudent();
                break;
            case 3:
                functions.deleteStudent();
                break;
            case 4:
                functions.addSubject();
                break;
            case 5:
                functions.editSubject();
                break;
            case 6:
                functions.deleteSubject();
                break;
            case 7:
                functions.addGrade();
                break;
            case 8:
                functions.editGrade();
                break;
            case 9:
                functions.deleteGrade();
                break;
            case 10:
                functions.displayStudents();
                break;
            case 11:
                functions.displaySubjects();
                break;
            case 12:
                functions.displayGrades();
                break;
            case 13:
                functions.calculateAverageInSubject();
                break;
            case 14:
                functions.calculateAverageOverall();
                break;
            case 15:
                functions.displayTopStudents();
                break;
            case 16:
                functions.displayRemedialExamStudents();
                break;
            case 17:
                functions.displayLowGradeStudents();
                break;
            case 18:
                functions.displayBirthdayToday();
                break;
            case 0:
                ConsoleUtils::printStatus("Exiting...", true);
                break;
            default:
                ConsoleUtils::printStatus("Invalid choice. Try again.", false);
        }

        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }

    } while (choice != 0);
} 
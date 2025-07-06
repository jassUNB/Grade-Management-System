#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main() {
    StudentNode* head = NULL;

    // Load existing data
    loadFromCSV(&head, "students.csv");

    int choice;
    do {
        printf("\n--- Student Grade Management System ---\n");
        printf("1. Add a student\n");
        printf("2. Display all students\n");
        printf("3. Save and exit\n");
        printf("4. Sort students\n");
        printf("5. Search for a student\n");
        printf("6. Print GPA bar chart\n");
        printf("7. Update GPA by ID\n");
        printf("8. Modify Marks by Name\n");
        printf("9. Remove a student\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent(&head);
                break;

            case 2:
                displayStudents(head);
                break;

            case 3:
                saveToCSV(head, "students.csv");
                printf("Data saved. Exiting...\n");
                break;

            case 4: {
                int sortChoice;
                printf("Sort by:\n1. ID\n2. Name\n3. GPA\nEnter your choice: ");
                if (scanf("%d", &sortChoice) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                sortStudents(&head, sortChoice);
                printf("Students sorted.\n");
                break;
            }

            case 5: {
                int searchID;
                printf("Enter student ID to search: ");
                if (scanf("%d", &searchID) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                searchStudent(head, searchID);
                break;
            }

            case 6:
                printGPAChart(head);
                break;

            case 7: {
                int studentID;
                printf("Enter student ID to update GPA: ");
                if (scanf("%d", &studentID) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                updateGPA(head, studentID);
                break;
            }

            case 8: {
                char name[50];
                printf("Enter student name to update marks: ");
                scanf(" %49[^\n]", name);
                updateMarksByName(head, name);
                break;
            }

            case 9: {
                int removeID;
                printf("Enter student ID to remove: ");
                if (scanf("%d", &removeID) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                removeStudent(&head, removeID);
                break;
            }

            default:
                if (choice != 3)
                    printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    // Free dynamically allocated memory before exit
    freeStudents(head);

    return 0;
}


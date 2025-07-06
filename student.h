#ifndef STUDENT_H
#define STUDENT_H

#define NUM_SUBJECTS 5

typedef struct Student {
    int id;
    char name[50];
    float grades[NUM_SUBJECTS];
    float gpa;
} Student;

typedef struct StudentNode {
    Student student;
    struct StudentNode* next;
} StudentNode;

// Function prototypes for dynamic list version
float calculateGPA(float grades[], int numGrades);

void addStudent(StudentNode** head);
void displayStudents(StudentNode* head);
void saveToCSV(StudentNode* head, const char *filename);
void loadFromCSV(StudentNode** head, const char *filename);
void removeStudent(StudentNode** head, int id);
void searchStudent(StudentNode* head, int id);
void updateGPA(StudentNode* head, int id);
void updateMarksByName(StudentNode* head, const char *studentName);
void printGPAChart(StudentNode* head);
void sortStudents(StudentNode** head, int sortType);
void freeStudents(StudentNode* head);  // memory cleanup

#endif


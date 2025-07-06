#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include "student.h"


int studentCount = 0;

/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
float calculateGPA(float grades[], int numGrades) {
	
    if (numGrades == 0) return 0.0;
    float sum = 0;
    for (int i = 0; i < numGrades; i++) {
        float gradePoint;

        if (grades[i] >= 90) {
            gradePoint = 4.3;
        } 
        else if (grades[i] >= 86) {
            gradePoint = 4.0;
        } 
        else if (grades[i] >= 79) {
            gradePoint = 3.7;
        } 
        else if (grades[i] >= 75) {
            gradePoint = 3.3;
        } 
        else if (grades[i] >= 70) {
            gradePoint = 3.0;
        } 
        else if (grades[i] >= 67) {
            gradePoint = 2.7;
        } 
        else if (grades[i] >= 59) {
            gradePoint = 2.3;
        } 
        else if (grades[i] >= 50) {
            gradePoint = 2.0;
        } 
        else if (grades[i] >= 44) {
            gradePoint = 1.7;
        } 
        else if (grades[i] >= 39) {
            gradePoint = 1.3;
        } 
        else if (grades[i] >= 31) {
            gradePoint = 1.0;
        } 
        else if (grades[i] >= 25) {
            gradePoint = 0.7;
        } 
        else {
            gradePoint = 0.0;
        }
        sum += gradePoint;
    }
    return sum / numGrades;
}

/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void addStudent(StudentNode** head){
    Student newStudent;

    while (1){
        printf("Enter student ID (7-digit): ");
        if (scanf("%d", &newStudent.id) != 1 || newStudent.id < 1000000 || newStudent.id > 9999999) {
            printf("Invalid ID. Must be a 7-digit number.\n");
            while (getchar() != '\n');
            continue;
        }

        StudentNode* temp = *head;
        int exists = 0;
        while (temp) {
            if (temp->student.id == newStudent.id) {
                exists = 1;
                break;
            }
            temp = temp->next;
        }
        if (exists) {
            printf("Student ID already exists. Try again.\n");
        } else {
            break;
        }
    }

    printf("Enter name: ");
    scanf(" %49[^\n]", newStudent.name);

    for (int i = 0; i < NUM_SUBJECTS; i++){
        while (1) {
            printf("Subject %d: ", i + 1);
            if (scanf("%f", &newStudent.grades[i]) != 1 || newStudent.grades[i] < 0 || newStudent.grades[i] > 100) {
                printf("Invalid grade. Try again.\n");
                while (getchar() != '\n');
            } else break;
        }
    }

    newStudent.gpa = calculateGPA(newStudent.grades, NUM_SUBJECTS);

    StudentNode* node = (StudentNode*)malloc(sizeof(StudentNode));
    node->student = newStudent;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
    } else {
        StudentNode* current = *head;
        while (current->next) current = current->next;
        current->next = node;
    }

    printf("Student added successfully.\n");
}



/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void displayStudents(StudentNode* head){
    if (!head) {
        printf("No students found.\n");
        return;
    }

    printf("%-10s %-20s %-5s", "ID", "Name", "GPA");
    for (int i = 0; i < NUM_SUBJECTS; i++){
     printf(" Sub%-3d", i + 1);
    }
    printf("\n");

    while (head) {
        printf("%-10d %-20s %-5.2f", head->student.id, head->student.name, head->student.gpa);
        for (int i = 0; i < NUM_SUBJECTS; i++){
         printf(" %-6.2f", head->student.grades[i]);
        }
        printf("\n");
        head = head->next;
    }
}


/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void removeStudent(StudentNode** head, int id) {
    StudentNode *temp = *head, *prev = NULL;

    while (temp && temp->student.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        printf("ID not found.\n");
        return;
    }

    if (!prev) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Student removed.\n");
}



/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void saveToCSV(StudentNode* head, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Error saving file.\n");
        return;
    }
    fprintf(f, "ID,Name,Grade1,Grade2,Grade3,Grade4,Grade5,GPA\n");
    while (head) {
	    fprintf(f, "%d,%s", head->student.id, head->student.name);
	    
	    for (int i = 0; i < NUM_SUBJECTS; i++){
		fprintf(f, ",%.2f", head->student.grades[i]);
	    }

	    fprintf(f, ",%.2f\n", head->student.gpa);
	    head = head->next;
    }


    fclose(f);
    printf("Data saved to %s.\n", filename);
}


/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void loadFromCSV(StudentNode** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("No CSV file found. Starting with an empty list.\n");
        return;
    }

    char line[256];

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        printf("CSV file is empty.\n");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        Student s;
        char nameBuffer[50];

        int fieldsRead = sscanf(line, "%d,%49[^,],%f,%f,%f,%f,%f,%f",
            &s.id, nameBuffer, &s.grades[0], &s.grades[1], &s.grades[2],
            &s.grades[3], &s.grades[4], &s.gpa);

        if (fieldsRead == 8) {
            strcpy(s.name, nameBuffer);

            StudentNode* newNode = malloc(sizeof(StudentNode));
            if (newNode == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return;
            }

            newNode->student = s;
            newNode->next = *head;
            *head = newNode;
        }
    }

    fclose(file);
    printf("CSV data successfully loaded into memory.\n");
}


/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void searchStudent(StudentNode* head, int id) {
    while (head) {
        if (head->student.id == id) {
            printf("ID: %d\nName: %s\nGPA: %.2f\n", head->student.id, head->student.name, head->student.gpa);
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}


void printBar(int value, float actualValue) {
    for (int i = 0; i < value; i++) {
        printf("#");
    }
    printf(" (%.2f)\n", actualValue);
}

/**
 * Arush Bhise 3769893
 * Modified to add color-coded bars 
 */
void printBarGPA(int value, float actualValue) {
    const char* color;
    if (actualValue >= 3.7) color = "\033[1;32m";  // Bright green 
    else if (actualValue >= 2.5) color = "\033[1;33m";  // Bright yellow
    else if (actualValue >= 1.5) color = "\033[1;31m";  // Bright red 
    else color = "\033[0;31m";  
    
    printf("%s", color);  
    for (int i = 0; i < value; i++) {
        printf("█");  
    }
    printf("\033[0m");  
    printf(" (%.2f)\n", actualValue);
}
void printBarGrades(int value, float actualValue) {
    const char* color;
    if (actualValue >= 90) color = "\033[1;32m";  // Bright green 
    else if (actualValue >= 80) color = "\033[0;32m";  // Green 
    else if (actualValue >= 70) color = "\033[1;33m";  // Bright yellow
    else if (actualValue >= 60) color = "\033[0;33m";  // Yellow
    else if (actualValue >= 50) color = "\033[1;31m";  // Bright red 
    else color = "\033[0;31m";  
    
    printf("%s", color);  
    for (int i = 0; i < value; i++) {
        printf("█");  
    }
    printf("\033[0m");  
    printf(" (%.2f)\n", actualValue);
}

void freeStudents(StudentNode* head) {
    while (head) {
        StudentNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}


void printGPAChart(StudentNode* head) {
    if (!head) {
        printf("No students found.\n");
        return;
    }

    int choice;
    printf("1.Show all GPAs\n2.Show one student's grades\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        StudentNode* current = head;
        while (current) {
            printf("%-15s: ", current->student.name);
            
            printBarGPA((int)(current->student.gpa * 4), current->student.gpa);
            current = current->next;
        }
    } 
    else if (choice == 2) {
        int id;
        printf("Enter student ID: ");
        scanf("%d", &id);

        StudentNode* current = head;
        while (current) {
            if (current->student.id == id) {
                printf("\nGrades for %s:\n", current->student.name);
                for (int i = 0; i < NUM_SUBJECTS; i++) {
                    printf("Subject %d: ", i+1);
                    printBarGrades((int)current->student.grades[i]/10, current->student.grades[i]);
                }
                return;
            }
            current = current->next;
        }
        printf("Student not found.\n");
    } 
    else {
        printf("Invalid choice.\n");
    }
}

/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void updateMarksByName(StudentNode* head, const char* name) {
    while (head) {
        if (strcmp(head->student.name, name) == 0) {
            printf("Updating grades for %s:\n", name);
            for (int i = 0; i < NUM_SUBJECTS; i++) {
                printf("Subject %d: ", i + 1);
                scanf("%f", &head->student.grades[i]);
            }
            head->student.gpa = calculateGPA(head->student.grades, NUM_SUBJECTS);
            printf("Updated GPA: %.2f\n", head->student.gpa);
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}




/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void updateGPA(StudentNode* head, int id) {
    while (head) {
        if (head->student.id == id) {
            printf("Updating GPA for %s:\n", head->student.name);
            for (int i = 0; i < NUM_SUBJECTS; i++) {
                printf("Subject %d: ", i + 1);
                scanf("%f", &head->student.grades[i]);
            }
            head->student.gpa = calculateGPA(head->student.grades, NUM_SUBJECTS);
            printf("Updated GPA: %.2f\n", head->student.gpa);
            return;
        }
        head = head->next;
    }
    printf("Student ID not found.\n");
}



/**
 ** Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
int compareByID(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return studentA->id - studentB->id;
}

/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
int compareByName(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;
    return strcmp(studentA->name, studentB->name);
}

/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
int compareByGPA(const void *a, const void *b) {
    const Student *studentA = (const Student *)a;
    const Student *studentB = (const Student *)b;

    if (studentB->gpa > studentA->gpa) return 1;
    if (studentB->gpa < studentA->gpa) return -1;
    return 0;
}


/**
 * Jaskaran Singh 3761860
 *Neerja Basil 3762258
 */
void sortStudents(StudentNode** headRef, int sortType) {
    if (*headRef == NULL || (*headRef)->next == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }

    StudentNode* quickSortRecur(StudentNode* head, int sortType);
    *headRef = quickSortRecur(*headRef, sortType);

    switch (sortType) {
        case 1: printf("Students sorted by ID.\n"); 
        	break;
        case 2: printf("Students sorted by Name.\n"); 
        	break;
        case 3: printf("Students sorted by GPA.\n"); 
        	break;
        default: printf("Invalid sort type.\n");
    }

    printf("\n--- Sorted Student List ---\n");
    displayStudents(*headRef);
}
/**
* Jaskaran Singh 3761860
*Neerja Basil 3762258
**/
int compareStudents(Student a, Student b, int sortType) {
    switch (sortType) {
        case 1: 
        	return a.id - b.id;
        case 2: 
        	return strcmp(a.name, b.name);
	case 3: {
	    if (a.gpa > b.gpa) {
		return -1;
	    } else if (a.gpa < b.gpa) {
		return 1;
	    } else {
		return 0;
	    }
	}
        default: return 0;
    }
}

StudentNode* getTail(StudentNode* cur) {
    while (cur && cur->next)
        cur = cur->next;
    return cur;
}

StudentNode* partition(StudentNode* head, StudentNode** newHead, StudentNode** newEnd, int sortType) {
    Student pivot = head->student;
    StudentNode *beforeStart = NULL, *beforeEnd = NULL;
    StudentNode *afterStart = NULL, *afterEnd = NULL;
    StudentNode *cur = head->next;

    while (cur != NULL) {
        StudentNode* next = cur->next;
        cur->next = NULL;

        if (compareStudents(cur->student, pivot, sortType) < 0) {
            if (!beforeStart) {
                beforeStart = beforeEnd = cur;
            } else {
                beforeEnd->next = cur;
                beforeEnd = cur;
            }
        } else {
            if (!afterStart) {
                afterStart = afterEnd = cur;
            } else {
                afterEnd->next = cur;
                afterEnd = cur;
            }
        }

        cur = next;
    }

    StudentNode* pivotNode = head;
    pivotNode->next = afterStart;

    if (beforeStart) {
        *newHead = beforeStart;
        beforeEnd->next = pivotNode;
    } else {
        *newHead = pivotNode;
    }

    *newEnd = afterEnd ? afterEnd : pivotNode;
    return pivotNode;
}


StudentNode* quickSortRecur(StudentNode* head, int sortType) {
    if (!head || !head->next)
        return head;

    StudentNode *newHead = NULL, *newEnd = NULL;

    StudentNode* pivot = partition(head, &newHead, &newEnd, sortType);

    if (newHead != pivot) {
        StudentNode* temp = newHead;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newHead = quickSortRecur(newHead, sortType);
        getTail(newHead)->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, sortType);
    return newHead;
}


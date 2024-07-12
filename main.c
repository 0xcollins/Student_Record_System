#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    int rollNumber;
    float marks;
} Student;

void greetUser();
void printMenu();
void addStudent(Student** students, int* count);
void modifyStudent(Student* students, int count);
void displayStudents(const Student* students, int count);
void saveStudentsToFile(const Student* students, int count, const char* filename);
void loadStudentsFromFile(Student** students, int* count, const char* filename);
void searchStudentByRollNumber(const Student* students, int count);
void calculateAverageMarks(const Student* students, int count);
void sortStudentsByMarks(Student* students, int count);

int main() {
    Student* students = NULL;
    int count = 0;
    int choice;
    const char* filename = "student-records.txt";

    greetUser();

    loadStudentsFromFile(&students, &count, filename);

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(&students, &count);
                break;
            case 2:
                modifyStudent(students, count);
                break;
            case 3:
                displayStudents(students, count);
                break;
            case 4:
                saveStudentsToFile(students, count, filename);
                break;
            case 5:
                loadStudentsFromFile(&students, &count, filename);
                break;
            case 6:
                searchStudentByRollNumber(students, count);
                break;
            case 7:
                calculateAverageMarks(students, count);
                break;
            case 8:
                sortStudentsByMarks(students, count);
                break;
            case 9:
                free(students);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Prints the menu options
void printMenu() {
    printf("\nMenu:\n");
    printf("1. Add Student\n");
    printf("2. Modify Student\n");
    printf("3. Display Students\n");
    printf("4. Save Students to File\n");
    printf("5. Load Students from File\n");
    printf("6. Search Student by Roll Number\n");
    printf("7. Calculate Average Marks\n");
    printf("8. Sort Students by Marks\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

// Greets the user and asks for their name
void greetUser() {
    char name[50];
    printf("Welcome! Please enter your name: ");
    scanf("%s", name);
    printf("Hello, %s!\n", name);
}


#define PRINT_TYPE(var) printf("Variable %s is of type %s\n", #var, __PRETTY_FUNCTION__) 
// Adds a new student to the list
void addStudent(Student** students, int* count) {
    *students = (Student*) realloc(*students, (*count + 1) * sizeof(Student));
    if (*students == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    printf("Enter student name: ");
    scanf("%s", (*students)[*count].name);
    
    int rollNumber;
    printf("Enter roll number: ");
    scanf("%d", &rollNumber);

    // Check for duplicate rollNumber
    for (int i = 0; i < *count; i++) {
        if ((*students)[i].rollNumber == rollNumber) {
            printf("Roll number already exists. Please enter a unique roll number.\n");
            return;
        }
    }

    (*students)[*count].rollNumber = rollNumber;
    printf("Enter mark: ");
    scanf("%f", &(*students)[*count].marks);

    (*count)++;
}

// Modifies an existing student's information
void modifyStudent(Student* students, int count) {
    int rollNumber, i;
    printf("Enter roll number of student to modify: ");
    scanf("%d", &rollNumber);

    for (i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new mark: ");
            scanf("%f", &students[i].marks);
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}

// Displays the list of students
void displayStudents(const Student* students, int count) {
    int i;
    printf("\n");
    for (i = 0; i < count; i++) {
        printf("-------------------------------------");
        printf("\n");
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].rollNumber);
        printf("Marks: %.2f\n", students[i].marks);
        printf("Status: %s\n", students[i].marks > 40 ? "Passed" : "Failed");
        printf("-------------------------------------");

    }
}

// Saves the list of students to a file
void saveStudentsToFile(const Student* students, int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
    printf("Students saved to file successfully.\n");
}

// Loads the list of students from a file
void loadStudentsFromFile(Student** students, int* count, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file or file does not exist");
        return;
    }

    fread(count, sizeof(int), 1, file);
    *students = (Student*) realloc(*students, (*count) * sizeof(Student));
    if (*students == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("The value of count is: %d\n", *count);
    fread(*students, sizeof(Student), *count, file);
    fclose(file);
    printf("Students loaded from file successfully.\n");
}

// Searches for a student by roll number
void searchStudentByRollNumber(const Student* students, int count) {
    int rollNumber, i;
    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);

    for (i = 0; i < count; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Name: %s, Roll Number: %d, Marks: %.2f\n", students[i].name, students[i].rollNumber, students[i].marks);
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNumber);
}

// Calculates the average marks of all students
void calculateAverageMarks(const Student* students, int count) {
    int i;
    float sum = 0;

    for (i = 0; i < count; i++) {
        sum += students[i].marks;
    }

    printf("Average Marks: %.2f\n", sum / count);
}

// Sorts the students by marks in ascending or descending order
void sortStudentsByMarks(Student* students, int count) {
    int i, j;
    Student temp;
    int choice;

    printf("Sort students by:\n");
    printf("1. Marks in ascending order\n");
    printf("2. Marks in descending order\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    if (students[i].marks > students[j].marks) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            printf("Students sorted by marks in ascending order.\n");
            break;
        case 2:
            for (i = 0; i < count - 1; i++) {
                for (j = i + 1; j < count; j++) {
                    if (students[i].marks < students[j].marks) {
                        temp = students[i];
                        students[i] = students[j];
                        students[j] = temp;
                    }
                }
            }
            printf("Students sorted by marks in descending order.\n");
            break;
        default:
            printf("Invalid choice. Sorting aborted.\n");
            return;
    }

    displayStudents(students, count);
}

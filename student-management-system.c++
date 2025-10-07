#include <iostream>
using namespace std;

struct Student {
    int roll;
    string name;
    float marks;
    Student* next;
};

Student* head = NULL;

// Function to add student
void addStudent() {
    Student* newStudent = new Student;
    cout << "\nEnter Roll Number: ";
    cin >> newStudent->roll;
    cout << "Enter Name: ";
    cin >> newStudent->name;
    cout << "Enter Marks: ";
    cin >> newStudent->marks;

    newStudent->next = NULL;

    if (head == NULL)
        head = newStudent;
    else {
        Student* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newStudent;
    }
    cout << "Student added successfully!\n";
}

// Function to display all students
void displayStudents() {
    if (head == NULL) {
        cout << "\nNo student records found.\n";
        return;
    }
    Student* temp = head;
    cout << "\n--- Student Records ---\n";
    while (temp != NULL) {
        cout << "Roll No: " << temp->roll
             << ", Name: " << temp->name
             << ", Marks: " << temp->marks << "\n";
        temp = temp->next;
    }
}

// Function to search student by roll number
void searchStudent() {
    if (head == NULL) {
        cout << "\nNo student records found.\n";
        return;
    }

    int roll;
    cout << "\nEnter roll number to search: ";
    cin >> roll;
    Student* temp = head;
    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Record found!\n";
            cout << "Roll: " << temp->roll << ", Name: " << temp->name << ", Marks: " << temp->marks << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Student not found.\n";
}

// Function to delete a student by roll number
void deleteStudent() {
    if (head == NULL) {
        cout << "\nNo student records to delete.\n";
        return;
    }

    int roll;
    cout << "\nEnter roll number to delete: ";
    cin >> roll;

    Student* temp = head;
    Student* prev = NULL;

    while (temp != NULL && temp->roll != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Student not found.\n";
        return;
    }

    if (prev == NULL)
        head = head->next;
    else
        prev->next = temp->next;

    delete temp;
    cout << "Student deleted successfully!\n";
}

// Function to update student record
void updateStudent() {
    if (head == NULL) {
        cout << "\nNo student records to update.\n";
        return;
    }

    int roll;
    cout << "\nEnter roll number to update: ";
    cin >> roll;
    Student* temp = head;

    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Enter new name: ";
            cin >> temp->name;
            cout << "Enter new marks: ";
            cin >> temp->marks;
            cout << "Record updated successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Student not found.\n";
}

// Main Menu
int main() {
    int choice;
    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

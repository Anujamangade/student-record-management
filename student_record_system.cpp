#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int roll;
    string name;
    float marks;

public:
    void getData() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void showData() const {
        cout << "Roll No: " << roll << "\n";
        cout << "Name: " << name << "\n";
        cout << "Marks: " << marks << "\n";
    }

    int getRoll() const { return roll; }
};

void addStudent() {
    Student s;
    ofstream outFile("students.dat", ios::binary | ios::app);
    s.getData();
    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();
}

void displayStudents() {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.showData();
        cout << "----------------------\n";
    }
    inFile.close();
}

void searchStudent(int rollNo) {
    Student s;
    bool found = false;
    ifstream inFile("students.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.getRoll() == rollNo) {
            s.showData();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Student not found.\n";
}

void menu() {
    int choice, rollNo;
    do {
        cout << "\n*** Student Record Management ***\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Enter Roll No to search: ";
                cin >> rollNo;
                searchStudent(rollNo);
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}

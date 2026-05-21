 #include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Student {
public:
    int id;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Student ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(25) << name
             << setw(10) << age
             << setw(20) << course << endl;
    }
};

void addStudent() {
    Student s;

    ofstream file("students.txt", ios::app);

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    s.input();

    file << s.id << "|"
         << s.name << "|"
         << s.age << "|"
         << s.course << endl;

    file.close();

    cout << "\nStudent added successfully.\n";
}

void displayStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    Student s;
    string line;

    cout << "\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(10) << "Age"
         << setw(20) << "Course" << endl;

    cout << string(65, '-') << endl;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        s.display();
    }

    file.close();
}

void updateStudent() {
    ifstream file("students.txt");

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    vector<Student> students;
    Student s;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        students.push_back(s);
    }

    file.close();

    int targetId;
    cout << "Enter Student ID to update: ";
    cin >> targetId;

    bool found = false;

    for (auto &student : students) {
        if (student.id == targetId) {
            found = true;

            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, student.name);

            cout << "Enter New Age: ";
            cin >> student.age;

            cin.ignore();

            cout << "Enter New Course: ";
            getline(cin, student.course);

            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
        return;
    }

    ofstream outFile("students.txt");

    for (const auto &student : students) {
        outFile << student.id << "|"
                << student.name << "|"
                << student.age << "|"
                << student.course << endl;
    }

    outFile.close();

    cout << "Student updated successfully.\n";
}

void deleteStudent() {
    ifstream file("students.txt");

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    vector<Student> students;
    Student s;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        s.id = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);

        students.push_back(s);
    }

    file.close();

    int targetId;
    cout << "Enter Student ID to delete: ";
    cin >> targetId;

    bool found = false;

    ofstream outFile("students.txt");

    for (const auto &student : students) {
        if (student.id == targetId) {
            found = true;
            continue;
        }

        outFile << student.id << "|"
                << student.name << "|"
                << student.age << "|"
                << student.course << endl;
    }

    outFile.close();

    if (found) {
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Student not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
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
                updateStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
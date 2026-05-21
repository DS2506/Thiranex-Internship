#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Book {
public:
    int bookId;
    string title;
    string author;
    bool issued;

    void addBook() {
        cout << "Enter Book ID: ";
        cin >> bookId;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBook() const {
        cout << left << setw(10) << bookId
             << setw(30) << title
             << setw(25) << author
             << setw(15) << (issued ? "Issued" : "Available")
             << endl;
    }
};

vector<Book> loadBooks() {
    vector<Book> books;

    ifstream file("library.txt");

    if (!file) {
        return books;
    }

    string line;
    Book book;

    while (getline(file, line)) {

        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        book.bookId = stoi(line.substr(0, pos1));
        book.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        book.issued = stoi(line.substr(pos3 + 1));

        books.push_back(book);
    }

    file.close();

    return books;
}

void saveBooks(const vector<Book>& books) {
    ofstream file("library.txt");

    for (const auto& book : books) {
        file << book.bookId << "|"
             << book.title << "|"
             << book.author << "|"
             << book.issued << endl;
    }

    file.close();
}

void addBook() {
    Book book;

    ofstream file("library.txt", ios::app);

    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }

    book.addBook();

    file << book.bookId << "|"
         << book.title << "|"
         << book.author << "|"
         << book.issued << endl;

    file.close();

    cout << "\nBook added successfully.\n";
}

void displayBooks() {
    vector<Book> books = loadBooks();

    if (books.empty()) {
        cout << "\nNo books available.\n";
        return;
    }

    cout << "\n";
    cout << left << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(15) << "Status" << endl;

    cout << string(80, '-') << endl;

    for (const auto& book : books) {
        book.displayBook();
    }
}

void issueBook() {
    vector<Book> books = loadBooks();

    int id;
    bool found = false;

    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (auto& book : books) {
        if (book.bookId == id) {

            found = true;

            if (book.issued) {
                cout << "Book is already issued.\n";
            } else {
                book.issued = true;
                cout << "Book issued successfully.\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }

    saveBooks(books);
}

void returnBook() {
    vector<Book> books = loadBooks();

    int id;
    bool found = false;

    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto& book : books) {
        if (book.bookId == id) {

            found = true;

            if (!book.issued) {
                cout << "Book is already available.\n";
            } else {
                book.issued = false;
                cout << "Book returned successfully.\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
    }

    saveBooks(books);
}

void searchBook() {
    vector<Book> books = loadBooks();

    int choice;
    bool found = false;

    cout << "\nSearch By:\n";
    cout << "1. Title\n";
    cout << "2. Author\n";
    cout << "Enter choice: ";

    cin >> choice;

    cin.ignore();

    string keyword;

    if (choice == 1) {
        cout << "Enter Book Title: ";
    } else if (choice == 2) {
        cout << "Enter Author Name: ";
    } else {
        cout << "Invalid choice.\n";
        return;
    }

    getline(cin, keyword);

    cout << "\n";
    cout << left << setw(10) << "Book ID"
         << setw(30) << "Title"
         << setw(25) << "Author"
         << setw(15) << "Status" << endl;

    cout << string(80, '-') << endl;

    for (const auto& book : books) {

        if ((choice == 1 && book.title == keyword) ||
            (choice == 2 && book.author == keyword)) {

            book.displayBook();
            found = true;
        }
    }

    if (!found) {
        cout << "No matching books found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n========== Library Management System ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                issueBook();
                break;

            case 4:
                returnBook();
                break;

            case 5:
                searchBook();
                break;

            case 6:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Member {
public:
    string name;
    int id;
    vector<string> borrowedBooks;

    // Default constructor
    Member() : name(""), id(0) {}

    // Parameterized constructor
    Member(string n, int i) : name(n), id(i) {}
};

class Book {
public:
    string title;
    string author;
    bool available;

    Book(string t, string a) : title(t), author(a), available(true) {}
};

class Library {
private:
    vector<Book> books;
    unordered_map<int, Member> members;

public:
    // Add a book to the library
    void addBook(string title, string author) {
        books.push_back(Book(title, author));
        cout << "Book added successfully!" << endl;
    }

    // Remove a book from the library
    void removeBook(string title) {
        auto it = find_if(books.begin(), books.end(), [&title](Book& book) {
            return book.title == title;
        });

        if (it != books.end()) {
            books.erase(it);
            cout << "Book removed successfully!" << endl;
        } else {
            cout << "Book not found!" << endl;
        }
    }

    // Search a book by title
    Book* searchBook(string title) {
        auto it = find_if(books.begin(), books.end(), [&title](Book& book) {
            return book.title == title;
        });

        if (it != books.end()) {
            return &(*it);
        }
        return nullptr;
    }

    // Borrow a book
    void borrowBook(int memberId, string title) {
        auto memberIt = members.find(memberId);
        if (memberIt != members.end()) {
            Book* book = searchBook(title);
            if (book && book->available) {
                book->available = false;
                memberIt->second.borrowedBooks.push_back(title);
                cout << "Book borrowed successfully!" << endl;
            } else if (book && !book->available) {
                cout << "Book is currently unavailable!" << endl;
            } else {
                cout << "Book not found!" << endl;
            }
        } else {
            cout << "Member not found!" << endl;
        }
    }

    // Return a book and calculate fine
    void returnBook(int memberId, string title) {
        auto memberIt = members.find(memberId);
        if (memberIt != members.end()) {
            Book* book = searchBook(title);
            if (book && !book->available) {
                book->available = true;
                auto& borrowedBooks = memberIt->second.borrowedBooks;
                borrowedBooks.erase(remove(borrowedBooks.begin(), borrowedBooks.end(), title), borrowedBooks.end());
                cout << "Book returned successfully!" << endl;
            } else if (!book || book->available) {
                cout << "This book was not borrowed!" << endl;
            }
        } else {
            cout << "Member not found!" << endl;
        }
    }

    // Add a member
    void addMember(string name, int id) {
        members[id] = Member(name, id);
        cout << "Member added successfully!" << endl;
    }

    // List all books
    void listBooks() {
        cout << "Listing all books in the library:" << endl;
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author
                 << ", Available: " << (book.available ? "Yes" : "No") << endl;
        }
    }

    // List all members
    void listMembers() {
        cout << "Listing all members:" << endl;
        for (const auto& pair : members) {
            cout << "Name: " << pair.second.name << ", ID: " << pair.second.id << endl;
        }
    }
};

int main() {
    Library lib;
    int choice;
    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. List Books\n";
        cout << "4. Add Member\n";
        cout << "5. List Members\n";
        cout << "6. Borrow Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title, author;
                cout << "Enter book title: ";
                cin >> title;
                cout << "Enter book author: ";
                cin >> author;
                lib.addBook(title, author);
                break;
            }
            case 2: {
                string title;
                cout << "Enter book title to remove: ";
                cin >> title;
                lib.removeBook(title);
                break;
            }
            case 3:
                lib.listBooks();
                break;
            case 4: {
                string name;
                int id;
                cout << "Enter member ID: ";
                cin >> id;
                cout << "Enter member name: ";
                cin >> name;
                lib.addMember(name, id);
                break;
            }
            case 5:
                lib.listMembers();
                break;
            case 6: {
                int memberId;
                string title;
                cout << "Enter member ID: ";
                cin >> memberId;
                cout << "Enter book title to borrow: ";
                cin >> title;
                lib.borrowBook(memberId, title);
                break;
            }
            case 7: {
                int memberId;
                string title;
                cout << "Enter member ID: ";
                cin >> memberId;
                cout << "Enter book title to return: ";
                cin >> title;
                lib.returnBook(memberId, title);
                break;
            }
            case 8:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Represents one course
struct Course {
    string number;
    string title;
    vector<string> prereqs;
};

// Node for BST
struct Node {
    Course data;
    Node* left;
    Node* right;

    Node(Course c) {
        data = c;
        left = nullptr;
        right = nullptr;
    }
};

// Simple Binary Search Tree for storing courses
class CourseTree {
private:
    Node* root;

    Node* addNode(Node* current, Course course) {
        if (current == nullptr) {
            return new Node(course);
        }

        if (course.number < current->data.number) {
            current->left = addNode(current->left, course);
        } else {
            current->right = addNode(current->right, course);
        }

        return current;
    }

    Course* findCourse(Node* current, const string& key) {
        if (current == nullptr) {
            return nullptr;
        }

        if (current->data.number == key) {
            return &current->data;
        }

        if (key < current->data.number) {
            return findCourse(current->left, key);
        } else {
            return findCourse(current->right, key);
        }
    }

    void printInOrder(Node* current) {
        if (current == nullptr) {
            return;
        }

        printInOrder(current->left);
        cout << current->data.number << ", "
             << current->data.title << endl;
        printInOrder(current->right);
    }

    void clearTree(Node* current) {
        if (current == nullptr) {
            return;
        }

        clearTree(current->left);
        clearTree(current->right);
        delete current;
    }

public:
    CourseTree() {
        root = nullptr;
    }

    ~CourseTree() {
        clearTree(root);
    }

    void insert(Course course) {
        root = addNode(root, course);
    }

    Course* search(const string& key) {
        return findCourse(root, key);
    }

    void printAll() {
        printInOrder(root);
    }

    bool empty() {
        return root == nullptr;
    }
};

// Convert user input to uppercase
string makeUpper(string text) {
    transform(text.begin(), text.end(), text.begin(), ::toupper);
    return text;
}

// Load CSV file into tree
void loadFile(string filename, CourseTree& tree) {

    ifstream input(filename);

    if (!input.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;

    while (getline(input, line)) {

        stringstream ss(line);
        string part;
        vector<string> pieces;

        while (getline(ss, part, ',')) {
            pieces.push_back(part);
        }

        if (pieces.size() < 2) {
            continue;
        }

        Course course;
        course.number = pieces[0];
        course.title = pieces[1];

        for (size_t i = 2; i < pieces.size(); i++) {
            course.prereqs.push_back(pieces[i]);
        }

        tree.insert(course);
    }

    input.close();
    cout << "File loaded successfully." << endl;
}

// Print details for one course
void showCourse(CourseTree& tree) {

    string key;
    cout << "What course do you want to know about? ";
    cin >> key;

    key = makeUpper(key);

    Course* found = tree.search(key);

    if (found == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << found->number << ", " << found->title << endl;

    if (found->prereqs.empty()) {
        cout << "Prerequisites: None" << endl;
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < found->prereqs.size(); i++) {
            cout << found->prereqs[i];
            if (i < found->prereqs.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// Print menu
void printMenu() {
    cout << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

int main() {

    CourseTree courseTree;
    bool isLoaded = false;
    int option = 0;

    cout << "Welcome to the course planner." << endl;

    while (option != 9) {

        printMenu();
        cout << "What would you like to do? ";
        cin >> option;

        if (option == 1) {
            string filename;
            cout << "Enter file name: ";
            cin >> filename;
            loadFile(filename, courseTree);
            isLoaded = true;
        }
        else if (option == 2) {
            if (!isLoaded) {
                cout << "Please load data first." << endl;
            } else {
                cout << "Here is a sample schedule:" << endl;
                courseTree.printAll();
            }
        }
        else if (option == 3) {
            if (!isLoaded) {
                cout << "Please load data first." << endl;
            } else {
                showCourse(courseTree);
            }
        }
        else if (option == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << option << " is not a valid option." << endl;
        }
    }

    return 0;
}
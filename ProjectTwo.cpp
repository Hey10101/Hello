/*
    CS 300 Project Two
    Advising Assistance Program

    This program loads course data from a CSV file and stores it
    in a map data structure. It allows the user to:
    1. Load course data
    2. Print all courses in alphanumeric order
    3. Print information for a specific course
    9. Exit the program
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Course structure
struct Course {
    string number;
    string title;
    vector<string> prerequisites;
};

// Map automatically keeps keys sorted alphanumerically
map<string, Course> courseMap;

// Function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");

    if (first == string::npos)
        return "";

    return str.substr(first, last - first + 1);
}

// Load file into data structure
void loadData() {
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Unable to open file.\n\n";
        return;
    }

    courseMap.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        // Course number
        getline(ss, token, ',');
        course.number = trim(token);

        // Course title
        getline(ss, token, ',');
        course.title = trim(token);

        // Prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(trim(token));
        }

        courseMap[course.number] = course;
    }

    file.close();
    cout << "Data loaded successfully.\n\n";
}

// Print sorted course list
void printCourseList() {
    if (courseMap.empty()) {
        cout << "No data loaded.\n\n";
        return;
    }

    cout << "\nCourse List:\n";
    cout << "---------------------\n";

    for (const auto& pair : courseMap) {
        cout << pair.second.number << ", "
             << pair.second.title << endl;
    }

    cout << endl;
}

// Print single course information
void printCourseInfo() {
    if (courseMap.empty()) {
        cout << "No data loaded.\n\n";
        return;
    }

    string courseNumber;
    cout << "Enter course number: ";
    cin >> courseNumber;

    // Convert input to uppercase
    transform(courseNumber.begin(), courseNumber.end(),
              courseNumber.begin(), ::toupper);

    auto it = courseMap.find(courseNumber);

    if (it == courseMap.end()) {
        cout << "Course not found.\n\n";
        return;
    }

    Course course = it->second;

    cout << "\n" << course.number << ", "
         << course.title << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None\n\n";
    } else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1)
                cout << ", ";
        }
        cout << "\n\n";
    }
}

// Main menu
int main() {

    int choice = 0;

    while (choice != 9) {

        cout << "---------------------------------\n";
        cout << "ABCU Advising Assistance Program\n";
        cout << "---------------------------------\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        // Input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n\n";
            continue;
        }

        switch (choice) {
            case 1:
                loadData();
                break;
            case 2:
                printCourseList();
                break;
            case 3:
                printCourseInfo();
                break;
            case 9:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid selection. Please try again.\n\n";
        }
    }

    return 0;
}

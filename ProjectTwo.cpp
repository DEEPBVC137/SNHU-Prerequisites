#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>  // for transform
using namespace std;

// Define the Course structure
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// Function to convert a string to uppercase
string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// Function to load courses from a pre-defined file
vector<Course> loadCourses() {
    vector<Course> courses;
    ifstream file("CS 300 ABCU_Advising_Program_Input.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, title, prereq;
        getline(ss, courseId, ',');
        getline(ss, title, ',');

        Course course;
        course.courseId = courseId;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            course.prerequisites.push_back(prereq);
        }

        courses.push_back(course);
    }

    file.close();
    return courses;
}

// Selection Sort to sort courses by courseId
void selectionSort(vector<Course>& courses) {
    for (size_t i = 0; i < courses.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < courses.size(); ++j) {
            if (courses[j].courseId < courses[minIndex].courseId) {
                minIndex = j;
            }
        }
        swap(courses[i], courses[minIndex]);
    }
}

// Function to print all courses
void printCourseList(const vector<Course>& courses) {
    cout << "Here is a sample schedule:" << endl;
    for (const auto& course : courses) {
        cout << course.courseId << ", " << course.title << endl;
    }
    cout << endl;
}

// Function to print specific course details (case-insensitive)
void printCourse(const vector<Course>& courses) {
    cout << "What course do you want to know about? ";
    string inputCourseId;
    cin >> inputCourseId;

    inputCourseId = toUpper(inputCourseId);  // Convert input to uppercase

    bool found = false;
    for (const auto& course : courses) {
        if (toUpper(course.courseId) == inputCourseId) {
            cout << course.courseId << ", " << course.title << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) cout << ", ";
                }
                cout << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Course not found." << endl;
    }
}

// Main menu and program logic
int main() {
    vector<Course> courses;
    bool dataLoaded = false;

    while (true) {
        cout << "Welcome to the course planner." << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        int choice;
        cin >> choice;

        if (cin.fail()) {  // Check if input failed
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input. Please enter a number." << endl;
            continue;  // Restart the loop
        }

        switch (choice) {
        case 1:
            courses = loadCourses();
            selectionSort(courses);  // Sort courses after loading
            dataLoaded = true;
            cout << "Data structure loaded successfully!" << endl;
            break;

        case 2:
            if (dataLoaded) {
                printCourseList(courses);
            }
            else {
                cout << "Please load the data structure first." << endl;
            }
            break;

        case 3:
            if (dataLoaded) {
                printCourse(courses);
            }
            else {
                cout << "Please load the data structure first." << endl;
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
        cout << endl;  // Add some spacing between iterations
    }
}

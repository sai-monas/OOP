#include "headers_testas.h"

structureBoolInt testas;

structureBoolInt validateGrade(std::string grade) {
    std::regex checkIfNumber("^\\d+$");

    if (cin.fail()) {
        // Redundant ?
        cout << "Grade is not a valid number" << endl;
        testas.inputOkay = false;
    }
    else if (std::regex_match(grade, checkIfNumber) == false) {
        cout << "Grade is not a valid number ((regex))" << endl;
        testas.inputOkay = false;
    }
    else if (std::stof(grade) > 10 || std::stof(grade) < 0 ) {
        cout << "Incorrect value entered. Make sure that the exam grade is in range 1-10. Please try again." << endl;
        testas.inputOkay = false;
    }
    else {
        testas.validatedGrade = std::stoi(grade);
        testas.inputOkay = true;
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
    return testas;
};

int main() {
    cout.precision(2);

    structureTest student;
    std::vector<structureTest> studentGroup;

    std::string stringClassGrade;
    std::string stringExamGrade;

    int classGradeSum = 0;
    float averageGrade;

    // Collect inputs
    while (student.name !=  "x") {

        // Collect student's first name
        cout << "Input student name: ";
        cin >> student.name;

        // Check if user wants to exit program
        if (student.name == "x") break;

        // Collect student's last name
        cout << "Input student surname: ";
        cin >> student.surname;

        // Check if collected grade is valid
        do {
            cout << "Input student grade: ";
            cin >> stringExamGrade;
            validateGrade(stringExamGrade);
         } while (testas.inputOkay == false);

        // Accept the exam grade
         student.examGrade = testas.validatedGrade;

        student.gradeCount = -1;

        // Collect student's class grades
        while (testas.validatedGrade != 0) {
            student.gradeCount++;
            cout << "Enter grade " << student.gradeCount + 1 << endl;
            // Check if collected grade is valid
             do {
                cin >> stringClassGrade;
                validateGrade(stringClassGrade);
             } while (testas.inputOkay == false);

             // Accept the class grade
             student.classGrade.push_back(testas.validatedGrade);

             // Get sum of class grades for avg calculation
             classGradeSum += testas.validatedGrade;
        };

        // Calculate average of all grades for each student
        student.averageGrade = static_cast<float>(classGradeSum + student.examGrade) / (student.gradeCount + 1);

        studentGroup.push_back({student});

        // Clear out variables
        student.classGrade.clear();
        classGradeSum = 0;
    }

    // Test if inputs are working
    /*cout << "Name   Surname   Exam grade    Class grades" << endl << "-------------------------------------------------" << endl;
    for (auto n :testukas){
	    cout << n.name << " " << n.surname << " " << n.examGrade << " ";
        for (auto v : n.classGrade)
            cout << v << " ";
        cout << endl;
    };*/

    // Print out students with their average grades
    cout << "Name       Surname   Average" << endl << "-------------------------------------------------" << endl;
    for (auto y :studentGroup){
	    cout << y.name << "  " << y.surname << "    " << y.averageGrade << endl;
    }
    return 0;
}

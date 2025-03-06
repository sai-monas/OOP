#include "headers.h"
#include <windows.h> // For Lithuanian output (SetConsoleOutputCP(CP_UTF8))

std::vector<structureTestVector> studentGroup;
structureTestVector student;


int main() {

    // Variable for user choice of input
    int inputOption;
    
    // Variables for user choice of output 
    std::string outputOption;
    int fileOutputOption;

    // For random student generation
    std::string randomNames[10] = {"Konstantinas", "Danielius", "Vardenis", "Aleksandras", "Kazimieras", "Fridrichas", "Deimantas", "Tautvydas", "Edgaras", "Marijonas"};
    std::string randomSurnames[10] = {"Muilinas", "Pavardenis", "Kavinukas", "Arbataitis", "Antinas", "Mogila", "Sudimtas", "Jonelaitis", "Regesas", "Mamontovas"};
    int studentCount;
    int keepingStudentCount = 0;
    bool generationFinished = false;
    // Providing a seed value for random numbers/grades
	srand(time(0));

    // Start menu with 5 options
    cout << "Welcome to student grade calculator. Choose next steps: " << endl;
    cout << "- Type 1 for manual grade input" << endl << "- Type 2 for grade generation" << endl
    << "- Type 3 to generate students and their grades" << endl  << "- Type 4 to calculate from file" << endl
    << "- Type 5 to exit the program" << endl;

    // Check which option to use
    do {
        cout << "Waiting for your answer: ";
        cin >> inputOption;
     } while (validateInputOption(inputOption) == false);

        // Exit program if 5th option is chosen
        if (inputOption == 5) {
            cout << endl << "Have a nice day!";
            return 0;};
    
        // File option chosen
        if (inputOption == 4) {
            int fileOption;

            cout << "File option chosen for the calculations!" << "Choose a method: " << endl;
            cout << "- Type 1 to use an existing file" << endl << "- Type 2 to generate a file" << endl;
            do {
                cout << "Waiting for your answer: ";
                cin >> fileOption;
             } while (validateFileMethod(fileOption) == false);

            if (fileOption == 1) {
                std::string currentLine;
            std::string firstLine;
            structureTestVector student;
            std::string fileName;
            bool fileRead = false;

            cout << "Input file name to use for calculations: ";
            while (fileRead == false) {
                try {
                    cin >> fileName;

                    // Read from the text file
                    ifstream file(fileName);

                    // Get first line from the file
                    getline(file, firstLine);

                    // Check if first line is empty
                    if (firstLine.empty() == false) {
                        cout << "File '" << fileName << "' opened successfully!" << endl;
                        fileRead = true;
                        }
                    else {
                        throw fileName;
                    }
                }
                catch (std::string input) {
                    setlocale(LC_ALL, ".UTF8");
                    SetConsoleOutputCP(CP_UTF8);
                    std::wcout << L"Klaida: pateiktas failas pavadinimu '";
                    std::cout << input;
                    std::wcout << L"' yra tuščias arba neegzistuoja. Bandykite iš naujo: ";
                }
            }

            
            // Read from the text file
            ifstream file(fileName);

            // Ignore the first line (header)
            getline(file, firstLine);

            while (getline (file, currentLine)) {
                student = parseStudentInfo(currentLine);

                // Turning last grade to exam grade and removing it from class grades
                student.examGrade = student.classGrade[student.classGrade.size() - 1];
                student.classGrade.pop_back();
            
                // Getting the count of class grades
                student.gradeCount = student.classGrade.size();

                // Calculate average grade
                student.averageGrade = calculateAverageGrade((calculateSum(student.classGrade) + student.examGrade), student.gradeCount + 1);

                // Calculate median grade
                student.medianGrade = calculateMedianGrade(student.classGrade, student.examGrade);

                studentGroup.push_back(student);

                // Clear out class grade vector to reuse it
                student.classGrade.clear();
            }

            // Close the file
            file.close();

            // Sorting option menu
            cout << "Would you like to sort the results by name, surname, average grade or median grade?" << endl;
            cout << "- Type 1 to sort by name" << endl << "- Type 2 to sort by surname" << endl
                << "- Type 3 to sort by average grade" << endl  << "- Type 4 to sort by median grade" << endl
                << "- Type 5 to skip sorting" << endl;

            // Check the sorting option chosen
            do {
                cout << "Waiting for your answer: ";
                cin >> fileOutputOption;
            } while (validateInputOption(fileOutputOption) == false);

            // Sort the structure
            sortOutput(studentGroup, fileOutputOption);

            outputMedianAndAverage(studentGroup);
            } // 4th option finished
        }

        // 1st, 2nd and 3rd options
        if ((inputOption == 1) || (inputOption == 2) || (inputOption == 3)) {

            if (inputOption == 3) {
                // Check amount of students to generate for full generation option
                cout << "Type the amount of students you wish to generate: ";
                cin >> studentCount; 
            }

            // Collect inputs
            // While clause only relevant for 1st and 2nd options
            while (student.name !=  "x" || student.name != "X") {
        
        
            // Get student's first name for 1st and 2nd options
            if ((inputOption == 1) || (inputOption == 2)) {
                cout << "- Please type X for the student name if you do not have any remaining students left." << endl;
                cout << "Input student name: ";
                cin >> student.name;
            }
            else {
                // Track number of students (and their grades) already generated
                keepingStudentCount += 1;
                if (keepingStudentCount <= studentCount) {
                    student.name = randomNames[generateRandomNumber()];
                }
                else {
                    generationFinished = true;
                }
            }

            // Check if user wants to exit program for 1st & 2nd options
            if (student.name == "x" || student.name == "X") {
                cout << "<< Student input finished >>" << endl;
                break;
            }

            // Check if all requested students were generated for 3rd option
            if (generationFinished == true) {
            break;
            }


            // Get student's last name
            if ((inputOption == 1) || (inputOption == 2)) {
                cout << "Input student surname: ";
                cin >> student.surname;
            }
            else {
                student.surname = randomSurnames[generateRandomNumber()];
                cout << "Student " << keepingStudentCount << " is: " << student.name << " " << student.surname << endl;
            }

            // Ask for exam grade for 1st option
            if (inputOption == 1) {
                student.examGrade = collectExamGrade();
            }
            // Generate exam grade for 2nd & 3rd options
            else {
                cout << "Exam grade is: ";
                student.examGrade = generateRandomGrade();
                cout << student.examGrade << endl;
            }

            // Ask for class grades for 1st option
            if (inputOption == 1) {

                // Collect student's class grades
                student.classGrade = collectClassGrade();

                // Remove last element (0) from vector
                student.classGrade.pop_back();
            }
            else {
                student.classGrade = generateClassGrades();
            }

            //Add 1 to grade count to account for exam grade
            student.gradeCount = (student.classGrade.size() + 1);

            // Calculate average of grades
            student.averageGrade = calculateAverageGrade((calculateSum(student.classGrade) + student.examGrade), student.gradeCount);

            // Calculate median of grades
            student.medianGrade = calculateMedianGrade(student.classGrade, student.examGrade);

            cout << "<< Class grade input finished for " << student.name << " >>" << endl;

            studentGroup.push_back({student});

            // Clear out variables
            student.classGrade.clear();
        } // While loop finished

        cout << "<< Student data collection finished >>" << endl;

        cout << "Would you like to receive a median or an average of the grades?" << endl << "Please type M for median, or A for average: ";
        do {
            cin >> outputOption;
        } while (validateOutputOption(outputOption) == false); // Check that chosen output option is M (m) or A (a)
        // Print chosen output
        outputMedianOrAverage(studentGroup, outputOption);
    } // 1st, 2nd and 3rd options finished

    return 0;
}
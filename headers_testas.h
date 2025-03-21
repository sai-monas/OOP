#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <string>

#include <iomanip>

// For regex
#include <regex>
#include <cstdlib>


using std::cout;
using std::cin;
using std::endl;


struct structureTestVector {
    std::string name;
    std::string surname;
    std::vector<int> classGrade;
    int examGrade;
    int gradeCount;
    double averageGrade;
    double medianGrade;
};

struct structureTestArray {
    std::string name;
    std::string surname;
    //int* classGrade = new int;
    int examGrade;
    int gradeCount;
    int* classGrade = new int[gradeCount];
    double averageGrade;
    double medianGrade;
};

struct structureBoolInt {
    bool inputOkay;
    int validatedGrade;
};
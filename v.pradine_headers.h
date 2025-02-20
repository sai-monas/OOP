#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <string>
#include <regex>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;


struct structureTest {
    std::string name;
    std::string surname;
    std::vector<int> classGrade;
    int examGrade;
    int gradeCount;
    double averageGrade;
};

struct structureBoolInt {
    bool inputOkay;
    int validatedGrade;
};

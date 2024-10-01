#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {

    Question question;
    string filename = question.selectFileFormat();
    const int numQuestions = 14;

    int totalPoints = question.runQuiz(filename, numQuestions);

    cout << endl << "\033[32m\033[1mEnd of quiz! Points = \033[0m" << "\033[32m\033[1m" << totalPoints << "\033[0m" << endl;

    return 0;
}


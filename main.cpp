#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {

    Question question;
    string filename = question.selectFileFormat();
    const int num_questions = 14;

    int total_points = question.runQuiz(filename, num_questions);

    cout << endl << "\033[32m\033[1mEnd of quiz! Points = \033[0m" << "\033[32m\033[1m" << total_points << "\033[0m" << endl;

    return 0;
}


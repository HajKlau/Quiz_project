#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    try {
        Question question;
        string filename = question.selectFileFormat();
        const int num_questions = 14;

        int total_points = question.runQuiz(filename, num_questions);

        cout << endl << "\033[32m\033[1mEnd of quiz! Points = \033[0m" << "\033[32m\033[1m" << total_points << "\033[0m" << endl;
    } catch (const runtime_error& e) {
        string message = e.what();
        if (message == "Exiting quiz") {
            cout << "User has exited the quiz." << endl;
        } else {
            cerr << "Error: " << message << endl;  
        }
        return 1;  
    } catch (const exception& e) {
        cerr << "An unexpected error occurred: " << e.what() << endl;
        return 2; 
    }

    return 0; 
}

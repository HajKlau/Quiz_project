#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>  // Może być potrzebne dla obsługi std::string

using namespace std;

int main() {
    cout << "Choose file format (txt, json, yml): ";
    string format, filename;
    cin >> format;
    format = toLower(format);
    filename = "quiz." + format; // Zakładamy nazwy plików quiz.txt, quiz.json, quiz.yml

    Question q[14];
    int sum = 0;
    for (int i = 0; i < 14; i++) {
        q[i].question_number = i + 1;
        q[i].load(filename);
        while (!q[i].ask()) {
            cout << "Invalid answer. Try again.\n";
        }
        q[i].check();
        sum += q[i].point;
    }

    cout << "End of quiz! Points = " << sum << endl;

    return 0;
}

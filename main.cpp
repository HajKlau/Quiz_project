#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    set<string> validFormats = {"txt", "json", "yml"};
    string format, filename;
    while (true) {
        cout << "Choose file format (txt, json, yml) or 'exit' to quit: ";
        cin >> format;
        format = toLower(format);

        if (format == "exit") {
            cout << "Exiting quiz." << endl;
            return 0;  // Zakończenie programu
        }

        if (validFormats.find(format) != validFormats.end()) {
            filename = "quiz." + format; // Zakładamy nazwy plików quiz.txt, quiz.json, quiz.yml
            break;
        } else {
            cout << "Invalid file format. Please enter 'txt', 'json', or 'yml'." << endl;
        }
    }

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


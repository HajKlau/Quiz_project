#include "questions.h"
#include "utility.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    map <string, string> formatMap = {
        {"1", "txt"},
        {"2", "json"},
        {"3", "yml"}
    };

    string format, filename;

    while (true) {
        cout << "Please select the file format from the list below and enter 1, 2 or 3 or 'exit' to quit: " << endl;
        for (const auto& pair : formatMap) {
            cout << pair.first << ". " << pair.second << endl;
        }
        cin >> format;
        format = toLower(format);

        if (format == "exit") {
            cout << "Exiting quiz." << endl;
            return 0; 
        }

        if (formatMap.find(format) != formatMap.end()) {
            filename = "quiz." + formatMap[format]; 
            break;
        } else {
            cout << "\033[1m\033[31mInvalid file format. Please enter '1', '2', '3' or 'exit' to quit.\033[0m" << endl;
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

    cout << endl << "\033[32m\033[1mEnd of quiz! Points = \033[0m" << "\033[32m\033[1m" << sum << "\033[0m" << endl;

    return 0;
}


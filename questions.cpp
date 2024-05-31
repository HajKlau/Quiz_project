// questions.cpp
#include "questions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

using namespace std;
using json = nlohmann::json;

string Question::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void Question::load(const string& filename) {
    string extension = filename.substr(filename.find_last_of(".") + 1);
    if (extension == "txt") {
        isTxtFormat = true; // Ustawienie flagi dla formatu TXT
        fstream file(filename, ios::in);
        if (!file.is_open()) {
            cout << "The file cannot be opened\n";
            exit(0);
        }
        loadTxt(file);
        file.close();
    } else {
        isTxtFormat = false; // Ustawienie flagi dla formatów JSON i YAML
        if (extension == "json") {
            loadJson(filename);
        } else if (extension == "yml") {
            loadYaml(filename);
        } else {
            cout << "Unsupported file format\n";
            exit(0);
        }
    }
}

void Question::loadTxt(fstream& file) {
    int line_number = (question_number - 1) * 6 + 1;
    int current_number = 1;
    string line;

    while (getline(file, line)) {
        if (current_number == line_number) {
            size_t pos = line.find('.');
            if (pos != string::npos) {
                contents = line.substr(pos + 2); // Usuń numer pytania i kropkę.
            } else {
                contents = line; // W przypadku braku numeru, użyj całej linii.
            }
        }
        if (current_number >= line_number + 1 && current_number <= line_number + 4) {
            if (line.length() > 2) {
                // Usuwamy prefiks odpowiedzi np. "a) ".
                switch (current_number - line_number) {
                    case 1: a = line.substr(line.find(')') + 2); break;
                    case 2: b = line.substr(line.find(')') + 2); break;
                    case 3: c = line.substr(line.find(')') + 2); break;
                    case 4: d = line.substr(line.find(')') + 2); break;
                }
            }
        }
        if (current_number == line_number + 5) {
            correct_answer = line;  // Bezpośrednie przypisanie litery jako odpowiedzi.
        }
        current_number++;
    }
}


void Question::loadJson(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    string questionKey = "Q" + to_string(question_number); // Tworzymy klucz pytania
    auto q = j[questionKey]; // Używamy klucza do dostępu do pytania
    contents = trim(q["text"].get<std::string>());
    a = trim(q["answer"][0].get<std::string>());
    b = trim(q["answer"][1].get<std::string>());
    c = trim(q["answer"][2].get<std::string>());
    d = trim(q["answer"][3].get<std::string>());
    correct_answer = trim(q["correct_answer"].get<std::string>());
}

void Question::loadYaml(const string& filename) {
    YAML::Node yaml = YAML::LoadFile(filename);
    string questionKey = "Q" + to_string(question_number); // Tworzymy klucz pytania
    auto q = yaml[questionKey]; // Używamy klucza do dostępu do pytania
    if (!q) {
        throw runtime_error("Question data not found in YAML file");
    }
    contents = trim(q["text"].as<string>());
    a = trim(q["answer"][0].as<string>());
    b = trim(q["answer"][1].as<string>());
    c = trim(q["answer"][2].as<string>());
    d = trim(q["answer"][3].as<string>());
    correct_answer = trim(q["correct_answer"].as<string>());
}

int Question::ask() {
    cout << endl << "Question " << question_number << ": " << contents << endl;
    cout << "a) " << a << endl;
    cout << "b) " << b << endl;
    cout << "c) " << c << endl;
    cout << "d) " << d << endl;
    cout << "---------------------------" << endl;
    cout << "Enter your answer (a, b, c, or d): ";
    cin >> answer;

    // Usunięcie warunku zależnego od poprawnej odpowiedzi; zawsze zwróć 1.
    map<string, string> answer_map = {
        {"a", a},
        {"b", b},
        {"c", c},
        {"d", d}
    };

    // Przypisanie pełnego tekstu odpowiedzi niezależnie od poprawności.
    if (answer_map.find(answer) != answer_map.end()) {
        answer = answer_map[answer];
    } else {
        cout << "Invalid answer, please enter a, b, c, or d." << endl;
    }
    return 1; // Zawsze zwracaj 1, aby przejść do następnego pytania
}


void Question::check() {
    cout << "User answer: '" << answer << "' vs Correct answer: '" << correct_answer << "'" << endl;
    if (trim(answer) == trim(correct_answer)) {
        cout << "Correct!" << endl;
        point = 1;
    } else {
        cout << "Wrong! Correct answer: " << correct_answer << endl;
        point = 0;
    }
}






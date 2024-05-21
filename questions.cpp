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


void Question::load(const string& filename) {
    string extension = filename.substr(filename.find_last_of(".") + 1);
    if (extension == "txt") {
        fstream file(filename, ios::in);
        if (!file.is_open()) {
            cout << "The file cannot be opened\n";
            exit(0);
        }
        loadTxt(file);
        file.close();
    } else if (extension == "json") {
        loadJson(filename);
    } else if (extension == "yml") {
        loadYaml(filename);
    } else {
        cout << "Unsupported file format\n";
        exit(0);
    }
}

void Question::loadTxt(fstream& file) {
    int line_number = (question_number - 1) * 6 + 1;
    int current_number = 1;
    string line;

    while (getline(file, line)) {
        if (current_number == line_number) contents = line;
        if (current_number == line_number + 1) a = line;
        if (current_number == line_number + 2) b = line;
        if (current_number == line_number + 3) c = line;
        if (current_number == line_number + 4) d = line;
        if (current_number == line_number + 5) correct_answer = line;
        current_number++;
    }
}

void Question::loadJson(const string& filename) {
    ifstream file(filename);
    json j;
    file >> j;
    string questionKey = "Q" + to_string(question_number); // Tworzymy klucz pytania
    auto q = j[questionKey]; // Używamy klucza do dostępu do pytania
    contents = q["text"];
    a = q["answer"][0];
    b = q["answer"][1];
    c = q["answer"][2];
    d = q["answer"][3];
    correct_answer = q["correct_answer"];
}


void Question::loadYaml(const string& filename) {
    YAML::Node yaml = YAML::LoadFile(filename);
    string questionKey = "Q" + to_string(question_number); // Tworzymy klucz pytania
    auto q = yaml[questionKey]; // Używamy klucza do dostępu do pytania
    if (!q) {
        throw runtime_error("Question data not found in YAML file");
    }
    contents = q["text"].as<string>();
    a = q["answer"][0].as<string>();
    b = q["answer"][1].as<string>();
    c = q["answer"][2].as<string>();
    d = q["answer"][3].as<string>();
    correct_answer = q["correct_answer"].as<string>();
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

    string options[4] = {"a", "b", "c", "d"};
    int valid_answer = 0;
    for (int i = 0; i < 4; i++) {
        if (options[i] == answer) {
            cout << endl << "Your answer: " << answer << endl;
            valid_answer = 1;
            break;
        }
    }
    if (valid_answer == 0) {
        cout << endl << "Invalid answer, please enter a, b, c, or d." << endl;
    }
    return valid_answer;
}


void Question::check() {
    if (answer == correct_answer) {
        point = 1;
    } else {
        point = 0;
    }
}

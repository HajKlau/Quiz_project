// questions.h
#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

using json = nlohmann::json;
using namespace std;

class Question {
public:
    string contents, a, b, c, d, answer, correct_answer;
    int point;
    int question_number;
     bool isTxtFormat;

    string trim(const string& str);
    void load(const string& filename);
    int ask();
    void check();
    void loadTxt(fstream& file);
    void loadJson(const string& filename);
    void loadYaml(const string& filename);
};

#endif // QUESTIONS_H

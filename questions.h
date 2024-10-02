#pragma once
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

    void load(const string& filename);
    void loadTxt(ifstream& file);
    void loadJson(ifstream& file);
    void loadYaml(ifstream& file);
    void check();
    int ask();
    int runQuiz(const string& filename, int num_questions);
    string selectFileFormat();
    void validateQuestionData();
};

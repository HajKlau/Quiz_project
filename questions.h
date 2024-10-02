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
    void loadTxt(fstream& file);
    void loadJson(const string& filename);
    void loadYaml(const string& filename);
    void check();
    int ask();
    int runQuiz(const string& filename, int numQuestions);
    string selectFileFormat();
    void validateQuestionData();
};

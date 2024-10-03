#include "questions.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <yaml-cpp/yaml.h>

using namespace std;
using json = nlohmann::json;

void Question::load(const string &filename)
{
    const string &extension = filename.substr(filename.find_last_of(".") + 1);

    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("The file cannot be opened: " + filename);
    }

    if (extension == "txt")
    {
        loadTxt(file);
    }
    else if (extension == "json")
    {
        loadJson(file);
    }
    else if (extension == "yaml")
    {
        loadYaml(file);
    }
    else
    {
        throw runtime_error("Unsupported file format: " + extension);
    }

    validateQuestionData();

    file.close();
}

void Question::loadTxt(ifstream &file)
{
    int line_number = (question_number - 1) * 6 + 1;
    int current_number = 1;
    string line;
    bool question_found = false;

    while (getline(file, line))
    {
        if (current_number == line_number)
        {
            size_t pos = line.find('.');
            if (pos != string::npos)
            {
                contents = line.substr(pos + 2);
            }
            else
            {
                contents = line;
            }
            question_found = true;
        }
        if (current_number >= line_number + 1 && current_number <= line_number + 4)
        {
            if (line.length() > 2)
            {
                switch (current_number - line_number)
                {
                case 1:
                    a = line.substr(2);
                    break;
                case 2:
                    b = line.substr(2);
                    break;
                case 3:
                    c = line.substr(2);
                    break;
                case 4:
                    d = line.substr(2);
                    break;
                }
            }
        }
        if (current_number == line_number + 5)
        {
            correct_answer = line;
        }
        current_number++;
    }

    if (!question_found)
    {
        throw runtime_error("Question not found in TXT file for question number " + to_string(question_number));
    }
}

void Question::loadJson(ifstream &file)
{
    json j;
    file >> j;

    string question_key = "Q" + to_string(question_number);
    if (j.contains(question_key))
    {
        auto q = j[question_key];
        contents = trim(q["text"].get<std::string>());
        a = trim(q["answer"][0].get<std::string>());
        b = trim(q["answer"][1].get<std::string>());
        c = trim(q["answer"][2].get<std::string>());
        d = trim(q["answer"][3].get<std::string>());
        correct_answer = trim(q["correct_answer"].get<std::string>());
    }
    else
    {
        throw runtime_error("Question data not found in JSON file for key " + question_key);
    }
}

void Question::loadYaml(ifstream &file)
{
    YAML::Node yaml = YAML::Load(file);
    string question_key = "Q" + to_string(question_number);
    auto q = yaml[question_key];
    if (!q)
    {
        throw runtime_error("Question data not found in YAML file for key " + question_key);
    }

    contents = trim(q["text"].as<string>());
    a = trim(q["answer"][0].as<string>());
    b = trim(q["answer"][1].as<string>());
    c = trim(q["answer"][2].as<string>());
    d = trim(q["answer"][3].as<string>());
    correct_answer = trim(q["correct_answer"].as<string>());
}

string Question::selectFileFormat()
{
    map<string, string> format_map = {
        {"1", "txt"},
        {"2", "json"},
        {"3", "yaml"}};

    string format;
    while (true)
    {
        cout << "Please select the file format from the list below and enter 1, 2 or 3 or 'exit' to quit: " << endl;
        for (const auto &pair : format_map)
        {
            cout << pair.first << ". " << pair.second << endl;
        }
        cin >> format;
        format = toLower(format);

        if (format == "exit")
        {
            throw runtime_error("Exiting quiz");
        }

        if (format_map.find(format) != format_map.end())
        {
            return "quiz." + format_map[format];
        }
        else
        {
            cout << "\033[1m\033[31mInvalid file format. Please enter '1', '2', '3' or 'exit' to quit.\033[0m" << endl;
        }
    }
}

int Question::runQuiz(const string &filename, int num_questions)
{
    Question q[num_questions];
    int total_points = 0;

    for (int i = 0; i < num_questions; i++)
    {
        q[i].question_number = i + 1;
        q[i].load(filename);

        while (!q[i].ask())
        {
            cout << "Invalid answer. Try again.\n";
        }

        q[i].check();
        total_points += q[i].point;
    }

    return total_points;
}

int Question::ask()
{
    map<string, string> answer_map = {
        {"a", a},
        {"b", b},
        {"c", c},
        {"d", d}};

    while (true)
    {
        cout << endl
             << "Question " << question_number << ": " << contents << endl;
        cout << "a) " << a << endl;
        cout << "b) " << b << endl;
        cout << "c) " << c << endl;
        cout << "d) " << d << endl;
        cout << "---------------------------" << endl;
        cout << "Enter your answer (a, b, c, or d) or 'exit' to quit: ";
        cin >> answer;
        answer = toLower(answer);

        if (answer == "exit")
        {
            throw runtime_error("Exiting quiz");
        }

        if (isValidInput(answer))
        {
            if (answer_map.find(answer) != answer_map.end())
            {
                answer = answer_map[answer];
                return 1;
            }
        }

        cout << endl
             << "\033[1m\033[31mInvalid answer, please enter a, b, c, or d.\033[0m" << endl;
    }
}

void Question::check()
{

    if (trim(answer) == trim(correct_answer))
    {
        cout << "Correct!" << endl;
        point = 1;
    }
    else
    {

        point = 0;
    }
}

void Question::validateQuestionData()
{
    if (contents.empty() || a.empty() || b.empty() || c.empty() || d.empty() || correct_answer.empty())
    {
        throw runtime_error("Incomplete question data for question number " + to_string(question_number));
    }
}

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

    if (extension == "json")
    {
        loadJson(file);
    }
    else if (extension == "yaml" || extension == "yml")
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
        {"1", "json"},
        {"2", "yaml"}};

    string format;
    while (true)
    {
        cout << "Please select the file format from the list below and enter 1 or 2 or 'exit' to quit: " << endl;
        for (const auto &pair : format_map)
        {
            cout << pair.first << ". " << pair.second << endl;
        }
        cin >> format;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        format = toLower(format);

        if (!isValidInput(format))
        {
            continue;
        }

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
            cout << "\033[1m\033[31mInvalid file format. Please enter '1', '2' or 'exit' to quit.\033[0m" << endl;
        }
    }
}

int Question::runQuiz(const string &filename, int num_questions)
{
    vector<Question> q(num_questions);
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
        string user_input;
        getline(cin, user_input);
        user_input = trim(toLower(user_input));

        if (!isValidInput(user_input))
        {
            continue;
        }

        if (user_input == "exit")
        {
            throw runtime_error("Exiting quiz");
        }

        if (user_input.empty())
        {

            cout << "\033[1m\033[31mNo answer provided. Please enter a, b, c, or d.\033[0m" << endl;
            continue;
        }

        if (user_input.length() == 1 && answer_map.find(user_input) != answer_map.end())
        {
            answer = answer_map[user_input];
            return 1;
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
        cout << "Incorrect." << endl;
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

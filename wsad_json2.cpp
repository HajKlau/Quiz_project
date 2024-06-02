#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string> 
#include <yaml-cpp/yaml.h> 

using namespace std;
using json = nlohmann::json;


int main( int argc, char* argv[] )

{   
    json json_data;  // Separate variable for JSON data
    YAML::Node yaml_data;  // Separate variable for YAML data
    string file_type;
    char question[5];
    string tablica[4] = {"a", "b", "c", "d"};
    string user_answer;
    string answer_translated;
    int score = 0;
    int i;

    std::ifstream f(argv[2]);

    if (strcmp(argv[1], "--json-file") == 0)
    {
        json json_data = json::parse(f);
        file_type = "json";
    }
    else if (strcmp(argv[1], "--yml-file") == 0)
    {
        YAML::Node yaml_data = YAML::Load(f); 
        file_type = "yml";
    }

    for (i = 1; i <= (file_type == "json" ? json_data.size() : yaml_data.size()); i++)
    {
        answer_translated = "";
        string text;
        string correct_answer;
        vector<string> answer;
        sprintf(question, "Q%d", i);
        if ( file_type == "yml")
        {
            text = yaml_data[question]["text"].as<string>(); 
            correct_answer = yaml_data[question]["correct_answer"].as<string>(); 
            answer = yaml_data[question]["answer"].as<vector<string>>(); 
        }
        else if ( file_type == "json")
        {
            text = json_data[question].value("text", "not found");
            correct_answer = json_data[question].value("correct_answer", "not found");
        const auto& json_answer = json_data[question]["answer"];
        if (json_answer.is_array()) {
            for (const auto& elem : json_answer) {
                answer.push_back(elem.get<std::string>());
            }
        }
        }
        
        cout << endl << "=====================================================";
        cout << endl << "Question:   " << endl << text << endl << endl; 

        for (int i=0;i<=(answer.size()-1);i++)
        {
            cout << tablica[i] << ")   " << answer[i] << endl;
            if (answer[i] == correct_answer)
            {
                answer_translated = tablica[i];
            }
        }

        cout << endl << "Your answer: " << endl;
        cin >> user_answer;

        bool exists = find(begin(tablica), std::end(tablica), user_answer) != std::end(tablica);
        if (!exists)
        {
            i--;
            cout << endl << "\033[1;34mThere is no such answer!\033[0m" << endl;
            continue;
        }

        if (user_answer == answer_translated)
        {
            cout << endl << "\033[1;32mCorrect!\033[0m" << endl;
            score++;
        }
        else
        {   
            cout << endl << "\033[1;31mWrong!\033[0m" << endl;
        }
    }
    cout << endl << "#######################################################";
    cout << endl << "\033[1;35mYou got " << score << " points\033[0m" << endl;
    cout << "#######################################################" << endl;

    return 0; 
}
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string> 
#include <yaml-cpp/yaml.h> 

using namespace std;
using json = nlohmann::json;





int main( int argc, char* argv[] )

{
    char question[5];
    string tablica[4] = {"a", "b", "c", "d"};
    string user_answer;
    string answer_translated;
    int score = 0;
    std::ifstream f(argv[2]);

    if (argv[1] == "--json-file")
    {
        json data = json::parse(f);
        
    for (int i=1; i<=data.size(); i++)
    {
        answer_translated = "";
        sprintf(question, "Q%d", i);
        string text = data[question].value("text", "not found");
        string correct_answer = data[question].value("correct_answer", "not found");
        vector<string> answer = data[question]["answer"]; 
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

        bool exists = find(begin(tablica), end(tablica), user_answer) != end(tablica);
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
    else if (argv[1] == "--yml-file")
    {
        YAML::Node config = YAML::Load(f); 

    for (int i=1; i<=config.size(); i++)
    {
        answer_translated = "";
        sprintf(question, "Q%d", i);
        string text = config[question]["text"].as<string>(); 
        string correct_answer = config[question]["correct_answer"].as<string>(); 
        vector<string> answer = config[question]["answer"].as<vector<string>>(); 
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
else 
{
        for (int i = 0; i < argc; ++i)
        cout << argv[i] << "\n";
}
}
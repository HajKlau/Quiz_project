#include <fstream> 
#include <iostream> 
#include <string> 
#include <yaml-cpp/yaml.h> 

using namespace std;

int main() 
{ 
    // Open the config file 
    ifstream fin("quiz.yml"); 
    YAML::Node config = YAML::Load(fin); 

    char question[5];
    string tablica[4] = {"a", "b", "c", "d"};
    string user_answer;
    string answer_translated;
    int score = 0;

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
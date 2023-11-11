#include <iostream>
using namespace std;

class Question
{
    public:

    string contents;
    string a,b,c,d;
    int question_number;
    string answer;
    string correct_answer;
    int point;


    void load(); //load a questions from a file
    int ask(); //shows the question and verifies the answer
    void check(); //checks if the answer is correct
};
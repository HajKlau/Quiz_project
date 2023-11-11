#include <iostream>
#include "questions.h"
#include <fstream>
#include <cstdlib>  

using namespace std;

void Question::load()
{
    fstream file;
    file.open("quiz.txt", ios::in);

    if(file.good()==false)
    {
        cout<<"The file cannot be opened";
        exit(0);
    }

    int line_number=(question_number-1)*6+1;
    int current_number = 1;
    string line;

    while(getline(file,line))
    {
        if(current_number==line_number) contents=line;
        if(current_number==line_number+1) a=line;
        if(current_number==line_number+2) b=line;
        if(current_number==line_number+3) c=line;
        if(current_number==line_number+4) d=line;
        if(current_number==line_number+5) correct_answer=line;
        current_number++; 
    }


    file.close();

}

int Question::ask()
{
    cout<<endl<<contents<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
    cout<<d<<endl;
    cout<<"---------------------------"<<endl;
    cin>>answer;
    
    string tablica[4] = {"a", "b", "c", "d"};
    int valid_answer = 0;
    for( int i=0; i<=4; i++) {
        if (tablica[i] == answer)
        {
            cout<<endl<<"Answer: "<<answer<<endl;
            valid_answer = 1;
        }
    }
    if (valid_answer == 0)
    {
        cout<<endl<<"There is no such answer"<<endl;
    }

    return valid_answer;
}

void Question::check()
{
    if(answer==correct_answer)
    {
        point=1;
    }
    else point=0;
}

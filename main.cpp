#include <iostream>
#include "questions.h"

using namespace std;

int main()
{
    Question q[14];
    int sum=0;
    int valid_answer=0;
    
    for(int i=0;  i<=13;  i++)
    {
        q[i].question_number=i+1;
        q[i].load();
        while(valid_answer == 0) {
            valid_answer = q[i].ask();
        }
        q[i].check();
        sum+=q[i].point;
        valid_answer = 0;
    }
    
    cout<<"End of quiz! Points = "<<sum;

    return 0;
}
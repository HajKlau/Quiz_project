#include "utility.h"
#include <iostream>
#include <cctype>

using namespace std;

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

string toLower(const string &str)
{
    string lower_str;
    lower_str.reserve(str.size());
    for (char c : str)
    {
        lower_str += tolower(static_cast<unsigned char>(c));
    }
    return lower_str;
}

bool isValidInput(const string &input)
{
    if (input.length() > 20)
    {
        cout << "\033[1m\033[31mError: Input is too long. Maximum 20 characters allowed.\033[0m" << endl;
        return false;
    }

    for (char c : input)
    {
        if (!isalnum(static_cast<unsigned char>(c)))
        {
            cout << "\033[1m\033[31mError: Invalid characters detected. Only letters and digits are allowed.\033[0m" << endl;
            return false;
        }
    }
    return true;
}

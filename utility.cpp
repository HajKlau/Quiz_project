#include "utility.h"
#include <iostream>
#include <cctype> 

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::string toLower(const std::string& str) {
    std::string lowerStr;
    lowerStr.reserve(str.size());
    for (char c : str) {
        lowerStr += std::tolower(static_cast<unsigned char>(c)); 
    }
    return lowerStr;
}

bool isValidInput(const std::string& input) {
    if (input.length() > 20) {
        std::cout << "\033[1m\033[31mError: Input is too long. Maximum 20 characters allowed.\033[0m" << std::endl;
        return false;
    }

    for (char c : input) {
        if (!std::isalnum(static_cast<unsigned char>(c))) {
            std::cout << "\033[1m\033[31mError: Invalid characters detected. Only letters and digits are allowed.\033[0m" << std::endl;
            return false;
        }
    }
    return true;
}

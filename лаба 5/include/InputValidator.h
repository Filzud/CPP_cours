#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <regex>
#include <string>

using namespace std;

class InputValidator {
public:
    bool isValidEmail(const string& email) const;
    bool isSafeInput(const string& text) const;
    bool isValidLength(const string& text, size_t minLen, size_t maxLen) const;
    bool isValidGrade(int grade) const;
};

#endif

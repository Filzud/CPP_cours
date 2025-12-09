#include "InputValidator.h"

bool InputValidator::isValidEmail(const string& email) const {
    static const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    return regex_match(email, pattern);
}

bool InputValidator::isSafeInput(const string& text) const {
    // Block simple SQL injection markers
    static const string badChars = "'\";--";
    for (char c : badChars) {
        if (text.find(c) != string::npos) return false;
    }
    return true;
}

bool InputValidator::isValidLength(const string& text, size_t minLen, size_t maxLen) const {
    return text.length() >= minLen && text.length() <= maxLen;
}

bool InputValidator::isValidGrade(int grade) const {
    return grade >= 0 && grade <= 100;
}

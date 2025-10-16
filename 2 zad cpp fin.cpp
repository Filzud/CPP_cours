#include <iostream>
using namespace std;

int cstrLength(const char* s) 
{
    int n = 0;
    while (s && s[n] != '\0') ++n;
    return n;
}
void reverseInPlace(char* s) 
{
    if (!s) return;
    int i = 0, j = cstrLength(s) - 1;
    while (i < j) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
        ++i; --j;
    }
}
int countChar(const char* s, char ch) 
{
    int c = 0;
    for (int i = 0; s && s[i] != '\0'; ++i) if (s[i] == ch) ++c;
    return c;
}

int main() 
{
    char s[256];
    cout << "Enter line: ";
    cin.getline(s, 256);

    cout << "Length: " << cstrLength(s) << "\n";

    reverseInPlace(s);
    cout << "Reversed: " << s << "\n";

    cout << "Char to count: ";
    char ch; cin >> ch;
    cout << "Count: " << countChar(s, ch) << "\n";
    return 0;
}

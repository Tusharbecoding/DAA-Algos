#include <iostream>
#include <cstring>

const int MAX_CHAR = 256; // Maximum ASCII characters

class BoyerMoore
{
private:
    char pattern[MAX_CHAR];
    int patternLength;

    void badCharHeuristic(int badchar[MAX_CHAR]);

public:
    BoyerMoore(const char pattern[]);
    void search(const char text[]);
};

BoyerMoore::BoyerMoore(const char pattern[])
{
    std::strcpy(this->pattern, pattern);
    this->patternLength = std::strlen(pattern);
}

void BoyerMoore::badCharHeuristic(int badchar[MAX_CHAR])
{
    for (int i = 0; i < MAX_CHAR; i++)
    {
        badchar[i] = -1;
    }

    for (int i = 0; i < patternLength; i++)
    {
        badchar[static_cast<int>(pattern[i])] = i;
    }
}

void BoyerMoore::search(const char text[])
{
    int textLength = std::strlen(text);

    int badchar[MAX_CHAR];
    badCharHeuristic(badchar);

    int s = 0; // Shift of the pattern with respect to text
    while (s <= (textLength - patternLength))
    {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[s + j])
        {
            j--;
        }

        if (j < 0)
        {
            std::cout << "Pattern found at index " << s << std::endl;

            // Shift based on bad character heuristic
            s += (s + patternLength < textLength) ? patternLength - badchar[static_cast<int>(text[s + patternLength])] : 1;
        }
        else
        {
            // Shift based on max of bad character and mismatch character
            s += std::max(1, j - badchar[static_cast<int>(text[s + j])]);
        }
    }
}

int main()
{
    const char text[] = "ABAAABCD";
    const char pattern[] = "ABC";

    BoyerMoore boyerMoore(pattern);
    boyerMoore.search(text);

    return 0;
}

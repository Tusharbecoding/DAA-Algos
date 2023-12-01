#include <iostream>

const int MAX_N = 1000; // Maximum length of the text and pattern (adjust as needed)

class KMP
{
private:
    int prefixTable[MAX_N];

public:
    void buildPrefixTable(const char pattern[], int patternLength);
    void search(const char text[], int textLength, const char pattern[], int patternLength);
};

void KMP::buildPrefixTable(const char pattern[], int patternLength)
{
    int j = 0;
    prefixTable[0] = 0;

    for (int i = 1; i < patternLength;)
    {
        if (pattern[i] == pattern[j])
        {
            prefixTable[i] = j + 1;
            j++;
            i++;
        }
        else
        {
            if (j != 0)
            {
                j = prefixTable[j - 1];
            }
            else
            {
                prefixTable[i] = 0;
                i++;
            }
        }
    }
}

void KMP::search(const char text[], int textLength, const char pattern[], int patternLength)
{
    buildPrefixTable(pattern, patternLength);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < textLength)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }

        if (j == patternLength)
        {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = prefixTable[j - 1];
        }
        else if (i < textLength && text[i] != pattern[j])
        {
            if (j != 0)
            {
                j = prefixTable[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
}

int main()
{
    const char text[] = "ABABDABACDABABCABAB";
    const char pattern[] = "ABABCABAB";

    KMP kmp;
    kmp.search(text, std::strlen(text), pattern, std::strlen(pattern));

    return 0;
}

#include <iostream>
#include <cmath>

const int prime = 101; // A prime number for hashing

void rabinKarp(const char text[], const char pattern[])
{
    int textLength = std::strlen(text);
    int patternLength = std::strlen(pattern);

    // Calculate (prime^(patternLength - 1)) % prime for rolling hash
    int h = 1;
    for (int i = 0; i < patternLength - 1; i++)
    {
        h = (h * 256) % prime;
    }

    // Calculate hash values for the pattern and the first window in the text
    int patternHash = 0;
    int windowHash = 0;
    for (int i = 0; i < patternLength; i++)
    {
        patternHash = (256 * patternHash + pattern[i]) % prime;
        windowHash = (256 * windowHash + text[i]) % prime;
    }

    // Iterate through the text using the rolling hash technique
    for (int i = 0; i <= textLength - patternLength; i++)
    {
        // Check if the hash values match
        if (patternHash == windowHash)
        {
            // Check character by character if the pattern matches the text
            int j;
            for (j = 0; j < patternLength; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    break;
                }
            }

            if (j == patternLength)
            {
                std::cout << "Pattern found at index " << i << std::endl;
            }
        }

        // Calculate the hash value for the next window in the text
        if (i < textLength - patternLength)
        {
            windowHash = (256 * (windowHash - text[i] * h) + text[i + patternLength]) % prime;

            // Handle negative hash values
            if (windowHash < 0)
            {
                windowHash += prime;
            }
        }
    }
}

int main()
{
    const char text[] = "ABABDABACDABABCABAB";
    const char pattern[] = "ABABCABAB";

    rabinKarp(text, pattern);

    return 0;
}

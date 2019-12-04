#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <crypt.h>
#include <unistd.h>

void iterateOverChars(string input, string salt, char *crackAttempt, int charIndex, int len);
//Recursive function to avoid hardcoding each char iteration; iterates each character in all possibilities until charIndex reaches len - 1

char result[5];
bool resultFound = false;

void iterateOverChars(string input, string salt, char *crackAttempt, int charIndex, int len)
{
    if (charIndex < len - 1)
    {
        for (char c = 'a'; c <= 'z'; c++)
        {
            crackAttempt[charIndex] = c;
            // Recurse
            iterateOverChars(input, salt, crackAttempt, charIndex + 1, len);
            // Recursive return
            if (resultFound) return;
        }
        for (char c = 'A'; c <= 'Z'; c++)
        {
            crackAttempt[charIndex] = c;
            // Recurse
            iterateOverChars(input, salt, crackAttempt, charIndex + 1, len);
            // Recursive return
            if (resultFound) return;
        }
    }
    else
    {
        // For the very last level of string construction, calculate the hash
        string resultHash = crypt(crackAttempt, salt);
        bool resultsMatch = true;
        // Compare the hash
        for (int i = 0; i < 13; i++)
        {{
            if (resultHash[i] != input[i])
            {
                resultsMatch = false;
                break;
            }
        }
        if (resultsMatch)
        {
            resultFound = true;
            for (int i = 0; i < len; i++)
            {
                result[i] = crackAttempt[i];
            }
            // Initialize recursive return
            return;
        }
    }
}}


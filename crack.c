// https://pastebin.com/eFY8uMVg

#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <crypt.h>

int MAX_KEY_LENGTH = 4;

//
// Notes: All passwords are assumed to be 4 letters long, case sensitive, and alphabetic.
/*
crypt()  is  the password encryption function.  It is based on the Data Encryption Standard algorithm with variations intended (among other things) to discourage use of hardware implementa‐
tions of a key search.

key is a user's typed password.

salt is a two-character string chosen from the set [a–zA–Z0–9./].  This string is used to perturb the algorithm in one of 4096 different ways.

By taking the lowest 7 bits of each of the first eight characters of the key, a 56-bit key is obtained.  This 56-bit key is used to encrypt repeatedly a constant string  (usually  a  string
consisting  of  all zeros).  The returned value points to the encrypted password, a series of 13 printable ASCII characters (the first two characters represent the salt itself).  The return
value points to static data whose content is overwritten by each call.

Warning: The key space consists of 2**56 equal 7.2e16 possible values.  Exhaustive searches of this key space are possible using massively parallel computers.  Software, such  as  crack(1),
is  available  which  will  search the portion of this key space that is generally used by humans for passwords.  Hence, password selection should, at minimum, avoid common words and names.
The use of a passwd(1) program that checks for crackable passwords during the selection process is recommended.

The DES algorithm itself has a few quirks which make the use of the crypt() interface a very poor choice for anything other than password authentication.  If you are planning on  using  the
crypt() interface for a cryptography project, don't do it: get a good book on encryption and one of the widely available DES libraries.
*/

void iterateOverChars(string input, string salt, char *crackAttempt, int charIndex, int len);
char result[5];
bool resultFound = false;

int main(int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 13)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    
    // Get salt from first two chars
    char salt[3] = {argv[1][0], argv[1][1], '\0'};
    
    // Iterate from 1 to the max key length of all possibilities for passwords.
    for (int len = 1, n = MAX_KEY_LENGTH + 2; len < n; len++)
    {
        // Construct string for crack attempts
        char crackAttempt[len + 1];
        crackAttempt[len] = '\0';
        
        iterateOverChars(argv[1], salt, crackAttempt, 0, len);
        if (resultFound)
        {
            printf("%s\n", result);
            return 0;
        }
    }
    printf("Password could not be cracked.\n");
    return 1;
}

//Recursive function to avoid hardcoding each char iteration; iterates each character in all possibilities until charIndex reaches len - 1
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


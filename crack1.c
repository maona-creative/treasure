#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <crypt.h>
#include "iterateOver.h"


int main(void)
{
//char hsh [14] = "50cI2vYkF0YU2";
//char salt [3] = "50";

        char crackAttempt[4];
        crackAttempt[3] = '\0';
        iterateOverChars("50cI2vYkF0YU2", "50", crackAttempt, 0, 3);
}

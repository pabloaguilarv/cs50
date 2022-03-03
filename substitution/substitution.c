
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

char LOW[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char UPS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// The duplicate string has to be initialized manually or else C randomly puts a character there that could be in the Key and it explodes.
char dups[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};

int main(int argc, string argv[])
{
    // Failsafe for not enough arguments inputs.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int keylen = strlen(argv[1]);
    // Failsafe for keys below 26 chars.
    if (keylen < 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }

    char a[keylen];
    string key = argv[1];
    string keycopy = key;
    // Check for duplicates
    for (int i = 0; i < 26; i++)
    {
        // Char is converted to ASCII for ease.
        int asc = key[i];
        for (int j = 0; j < 26; j++)
        {
            //  For uppercase letters
            if (64 < asc && asc < 91)
            {
                if (key[i] == dups[j])
                {
                    printf("Duplicates are invalid.\n");
                    return 1;
                }
            }
            // For lowercase letters
            else if (96 < asc && asc < 123)
            {
                if (key[i] == dups[j])
                {
                    printf("Duplicates are invalid.\n");
                    return 1;
                }
            }
            else
            {
                // If the character is outside of the ranges.
                // For example an invalid character.
                printf("Non-alphabetic characters are invalid.\n");
                return 1;
            }
        }
        dups[i] = key[i];
    }
    string inp = get_string("plaintext: ");
    int len = strlen(inp);

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            // Encrypt uppercase to uppercase.
            if (inp[i] == UPS[j])
            {
                inp[i] = toupper(key[j]);
                break;
            }
            // Encrypt lowercase to lowercase.
            else if (inp[i] == LOW[j])
            {
                inp[i] = tolower(key[j]);
                break;
            }
        }
    }

    printf("ciphertext: %s\n", inp);
}

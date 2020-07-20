#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int check_key(string);
string encipher(string, string);
int main(int argc, char *argv[])
{
    string key = argv[1];
    int code;
    string plaintext = "";
    if (argc == 2)
    {
        code = check_key(argv[1]);
        if (code == 0)
        {
            plaintext = get_string("plaintext: ");
            string cypher = encipher(key, plaintext);
            printf("ciphertext: %s\n", cypher);
        }
        else
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

int check_key(string key)
{
    char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; key[i]; i++)
    {
        key[i] = tolower(key[i]);
    }
    if (strlen(key) == 26)
    {
        for (int i = 0; i < strlen(alpha); i++)
        {
            char *position_ptr = strchr(key, alpha[i]);

            int position = (position_ptr == NULL ? -1 : position_ptr - key);

            if (position == -1)
            {
                printf("The key is invalid! %c is missing.", alpha[i]);
                return 1;
            }
        }
        return 0;
    }
    else
    {
        printf("Wrong key.");
        return 1;
    }
}

string encipher(string key, string plaintext)
{
    int i = 0;
    char alpha[] = "abcdefghijklmnopqrstuvwxyz";
    while (plaintext[i] != '\0')
    {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            char *position_ptr = strchr(alpha, plaintext[i]);
            int position = (position_ptr == NULL ? -1 : position_ptr - alpha);
            plaintext[i] = key[position];
        }
        else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            char *position_ptr = strchr(alpha, tolower(plaintext[i]));
            int position = (position_ptr == NULL ? -1 : position_ptr - alpha);
            plaintext[i] = toupper(key[position]);
        }
        else
        {
            plaintext[i] = plaintext[i];
        }
        i++;
    }
    return plaintext;
}
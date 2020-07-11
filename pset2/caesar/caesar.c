#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string key = argv[1];

    if (argc == 2) {
        for (int i = 0, n = strlen(key); i < n; i++) {
            if (!isdigit(key[i])) {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        int k = atoi(key);

        // promp for plaintext
        string text = get_string("plaintext: ");

        for (int i = 0, n = strlen(text); i < n; i++) {
            char letter = text[i];

            if (isupper(letter)) {
                int place = ((letter % 65) + (k % 26)) % 26;
                text[i] = place + 65;
            } else if (islower(letter)) {
                int place = ((letter % 97) + (k % 26)) % 26;
                text[i] = place + 97;
            }
        }

        printf("ciphertext: %s\n", text);
    } else {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    return 0;
}  
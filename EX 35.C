#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000


void encryptVigenereOneTimePad(char *plaintext, int *key, char *ciphertext) {
    int keyIndex = 0;
    int i = 0;

    while (plaintext[i] != '\0') {
        char c = plaintext[i];

        if (isalpha(c)) {
          
            c = toupper(c);
         
            int shift = key[keyIndex] % 26;
            char encryptedChar = ((c - 'A' + shift) % 26) + 'A';
            ciphertext[i] = encryptedChar;

            keyIndex = (keyIndex + 1) % MAX_TEXT_LENGTH;
        } else {
           
            ciphertext[i] = c;
        }

        i++;
    }


    ciphertext[i] = '\0';
}

int main() {
    char plaintext[MAX_TEXT_LENGTH];
    int key[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

    printf("Enter the plaintext (uppercase letters and spaces only): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the key (space-separated random numbers between 0 and 26): ");
    for (int i = 0; i < MAX_TEXT_LENGTH; i++) {
        if (scanf("%d", &key[i]) != 1) {
            break;
        }
    }

  
    encryptVigenereOneTimePad(plaintext, key, ciphertext);

    printf("Encrypted ciphertext: %s\n", ciphertext);

    return 0;
}

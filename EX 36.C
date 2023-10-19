#include <stdio.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
char encrypt(char ch, int a, int b) {
    if (ch >= 'A' && ch <= 'Z') {
        return ((a * (ch - 'A') + b) % 26) + 'A';
    } else if (ch >= 'a' && ch <= 'z') {
        return ((a * (ch - 'a') + b) % 26) + 'a';
    } else {
        return ch; 
    }
}
char decrypt(char ch, int a, int b) {
    int aInverse = modInverse(a, 26);
    if (aInverse == -1) {
        printf("Modular inverse of 'a' does not exist. Decryption not possible.\n");
        return ch;
    }
    if (ch >= 'A' && ch <= 'Z') {
        return (aInverse * (ch - 'A' - b + 26) % 26) + 'A';
    } else if (ch >= 'a' && ch <= 'z') {
        return (aInverse * (ch - 'a' - b + 26) % 26) + 'a';
    } else {
        return ch; 
    }
}
int main() {
    int a, b;
    char plaintext[1000];    
    printf("Enter the value of 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of 'b': ");
    scanf("%d", &b);
    if (a <= 0 || a >= 26 || modInverse(a, 26) == -1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return 1;
    }
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
    printf("Encrypted text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", encrypt(plaintext[i], a, b));
    }
    printf("\n");
    printf("Decrypted text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", decrypt(plaintext[i], a, b));
    }
    printf("\n");

    return 0;
}

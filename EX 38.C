#include <stdio.h>

int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

int mod_inverse(int a, int m) {
    int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Modular inverse does not exist
}

void decrypt(int cipher[], int key[][2], int size, int mod) {
    int inverse_a = mod_inverse(key[0][0], mod);
    int inverse_d = mod_inverse(key[1][1], mod);

    if (inverse_a == -1 || inverse_d == -1) {
        printf("Inverse does not exist. Unable to decrypt.\n");
        return;
    }

    int det_inv = mod_inverse(determinant(key[0][0], key[0][1], key[1][0], key[1][1]), mod);

    int inverse_key[2][2] = {
        {key[1][1] * det_inv, -key[0][1] * det_inv},
        {-key[1][0] * det_inv, key[0][0] * det_inv}
    };

    for (int i = 0; i < size; i++) {
        int x = (cipher[i] * inverse_key[0][0] + cipher[i+1] * inverse_key[1][0]) % mod;
        int y = (cipher[i] * inverse_key[0][1] + cipher[i+1] * inverse_key[1][1]) % mod;
        printf("%c%c", x + 'A', y + 'A');
        i++; 
    }
    printf("\n");
}

int main() {
    int mod = 26;
    int key[2][2] = {{3, 2}, {5, 7}}; 
    int size = 0;

    printf("Enter the size of ciphertext: ");
    scanf("%d", &size);

    int cipher[size];
    printf("Enter the ciphertext (as numbers 0-25): ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &cipher[i]);
    }

    printf("Decrypted plaintext: ");
    decrypt(cipher, key, size, mod);

    return 0;
}

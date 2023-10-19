#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long mod_pow(long long base, long long exp, long long modulus) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp /= 2;
    }
    return result;
}

long long encrypt(long long message, long long e, long long n) {
    return mod_pow(message, e, n);
}

long long decrypt(long long encrypted_msg, long long d, long long n) {
    return mod_pow(encrypted_msg, d, n);
}

int main() {
    long long p, q, n, phi, e, d, message, encrypted_msg, decrypted_msg;

    p = 997;
    q = 983; 

    n = p * q;
    phi = (p - 1) * (q - 1);

    e = 65537; 

    d = 1;
    while (((d * e) % phi) != 1) {
        d++;
    }

    printf("Public key (e, n): (%lld, %lld)\n", e, n);
    printf("Private key (d, n): (%lld, %lld)\n", d, n);

    message = 15; 

    encrypted_msg = encrypt(message, e, n);
    printf("Encrypted message: %lld\n", encrypted_msg);

    decrypted_msg = decrypt(encrypted_msg, d, n);
    printf("Decrypted message: %lld\n", decrypted_msg);

    return 0;
}

#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main() {
    RSA *rsa = RSA_new();

    int old_key_bits = 2048; 
    int new_key_bits = 4096; 

    rsa = RSA_generate_key(new_key_bits, RSA_F4, NULL, NULL);

    printf("New public key (N, e):\n");
    BN_print_fp(stdout, rsa->n);
    printf(", ");
    BN_print_fp(stdout, rsa->e);
    printf("\n");

    printf("New private key (N, d):\n");
    BN_print_fp(stdout, rsa->n);
    printf(", ");
    BN_print_fp(stdout, rsa->d);
    printf("\n");

    const char *message = "Hello, RSA!";
    unsigned char encrypted[4096] = {0};
    unsigned char decrypted[4096] = {0};
    int encrypted_len, decrypted_len;

    encrypted_len = RSA_public_encrypt(strlen(message), (unsigned char*)message, encrypted, rsa, RSA_PKCS1_PADDING);
    if (encrypted_len == -1) {
        printf("Encryption error.\n");
        return 1;
    }

    decrypted_len = RSA_private_decrypt(encrypted_len, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (decrypted_len == -1) {
        printf("Decryption error.\n");
        return 1;
    }

    decrypted[decrypted_len] = '\0';
    printf("Decrypted message: %s\n", decrypted);

    RSA_free(rsa);
    return 0;
}

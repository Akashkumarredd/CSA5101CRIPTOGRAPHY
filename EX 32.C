#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

DSA_SIG *generate_dsa_signature(const unsigned char *msg, int msg_len, DSA *dsa_key) {
    DSA_SIG *sig = DSA_do_sign(msg, msg_len, dsa_key);
    if (sig == NULL) {
        fprintf(stderr, "Error generating DSA signature\n");
        return NULL;
    }
    return sig;
}
unsigned char *generate_rsa_signature(const unsigned char *msg, int msg_len, RSA *rsa_key, unsigned int *sig_len) {
    unsigned char *sig = (unsigned char *)malloc(RSA_size(rsa_key));
    if (sig == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }

    if (RSA_sign(NID_sha256, msg, msg_len, sig, sig_len, rsa_key) != 1) {
        fprintf(stderr, "Error generating RSA signature\n");
        free(sig);
        return NULL;
    }

    return sig;
}

int main() {
  
    const char *message = "Hello, DSA vs RSA!";
    unsigned char msg_hash[SHA256_DIGEST_LENGTH];

    DSA *dsa_key = DSA_generate_parameters(1024, NULL, 0, NULL, NULL, NULL, NULL);
    DSA_generate_key(dsa_key);

    RSA *rsa_key = RSA_generate_key(1024, RSA_F4, NULL, NULL);

    SHA256((unsigned char *)message, strlen(message), msg_hash);

    DSA_SIG *dsa_sig = generate_dsa_signature(msg_hash, sizeof(msg_hash), dsa_key);
    if (dsa_sig == NULL) {
        DSA_free(dsa_key);
        RSA_free(rsa_key);
        return 1;
    }

  
    unsigned int rsa_sig_len;
    unsigned char *rsa_sig = generate_rsa_signature(msg_hash, sizeof(msg_hash), rsa_key, &rsa_sig_len);
    if (rsa_sig == NULL) {
        DSA_free(dsa_key);
        DSA_SIG_free(dsa_sig);
        RSA_free(rsa_key);
        return 1;
    }


    printf("DSA Signature:\n");
    printf("  r: %s\n", BN_bn2hex(dsa_sig->r));
    printf("  s: %s\n", BN_bn2hex(dsa_sig->s));

    printf("\nRSA Signature:\n");
    for (unsigned int i = 0; i < rsa_sig_len; i++) {
        printf("%02x", rsa_sig[i]);
    }
    printf("\n");

   
    DSA_free(dsa_key);
    DSA_SIG_free(dsa_sig);
    RSA_free(rsa_key);
    free(rsa_sig);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>#define MAX_INPUT_LENGTH 100
void compute_md5(const char *input, unsigned char *md5_hash) {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, input, strlen(input));
    MD5_Final(md5_hash, &ctx);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    printf("Enter the input string: ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove the newline character from the input
    compute_md5(input, md5_hash);
    printf("MD5 Hash: ");
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", md5_hash[i]);
    }
    printf("\n");
    return 0;
}

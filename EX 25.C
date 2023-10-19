#include <stdio.h>

unsigned long long modExp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    unsigned long long n, e;
    int num_blocks;

    printf("Enter the public key (n, e): ");
    scanf("%llu %llu", &n, &e);

    printf("Enter the number of blocks: ");
    scanf("%d", &num_blocks);

    unsigned long long blocks[num_blocks];

    printf("Enter the ciphertext blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        scanf("%llu", &blocks[i]);
    }

    printf("Encrypted blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        unsigned long long encrypted_block = modExp(blocks[i], e, n);
        printf("%llu ", encrypted_block);
    }

    return 0;
}

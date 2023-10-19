#include <stdio.h>
#include <stdint.h>

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint8_t uint8;

static const int initial_permutation_table[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

static const uint8 sample_key[] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF};

uint64 initial_permutation(uint64 data) {
    uint64 result = 0;
    for (int i = 0; i < 64; i++) {
        result |= ((data >> (64 - initial_permutation_table[i])) & 1) << (63 - i);
    }
    return result;
}

void generate_round_keys(uint8 key[], uint64 round_keys[]) {
    for (int i = 0; i < 16; i++) {
        round_keys[i] = 0;
        for (int j = 0; j < 8; j++) {
            round_keys[i] |= ((uint64)key[j] << ((7 - j) * 8));
        }
    }
}

uint64 des_encrypt(uint64 data, uint64 round_keys[]) {
    data = initial_permutation(data);
    
    for (int round = 0; round < 16; round++) {
    
        data ^= round_keys[round];
    }
  
    data = ((data & 0xFFFFFFFF) << 32) | ((data >> 32) & 0xFFFFFFFF);
  
    data = initial_permutation(data);
    
    return data;
}

int main() {
    uint64 data = 0x0123456789ABCDEF; 
    
    printf("Plaintext: %016llX\n", data);
    
    uint8 key[8];
    for (int i = 0; i < 8; i++) {
        key[i] = sample_key[i];
    }
    
    uint64 round_keys[16];
    generate_round_keys(key, round_keys);
    
    uint64 ciphertext = des_encrypt(data, round_keys);
    
    printf("Ciphertext: %016llX\n", ciphertext);
    
    return 0;
}

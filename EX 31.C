#include <stdio.h>

void applyBlockCipher(unsigned char *block, int blockSize) {
 
    printf("Block Cipher Output: ");
    for (int i = 0; i < blockSize / 8; i++) {
        printf("%02X ", block[i]);
    }
    printf("\n");
}

void leftShiftOneBit(unsigned char *block, int blockSize) {
    int carry = 0;
    for (int i = blockSize / 8 - 1; i >= 0; i--) {
        int newCarry = block[i] & 0x80 ? 1 : 0;
        block[i] = (block[i] << 1) | carry;
        carry = newCarry;
    }
}

void conditionalXOR(unsigned char *block, int blockSize) {
    if (blockSize == 64) {
        unsigned char constant[8] = {0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B};
        for (int i = 0; i < blockSize / 8; i++) {
            block[i] ^= constant[i];
        }
    } else if (blockSize == 128) {
        unsigned char constant[16] = {0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87,
                                     0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87};
        for (int i = 0; i < blockSize / 8; i++) {
            block[i] ^= constant[i];
        }
    }
}

int main() {
    int blockSize64 = 64;
    int blockSize128 = 128;

    unsigned char subkey64[blockSize64 / 8] = {0};
    applyBlockCipher(subkey64, blockSize64);
    leftShiftOneBit(subkey64, blockSize64);
    conditionalXOR(subkey64, blockSize64);
    printf("Subkey 1 (64-bit): ");
    for (int i = 0; i < blockSize64 / 8; i++) {
        printf("%02X ", subkey64[i]);
    }
    printf("\n");

    unsigned char subkey128[blockSize128 / 8] = {0};
    applyBlockCipher(subkey128, blockSize128);
    leftShiftOneBit(subkey128, blockSize128);
    conditionalXOR(subkey128, blockSize128);
    printf("Subkey 1 (128-bit): ");
    for (int i = 0; i < blockSize128 / 8; i++) {
        printf("%02X ", subkey128[i]);
    }
    printf("\n");

    leftShiftOneBit(subkey64, blockSize64);
    conditionalXOR(subkey64, blockSize64);
    printf("Subkey 2 (64-bit): ");
    for (int i = 0; i < blockSize64 / 8; i++) {
        printf("%02X ", subkey64[i]);
    }
    printf("\n");

    leftShiftOneBit(subkey128, blockSize128);
    conditionalXOR(subkey128, blockSize128);
    printf("Subkey 2 (128-bit): ");
    for (int i = 0; i < blockSize128 / 8; i++) {
        printf("%02X ", subkey128[i]);
    }
    printf("\n");

    return 0;
}

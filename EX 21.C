#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

void printHex(const unsigned char* buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02x", buffer[i]);
    }
    printf("\n");
}

void des_ecb_encrypt_with_padding(const unsigned char* key, const unsigned char* plaintext, size_t plaintext_len) {
    DES_cblock des_key;
    DES_key_schedule schedule;
    DES_string_to_key(key, &des_key);
    DES_set_key_checked(&des_key, &schedule);

    const size_t block_size = DES_BLOCK_SIZE;
    unsigned char padded_plaintext[block_size];

    size_t padded_len = plaintext_len + (block_size - (plaintext_len % block_size));
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, 0x80, padded_len - plaintext_len);

    printf("ECB Encrypted: ");
    for (size_t i = 0; i < padded_len; i += block_size) {
        DES_ecb_encrypt((DES_cblock*)(padded_plaintext + i), (DES_cblock*)(padded_plaintext + i), &schedule, DES_ENCRYPT);
        printHex(padded_plaintext + i, block_size);
    }
}

void des_cbc_encrypt_with_padding(const unsigned char* key, const unsigned char* iv, const unsigned char* plaintext, size_t plaintext_len) {
    DES_cblock des_key, des_iv;
    DES_key_schedule schedule;
    DES_string_to_key(key, &des_key);
    DES_set_key_checked(&des_key, &schedule);
    memcpy(&des_iv, iv, sizeof(DES_cblock));

    const size_t block_size = DES_BLOCK_SIZE;
    unsigned char padded_plaintext[block_size];

    size_t padded_len = plaintext_len + (block_size - (plaintext_len % block_size));
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, 0x80, padded_len - plaintext_len);

    printf("CBC Encrypted: ");
    DES_cbc_encrypt(padded_plaintext, padded_plaintext, padded_len, &schedule, &des_iv, DES_ENCRYPT);
    printHex(padded_plaintext, padded_len);
}

void des_cfb_encrypt_with_padding(const unsigned char* key, const unsigned char* iv, const unsigned char* plaintext, size_t plaintext_len) {
    DES_cblock des_key, des_iv;
    DES_key_schedule schedule;
    DES_string_to_key(key, &des_key);
    DES_set_key_checked(&des_key, &schedule);
    memcpy(&des_iv, iv, sizeof(DES_cblock));

    const size_t segment_size = 8; // 64 bits for CFB-64
    unsigned char padded_plaintext[segment_size];

    size_t padded_len = plaintext_len + (segment_size - (plaintext_len % segment_size));
    memcpy(padded_plaintext, plaintext, plaintext_len);
    memset(padded_plaintext + plaintext_len, 0x80, padded_len - plaintext_len);

    printf("CFB Encrypted: ");
    for (size_t i = 0; i < padded_len; i += segment_size) {
        DES_cfb_encrypt(padded_plaintext + i, padded_plaintext + i, segment_size, &schedule, &des_iv, DES_ENCRYPT);
        printHex(padded_plaintext + i, segment_size);
    }
}

int main() {
  
    const unsigned char key[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    const unsigned char iv[8] = {0x8F, 0x1E, 0x8C, 0x06, 0xE7, 0x9F, 0x29, 0xA6};
 const unsigned char plaintext[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64};

    printf("Original Plaintext: ");
    printHex(plaintext, sizeof(plaintext));

    des_ecb_encrypt_with_padding(key, plaintext, sizeof(plaintext));
    des_cbc_encrypt_with_padding(key, iv, plaintext, sizeof(plaintext));
    des_cfb_encrypt_with_padding(key, iv, plaintext, sizeof(plaintext));

    return 0;
}

#include <stdio.h>

unsigned char s_des_encrypt(unsigned char plaintext, unsigned char key);
unsigned char s_des_decrypt(unsigned char ciphertext, unsigned char key);

void cbc_encrypt(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key, const unsigned char* iv, int length);
void cbc_decrypt(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key, const unsigned char* iv, int length);

const unsigned char s_des_key = 0x3D; 

const unsigned char iv = 0xAA; 

int main() {
    unsigned char plaintext[] = { 0x01, 0x23 }; 
    unsigned char ciphertext[sizeof(plaintext)];

    printf("CBC Encryption Test\n");
    cbc_encrypt(plaintext, ciphertext, &s_des_key, &iv, sizeof(plaintext));
    printf("Ciphertext: ");
    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%x ", ciphertext[i]);
    }
    printf("\n");

    unsigned char decrypted[sizeof(plaintext)];
    printf("\nCBC Decryption Test\n");
    cbc_decrypt(ciphertext, decrypted, &s_des_key, &iv, sizeof(ciphertext));
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < sizeof(decrypted); i++) {
        printf("%x ", decrypted[i]);
    }
    printf("\n");

    return 0;
}

unsigned char s_des_encrypt(unsigned char plaintext, unsigned char key) {
    
}

unsigned char s_des_decrypt(unsigned char ciphertext, unsigned char key) {
  
}
void cbc_encrypt(const unsigned char* plaintext, unsigned char* ciphertext, const unsigned char* key, const unsigned char* iv, int length) {
    unsigned char previous_ciphertext = *iv; 

    for (int i = 0; i < length; i++) {
      
        unsigned char block = plaintext[i] ^ previous_ciphertext;


        unsigned char encrypted_block = s_des_encrypt(block, *key);

       
        previous_ciphertext = encrypted_block;

    
        ciphertext[i] = encrypted_block;
    }
}

void cbc_decrypt(const unsigned char* ciphertext, unsigned char* plaintext, const unsigned char* key, const unsigned char* iv, int length) {
    unsigned char previous_ciphertext = *iv; 
    for (int i = 0; i < length; i++) {
        
        unsigned char decrypted_block = s_des_decrypt(ciphertext[i], *key);

        plaintext[i] = decrypted_block ^ previous_ciphertext;

        previous_ciphertext = ciphertext[i];
    }
}

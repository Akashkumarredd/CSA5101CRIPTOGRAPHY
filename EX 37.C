#include <stdio.h>
#include <string.h>
#include <ctype.h>

// English letter frequencies in order: 'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'
const char english_letter_frequencies[26] = {'e', 't', 'a', 'o', 'i', 'n', 's', 'h', 'r', 'd', 'l', 'c', 'u', 'm', 'w', 'f', 'g', 'y', 'p', 'b', 'v', 'k', 'j', 'x', 'q', 'z'};

void to_lower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void decrypt(char* ciphertext, char* key, char* plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            int index = tolower(c) - 'a';
            plaintext[i] = isupper(c) ? toupper(key[index]) : key[index];
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

double get_frequency_score(char* text) {
    int letter_count[26] = {0};
    int total_letters = 0;
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            letter_count[index]++;
            total_letters++;
        }
    }
    
    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        double expected_freq = (double)english_letter_frequencies[i] / 100.0;
        double actual_freq = (double)letter_count[i] / (double)total_letters;
        score += (expected_freq - actual_freq) * (expected_freq - actual_freq);
    }
    
    return score;
}

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void sort_possible_plaintexts(char** plaintexts, int num_plaintexts) {
    for (int i = 0; i < num_plaintexts - 1; i++) {
        for (int j = i + 1; j < num_plaintexts; j++) {
            if (get_frequency_score(plaintexts[i]) > get_frequency_score(plaintexts[j])) {
                swap(&plaintexts[i], &plaintexts[j]);
            }
        }
    }
}

int main() {
    char ciphertext[1000];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    to_lower(ciphertext);
    
    int key_length = 26;
    char key[27] = "abcdefghijklmnopqrstuvwxyz";
    
    char plaintext[1000];
    char* possible_plaintexts[10];
    
    for (int i = 0; i < 10; i++) {
        possible_plaintexts[i] = (char*)malloc(sizeof(char) * (strlen(ciphertext) + 1));
    }
    
    sort_possible_plaintexts(possible_plaintexts, 10);
    
    printf("\nTop 10 possible plaintexts in rough order of likelihood:\n");
    for (int i = 0; i < 10; i++) {
        decrypt(ciphertext, key, possible_plaintexts[i]);
        printf("%d. %s\n", i + 1, possible_plaintexts[i]);
    }
    
    for (int i = 0; i < 10; i++) {
        free(possible_plaintexts[i]);
    }
    
    return 0;
}

#include <stdio.h>
#include <string.h>
void encrypt(char *plaintext, int key) 
{
    int length = strlen(plaintext);
    int rows = (length + key - 1) / key;
    char matrix[rows][key];
    int k = 0;
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < key; j++) 
		{
            if (k < length)
                matrix[i][j] = plaintext[k++];
            else
                matrix[i][j] = 'X'; 
        }
    }
    printf("Encrypted ciphertext: ");
    for (int j = 0; j < key; j++) 
	{
        for (int i = 0; i < rows; i++) 
		{
            printf("%c", matrix[i][j]);
        }
    }
    printf("\n");
}
int main() 
{
    char plaintext[100];
    int key;
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key (number of columns): ");
    scanf("%d", &key);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    encrypt(plaintext, key);
    return 0;
}

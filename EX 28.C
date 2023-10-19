#include <stdio.h>
#include <math.h>

int power_mod(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        
        exp = exp / 2;
        base = (base * base) % mod;
    }
    
    return result;
}

int main() {
    int q, a, xa, xb;
    
    printf("Enter the value of q (a prime number): ");
    scanf("%d", &q);
    
    printf("Enter the value of a (a primitive root of q): ");
    scanf("%d", &a);
    
    printf("Alice, enter your secret number xa: ");
    scanf("%d", &xa);
    
    printf("Bob, enter your secret number xb: ");
    scanf("%d", &xb);
    
    int ya = power_mod(a, xa, q);
    int yb = power_mod(a, xb, q);
    
    int ka = power_mod(yb, xa, q);
    int kb = power_mod(ya, xb, q);
    
    printf("Shared key for Alice: %d\n", ka);
    printf("Shared key for Bob: %d\n", kb);
    
    return 0;
}

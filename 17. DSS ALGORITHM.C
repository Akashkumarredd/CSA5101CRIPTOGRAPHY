#include <stdio.h>
void suggestTransportation(float distance) {
    if (distance < 0) {
        printf("Invalid distance. Please enter a non-negative value.\n");
    } else if (distance <= 1) {
        printf("You can walk to your destination.\n");
    } else if (distance <= 5) {
        printf("You can use a bicycle or take public transportation.\n");
    } else if (distance <= 50) {
        printf("You can take a car.\n");
    } else {
        printf("Consider taking a flight for long distances.\n");
    }
}

int main() {
    float distance;
    printf("Enter the distance to travel (in kilometers): ");
    scanf("%f", &distance);
    suggestTransportation(distance);

    return 0;
}

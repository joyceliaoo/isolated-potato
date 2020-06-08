#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Problem:
 * Given a list of numbers and a number k, return whether any two numbers 
 * from the list add up to k.
 * For example, given [10, 15, 3, 7] and k of 17, return true 
 * since 10 + 7 is 17.

 * Bonus: Can you do this in one pass?
 */

int main() {
    printf("Enter your numbers each separated by a space: ");

    // read in list of numbers
    char* buffer = NULL;
    size_t size = 0;
    size_t str_len = 0;
    char c;
    
    // resize dynamically
    while ( c != '\n') {
        c = fgetc(stdin);
        size = size*2 + 1;
        buffer = realloc(buffer, size);
        buffer[str_len++] = c;
    } 
    buffer[str_len-1] = '\0';

    printf("Enter target number k: ");
    char target[256];
    fgets(target, 256, stdin);
    int sum = atoi(target); 

    printf("You entered: [%s]\n", buffer);

    // convert input to int array
    char* num;
    int* nums = malloc(str_len*sizeof(int));
    int n = 0;
    num = strtok(buffer, " ");
    while (num != NULL) {
        nums[n++] = atoi(num);
        num = strtok(NULL, " ");
    } 
    
    // search
    char found = 0;
    for (int i = 0; i < n; i++) {
        int curr = nums[i];
        for (int j = i+1; j < n; j++) {
            if (curr + nums[j] == sum) {
                found = 1;
                printf("Found! %d + %d = %d\n", curr, nums[j], sum);
            }
        }
    }

    if (!found) printf("No pairs found! \n");

    free(buffer);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Problem:
 * Given an array of integers, return a new array such that each element 
 * at index i of the new array is the product of all the numbers in the 
 * original array except the one at i.

 * For example, if our input was [1, 2, 3, 4, 5], the expected output 
 * would be [120, 60, 40, 30, 24]. 
 * If our input was [3, 2, 1], the expected output would be [2, 3, 6].
 *
 * Follow-up: what if you can't use division?
 */

int* withDivision (int* input, size_t num_ele);
int* withoutDivision (int* input, size_t num_ele);

int main() {
    printf("Enter numbers each separated by a comma and a space:\n");

    char* buffer = NULL;
    size_t size = 0;
    size_t str_len = 0;
    char c;

    while (c != '\n') {
       // if more space is needed to store input
       if (size <= str_len) {
          size = size*2 + 1;
          buffer = realloc(buffer, size);
       }
       c = fgetc(stdin);
       buffer[str_len++] = c;
    }

    printf("You entered: %s", buffer);
    int nums[str_len]; 
    size_t ele = 0;
    char* num = strtok(buffer, ", ");
    int valid_num;
    while (num != NULL) {
        // if input element is a number
        if (sscanf(num, "%d", &valid_num)) {
            nums[ele++] = atoi(num);
        }
        else {
            perror("Please enter valid integers only");
            exit(1);
        }
        num = strtok(NULL, ", ");
    }

    int* ans1 = withDivision(nums, ele);
    int* ans2 = withoutDivision(nums, ele);

    printf("withDivision: \n");
    for (int i = 0; i < ele; i++) {
       printf("%d ", ans1[i]);
    } 
    printf("\n");

    printf("withoutDivision: \n");
    for (int i = 0; i < ele; i++) {
       printf("%d ", ans2[i]);
    } 
    printf("\n");

    free(buffer);
    free(ans1);
    free(ans2);

    return 0;
}

int* withDivision (int* input, size_t num_ele) {
    // find product of every number in input
    int product = 1;
    for (int i = 0; i < num_ele; i++) {
        product *= input[i];
    }
    int* res = malloc(num_ele*sizeof(int));
    // divide overall product by element at each index
    for (int i = 0; i < num_ele; i++) {
        res[i] = product / input[i];
    }

    return res;
}

int* withoutDivision (int* input, size_t num_ele) {
    // product of all integers we've passed
    int running_product = 1;
    // product of all integers after current integer
    int product_of_rest;
    int* res = malloc(num_ele*sizeof(int));
    for (int i = 0; i < num_ele; i++) {
        product_of_rest = 1;
        for (int j = i+1; j < num_ele; j++) {
            product_of_rest *= input[j];
        }
        // product of all integers before & after current index
        res[i] = running_product * product_of_rest;
        running_product *= input[i];
    }

    return res;
}




#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* problem:
 * Given an array of integers, find the first missing positive integer 
 * in linear time and constant space. In other words, find the lowest 
 * positive integer that does not exist in the array. The array can 
 * contain duplicates and negative numbers as well.
 *
 * For example, the input [3, 4, -1, 1] should give 2. 
 * The input [1, 2, 0] should give 3.
 *
 * You can modify the input array in-place.
 */

// find max element of array
int max(int* arr, size_t n) {
    if (n < 1) {
        printf("array is empty");
        exit(1);
    } else if (n == 1) {
        return arr[0];
    } else {
        int res = arr[0];
        for (int i = 1; i < n; i++) {
            if (arr[i] > res) {
                res = arr[i];
            }
        }
        return res;
    }
}

int find_Missing(int* arr, size_t n) {
    int largest = max(arr, n);
    if (largest <= 0) return 1;
    int max_possible;
    if (largest <= n) {
        // best case all positive integers less than max appear
        max_possible = largest+1;
    } else {
        // best case all n elements are distinct and consecutive
        max_possible = n+1;
    }
    char* table = calloc(max_possible, 1);
    // mark all numbers that are present
    for (size_t i = 0; i < n; i++) {
        // only record positive integers in range
        if (arr[i] > 0 && arr[i] < max_possible) {
            table[arr[i]] = 1;
        }
    }

    for (size_t i = 1; i < max_possible; i++) {
        if (!table[i]) return i;
    }

    return max_possible;
}

// =============================================
// correct solution
int find_Missing_better(int* arr, size_t n) {
    size_t nonpos = 0;
    // move all nonpositive integers to front of array
    for (size_t i = 0; i < n; i++) {
        if (arr[i] <= 0) {
            int temp = arr[nonpos];
            arr[nonpos++] = arr[i];
            arr[i] = temp;
        }
    }

    // negate all negative integers for use as markers
    for (size_t i = 0; i < nonpos; i++) {
        arr[i] = -arr[i];
    }

    // mark all positive integers by index
    int curr;
    for (; nonpos < n; nonpos++) {
        // if index has been marked by an earlier number
        if (arr[nonpos] < 0) {
            curr = -arr[nonpos];
        } else {
            curr = arr[nonpos];
        }
        // max possible missing num is n+1
        if (curr <= n) {
            // change corresponding index to negative
            if (arr[curr-1] > 0) {
               arr[curr-1] = -arr[curr-1];
            }
        } 
    }

    // look for first unmarked number
    for (size_t i = 0; i < n; i++) {
        if (arr[i] > 0) return i+1;
    }
    // all numbers from 1-n are present
    return n+1;
}

// takes in a string of space-separated numbers and return 
// corresponding array
int* string_to_int_array(char* input, size_t input_len, size_t* num_ele) {
    int valid_int;
    int* res = malloc(input_len*sizeof(int));
    *num_ele = 0;
    char* curr = strtok(input, " ");
    while (curr != NULL) {
        if (sscanf(curr, "%d", &valid_int)) {
            res[(*num_ele)++] = valid_int;
        } else {
            printf("Invalid integer %s\n", curr);
            exit(1);
        }
        curr = strtok(NULL, " ");
    }
    return res;
}

char* read_input(char* buffer, size_t capacity, size_t* input_len) {
    char c = fgetc(stdin);
    while( c != '\n') {
        if (capacity <= *input_len+1) {
            capacity = capacity*2 + 1;
            buffer = realloc(buffer, capacity); 
        }

        if (buffer == NULL) {
            printf("Not enough memory\n");
            exit(1);
        }
        buffer[(*input_len)++] = c;
        c = fgetc(stdin);

    }
    buffer[*input_len] = '\0';
    return buffer;
}


int main() {

    printf("Enter numbers each separated by a space:\n");

    size_t input_len = 0;
    
    char* input = read_input(NULL, 0, &input_len);
    
    size_t num_ele;
 
    int* arr = string_to_int_array(input, input_len, &num_ele);

    printf("You entered: ");
    for (size_t i = 0; i < num_ele; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("It has %lu elements\n", num_ele);

    int ans = find_Missing_better(arr, num_ele);

    printf("Smallest missing positive integer is %d \n", ans);

    free(input);
    free(arr);

    return 0;
}

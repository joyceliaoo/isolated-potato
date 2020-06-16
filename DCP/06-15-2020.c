#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* Problem:
 * Given a list of integers, write a function that returns the largest 
 * sum of non-adjacent numbers. Numbers can be 0 or negative.
 *
 * For example, [2, 4, 6, 2, 5] should return 13, since we pick 
 * 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.
 *
 * Follow-up: Can you do this in O(N) time and constant space?
 */

int non_adjacent_sum(int* arr, size_t len) {
    int sum_with_prev = arr[0];
    int sum_without_prev = 0;

    for (int i = 1 ; i < len; i++) {
        int temp = sum_without_prev;
        sum_without_prev = (int)
            (fmax( (double) sum_with_prev, (double) sum_without_prev)); 
        sum_with_prev = temp + arr[i];
    }

    return (int)(fmax((double)sum_with_prev, (double) sum_without_prev));
}

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
   
   size_t str_len = 0;
   char* buffer = read_input(NULL, 0, &str_len);
   size_t num_ele;
   int* input = string_to_int_array(buffer, str_len, &num_ele);
   
   printf("you entered: ");
   for (size_t i = 0; i < num_ele; i++) {
       printf("%d ", input[i]);
   }
   printf("\n");

   printf("Max non-adjacent sum: %d\n", non_adjacent_sum(input, num_ele));

   free(buffer);
   free(input);

   return 0;
}

    




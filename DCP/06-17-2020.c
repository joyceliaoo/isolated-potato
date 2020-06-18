#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Problem:
 * Implement an autocomplete system. That is, given a query string s 
 * and a set of all possible query strings, return all strings in the
 * set that have s as a prefix.
 *
 * For example, given the query string de and the set of 
 * strings [dog, deer, deal], return [deer, deal].
 *
 * Hint: Try preprocessing the dictionary into a more efficient
 * data structure to speed up queries.
 */

struct node {
    struct node** children;
    size_t num_children;
    char is_end;
    char letter;
};

struct node* new_node() {
    struct node* new = malloc(sizeof(struct node));
    new->num_children = 0;
    new->children = malloc(26 * sizeof(struct node));
    new->is_end = 0;
    return new;
}

void free_tree(struct node* root) {
    if (root == NULL) return;
    for (size_t i = 0; i < root->num_children; i++) {
        free_tree(root->children[i]);
    }
    free(root->children);
    free(root);
}

void insert_string(struct node* root, char* string) {
    if (*string == '\0') {
        if (!root->is_end) root->is_end = 1;
        return;
    } else {
        for (size_t i = 0; i < root->num_children; i++) {
            if (root->children[i]->letter == *string) {
                insert_string(root->children[i], ++string);
                return;
            }
        }
        struct node* new = new_node();
        root->children[(root->num_children)++] = new;
        new->letter = *string;
        insert_string(new, ++string);
    }
}

struct node* search(struct node* root, char* prefix) {
    if (*prefix == '\0') return root;
    for (size_t i = 0; i < root->num_children; i++) {
        if (root->children[i]->letter == *prefix) {
            return search(root->children[i], ++prefix);
        }
    }
    return NULL;
}

void get_words(struct node* root, char* prefix, char* buffer) {
    if (root == NULL) return;
    if (root->is_end) {
        strcat(buffer, prefix);
        strcat(buffer, &(root->letter));
        strcat(buffer, "\n");
    }
    for (size_t i = 0; i < root->num_children; i++) {
        char* temp = malloc(256);
        strcpy(temp, prefix);
        strcat(temp, &(root->letter));
        get_words(root->children[i], temp, buffer);
        free(temp);
    }
}

void get_queries(struct node* root, char* prefix) {
    struct node* target = search(root, prefix);
    if (target == NULL) {
        printf("No queries found for %s \n", prefix);
        return;
    }
    char* res = calloc(1024, sizeof(char));
    for (size_t i = 0; i < target->num_children; i++) {
        get_words(target->children[i], prefix, res);
    }
    printf("All words with prefix %s: \n%s", prefix, res);
    free(res);
}

int main() {

    struct node* root = new_node();
    insert_string(root, "dog");
    insert_string(root, "deer");
    insert_string(root, "deal");
    insert_string(root, "decorate");
    insert_string(root, "donuts");
    insert_string(root, "hello");
    insert_string(root, "hesitate");
    insert_string(root, "egg");
    insert_string(root, "dumplings");
    insert_string(root, "hot dog");

    get_queries(root, "de");
    get_queries(root, "he");
    get_queries(root, "hop");
    get_queries(root, "a");

    free_tree(root);

    return 0;
}




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* problem:
 * Given the root to a binary tree, implement serialize(root), 
 * which serializes the tree into a string, and deserialize(s),
 * which deserializes the string back into the tree.
 */

#define MAX_CHAR 256

struct node {
    char* data;
    struct node* left;
    struct node* right;
};

// preorder traversal of given tree, NULL nodes are denoted as N
char* serialize(struct node* root) {
    
    if (root == NULL) {
        char* res = malloc(2);
        strcpy(res, "N");
        return res;
    }
    char* res = malloc(MAX_CHAR);
    if (strlen(root->data) > MAX_CHAR-2) {
        perror("Max char limit exceeded");
        exit(1);
    }
    else{
        strncpy(res, root->data, MAX_CHAR);
        strcat(res, "|");
    }

    char* left = serialize(root->left);
    char* right = serialize(root->right);

    if (strlen(left)+2 + strlen(res) > MAX_CHAR) {
        perror("Max char limit exceeded");
        exit(1);
    }
    else {
        strcat(res, left);
        strcat(res, "|");
    }
    if (strlen(right)+2 + strlen(res) > MAX_CHAR) {
        perror("Max char limit exceeded");
        exit(1);
    }
    else {
        strcat(res, right);
    }

    free(left);
    free(right);

    return res;
}

struct node* deserialize_helper(char* start) {
    if (start == NULL || (start[0] == 'N' && strlen(start) == 1)) {
        return NULL;
    } else {
        struct node* new = malloc(sizeof(struct node));
        new->data = start;
        char* next = strtok(NULL, "|"); 
        new->left = deserialize_helper(next);
        next = strtok(NULL, "|");
        new->right = deserialize_helper(next);
        return new;
    }
}

struct node* deserialize(char* rep) {
    char* root = strtok(rep, "|");
    return deserialize_helper(root);
}

void free_tree(struct node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {

    struct node* leftleftB = malloc(sizeof(struct node));
    leftleftB->data = "left.left";
    leftleftB->left = NULL;
    leftleftB->right = NULL;

    struct node* leftB = malloc(sizeof(struct node));
    leftB->data = "left";
    leftB->left = leftleftB;
    leftB->right = NULL;

    struct node* rightB = malloc(sizeof(struct node));
    rightB->data = "right";
    rightB->left = NULL;
    rightB->right = NULL;

    struct node* root = malloc(sizeof(struct node));
    root->data = "root";
    root->left = leftB;
    root->right = rightB;

    char* preO = serialize(root);
    printf("Serialized string: %s\n", preO);
    struct node* res = deserialize(preO);
    printf("root:%s, left:%s, left.left:%s, right:%s\n", res->data, 
            res->left->data, res->left->left->data, res->right->data);

    free_tree(root);
    free_tree(res); 
    free(preO);

    return 0;
}


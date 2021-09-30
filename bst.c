#include "bst.h"


struct BSTWord* bstWord(char* word, int count, struct BSTWord* left, struct BSTWord* right) {
        struct BSTWord* node = (struct BSTWord*) malloc(sizeof(struct BSTWord ));
        for(int i = 0; i < 100; ++i) {
            if(word[i] == '\0') {
                break;
            }
            node->word[i] = word[i];
        }

        node->count = count;
        node->left = left;
        node->right = right;
        return node;
}

int getIndex(char* word) {
    return word[0] - 97;
}

struct BSTWord* addWord(struct BSTWord* root, struct BSTWord* node) {
    if(root == NULL) {
        return node;
    }

    if(strcmp(node->word, root->word) < 0) {
        root->left = addWord(root->left, node);
        return root;
    }
    else if(strcmp(node->word, root->word) > 0) {
        root->right = addWord(root->right, node);
        return root;
    }
     else {
         root->count = root->count + 1;
         return root;
     }
}

void findLongWord(struct BSTWord* root, int *max) {
     if(root != NULL) {
        findLongWord(root->left, max);
        if(strlen(root->word) > *max) {
            *max = strlen(root->word);
        }
        findLongWord(root->right, max);
    }
}

void findMostwords(struct BSTWord* root, int *max) {
    if(root != NULL) {
        findLongWord(root->left, max);
        if(root->count > *max) {
            *max = root->count;
        }
        findLongWord(root->right, max);
    }
}


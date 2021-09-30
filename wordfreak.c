#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "bst.h"
#include <ctype.h>
#include <errno.h>


/* Recursive function that writes words and its count into the output file
 * Parameters : root - a pointer to a node of type struct BSTWord*
 *              maxLength - length of the longest word read from the input file/s
 *              maxWords - number of digits of the count of the word that occurs the most.
 *              fd = file descriptor of the output file. 
 */

void writeWords(struct BSTWord* root, int maxLength, int maxWords, int fd) {
    if(root != NULL) {
        char s1[500];
        char s2[500];
        int bytes = 0;
        writeWords(root->left, maxLength, maxWords, fd);
        sprintf(s1,"%*.*s :",-maxLength,20, root->word);
        sprintf(s2," %*i\n",maxWords,root->count);
        strcat(s1,s2);
        bytes = write(fd,s1,strlen(s1));
        if(bytes == -1) {
            perror("Error while writing, ");
        }
        writeWords(root->right, maxLength, maxWords, fd);
    }
}
/*  Frees every node in the BST using recursion.
 *  Parameter : root - a pointer to a node of type struct BSTWord*
 */

void freeBST(struct BSTWord* root) {
    if(root == NULL) {
        return;
    }
    freeBST(root->left);
    freeBST(root->right);
    free(root);
    return;
}

int main(int argc, char* argv[]) {

    struct BSTWord* array[26]; //Hashtable

    for(int i = 0; i < 26; ++i) {
        array[i] = NULL;
    }    

    char text[1024];
    int fd[argc+1];    // Array of file descriptors
    int numBytes = 0;;
    char word[1000];
    int numFiles = 1;  // counts the number of files required to open
    int maxLength = 1;
    int maxWords = 1;
    int temp1 = 1;
    int temp2 = 1;

    struct BSTWord* node = (struct BSTWord*) malloc(sizeof(struct BSTWord));

    for(int i = 0; i < argc + 1; ++i) {
        fd[i] = -13;
    }

    fd[0] = 0; // To read from Standard Input
    char* env; // variable to store the name of the file from the environment variable WORD_FREAK
    env = getenv("WORD_FREAK");

    if(env != NULL) {
        fd[numFiles] = open(env, O_RDONLY);
        if(fd[numFiles] == -1) {
            char error[100];
            sprintf(error, "Could not open file %s, value of errno: %d\n", env, errno);
            write(2, error, strlen(error)); 
            fd[numFiles] = -13;
        }
            ++numFiles;

    }
    for(int i = 0; i < argc - 1; ++i) {
        fd[numFiles] = open(argv[i+1], O_RDONLY);
        if(fd[numFiles] == -1) {
            char error[100];
            sprintf(error, "Could not open file %s, value of errno: %d\n", argv[i+1], errno);
            write(2, error, strlen(error));
            fd[numFiles] = -13;
            continue;
        }
        ++numFiles;
    }

    for(int i = 0; i < numFiles; ++i) {
        char buffer[1];
        if(fd[i] == -13) {
            continue;
        }
        numBytes = read(fd[i], buffer, 1);
        if(numBytes == -1) {
            char error[100];
            sprintf(error, "Could not read, value of errno: %d\n", errno);
            write(2, error, strlen(error)); 
            exit(2);
        }
        int j = 0;
        while(numBytes > 0) {
            if(!isalpha(buffer[0])) {
                word[j] = '\0';
                if(strlen(word) != 0) {
                    int key = getIndex(word);
                    node = bstWord(word, 1, NULL, NULL);
                    if(array[key] == NULL) {
                        array[key] = addWord(array[key], node);
                    }
                    else {
                        addWord(array[key], node);
                    }
                }
                for(int m = 0; m <= j; ++m) {
                    word[m] = '\0'; //clears the word array
                }
                j = 0;
            }
            else {
                word[j++] = tolower(buffer[0]);
            }
            numBytes = read(fd[i], buffer, 1);
        }
    }
    
    for(int i = 0; i < 26; ++i) {
        findLongWord(array[i], &temp1);
        if(temp1 > maxLength) {
            maxLength = temp1;
        }
        findMostwords(array[i], &temp2);
        if(temp2 > maxWords) {
            maxWords = temp2;
        }
    }
    int digCounter = 0; // Counts the number of digits in the largest number
    while(maxWords > 0) {
        digCounter++;
        maxWords /= 10;
    }

    int wrFd = open("output.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if(wrFd == -1) {
        char error[100];
        sprintf(error, "Could not open file %s, value of errno: %d\n", "output.txt", errno);
        write(2, error, strlen(error)); 
        exit(2);
    }

    for(int i = 0; i < 26; ++i) {
        writeWords(array[i], maxLength, digCounter, wrFd);
    }

    fd[numFiles++] = wrFd;

    for(int i = 1; i < numFiles; ++i) {
        close(fd[i]);
        if(fd[i] == -1) {
            char error[50];
            sprintf(error, "Could not close the file, value of errno: %d\n", errno);
            write(2, error, strlen(error));
        }
    }

    for(int i = 0; i < 26; ++i) {
        freeBST(array[i]);
    } 
    return 0;
}
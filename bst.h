#include <string.h>


struct BSTWord {
    char word[100];
    int count;
    struct BSTWord* left;
    struct BSTWord* right;
};

/* Constructor for BSTWord* 
 * Paramters : word - word read from the file
 *             count - number of times the word occurs in the file
 *             left - pointer to left node in BST
 *             right = pointer to right node in BST
 * Return : pointer to a node of type struct BSTWord*
 */

struct BSTWord* bstWord(char* word, int count, struct BSTWord* left, struct BSTWord* right);

/* recursive function to add the word to the BST or increase the counter if the word is already in BST.
 *  Parameters : root - current node being accessed in BST
 *               node - The node to be added to BST
 *  Return : the node added to BST
 */

struct BSTWord* addWord(struct BSTWord* root, struct BSTWord* node);

/* Hash function to return the index of the desired letter
   Parameter : word - the word whose first letter to be used in the hash function
   Returns : the hash key index
*/

int getIndex(char* word);

/* finds the length of the longest word in the BST and stores it in max
 * Parameters : root - current node being accessed in BST
 *              max - an integer pointer that stores the address of the counter value of the longest length
 */

void findLongWord(struct BSTWord* root, int *max);

/* finds the count of the word the occurs the most in the BST and stores it in max
 * Parameters : root - current node being accessed in BST
 *              max - an integer pointer that stores the address of the counter value of the largest number
 */

void findMostwords(struct BSTWord* root, int *max);
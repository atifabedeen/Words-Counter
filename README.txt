wordfreak is a C program that takes in file/s from various input ways or reads the words from the terminal and writes into an output file showing the different words occuring in the file/s and it respective count.

Files that are piped in or if typed into the terminal are read from stdin(or 0) using read().
Files that are passed as arguments are looped through an array of file descriptors and are opened, read, and closed accordingly. File that is got from the environment variable is also added to this array of file descriptors (if valid and if it exists).

Words from files or STDIN are read 1 byte at a time. Although inefficient, it solves the problem of buffer cutting off words in the middle and overcomplicating code.

words are written into the output file using a recursive function writeWords() that traverses BSTs of every letter. formatting of the output is done with helper functions findLongWord() that finds the longest word read from the file/s and findMostwords() that finds the count of the word that occurs the most. These functions helps to find the appropriate number of spaces between the words, colon and count.

Binary Search Tress are used to store nodes of words of specific letters. Recursive function addWord()  traverses the BST to see if the word exists and update its counter or to add the node if the word isn't there.

A hashTable array type of struct BSTWord* of size 26 is created that stores a BST for every alphabet. getIndex() is a hash function and returns the index of the letter BST to which that word should be added. 

Error checking have been done when using open() and close() and the description of the error is written into STDERR.

All pointers of every BST has been freed using a recursive function freeBST(). 

Video Link:
https://youtu.be/-fx42VAK_fI
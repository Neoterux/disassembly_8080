#ifndef DISSASSEMBLY_H
#define DISSASSEMBLY_H
typedef char byte;

/**
 * Dissasembly a specific byte array, and append the result to the given string.
 *
 * @param byte[] The byte array to dissasembly
 * @param char* the string where the dissasembly would be pasted
 *
 * @return 1 if an error ocurried, 0 if not
 */
int dissasembly(byte[], char*);


#endif

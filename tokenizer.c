/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 
struct TokenizerT_ {
	FILE *file;

};
typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 */
 
TokenizerT *TKCreate( FILE *file ) {
  
  TokenizerT *tok = (TokenizerT * ) malloc (sizeof(TokenizerT));
  if (tok == NULL) {
	  return NULL;
  }
  tok->file = file;
  return tok; 
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 */

void TKDestroy(TokenizerT * tok) {
	free(tok);
}

/*TKGetNextToken returns the next token from the token stream as a character string*/

char *TKGetNextToken( TokenizerT * tk ) {
	
	/*STILL NEED TO MODIFY for this assignment */
	return 0;
}
	
	
	 
 

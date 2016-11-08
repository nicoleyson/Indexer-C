

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.c"
#include "sorted-list.h"

SortedListPtr masterTkList; //master list of token structs

/*token structs*/
typedef struct tokenData {    
	char* fileName; 
	int freq; 
} tokenData;

typedef struct token {
	char* string;
	SortedListPtr SLFiles;  //list files which contain the token 
}token;

/*comarator for tokenData structs*/
int comparefileName  (void*f1, void *f2) {
	struct tokenData *x1 = (struct tokenData *)f1;
	struct tokenData *x2 = (struct tokenData *)f2;
	
	char *y1 = (char*)x1->fileName;
	char *y2 = (char*)x2->fileName;
	
	return strcmp(y1,y2);
	
}

/*frees given token*/

void tkDestroy(void* tkPtr){
	token *tk = tkPtr;
	free(tk->string);
	free(tk->SLFiles);
	
	free(tk);
}

/* Adds token and fileName to mastertKlist.
 * Frequency increased if token already exists
 * */
void addToken (char* string, char* fileName) {
	
	token * iterToken;
	token *newTk = malloc(sizeof(token));        //token Struct to insert
	
	tokenData * iterData;
	tokenData * newTkData = malloc(sizeof(tokenData));  //tokenData Struct for new token
	
	if (newTkData == NULL || newTk == NULL){
		printf("malloc fail\n");   //need to write error to file and exit, rather than just printf
		return;
	}
	
	newTk->string = string;    //initialize newToken to insert into master sortedList
	newTk->SLFiles = NULL;
	newTkData->fileName= fileName; 
	newTkData->freq = 1;
	
	if ((iterToken = SLSearch(masterTkList, newTk, comparefileName)) != NULL) {    //check to see if the token exists in master tkList; if it does then do SLFile check
			if ((iterData = SLSearch(iterToken->SLFiles, newTkData, comparefileName)) != NULL) { //check if SLFiles has previously recorded an instance of this token
				int freqTmp; 
				freqTmp = iterData->freq;                               //if there is no instance in SLFiles, then need to create a record of the token
				newTkData->freq = freqTmp+1;
				SLInsert(iterToken->SLFiles, newTkData);
				SLRemove(iterToken->SLFiles, iterData);
			}else {
				SLInsert(iterToken->SLFiles, newTkData);                //the token does not exist in the master tkList but does in the SLFiles
			}
			
			tkDestroy(newTk);                                                      
	}else {                                                             //else: token does not yet exist in master tkList 
		//newTk->SLFiles = SLCreate(                                    //need to create tokenData compare and destroy functions to pass to SLCreate to initialize the SLFiles for the newTk we are inserting
		SLInsert(newTk->SLFiles, newTkData);                            //update SLFiles with new tokenData struct 
		SLInsert(masterTkList, newTk);                                  //insert token in master list
	}
	
}

/*Reads through file with tokenizer. Calls TKGetNextToken to get a token and calls addToken to add to masterTkList*/
void readInput(FILE * file, char * filename){
	   
}

/*output to file in JSON format*/
void outputFile() { 

}

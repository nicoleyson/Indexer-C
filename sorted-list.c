#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "sorted-list.h"






/*
  Creates a new node on the stack.
*/
WordNODE* createNode()
{
	WordNODE* newNODE;
	newNODE = malloc(sizeof(WordNODE));
	newNODE->WORDS = NULL;
	newNODE->prev = NULL;
	newNODE->next = NULL;
    
    //newNODE->FILES is of type FileNODE
	return newNODE;
}

/*
  Frees all WordNODE in the input list.
*/
void freeList( WordNODE* list )
{
	WordNODE* temp;
	while(list)
	{
		temp = list->next;
		free(list->WORDS);
		freeFile(list);
		free(list);
		list = temp;
	}
}

/*
  Frees all FileNODE objects of a given WordNODE.
*/
void freeFile(WordNODE* node)
{
	FileNODE* temp;
	while(node)
	{
      
        temp = node->FILES->next;
        if (temp != NULL) {
            free(node->FILES->fileName);
            //********
            //also seg faulting here when trying to access FILES->fileName
            //********
            free(node->FILES);
            node->FILES = temp;
        }
        return;
    
	}
}

/*
  Similar word counter.  It adds to the count value related to the fileName specified.
*/
int wordTallier(FileNODE* head, char* fileName)
{
	FileNODE* node;
	FileNODE* prevNODE;
	node = head;

	if(!fileName)
	{
		printf("Error: Empty file name in wordTallier.");
		return 0;
	}
	if(!head)
	{
		printf("Error: Empty list in wordTallier.");
		return 0;
	}

	if(!head->fileName)
	{ /* Empty - fill in with info provided/passed */
		head->fileName = malloc(strlen(fileName) + 1);
		strcpy(head->fileName, fileName);
		head->wordCounter = 1;
		head->next = NULL;
		return 1;
	}
    if (!node->fileName)  {
        while(node && strcmp(node->fileName,fileName) != 0)
            { /* Skip up to proper location of the node to count */
                prevNODE = node;
                node = node->next;
            }
    }

	/* Create a new node for insertion */
	FileNODE* temp;
	temp = malloc(sizeof(FileNODE));
	temp->wordCounter = 1;
	temp->fileName = malloc(strlen(fileName) + 1);
	strcpy(temp->fileName, fileName);
	temp->next = NULL;

	if(!node)
	{
		/* End-Of-List: Insert new node at the end */
		prevNODE->next = temp;
		temp->next = NULL;
		return 1;
	}

	if(strcmp(node->fileName,fileName) == 0)
	{
		/* Found node:  increment wordCounter */
		free(temp->fileName);
		free(temp);
		(node->wordCounter)++;
		return 1;
	}
	return 0;
}


/*
 	Inserts word (sorted)
	Inputs: head (WordNODE*): the list into which the word should be inserted.
			newWORD (char*): the word that was scanned in.
			fileName (char*): the fileName in which the word was found.
*/
int insertNode( WordNODE* head, char* newWORD, char* fileName )
{
	WordNODE* node;
	node = head;
	WordNODE* prevNODE;

	if(!fileName || !newWORD || !head)
	{
		printf("insertNode input ERROR!");
		return 0;
	}

	if(!head->WORDS)
	{	/* Empty - fill in with info provided/passed */
		head->WORDS = malloc(strlen(newWORD) + 1);
		strcpy(head->WORDS, newWORD);
		head->FILES = malloc(sizeof(FileNODE));
		head->FILES->wordCounter = 1;
		head->FILES->fileName = malloc(strlen(fileName) + 1);
		strcpy(head->FILES->fileName, fileName);
		

		return 1;
	}

	while(node && strcmp(node->WORDS,newWORD) < 0)
	{	/* Skip up to proper location of insertion */
		prevNODE = node;
		node = node->next;
	}

	/* Create a new node for insertion */
	WordNODE* temp;
    
	temp = malloc(sizeof(WordNODE));
	temp->WORDS = malloc(strlen(newWORD) + 1);
	temp->FILES = malloc(sizeof(FileNODE));
	temp->FILES->fileName = malloc(strlen(fileName) + 1);
	temp->FILES->wordCounter = 1;
    
    //temp->FILES->next->wordCounter = NULL;
    //this is where wordCounter may need to be initialized
    
	strcpy(temp->FILES->fileName, fileName);
	strcpy(temp->WORDS, newWORD);
    
	temp->next = NULL;

	if(!node)
	{	/* End-Of-List: Insert new node at the end */
		temp->prev = prevNODE;
		prevNODE->next = temp;
		temp->next = NULL;
		return 1;
	}

	if(strcmp(node->WORDS,newWORD) == 0)
	{	/* Found node:  Update it with necessary info */
		freeList(temp);
		if(!node->FILES)
		{
			node->FILES = malloc(sizeof(FileNODE));
			node->FILES->fileName = malloc(strlen(fileName)+1);
			node->FILES->wordCounter = 1;
			node->FILES->fileName = fileName;
			return 1;
		}
		wordTallier(node->FILES, fileName);
		return 1;
	}
	/*
	  	  If the searched node is NOT equal to list, that means that new word should be inserted
	  	  before all items in the list by switching head and temp, and insert head after temp.
	*/
	if(node != head)
	{
		prevNODE->next = temp;
		node->prev = temp;
		temp->next = node;
		temp->prev = prevNODE;
		return 1;
	}
	else
	{	/*
	  	  Insert new word before all items in the list by switching head and temp,
	  	  and insert head after temp.
	 	 */
		free(temp->WORDS);
		temp->WORDS = malloc(strlen(head->WORDS) + 1);
		strcpy(temp->WORDS, head->WORDS);
		free(temp->FILES->fileName);
		free(temp->FILES);
		temp->FILES = malloc(sizeof(FileNODE));
		temp->FILES = head->FILES;
        temp->FILES->wordCounter = 1;
		temp->next = head->next;
		head->next = temp;
		temp->prev = head;

		free(head->WORDS);
		head->WORDS = malloc(strlen(newWORD) + 1);
		strcpy(head->WORDS, newWORD);

		/* Initialize head */
		head->FILES = NULL;
		head->FILES = malloc(sizeof(FileNODE));
		head->FILES->fileName = malloc(strlen(fileName)+1);
		strcpy(head->FILES->fileName, fileName);
		head->FILES->wordCounter = 1;
		return 1;
	}
	return 0;
}

/*
  Output inverted sorted list to file provided in arg1
 */


	

void printList(WordNODE* list, char* fileName)
{
	FILE* sortedListFile;
	sortedListFile = fopen(fileName, "w+"); /* Overwrite existing output file */
	if(!sortedListFile)
	{
		printf("File NOT Found! %s.\n", fileName);
		exit(-1);
	}
	fprintf(sortedListFile, "{\"list\" : [\n");
	WordNODE* sortedLIST = list;
	while(sortedLIST)
	{
		fprintf(sortedListFile, "\t{\"%s\" : [\n", sortedLIST->WORDS);
        FileNODE* temp;
        temp = sortedLIST->FILES;
		while(temp)
		{
            if(temp->wordCounter) {  //just split to check where seg fault is occuring
                if ( temp->fileName != NULL) {
                    fprintf(sortedListFile, "\t\t{\"%s\" : %d}\n", temp->fileName, temp->wordCounter);
                    //*******
                    //seg fault when wordCounter is accessed, wordCounter =garbage value 
                    //*******
                    temp = temp->next;
                }
            }
		}
		fprintf(sortedListFile, "\t]}\n");
		sortedLIST = sortedLIST->next;
	}
	fprintf(sortedListFile, "]}");
	if(fclose(sortedListFile) != 0)
	{
		printf("Unable to close file %s.\n", fileName);
		exit(-1);
	}
}

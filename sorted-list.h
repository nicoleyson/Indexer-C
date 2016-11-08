#ifndef SORTED_LIST_H
#define SORTED_LIST_H


#include <stdlib.h>
#include <stdio.h>



typedef int (*CompareFuncT)( void *, void * );
typedef void (*DestructFuncT)( void * );
typedef struct LLNode* LLNodePtr;

typedef struct LLNode
{
	void* data; 
	struct LLNode *next; 

}LLNode ; 


struct SortedList
{
	LLNodePtr head;
	CompareFuncT compare;
	DestructFuncT destroy;
	//int nodeCount; 
	
};
typedef struct SortedList* SortedListPtr;



struct SortedListIterator
{
	LLNode *currNode;
	SortedListPtr SList;
	DestructFuncT iterDestroy; 
	//CompareFuncT iterCompare; 
	//int nodeCount; 
	//void *first;

	
};
typedef struct SortedListIterator* SortedListIteratorPtr;

/*
 * SLCreate creates a new, empty, 'SortedList'.
 *
 * SLCreate's parameters will be a comparator (cf) and destructor (df) function.
 *   Both the comparator and destructor functions will be defined by the user as per
 *     the prototypes above.
 *   Both functions must be stored in the SortedList struct.
 * 
 * SLCreate must return NULL if it does not succeed, and a non-NULL SortedListPtr
 *   on success.
 */
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df);


/*
 * SLDestroy destroys a SortedList, freeing all dynamically-allocated memory.
 */
 
void SLDestroy(SortedListPtr list);



/*
 * SLInsert inserts a given data item 'newObj' into a SortedList while maintaining the
 *   order and uniqueness of list items.
 * 
 * SLInsert should return 1 if 'newObj' is not equal to any other items in the list and
 *   was successfully inserted.
 * SLInsert should return 0 if 'newObj' is equal to an item already in the list or it was
 *   not successfully inserted
 *
 * Data item equality should be tested with the user's comparator function *
 */
 
int SLInsert(SortedListPtr list, void *newObj);


/*
 * SLRemove should remove 'newObj' from the SortedList in a manner that
 *   maintains list order.
 *
 * SLRemove must not modify the data item pointed to by 'newObj'.
 *
 * SLRemove should return 1 on success, and 0 on failure.
 */


int SLRemove(SortedListPtr list, void *newObj);

void * SLSearch(SortedListPtr list, void*newObj, CompareFuncT cf); //search a soredList using compare function cf 


SortedListIteratorPtr SLCreateIterator(SortedListPtr list);


/*
 * SLDestroyIterator destroys a SortedListIterator pointed to by parameter 'iter'.
 *
 * SLDestroyIterator should destroy the SortedListIterator, but should NOT
 *  affect the list used to create the SortedListIterator in any way.
 */

void SLDestroyIterator(SortedListIteratorPtr iter);


//===1.2: SortedList Iterator Get/Next Operations

/*
 * SLNextItem returns a pointer to the data associated with the
 *  next item in the SortedListIterator's list
 *
 * SLNextItem should return a NULL if all of iter's elements have
 *  been iterated through.
 *
 * NB: Be sure to check the length of the list that SortedListIterator holds
 *         before attempting to access and return an item from it.
 *         If an item is removed from the list, making it shorter, be careful not
 *         to try to read and return an item off the end of the list.
 */

void * SLNextItem(SortedListIteratorPtr iter);


/*
 * SLGetItem should return a pointer to the current data item
 *   The current data item is the item that was most recently returned by SLNextItem
 *   SLGetItem should not alter the data item that SortedListIterator currently refers to
 *
 * SLGetItem should return a NULL pointer if the SortedListIterator has been advanced
 *  all the way through its list.
 *
 * NB: Be sure to check the length of the list that SortedListIterator holds
 *         before attempting to access and return an item from it.
 *         If an items are removed from the list, making it shorter, be careful not
 *         to try to read and return an item off the end of the list.
 */

void * SLGetItem( SortedListIteratorPtr iter );





#endif


//LYDIA KIM
//PROJECT 4,WK 2,COEN 12
//WED 2:15 LAB

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "set.h"


//NOTES
//All functions except destroyList, removeItem, findItem, and getItems must run in O(1)
//circular, doubly-linked list with sentinel node


struct set {
	int count;
	int length;
	LIST **data;
	int (*compare)();
	unsigned (*hash)();
};

typedef struct set SET;

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())//big o of o(n)
{
//initializing new sp pointer 
	int i;
	SET *sp=malloc(sizeof(SET));
	assert (sp!=NULL);

	sp->length=maxElts/20;
	sp->count=0;
	sp->data=malloc(sizeof(LIST*)*sp->length);
	sp->compare=compare;
	sp->hash=hash;
	
	for(i=0;i<sp->length;i++)
		sp->data[i]=createList(compare);

	return sp;
}
void destroySet(SET *sp)//big o of o(n)
{
//destroys the nodes 
	int i;

	for(i=0;i<sp->length;i++)
		destroyList(sp->data[i]);

	free(sp->data);
	free(sp);
}

int numElements(SET *sp)//big o of o(1)
{
	assert(sp!=NULL);
	return sp->count;	
}

void addElement(SET *sp, void *elt) //big o of o(1)
{
	assert(sp!=NULL && elt!=NULL);
	unsigned idx = (*sp->hash)(elt) % sp->length;

	if (findItem(sp->data[idx],elt) == NULL) //if item is not found 
	{
		addFirst(sp->data[idx],elt);
		sp->count++;			
	}

}

void removeElement(SET *sp, void *elt)//big o of o(n)
{
	assert(sp!=NULL && elt!=NULL);
	unsigned idx = (*sp->hash)(elt) % sp->length;
	
	if(findItem(sp->data[idx],elt) != NULL) //if item is found 
	{
		removeItem(sp->data[idx],elt);
		sp->count--;
	}
}


void *findElement(SET *sp, void *elt) //big o of o(n)
{
	assert(sp!=NULL);
	unsigned idx = (*sp->hash)(elt) % sp->length;//hashes to find elt 
	
	return findItem(sp->data[idx],elt);
}

void *getElements(SET *sp)//big o of o(n)
{
	assert(sp!=NULL);
	int i,idx=0;
	void **arrcpy=malloc(sizeof(void*)*sp->count);
	
	for(i=0;i<sp->length;i++)
	{//copies array into a void copy arr 
		memcpy(arrcpy+idx,getItems(sp->data[i]),sizeof(void*)*numItems(sp->data[i]));
		idx+= numItems(sp->data[i]);//incrementing cpy arr by idx bc you are inserting groups at a time 
	}
	return arrcpy;
}

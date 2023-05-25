//Lydia Kim
//project 5 week 1
//coen 12 , wed 2:15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

typedef struct pqueue
{
	int count;//# of entries
	int length;//length of arr 
	void **data;//allocated array of entries
	int (*compare)();//save ptr to this fnctn
}PQ;

//ALL FUNCTIONS THAT TRAVERSE WHOLE HEAP IS o(logn) bc the shape is definite

PQ *createQueue(int(*compare)())//big o is o(1)
{//create new pq ptr
	PQ *pq = malloc(sizeof(PQ));
	pq->count=0;
	pq->length=10;
	pq->data=malloc(sizeof(void*)*pq->length);
	pq->compare=compare;

	return pq;		
}

void destroyQueue(PQ *pq)//big o is o(1)
{//deallocate memory associated with prioirty queue pointed to by pq

	assert(pq!=NULL);//if theres nothing to delete

	free(pq->data); 
	free(pq);		
}

int numEntries(PQ *pq)//big o is o(1)
{//return # of entries in prior. que. pointed by pq
	return pq->count; 
}

void addEntry(PQ *pq, void *entry)//big o is o(logn)
{
//add entry to prior. que. pointed by pq
//reheap up by checking parent 
	if( pq->count == pq->length )//queue is full
	{
		pq->length=pq->length*2;//doubles arr length
		pq->data=realloc(pq->data,sizeof(void*)*pq->length);//mem alloc for new size
	}
	
	int i=pq->count++;//increase count bc adding

	while(i>0 && (*pq->compare)(pq->data[(i-1)/2],entry) > 0) //can stop traversing when the parent is smaller
	{
		pq->data[i]=pq->data[(i-1)/2];//swapping added node w/ parent 
		i=(i-1)/2;
	}
	pq->data[i]=entry;//puts new elt @ end of binary heap
}

void *removeEntry(PQ *pq)//big o is o(logn)
{
	int i=0,child=0;
	void *root,*last;	

	root=pq->data[0];
	last=pq->data[pq->count-1];


	while ((2*i+1) < pq->count ) 
	{
		//compare b/w left and right
		child=2*i+1;
		if( (2*i+2) < pq->count)
		{
			if ((*pq->compare)(pq->data[2*i+1],pq->data[2*i+2]) > 0) //checks if right child is smaller
				child=2*i+2;
		}

		if ((*pq->compare)(last,pq->data[child]) > 0)
		{ 
			pq->data[i]=pq->data[child];//puts left child @ entry node
			i=child;//compare from left child
		}	
		else
			break;
		
	}

	pq->data[i]=last;//put last node into root 
	pq->count--;
	return root; 
}

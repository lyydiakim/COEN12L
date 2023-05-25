//Lydia Kim
//COEN 12 PROJECT 2 
//DUE 4/18/21
//WED. 2:15-5 LAB SESSION



#include <stdio.h>
#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct set
{
	int count;
	int length;
	char **data;	
}SET;


int search(char **a, int n, char *x, bool *found);

SET *createSet(int maxElts)//initializes struct values
{
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->count = 0;
	sp->length = maxElts;
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data != NULL);
	return sp;
}

void destroySet(SET *sp)
{
	assert(sp!=NULL);
	int i;

	for(i=0;i<sp->count;i++) //frees all data
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

int numElements(SET *sp)//counts # of elements in sp
{
	return sp->count;
}

void addElement(SET *sp, char *elt)
{
//1. search 2. shift down 3. insertion
	int idx,i;
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;

	idx=search(sp->data,sp->count,elt,&found);//search call

	if (found == false)//if element does not exist
	{	
		if(sp->length >= sp->count)//checks if # of elts in arr is < than length
		{
			for(i=sp->count-1;i>=idx;i--)
			{
				sp->data[i+1]=sp->data[i];
			}

			sp->data[idx] = strdup(elt);
			sp->count++;
			return;
		}
	}

}

char **getElements(SET *sp)
{
	assert(sp!=NULL);
	char **array= malloc(sizeof(char*)*sp->count);
	memcpy(array,sp->data,(sizeof(char*)*sp->count));//copies data 
	return array;
}

void removeElement(SET *sp, char *elt)
{
//1. search 2. shift up 
	int idx,i;
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;

	idx=search(sp->data,sp->count,elt,&found);

	if(found == false)
		return;

	free(sp->data[idx]);

	for(i=idx;i<sp->count-1;i++)//shifts up deleting idx
		sp->data[i]=sp->data[i+1];
	sp->count--;
	
}

char *findElement(SET *sp, char *elt) //public search
{
	int idx;
	assert(sp!=NULL);
	assert(elt!=NULL);
	bool found;

	idx=search(sp->data,sp->count,elt,&found);
	if (found == false)//element does not exist
		return NULL;

	return sp->data[idx];	
}

int search(char **a, int n,char *x, bool *found)//private binary search
{
	int lo,hi,mid;
	lo=0;hi=n-1;
		
	while(lo<=hi)
	{
		mid = (lo+hi)/2;
		if(strcmp(x,a[mid])<0)
			hi=mid-1;
		
		else if(strcmp(x,a[mid])>0)
			lo = mid+1;

		else
		{
			*found = true;//if element is found
			return mid;//index
		}
	}
	*found = false;//element is not found
	return lo;//index of element 

}

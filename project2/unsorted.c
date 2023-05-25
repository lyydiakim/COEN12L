//LYDIA KIM
//COEN 12, PROJECT 2
//WED. 2:15-5:00 LAB SESSION 
//DUE 4/18/2021



#include <stdio.h>
#include "set.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct set
{
	int count;
	int length;
	char **data;	
}SET;


static int search(SET *sp, char *elt);

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

	for(i=0;i<sp->count;i++)
	{
		free(sp->data[i]);//free all data
	}
	free(sp->data[i]);
	free(sp);
}

int numElements(SET *sp)//counts # of elements in sp
{
	return sp->count;
}

void addElement(SET *sp, char *elt)
{
	int ret;
	assert(sp!=NULL);
	assert(elt!=NULL);

	ret=search(sp,elt);
	if (ret == -1)//if no duplicates
	{	
		if(sp->length >= sp->count)//make sure the # of elements is not > then size of arr
		{
			sp->data[sp->count] = strdup(elt);//places element
			sp->count++;//increment bc you are adding another element
			return;
		}
	}

}

void removeElement(SET *sp, char *elt)
{
	int ret;
	assert(sp!=NULL);
	assert(elt!=NULL);

	ret=search(sp,elt);
	if(ret == -1)//element doesnt exist
		return;

	free(sp->data[ret]);
	sp->data[ret]=sp->data[sp->count-1];//replaces element w last element
	sp->count--;
}

char *findElement(SET *sp, char *elt) //public search
{
	int ret;
	assert(sp!=NULL);
	assert(elt!=NULL);

	ret=search(sp,elt);
	if (ret == -1)//element does not exist
		return NULL;

	return sp->data[ret];	
}
static int search(SET *sp, char *elt) //private SEQUENTIAL search
{
	int i;
	assert(sp!=NULL);
	assert(elt!=NULL);

	for(i=0;i<sp->count;i++)
	{
		if( strcmp(sp->data[i],elt) == 0)//if element exists
			return i;//index of search element 
	}
	return -1;//doesnt exist			
}

char **getElements(SET *sp)
{
	assert(sp!=NULL);
	char **array= malloc(sizeof(char*)*sp->count);
	memcpy(array,sp->data,(sizeof(char*)*sp->count));//COPIES DATA
	return array;
}

//LYDIA KIM
//PROJECT 3, COEN 12
//WED. 2:15 LAB

//GENERIC

#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


int search(SET *sp, int len,char *x, bool *found);
unsigned strhash(char *s);

typedef struct set
{
	int count;
	int length;
	void **data;	
	char *flag;
	int (*compare)();//need compare&hash because passing unknown data type
	unsigned (*hash)();
}SET;



SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
	int i;
	SET *sp = malloc(sizeof(SET));
	assert(sp != NULL);
	
	sp->length = maxElts;
	sp->compare=compare;
	sp->hash=hash;
	sp->data = malloc(sizeof(void*)*maxElts);
	assert(sp->data != NULL);
	sp->flag= malloc(sizeof(char)*maxElts);
	for (i=0;i<sp->length; i++)
		sp->flag[i]='E';
	return sp;
}

void destroySet(SET *sp)//deallocate memory associated with the set pointed to by sp
{
	assert(sp!=NULL);
	int i;

	free(sp->flag);
	free(sp);
}

int numElements(SET *sp)//return # of elts in set pointed by sp
{
	return sp->count;
}

void addElement(SET *sp, void *elt)
{
	int ret;
	bool found;
	assert(sp!=NULL);
	assert(elt!=NULL);

	ret=search(sp,sp->length,elt,&found);

	if (found == false)//if no duplicates
	{	
		assert(sp->count < sp->length);//make sure the # of elements is not > then size of arr
		sp->flag[ret]='F';//changes corresponding flag to filled 
		sp->data[ret] = elt;//places element
		sp->count++;//increment bc you are adding another element
		return;
	}
}

void removeElement(SET *sp, void *elt)
{
	int ret;
	bool found;
	assert(sp!=NULL);
	assert(elt!=NULL);

	ret=search(sp,sp->length,elt,&found);

	if(found == false)
		return;

	sp->flag[ret]= 'D';
	sp->count--;
}

void *findElement(SET *sp, void *elt)
{
	int ret;
	bool found;
	assert(sp!=NULL);
	assert(elt!=NULL);
	
	ret = search(sp,sp->length,elt,&found);
	if (found == false)//element does not exist
		return NULL;

	return sp->data[ret];
}

void *getElements(SET *sp)
{
	int i,j=0;
	void **elts;
	elts=malloc(sizeof(void*)*sp->count);
	assert(sp != NULL);
	
	for (i=0; i<sp->length; i++)
	{
		if (sp->flag[i] == 'F')//if spot is filled
		{
			elts[j]=sp->data[i];//put data from corresponding idx into elts
			j++;
		}
	}
	return elts;
}

int search(SET *sp, int len,char *x, bool *found)
{
	

	int i,new_idx,hash_idx;
	int avail = -1;
	
	hash_idx=(*sp->hash)(x) % len;

	
	for(i=0;i<len;i++) 
	{
		new_idx = (hash_idx+i) % len; //linear probing new hash idx
		if(sp->flag[new_idx] == 'E')//if empty return that idx
		{
			*found = false;
			if (avail != -1)
				return avail;
			return new_idx;

		}			

		else if(sp->flag[new_idx] == 'D')//deleted therefore keep going 
		{
			if (avail == -1)
				avail = new_idx;
		}
			
		else if(sp->flag[new_idx] == 'F')//filled look for next empty spot 
		{
			if((*sp->compare)(x,sp->data[new_idx]) == 0)
			{
				*found = true; 
				return new_idx;
			}
			
                }

	}

}

unsigned strhash(char *s) // generate hash index
{
	unsigned hash = 0; 
	while (*s != '\0')
		hash = 31 * hash + *s ++; 
	
	return hash;
}

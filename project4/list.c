//LYDIA KIM
//PROJECT 4, COEN 12
//WED 2:15 LAB

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//NOTES
//All functions except destroyList, removeItem, findItem, and getItems must run in O(1)
//circular, doubly-linked list with sentinel node

struct node{   
	void *data;     
	struct node *next;   
	struct node *prev;
};

typedef struct node NODE;

struct list{   
	int count;   
	struct node *head;
	int (*compare)(); // function pointer
};

typedef struct list LIST;

LIST *createList(int (*compare)()) //big o of o(1)
{
	LIST *lp=malloc(sizeof(LIST));
	lp->head = malloc(sizeof(NODE));
	lp->compare=compare; 	
	lp->count=0;
	lp->head->next=lp->head;
	lp->head->prev=lp->head;
	return lp;
}
void destroyList(LIST *lp)//big o of o(n)
{
	assert(lp != NULL);
	NODE *pDel, *pNext;
	pDel = lp->head;

	do {
		pNext = pDel ->next;
		free(pDel);
		pDel = pNext;
	} while (pDel!= lp->head);     

	free(lp);
}
int numItems(LIST *lp) //big o of o(1)
{
	return lp->count;	
}
void addFirst(LIST *lp, void *item) //big o of o(1)
//add item as the first item in the list 
{
	NODE *new=malloc(sizeof(NODE));
	new->data=item;
	new->next=lp->head->next;
	new->prev=lp->head;
	lp->head->next->prev=new;	
	lp->head->next=new;
	lp->count++;
}
void addLast(LIST *lp, void *item)//big o of o(1)
{
	NODE *new=malloc(sizeof(NODE));
	new->data=item;
	new->next=lp->head;
	new->prev=lp->head->prev;
	lp->head->prev->next=new;
	lp->head->prev=new;
	lp->count++;
}
void *removeFirst(LIST *lp) //big o of o(1)
{
	NODE *first=lp->head;
	void *item=first->next->data;
	NODE *fnext=first->next;

	first->next=first->next->next;
	first->next->next->prev=first;

	lp->count--;
	free(fnext);
	return item;
}
void *removeLast(LIST *lp) //big o of o(1)
{
	NODE *del=lp->head->prev;
	void *item=del->data;

	del->prev->next=lp->head;
	lp->head->prev=del->prev;;

	free(del);
	lp->count--;
	return item;
}

void *getFirst(LIST *lp)//big o of o(1)
//return first item in the list pointed to by lp
{
	assert(lp->count != 0 && lp != NULL);
	return lp->head->next->data;
}

void *getLast(LIST *lp) //big o of o(1)
{
	assert(lp->count != 0 && lp != NULL);
	return lp->head->prev->data;	
}

void removeItem(LIST *lp, void *item) //big o of o(n)
{
//sequential search
//if item is present in the list pointed to by lp then remove it
	NODE *new=lp->head->next;

	while(new != lp->head)
	{
		if( (*lp->compare)(new->data,item) == 0)
		{
			new->prev->next=new->next;
			new->next->prev=new->prev;	
			lp->count--;
			free(new);
			break;
		}
		new=new->next;

	}	
}

void *findItem(LIST *lp, void *item)//big o of o(n)
{
//if item is present in list return matching item, else ret NULL; comparison function must not be NULL
	NODE *new=lp->head->next;

	while(new != lp->head)
	{
		if((*lp->compare)(new->data,item) == 0)		
			return new->data;
		new=new->next;
	}
	return NULL;//not found
}

void *getItems(LIST *lp) //big o of o(n)
{
//allocate and return an array of items in the list pointed to by lp
	NODE *ptr=lp->head->next;
	void **cpyarr = malloc(sizeof(void*)*lp->count);
	int i=0;

	while(ptr != lp->head)
	{
		cpyarr[i]=ptr->data;
		i++;
		ptr=ptr->next;
	}
			
	return cpyarr;		
	
}

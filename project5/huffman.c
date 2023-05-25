//LYDIA KIM
//COEN 12 WED 2:15
//PROJECT 5 WEEK 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

//function declarations
int compare(struct node *n1, struct node *n2);
int depth(struct node *n);
struct node *mknode(int data, struct node *left, struct node *right);

int main(int argc, char *argv[]) //big o of o(n)
{//open file and count frequency of letters
	FILE *fp;
	int i,c,d,sum,count[257];//length of ascii table + eof
	struct node *l,*r,*np,*leaves[257];
	struct pqueue *pq;
	
	for(i=0;i<257;i++)
	{
		leaves[i]=NULL;//initialize node array as null
		count[i]=0;
	}
	
	if (argc == 1) //only 1 argument which is the executable
	{
		printf("Filename missing.\n");
		return 0;
	}
	
	if ((fp = fopen(argv[1], "r")) == NULL)//cannot read 
	{
		printf("Cannot open.\n");
		return 0;
	}

	while( (c=fgetc(fp)) != EOF) 
		count[c]++;//converts letter to ascii value

	pq=createQueue(compare);//returns new empty priority queue

	for(i=0;i<255;i++)
	{
		if(count[i] > 0)//letter exists (occurs 1 or more times)
		{
			leaves[i]=mknode(count[i],NULL,NULL);//set leaf node to hold counts[c]
			addEntry(pq,leaves[i]);//adds leaf nodes into priority queue
		}
	}

	leaves[256]=mknode(count[0],NULL,NULL);
	addEntry(pq,leaves[256]);


	while(numEntries(pq) > 1)
	{//repeat until theres only 1 tree left	
		l=removeEntry(pq);
		r=removeEntry(pq);
		sum=l->count + r->count;//add the left and right to create its parent 
		np=mknode(sum,l,r);
		addEntry(pq,np);//add new node to priority queue
	}


	for(i=0;i<257;i++)
	{
		if(leaves[i]!=NULL)
		{
			d=depth(leaves[i]);
			if (isprint(i))//if printable characters
				printf("'%c': %d x %d bits = %d bits\n",i,count[i],d,count[i]*d);	
			else  //non printable octal value
				printf("%03o : %d x %d bits = %d bits\n",i,count[i],d,count[i]*d);
		}
	}

	fclose(fp);
	pack(argv[1],argv[2],leaves);
	return 0;
}

struct node *mknode(int data, struct node *left, struct node *right) //big o of o(1)
{
	struct node *np=malloc(sizeof(struct node*));
	np->parent=NULL;
	np->count=data;
	if (left!=NULL && right!=NULL)
	{	
		left->parent=np; 
		right->parent=np;
	}

	return np;
}

int compare(struct node *n1, struct node *n2) //big o of o(1)
{
	if(n1->count > n2->count)
		return 1;//node 1's frequency is larger
	else
		return -1; //node 2's frequency is larger
	
}

int depth(struct node *n) //big o of o(n)
{
	assert(n!=NULL);
	int depth=0;

	while(n->parent != NULL ) //can stop traversing when the parent is smaller
	{
		depth++;
		n=n->parent;
	}

	return depth;//this is # of bits
}

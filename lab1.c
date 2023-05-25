
//LYDIA KIM
//coen 12, wed. 2:15
//lab 1 

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#define MAX_WORD_LENGTH 30

int main (int argc, char *argv[])
{
	FILE *fp;
	char word[MAX_WORD_LENGTH];
	int count=0;

	if (argc == 1) //if filename is missing
	{
		printf("Filename is missing.");
		return;

	}	
	
	fp = fopen(argv[1], "r"); //open file 

	if (fp == NULL) //if unable to open file
	{
		printf("File does not exist.\n");
		return;
	}
	
	while (fscanf(fp,"%s",&word) == 1) //when fp can read file 
	{
		count++;
	}

	printf("%d words.\n",count); //print # of words

	fclose(fp); //close file
	return;
}

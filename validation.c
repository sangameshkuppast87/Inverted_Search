/*

Name : Sangamesh I Kuppast
Date : 26/12/2025
Description :  ******* INVERTED SEARCH ******

             -> This project is an Inverted Search Engine designed to efficiently index and search large collections of text files.
             -> It creates an inverted index that maps words to the files in which they appear, along with their frequency of occurrence.
             -> Unlike simple search methods, this approach significantly improves search speed and scalability for large datasets.
             -> The project supports operations such as database creation, word search, displaying indexed data, saving the index to a backup file, and updating the database from backups.
             -> It efficiently handles multiple input files and avoids duplication while building the database.
             -> The Inverted Search Engine ensures fast and accurate retrieval of information, making it suitable for applications like search engines, document indexing, and information retrieval systems.

*/


#include"header.h"

/* Function to read and validate the command line arguments */
#if 0
int read_validate(int argc, char *argv[], Flist **head)
{
	int size1 = 0, size2 = 0;
	/* Array to store the valid file name's index */
	int valid[argc];			
	for(int i = 1; i < argc; i++)
	{
		if(check_extension(argv[i]) == FAILURE)
			printf("File %s is not .txt extension!!\n", argv[i]);
		else
		{
			if(strlen(argv[i]) <= 4)
				printf("File name is not mentioned!!\n");
			else
				valid[size1++] = i;
		}
	}
	for(int i = 0; i < size1; i++)
	{
		int result = (check_file_existence_and_emptyness(argv[valid[i]]));
		if(result == FILE_NOT_FOUND)
			printf("File %s is not available in the present directory!!!\n", argv[valid[i]]);
		else if(result == FILE_EMPTY)
			printf("File %s is empty!!!\n", argv[valid[i]]);
		else
			valid[size2++] = valid[i];
	}

	/* Function to remove the duplicates from the list of valid files */
	remove_duplicates(argv, valid, &size2);

	for(int i = 0; i < size2; i++)
	{
		if(insert_at_last(head, argv[valid[i]]) == FAILURE)
		{
			printf("File were not able to load to list!!!\n");
			return FAILURE;
		}
	}

	if(size1 > 0 && size2 > 0)
		return SUCCESS;
	else
		return FAILURE;
}

/* Function to check the extension of the file */
int check_extension(char *str)
{
	char *ptr = strstr(str, ".txt");
	if(ptr != NULL && (strcmp(ptr, ".txt") == 0))
		return SUCCESS;
	else
		return FAILURE;
}

/* Function to check if the file is present in the present directory and is present the file is empty or not */
int check_file_existence_and_emptyness(char *file)
{
	FILE *fptr = fopen(file, "r");
	if(fptr == NULL)
		return FILE_NOT_FOUND;

	char ch = fgetc(fptr);

	if (ch == EOF)
	{
		fclose(fptr);
		return FILE_EMPTY;
	}

	fclose(fptr);
	return SUCCESS;
}
#endif

/*  Function to remove the duplicates from the list of valid files using the shifting method */
void remove_duplicates(char *argv[], int valid[], int *size)
{
	for(int i = 0; i < *size - 1; i++)
	{
		for(int j = i + 1; j < *size;)
		{
			if(strcmp(argv[valid[i]], argv[valid[j]]) == 0)
			{
				for(int k = j; k < *size - 1; k++)
				{
					valid[k] = valid[k + 1];
				}
				(*size)--;
			}
			else
				j++;
		}
	}
} 	


/* Function to insert the file name at last of the single linked list */
int insert_at_last(Flist **head, char *file)
{
	Flist *new = malloc(sizeof(Flist));

	if(new == NULL)
	{
		return FAILURE;
	}

	new -> fname = malloc(strlen(file) + 1);
	if (new -> fname == NULL)
	{
		free(new);
		return FAILURE;
	}

	strcpy(new -> fname, file);
	new -> link = NULL;

	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	else
	{
		Flist *temp = *head;
		while(temp -> link != NULL)
		{
			temp = temp -> link;
		}
		temp -> link = new;
		return SUCCESS;
	}
}


int read_and_validate(char *argv[], Flist **head, int argc)
{
	int valid[argc], size = 0;
	for(int i = 1; i < argc; i++)
	{
		if(valid_files(argv[i]) == SUCCESS)
			valid[size++] = i;
	}
	remove_duplicates(argv, valid, &size);
	for(int i = 0; i < size; i++)
		insert_at_last(head, argv[valid[i]]);

	if(size > 0)
		return SUCCESS;
	else
		return FAILURE;
}


int valid_files(char *file)
{
	char *ptr = strstr(file, ".txt");
	if(ptr != NULL && strcmp(ptr, ".txt") == 0)
	{
		FILE *fptr = fopen(file, "r");
		if(fptr == NULL)
			return FAILURE;
		char ch = fgetc(fptr);
		fclose(fptr);
		if(ch == EOF)
			return FAILURE;

		return SUCCESS;
	}
	else
		return FAILURE;
}
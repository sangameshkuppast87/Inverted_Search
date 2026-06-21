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

/* Function to create database */
int create_database(main_node *arr[27], Flist *head)
{
	if(head == NULL)
		return FAILURE;

	/* Running the loop till all the file's data is being fetched */
	Flist *tempF = head;
	while(tempF != NULL)
	{
		FILE *ptr = fopen(tempF -> fname, "r");
		if(ptr == NULL)
		{
			printf("Error : File opening not possible!!\n");
			return FAILURE;
		}
		char ch;
		while ((ch = fgetc(ptr)) != EOF)
		{
			int i = 0;
			char buffer[20];

			/* Collecting the word in the buffer */
			while (ch != ' ' && ch != '\n' && ch != EOF)
			{
				buffer[i++] = ch;
				ch = fgetc(ptr);   
			}
			buffer[i] = '\0';

			/* Skipping the white spaces */
			if (i == 0)
				continue;
			
			/* Getting the index for insertion */
			int index = check_for_index(buffer[0]);
			if(arr[index] == NULL)
			{
				arr[index] = create_main_node(buffer, tempF -> fname, 1);
			}
			else
			{
				main_node *tempM = arr[index];
				while(tempM != NULL)
				{
					if(strcmp(tempM -> word, buffer) == 0)
						break;

					if(tempM -> main_link == NULL)
						break;

					tempM = tempM -> main_link;
				}
				if(strcmp(tempM -> word, buffer) == 0)
				{
					sub_node *tempS = tempM -> sub_link;
					int found = 0;
					while (tempS)
					{
						if (strcmp(tempS -> file_name, tempF -> fname) == 0)
						{
							tempS -> word_count++;
							found = 1;
							break;
						}
						if (tempS -> sub_link == NULL)
							break;
						tempS = tempS -> sub_link;
					}

					if (!found)
					{
						tempS -> sub_link = create_sub_node(tempF -> fname,1);
						tempM -> file_count++;
					}

				}
				else
					tempM -> main_link = create_main_node(buffer, tempF -> fname, 1);
			}
		}
		fclose(ptr);

		tempF = tempF -> link;
	}
	return SUCCESS;
}

/* Function to get the index for insertion inside the database */
int check_for_index(char ch)
{
	if(ch >= 'A' && ch <= 'Z')
		return ch - 'A';
	else if(ch >= 'a' && ch <= 'z')
		return ch - 'a';
	else
		return 26;
}

/* Function to create the main node */
main_node *create_main_node(char word[], char fname[], int file_count)
{
	main_node *new = malloc(sizeof(main_node));
	if(new == NULL)
		return NULL;

	new -> file_count = file_count;
	new -> word = malloc(strlen(word) + 1);
	strcpy(new -> word, word);
	new -> sub_link = create_sub_node(fname, 1);
	new -> main_link = NULL;

	return new;
}

/* Function to create the subnode */
sub_node *create_sub_node(char fname[], int word_count)
{
	sub_node *new = malloc(sizeof(sub_node));
	if(new == NULL)
		return NULL;

	new -> file_name = malloc(strlen(fname) + 1);
	strcpy(new -> file_name, fname);

	new -> word_count = word_count;
	new -> sub_link = NULL;
	return new;
}


/* Function to get the unique files after the update database option */
Flist* get_unique_files(Flist *bkp_head, Flist *head)
{
	Flist *res_head = NULL;
	Flist *temp2 = head;
	while(temp2 != NULL)
	{
		int found = 0;
		Flist *temp1 = bkp_head;
		while(temp1 != NULL)
		{
			if(strcmp(temp1 -> fname, temp2 -> fname) == 0)
			{
				found = 1;
				break;
			}
			temp1 = temp1 -> link;
		}

		if(found == 0)
			insert_at_last(&res_head, temp2 -> fname);

		temp2 = temp2 -> link;
	}
	return res_head;
}
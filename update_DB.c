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

/* Function to update the database */
int update_database(main_node *arr[27], Flist **bkp_head)
{
	for(int i = 0; i < 27; i++)
	{
		if(arr[i] != NULL)
			return NON_EMPTY_DATABASE;
	}

	char bkp_file[20];

	printf("Enter the backup file name : ");
	scanf("%s", bkp_file);

	if(validate_back_up_file(bkp_file) == FAILURE)
	{
		printf("BackUp file dosen't meet the requirement!!\n");
		return SUCCESS;
	}

	FILE *fp = fopen(bkp_file, "r");
	if(fp == NULL)
	{
		printf("Error : Unable to open the backup file!!!\n");
		return FAILURE;
	}

	char ch;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '#')
		{
			int index, file_count;
			char word[50];

			fscanf(fp, "%d;%[^;];%d;", &index, word, &file_count);

			/* Creating the main node */
			main_node *mnew = malloc(sizeof(main_node));
			if (mnew == NULL)
				return FAILURE;
			mnew -> word = malloc(strlen(word) + 1);
			strcpy(mnew -> word, word);
			mnew -> file_count = file_count;
			mnew -> sub_link = NULL;
			mnew -> main_link = NULL;

			sub_node *sprev = NULL;
			for (int i = 0; i < file_count; i++)
			{
				char fname[50];
				int wcount;

				fscanf(fp, "%[^;];%d;", fname, &wcount);

				/* Creating the subnode */
				sub_node *snew = malloc(sizeof(sub_node));
				if (snew == NULL)
					return FAILURE;

				/* Creating list of files for creating database */
				if(check_already_present(*bkp_head, fname) == FAILURE)
					insert_at_last(bkp_head, fname);	

				snew -> file_name = malloc(strlen(fname) + 1);

				strcpy(snew -> file_name, fname);
				snew -> word_count = wcount;
				snew -> sub_link = NULL;

				if (sprev == NULL)
					mnew -> sub_link = snew;
				else
					sprev -> sub_link = snew;

				sprev = snew;
			}

			if (arr[index] == NULL)
			{
				arr[index] = mnew;
			}
			else
			{
				main_node *temp = arr[index];
				while (temp -> main_link != NULL)
					temp = temp -> main_link;

				temp -> main_link = mnew;
			}
			fgetc(fp);
		}
	}
	return SUCCESS;
}

/* Function to validate the backup file */
int validate_back_up_file(char *file)
{
	if(strlen(file) > 4)
	{
		char *ptr = strstr(file, ".txt");
		if(ptr != NULL && strcmp(ptr, ".txt") == 0)
		{
			FILE *fptr = fopen(file, "r");
			if(fptr == NULL)
			{
				printf("Entered BackUp file is not available in the present directory!!!\n");
				return FAILURE;
			}
			else
			{
				/* Checking for the prototype match of the backup file */
				char line[1024];
				char ch;
				int flag = 1;
				while((ch = fgetc(fptr)) != EOF)
				{
					int i = 0;
					while(ch != '\n' && ch != EOF)
					{
						line[i++] = ch;
						ch = fgetc(fptr);
					}
					line[i] = '\0';

					if (i == 0)
						continue;

					if(line[0] != '#' || line[i - 1] != '#')
					{
						flag = 0;
						fclose(fptr);
						return FAILURE;
					}
				}
				if(flag == 1)
				{
					fclose(fptr);
					return SUCCESS;
				}
			}
		}
		else
		{
			printf("Error : BackUp file mentioned is not of .txt extension!!!\n");
			return FAILURE;
		}
	}
	else
	{
		printf("Error : The length of the BackUp file should be more than 4!!!\n");
		return FAILURE;
	}

	return SUCCESS;
}

/* Function to check if the file is already present in the list */
int check_already_present(Flist *head, char *fname)
{
	Flist *temp = head;
	while(temp != NULL)
	{
		if(strcmp(temp -> fname, fname) == 0)
			return SUCCESS;

		temp = temp -> link;
	}
	return FAILURE;
}
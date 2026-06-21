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

/* Function to save the database to the backup file */
int save_database(main_node *arr[27])
{
	/* Checking if the database is empty */
	int empty = 0;
        for(int i = 0; i < 27; i++)
        {
                if(arr[i] != NULL)
                {
                        empty = 1;
                        break;
                }
        }
	if(empty == 0)
		return EMPTY_DATABASE;

	char back_up[30];
	printf("Enter the backup file name : ");
	scanf("%s", back_up);
	
	/* Validating the user input */
	if(validate_file(back_up) == FAILURE)
	{	printf("Error : BackUp file name is not valid!!\nUasge : filename.txt\n");
		return FAILURE;
	}

	FILE *fptr = fopen(back_up, "w");
	if(fptr == NULL)
	{
		printf("Error : Unable to open the %s file!!!\n", back_up);
		return FAILURE;
	}
	
	/* Writing the database data to user given backup file */
	for(int i = 0; i < 27; i++)
	{
		if(arr[i] != NULL)
		{
			main_node *tempM = arr[i];
			while(tempM != NULL)
			{
				fprintf(fptr,"#%d;%s;%d;", i, tempM -> word, tempM -> file_count);
				sub_node *tempS = tempM -> sub_link;
				while(tempS != NULL)
				{
					fprintf(fptr,"%s;%d;", tempS -> file_name, tempS -> word_count);
					tempS = tempS -> sub_link;
				}
				fprintf(fptr,"#\n");
				tempM = tempM -> main_link;
			}
		}
	}
	fclose(fptr);
	
	return SUCCESS;
}

/* Function to validate the file */
int validate_file(char *file)
{
	char *ptr = strstr(file, ".txt");	
	if(ptr != NULL && strcmp(ptr, ".txt") == 0)
	{
		if(strlen(file) > 4)
			return SUCCESS;
		else
		{
			printf("File name is not mentioned only the extension is mentioned!!\n");
			return FAILURE;
		}
	}

	return FAILURE;
}
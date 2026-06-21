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

/* Function to search the user given word in the database */
int search_database(main_node *arr[27])
{
	/* Check for empty database */
	int empty = 1;
	for (int i = 0; i < 27; i++)
	{
		if (arr[i] != NULL)
		{
			empty = 0;
			break;
		}
	}

	if (empty)
		return EMPTY_DATABASE;

	char word[20];
	printf("Enter the word you want to search : ");
	scanf("%19s", word);

	int index = check_for_index(word[0]);
	main_node *tempM = arr[index];

	while (tempM != NULL)
	{
		if (strcmp(tempM -> word, word) == 0)
		{
			printf("\n+--------------------+------------+-------------------------+------------+\n");
			printf("|%-20s|%-12s|%-25s|%-12s|\n", "Word", "File Count", "File Name", "Word Count");
			printf("+--------------------+------------+-------------------------+------------+\n");

			sub_node *tempS = tempM -> sub_link;
			int first = 1;

			while (tempS != NULL)
			{
				if (first)
				{
					printf("|%-20s|%-12d|%-25s|%-12d|\n", tempM -> word, tempM -> file_count, tempS -> file_name, tempS -> word_count);
					first = 0;
				}
				else
				{
					printf("|%-20s|%-12s|%-25s|%-12d|\n"," ", " ", tempS -> file_name,tempS -> word_count);
				}

				tempS = tempS->sub_link;
			}

			printf("+--------------------+------------+-------------------------+------------+\n\n");
			return SUCCESS;
		}

		tempM = tempM -> main_link;
	}
	return FAILURE;
}
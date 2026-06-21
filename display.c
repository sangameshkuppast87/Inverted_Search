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

/* Function to print the valid files */
void print_valid_files(Flist *head)
{
        if (head == NULL)
                printf("INFO : List is empty\n");
        else
        {
		printf("\nValid files : \n");
                while (head)
                {
                        printf("%s\n", head -> fname);
                        head = head -> link;
                }
        }
}

/* Function to display database */
void display_database(main_node *arr[27])
{
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
	{
		printf("\nDatabase is empty!!!\n");
		return;
	}

	printf("\n+-------+------------------+--------------+-------------------------+------------------+\n");
	printf("|%-7s|%-18s|%-14s|%-25s|%-18s|\n", "Index", "Word", "File Count", "File Name", "Word Count");
	printf("+-------+------------------+--------------+-------------------------+------------------+\n");

	for (int i = 0; i < 27; i++)
	{
		if (arr[i] != NULL)
		{
			main_node *tempM = arr[i];

			while (tempM != NULL)
			{
				sub_node *tempS = tempM -> sub_link;
				int first = 1;

				while (tempS != NULL)
				{
					if (first)
					{
						printf("|%-7d|%-18s|%-14d|%-25s|%-18d|\n", i, tempM -> word, tempM -> file_count, tempS -> file_name, tempS -> word_count);
						first = 0;
					}
					else
					{
						printf("|%-7s|%-18s|%-14s|%-25s|%-18d|\n"," ", " ", " ", tempS -> file_name, tempS -> word_count);
					}

					tempS = tempS -> sub_link;
				}

	printf("+-------+------------------+--------------+-------------------------+------------------+\n");
				tempM = tempM -> main_link;
			}
		}
	}
}
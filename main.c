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

int main(int argc, char *argv[])
{
	int db_created = 0;
	int db_updated = 0;
	
	Flist *head = NULL;
	Flist *bkp_head = NULL;
	
	main_node *arr[27];
	
	/* Pointing the array members to NULL address */
	for(int i = 0; i < 27; i++)
		arr[i] = NULL;

	if(argc == 1)
	{
		printf("Error : No text files passed!!!\n");
		return FAILURE;
	}
	if(read_and_validate(argv, &head, argc) == FAILURE)
	{
		printf("Read and Validation failed!!!\n");
                return FAILURE;
	}
	/*
	if(read_validate(argc, argv, &head) == FAILURE)
	{
		printf("Read and Validation failed!!!\n");
		return FAILURE;
	}*/
	else
	{
		printf("Read and Validation successful!!!\n");
		print_valid_files(head);
	}

	int opt;
	do{
		printf("\nInverted Search Menu\n");
		printf("1. Create DataBase\n");
		printf("2. Display DataBase\n");
		printf("3. Search DataBase\n");
		printf("4. Save DataBase\n");
		printf("5. Update DataBase\n");
		printf("6. Exit\n");

		printf("Enter your option!!\n");
		scanf("%d", &opt);

		switch(opt)
		{
			case 1:
				{
					if(db_created == 1)
					{
						printf("DataBase is already created!!\n");
						break;
					}
					if(db_updated == 1)
					{
						Flist *res_head = get_unique_files(bkp_head, head);
						create_database(arr, res_head);
						free_flist(res_head);
					}
					else
					{
						create_database(arr, head);
					}
					db_created = 1;
					printf("DataBase is created successfully!!!\n");
					break;
				}
			case 2:
				display_database(arr);
				break;
			case 3:
				{
					int res = search_database(arr);
					if(res == EMPTY_DATABASE)
						printf("The DataBase is empty!!\n");
					else if(res == FAILURE)
						printf("Word not found!!!\n");
					break;
				}
			case 4:
				{
					int res = save_database(arr);
					if(res == SUCCESS)
						printf("DataBase saved successfully!!!\n");
					else if(res == EMPTY_DATABASE)
						printf("DataBase is empty!!\n");
					else
						printf("DataBase was not saved!!\n");
					break;
				}
			case 5:
				{
					if(db_updated == 1)
					{
						printf("Database already updated!!\n");
						break;
					}

					if(db_created == 1)
					{
						printf("Update not allowed after Create DB!!\n");
						break;
					}

					if(update_database(arr, &bkp_head) == SUCCESS)
					{
						db_updated = 1;
						printf("Database updated successfully!!!\n");
					}
					else
						printf("Database not updated!!!\n");

					break;
				}
			case 6:
				printf("Exiting....\n");
				return SUCCESS;
			default:
				printf("Enter correct option!!\n");

		}

	}while(opt != 6);

	/* Freeing the memory of the dynamically allocated lists */
	free_database(arr);
	free_flist(head);

	return SUCCESS;
}
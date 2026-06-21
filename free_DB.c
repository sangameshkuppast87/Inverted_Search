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


/* Function to free the memory of the list which is holding the valid file names */
void free_flist(Flist *head)
{
    while(head != NULL)
    {
        Flist *temp = head;
        head = head -> link;

        free(temp -> fname);
        free(temp);
    }
}

/* Function to free memory of subnodes */
void free_sub_list(sub_node *head)
{
    while (head != NULL)
    {
        sub_node *temp = head;
        head = head -> sub_link;

        free(temp -> file_name);
        free(temp);
    }
}

/* Functions to free memory of main nodes */
void free_main_list(main_node *head)
{
    while (head != NULL)
    {
        main_node *temp = head;
        head = head -> main_link;

        free(temp -> word);                 
        free_sub_list(temp -> sub_link);    
        free(temp);                       
    }
}

/* Function to free the memory of database */
void free_database(main_node *arr[27])
{
    for (int i = 0; i < 27; i++)
    {
        if (arr[i] != NULL)
        {
            free_main_list(arr[i]);
            arr[i] = NULL;
        }
    }
}
#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

#define SUCCESS 1
#define FAILURE 0
#define FILE_NOT_FOUND -1
#define FILE_EMPTY -2
#define NON_EMPTY_DATABASE -3
#define EMPTY_DATABASE -4

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Flist
{
	char *fname;
	struct Flist *link;
}Flist;

typedef struct sub
{
	char *file_name;
	int word_count;
	struct sub *sub_link;
}sub_node;

typedef struct main
{
	int file_count;
	char *word;
	struct sub *sub_link;
	struct main *main_link;
}main_node;

/* Function to read and validate command line arguments  */
int read_validate(int argc, char *argv[], Flist **head);

/* Function to check the extension of the file */
int check_extension(char *str);

/* Function to check the file existence and emptyness */
int check_file_existence_and_emptyness(char *file);

/* Function to remove the duplicate file names */
void remove_duplicates(char *argv[], int valid[], int *size);

/* Function to insert the file name at the last */
int insert_at_last(Flist **head, char *file);

/* Function to print the valid files */
void print_valid_files(Flist *head);

/* Function to create the database */
int create_database(main_node *arr[27], Flist *head);

/* Function to get the index */
int check_for_index(char ch);

/* Functio to create the main node */
main_node  *create_main_node(char word[], char fname[], int file_count);

/* Function to create sub node */
sub_node *create_sub_node(char fname[], int word_count);

/* Function to display the database */
void display_database(main_node *arr[27]);

/* Function to free the valid files list */
void free_flist(Flist *head);

/* Function to free the subnode */
void free_sub_node(sub_node *head);

/* Function to free the main node */
void free_main_mode(main_node *head);

/* Function to free the database */
void free_database(main_node *arr[27]);

/* Function to search for the word in the database */
int search_database(main_node *arr[27]);

/* Function to validate the backup file during the update function */
int validate_back_up_file(char *file);

/* Function to save the database to the backup file */
int save_database(main_node *arr[27]);
 
/* Function to update the database using the backup file*/
int update_database(main_node *arr[27], Flist **bkp_head);

/* Function to validate the file during the save database function */
int validate_file(char *file);

/* Function to check if the file is already present in the lists */
int check_already_present(Flist *head, char *fname);

/* Function to get the unique files from the lists */
Flist* get_unique_files(Flist *bkp_head, Flist *head);

int read_and_validate(char *argv[], Flist **head, int argc);
int valid_files(char *file);
#endif
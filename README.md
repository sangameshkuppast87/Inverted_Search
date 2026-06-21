# Inverted_Search


This project implements an Inverted Search Engine in C, designed to efficiently index and search keywords across multiple text files. Instead of scanning files repeatedly, the program builds an inverted index that maps each word to the files in which it appears along with its frequency, enabling fast and scalable searches.


## ⚙️ Features

Create an inverted index from multiple input text files

Search for a keyword and display the files in which it appears

Display the complete indexed database

Save the database to a backup file

Restore / update the database from a backup file

Avoids duplicate indexing of files

Efficient memory management using dynamic allocation

## 🛠️ Technologies Used

**Language:** C (Advanced C)

**Data Structures:** Hash Tables, Linked Lists

**Concepts:**

Dynamic memory management

String processing

File handling

Command-line arguments

**Build Tool:** Makefile

**Compiler:** GCC

## 📂 Project Structure

├── main.c            # Entry point and menu handling\
├── header.h          # Structure definitions and function prototypes\
├── create_DB.c       # Database creation logic\
├── display.c         # Display indexed database\
├── search_DB.c       # Search functionality\
├── update_DB.c       # Update database from backup\
├── save_DB.c         # Save database to file\
├── free_DB.c         # Memory deallocation\
├── validation.c      # Input and file validation\
├── Makefile          # Build automation\
├── 1example.txt      # Sample input file\
├── 2example.txt      # Sample input file\
├── 3example.txt      # Sample input file\
├── bkp.txt           # Backup file

## 🚀 How to Build

Make sure gcc and make are installed.

```bash
make
```

This will generate the executable file.

## ▶️ How to Run

Provide one or more text files as command-line arguments:
```bash
./a.out 1example.txt 2example.txt 3example.txt
```

## 📋 Menu Operations

Once the program starts, you can perform the following operations:

Create Database – Builds the inverted index from input files

Display Database – Shows all indexed words with file details

Search – Searches for a specific keyword

Save Database – Saves the index to a backup file

Update Database – Restores the index from backup

Exit – Frees memory and exits safely

## 🧠 Key Learnings

Understood inverted indexing, a core concept used in search engines

Strengthened knowledge of hash tables and linked lists

Gained hands-on experience with string parsing and file processing

Implemented efficient collision handling and database persistence

Improved debugging and modular programming skills

## 📈 Future Enhancements

Case-insensitive searching

Stop-word filtering

Support for larger datasets

Sorting results by frequency

Improved CLI with command-based execution

## 👤 Author

**Sangamesh Kuppast**

# Library Management System

## Overview

This is a simple console-based Library Management System implemented in C. It allows users to add, search, display, and delete books from a library catalog. The program utilizes a hash table to store and manage books based on their ISBN numbers.

## Features

1. **Add Book**: Allows users to add a new book to the library catalog.
2. **Search Book**: Searches for a book using its ISBN.
3. **Display All Books**: Displays all the books currently in the catalog.
4. **Delete Book**: Deletes a book from the catalog using its ISBN.
5. **Exit**: Exits the program.

## Data Structure

The program uses a **hash table** to store books, with each book being represented as a linked list node in case of collisions.

### Book Structure

```c
typedef struct Book
{
    char isbn[ISBN_LENGTH];
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int available;
    struct Book *next;
} Book;
```

### Hash Function

A simple hash function sums up the ASCII values of the characters in the ISBN and takes the modulus with the table size.

```c
int hashFunction(char *isbn)
{
    int sum = 0;
    for (int i = 0; isbn[i] != '\0'; i++)
    {
        sum += isbn[i];
    }
    return sum % TABLE_SIZE;
}
```

## How to Use

1. **Compile the Code**: Use the following command to compile the program:
   ```bash
   gcc lms.c -o lms
   ```
2. **Run the Program**:

   ```bash
   ./lms
   ```

3. **Follow the Menu Options**:
   - **1. Add Book**: Input the ISBN, title, author, and availability status.
   - **2. Search Book**: Enter the ISBN to search for a book.
   - **3. Display All Books**: View all the books currently in the catalog.
   - **4. Delete Book**: Enter the ISBN to delete a book.
   - **5. Exit**: Close the program.

## Code Structure

### Functions

1. **createBook**: Creates a new book record.
2. **hashFunction**: Generates an index based on the ISBN.
3. **insertBook**: Inserts a book into the hash table.
4. **searchBook**: Searches for a book by ISBN.
5. **displayBooks**: Displays all books in the catalog.
6. **deleteBook**: Deletes a book by ISBN.
7. **main**: Manages user interactions and menu options.

## Example Interaction

```
Library Management System
1. Add Book
2. Search Book
3. Display All Books
4. Delete Book
5. Exit
Enter your choice: 1
Enter ISBN: 9781234567890
Enter Title: Programming in C
Enter Author: John Doe
Enter Availability (1 for Yes, 0 for No): 1
Book added successfully.

Enter your choice: 3
Books in the Library:
ISBN: 9781234567890, Title: Programming in C, Author: John Doe, Available: 1

Enter your choice: 2
Enter ISBN to search: 9781234567890
Book found: ISBN: 9781234567890, Title: Programming in C, Author: John Doe, Available: 1
```

## Notes

- Make sure to enter valid ISBNs and details.
- The program currently does not handle invalid input types robustly.
- Hash collisions are managed using chaining (linked lists).

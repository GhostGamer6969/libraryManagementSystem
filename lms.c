#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10
#define ISBN_LENGTH 13
#define TITLE_LENGTH 100
#define AUTHOR_LENGTH 50

// Book structure
typedef struct Book
{
    char isbn[ISBN_LENGTH];
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    int available;
    struct Book *next;
} Book;

// Hash Table array
Book *hashTable[TABLE_SIZE];

// Function to create a new book
Book *createBook(char *isbn, char *title, char *author, int available)
{
    Book *newBook = (Book *)malloc(sizeof(Book));
    strcpy(newBook->isbn, isbn);
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->available = available;
    newBook->next = NULL;
    return newBook;
}

// Hash function to generate index from ISBN
int hashFunction(char *isbn)
{
    int sum = 0;
    for (int i = 0; isbn[i] != '\0'; i++)
    {
        sum += isbn[i];
    }
    return sum % TABLE_SIZE;
}

// Insert a book into the hash table
void insertBook(Book *book)
{
    int index = hashFunction(book->isbn);
    book->next = hashTable[index];
    hashTable[index] = book;
}

// Search for a book by ISBN
Book *searchBook(char *isbn)
{
    int index = hashFunction(isbn);
    Book *current = hashTable[index];
    while (current != NULL)
    {
        if (strcmp(current->isbn, isbn) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Display all books in the library
void displayBooks()
{
    printf("Books in the Library:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Book *current = hashTable[i];
        while (current != NULL)
        {
            printf("ISBN: %s, Title: %s, Author: %s, Available: %d\n",
                   current->isbn, current->title, current->author, current->available);
            current = current->next;
        }
    }
}

// Delete a book by ISBN
void deleteBook(char *isbn)
{
    int index = hashFunction(isbn);
    Book *current = hashTable[index];
    Book *previous = NULL;

    while (current != NULL && strcmp(current->isbn, isbn) != 0)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Book not found.\n");
        return;
    }

    if (previous == NULL)
    {
        hashTable[index] = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    free(current);
    printf("Book deleted successfully.\n");
}

// Main function
int main()
{
    int choice;
    char isbn[ISBN_LENGTH], title[TITLE_LENGTH], author[AUTHOR_LENGTH];
    int available;

    while (1)
    {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Search Book\n");
        printf("3. Display All Books\n");
        printf("4. Delete Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter ISBN: ");
            scanf("%s", isbn);
            printf("Enter Title: ");
            getchar(); // to consume newline
            fgets(title, TITLE_LENGTH, stdin);
            title[strcspn(title, "\n")] = 0; // remove newline
            printf("Enter Author: ");
            fgets(author, AUTHOR_LENGTH, stdin);
            author[strcspn(author, "\n")] = 0; // remove newline
            printf("Enter Availability (1 for Yes, 0 for No): ");
            scanf("%d", &available);
            insertBook(createBook(isbn, title, author, available));
            printf("Book added successfully.\n");
            break;

        case 2:
            printf("Enter ISBN to search: ");
            scanf("%s", isbn);
            Book *book = searchBook(isbn);
            if (book)
            {
                printf("Book found: ISBN: %s, Title: %s, Author: %s, Available: %d\n",
                       book->isbn, book->title, book->author, book->available);
            }
            else
            {
                printf("Book not found.\n");
            }
            break;

        case 3:
            displayBooks();
            break;

        case 4:
            printf("Enter ISBN to delete: ");
            scanf("%s", isbn);
            deleteBook(isbn);
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

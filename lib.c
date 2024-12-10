#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_STRING 100

// Struktur data untuk buku
typedef struct {
    int id;
    char title[MAX_STRING];
    char author[MAX_STRING];
    int year;
} Book;

Book library[MAX_BOOKS];
int book_count = 0;

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk menampilkan menu
void displayMenu() {
    printf("=============================\n");
    printf("    Library System Menu\n");
    printf("=============================\n");
    printf("1. Read/Load Books from File\n");
    printf("2. Add Book\n");
    printf("3. Display Books\n");
    printf("4. Sort Books by ID\n");
    printf("5. Write/Update Books to File\n");
    printf("6. Report\n");
    printf("7. Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
}

// Fungsi untuk menambahkan buku
void addBook() {
    if (book_count >= MAX_BOOKS) {
        printf("================\n");
        printf("Library is Full!\n");
        printf("================\n");
        return;
    }

    char choice[5];
    do{
        printf("=============================================\n");
        printf("            Add Book to Library\n");
        printf("=============================================\n");

        printf("Enter Book ID (Only Numbers)                : ");
        scanf("%d", &library[book_count].id); getchar();

        printf("Enter Book Title (Uppercase At 1st Letter)  : "); 
        fgets(library[book_count].title, MAX_STRING, stdin);
        library[book_count].title[strcspn(library[book_count].title, "\n")] = 0; // Hilangkan newline
        if (library[book_count].title[0] >= 'a' && library[book_count].title[0] <= 'z') {
        library[book_count].title[0] = toupper(library[book_count].title[0]);
        }

        printf("Enter Author Name (Uppercase At 1st Letter) : ");
        fgets(library[book_count].author, MAX_STRING, stdin);
        library[book_count].author[strcspn(library[book_count].author, "\n")] = 0;
        if (library[book_count].author[0] >= 'a' && library[book_count].author[0] <= 'z') {
        library[book_count].author[0] = toupper(library[book_count].author[0]);
        }

        printf("Enter Publication Year (Only Numbers)       : ");
        scanf("%d", &library[book_count].year);
        getchar();

        book_count++;
        printf("=============================================\n");
        printf("         Book Added Successfully!\n");
        printf("=============================================\n");

        printf("Do You Want to Add Another Book? (Yes/No): ");
        scanf("%s", choice); getchar();
        clearTerminal();
    }while(strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0);
    printf("==========================\n");
    printf("Press Enter to continue...\n");
    printf("==========================\n");
    getchar();
}

// Fungsi untuk menampilkan semua buku
void displayBooks() {
    if (book_count == 0) {
        printf("==================================\n");
        printf("No Books Available in The Library.\n");
        printf("==================================\n");
        return;
    }
    printf("==============================================================================\n");
    printf("| %-5s | %-30s | %-20s | %-10s |\n", "ID", "Title", "Author", "Year");
    printf("==============================================================================\n");
    for (int i = 0; i < book_count; i++) {
        printf("| %-5d | %-30s | %-20s | %-10d |\n", 
            library[i].id, library[i].title, library[i].author, library[i].year);
    }
    printf("==============================================================================\n");
}

// Fungsi untuk menyortir buku berdasarkan judul
void sortBooks() {
    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            if (library[j].id > library[j + 1].id) {
                Book temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }
    printf("===================\n");
    printf("Books Sorted by ID.\n");
    printf("===================\n");
}

// Fungsi untuk membaca buku dari file
void readFromFile() {
    FILE *file = fopen("library.txt", "r");
    if (!file) {
        printf("====================\n");
        printf("Could Not Open File.\n");
        printf("====================\n");
        return;
    }
    book_count = 0;
    while (fscanf(file, "ID          : %d\nTitle     : %[^\n]\nAuthor    : %[^\n]\nYear      : %d\n\n", 
                  &library[book_count].id, library[book_count].title,
                  library[book_count].author, &library[book_count].year) != EOF) {
        book_count++;
    }
    fclose(file);
    printf("=======================\n");
    printf("Books Loaded From File.\n");
    printf("=======================\n");
}

// Fungsi untuk menulis buku ke file dengan format baru
void writeToFile() {
    FILE *file = fopen("library.txt", "w");
    if (!file) {
        printf("====================\n");
        printf("Could Not Open File.\n");
        printf("====================\n");
        return;
    }
    for (int i = 0; i < book_count; i++) {
        fprintf(file, "ID        : %d\nTitle     : %s\nAuthor    : %s\nYear      : %d\n\n",
                library[i].id, library[i].title, library[i].author, library[i].year);
    }
    fclose(file);
    printf("====================\n");
    printf("Books Saved to File.\n");
    printf("====================\n");
}

// Fungsi untuk menampilkan laporan
void report() {
    printf("==========================\n");
    printf("     Library Report:\n");
    printf("==========================\n");
    printf("Total Books     : %d\n", book_count);
    int oldestYear = 9999, newestYear = 0;
    for (int i = 0; i < book_count; i++) {
        if (library[i].year < oldestYear) oldestYear = library[i].year;
        if (library[i].year > newestYear) newestYear = library[i].year;
    }
    if (book_count > 0) {
        printf("Oldest Book Year: %d\n", oldestYear);
        printf("Newest Book Year: %d\n", newestYear);
        printf("==========================\n");
    }
}


void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Fungsi utama
int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice); getchar();
        clearTerminal();
        switch (choice) {
            case 1:
                readFromFile();
                waitForEnter();
                clearTerminal();
                break;
            case 2:
                addBook();
                clearTerminal();
                break;
            case 3:
                displayBooks();
                waitForEnter();
                clearTerminal();
                break;
            case 4:
                sortBooks();
                waitForEnter();
                clearTerminal();
                break;
            case 5:
                writeToFile();
                waitForEnter();
                clearTerminal();
                break;
            case 6:
                report();
                waitForEnter();
                clearTerminal();
                break;
            case 7:
                printf("=========================\n");
                printf("Exiting program. Goodbye!\n");
                printf("=========================\n");
                break;
            default:
                printf("=========================\n");
                printf("Invalid choice. Try again.\n");
                printf("=========================\n");
        }
    } while (choice != 7);

    return 0;
}
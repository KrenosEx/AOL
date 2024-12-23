#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Untuk strcpy, strcpsn
#include <ctype.h> // Untuk toupper
#include <stdbool.h> // Mengembalikan nilai true & false

#define MAX_BOOKS 100 // Membatasi jumlah buku
#define MAX_STRING 100 // Membatasi panjang string

// Struktur data untuk buku
typedef struct {
    int id;
    char title[MAX_STRING];
    char author[MAX_STRING];
    int year;
    bool isBorrowed;
} Book;

Book library[MAX_BOOKS];
int book_count = 0;

// Fungsi untuk membersihkan terminal ketika dipanggil
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
    printf("4. Sort Books\n");
    printf("5. Write/Update Books to File\n");
    printf("6. Report\n");
    printf("7. Search Book by ID\n");
    printf("8. Delete Book by ID\n");
    printf("9. Borrow Book\n");
    printf("10. Return Book\n");
    printf("11. Exit\n");
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

        while (1) { // Memastikan user memasukkan angka
        printf("Enter Book ID (Only Numbers) : ");
        if (scanf("%d", &library[book_count].id) != 1) {
            printf("Invalid input. Try again.\n"); 
            while (getchar() != '\n');
            continue;
        }
        getchar();
        break;
        }

        printf("Enter Book Title (Uppercase At 1st Letter)  : "); 
        fgets(library[book_count].title, MAX_STRING, stdin);
        library[book_count].title[strcspn(library[book_count].title, "\n")] = 0; // Menghilangkan newline
        if (library[book_count].title[0] >= 'a' && library[book_count].title[0] <= 'z') {
        library[book_count].title[0] = toupper(library[book_count].title[0]); 
        // Ubah huruf awal menjadi huruf besar jika user memasukkan huruf kecil
        }

        printf("Enter Author Name (Uppercase At 1st Letter) : ");
        fgets(library[book_count].author, MAX_STRING, stdin);
        library[book_count].author[strcspn(library[book_count].author, "\n")] = 0;
        if (library[book_count].author[0] >= 'a' && library[book_count].author[0] <= 'z') {
        library[book_count].author[0] = toupper(library[book_count].author[0]);
        }

        while (1) {
        printf("Enter Publication Year (Only Numbers)       : ");
        if (scanf("%d", &library[book_count].year) != 1) {
            printf("Invalid input. Try again.\n"); 
            while (getchar() != '\n');
            continue;
        }
        getchar();
        break;
        }

        library[book_count].isBorrowed = 0;
        book_count++;
        printf("=============================================\n");
        printf("         Book Added Successfully!\n");
        printf("=============================================\n");

        printf("Do You Want to Add Another Book? (Yes/No): "); // Meminta user apakah ingin menambahkan buku lagi
        scanf("%s", choice); getchar();
        clearTerminal();
    }while(strcmp(choice, "Yes") == 0 || strcmp(choice, "yes") == 0); // Jika iya maka looping akan dilanjutkan
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
    printf("=============================================================================================\n");
    printf("| %-5s | %-30s | %-20s | %-10s | %-12s |\n", "ID", "Title", "Author", "Year", "Status");
    printf("=============================================================================================\n");
    for (int i = 0; i < book_count; i++) {
        printf("| %-5d | %-30s | %-20s | %-10d | %-12s |\n", 
            library[i].id, library[i].title, library[i].author, library[i].year, 
            library[i].isBorrowed ? "Borrowed" : "Available");
    }
    printf("=============================================================================================\n");
}

// Fungsi untuk menyortir buku berdasarkan id dengan bubble sort
void sortBooksByID() {
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

// Fungsi untuk menyortir buku berdasarkan judul dengan bubble sort
void sortBooksByTitle() {
    for (int i = 0; i < book_count - 1; i++) {
        for (int j = 0; j < book_count - i - 1; j++) {
            if (strcmp(library[j].title, library[j + 1].title) > 0) {
                Book temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }
    printf("=====================\n");
    printf("Books Sorted by Title.\n");
    printf("=====================\n");
}

// Fungsi untuk membaca data buku dari file
void readFromFile() {
    FILE *file = fopen("library.txt", "r"); // membuka file dan membuat jika belum ada dengan nama "library.txt"
    if (!file) { // jika file tidak ditemukan
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

// Fungsi untuk menulis data buku ke file 
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
        if (library[i].year < oldestYear) oldestYear = library[i].year; // Menyimpan tahun terkecil
        if (library[i].year > newestYear) newestYear = library[i].year; // Menyimpan tahun terbesar
    }
    if (book_count > 0) {
        printf("Oldest Book Year: %d\n", oldestYear);
        printf("Newest Book Year: %d\n", newestYear);
        printf("==========================\n");
    }
}

// Fungsi untuk mencari buku berdasarkan id dengan linear search
void searchBookByID() {
    int id;
    printf("======================================\n");
    printf("Enter Book ID: ");
    scanf("%d", &id);getchar();
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) { // Mencocokkan id dengan id buku
            printf("======================================\n");
            printf("              Book Found\n");
            printf("======================================\n");
            printf("ID          : %d\n", library[i].id);
            printf("Title       : %s\n", library[i].title);
            printf("Author      : %s\n", library[i].author);
            printf("Year        : %d\n", library[i].year);
            printf("======================================\n");
            return;
        }
    }
    printf("===============\n");
    printf("Book Not Found.\n");
    printf("===============\n");
}

// Fungsi untuk menghapus buku berdasarkan id
void deleteBookByID() {
    int id;
    printf("===============\n");
    printf("Enter Book ID: ");
    scanf("%d", &id); getchar();
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) { // Mencocokkan id dengan id buku
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1];
            }
            book_count--;
            printf("===============\n");
            printf("Book Deleted.\n");
            printf("===============\n");
            return;
        }
    }
    printf("===============\n");
    printf("Book Not Found.\n");
    printf("===============\n");
}

// Fungsi untuk meminjam buku
void borrowBook() {
    int id;
    printf("=====================================\n");
    printf("Enter Book ID to Borrow: ");
    scanf("%d", &id); getchar();
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (library[i].isBorrowed) {
                printf("=============================\n");
                printf("This book is already borrowed.\n");
                printf("=============================\n");
                return;
            }
            library[i].isBorrowed = 1; // Mengubah status buku menjadi "borrowed"
            printf("===========================\n");
            printf("You have borrowed the book: %s\n", library[i].title);
            printf("===========================\n");
            return;
        }
    }
    printf("===============\n");
    printf("Book Not Found.\n");
    printf("===============\n");
}

// Fungsi untuk mengembalikan buku
void returnBook() {
    int id;
    printf("=====================================\n");
    printf("Enter Book ID to Return: ");
    scanf("%d", &id); getchar();
    for (int i = 0; i < book_count; i++) {
        if (library[i].id == id) {
            if (!library[i].isBorrowed) {
                printf("==========================\n");
                printf("This book was not borrowed.\n");
                printf("==========================\n");
                return;
            }
            library[i].isBorrowed = 0; // Mengubah status buku menjadi "available"
            printf("===========================\n");
            printf("You have returned the book: %s\n", library[i].title);
            printf("===========================\n");
            return;
        }
    }
    printf("===============\n");
    printf("Book Not Found.\n");
    printf("===============\n");
}

// Fungsi untuk menunggu enter dari user
void waitForEnter() {
    printf("\nPress Enter to continue...");
    getchar();
}

// Fungsi utama
int main() {
    int choice,choicesort;
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
                // Pilih sorting berdasarkan apa
                printf("================\n");
                printf("Sort By:\n");
                printf("================\n");
                printf("1. Sort by ID\n");
                printf("2. Sort by Title\n");
                printf("================\n");
                printf("Enter your choice: ");
                scanf("%d", &choicesort); getchar();
                clearTerminal();
                switch(choicesort) {
                    case 1:
                        sortBooksByID();
                        waitForEnter();
                        clearTerminal();
                        break;
                    case 2:
                        sortBooksByTitle();
                        waitForEnter();
                        clearTerminal();
                        break;
                }
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
                searchBookByID();
                waitForEnter();
                clearTerminal();
                break;
            case 8:
                deleteBookByID();
                waitForEnter();
                clearTerminal();
                break;
            case 9:
                borrowBook();
                waitForEnter();
                clearTerminal();
                break;
            case 10:
                returnBook();
                waitForEnter();
                clearTerminal();
                break;
            case 11:
                printf("=========================\n");
                printf("Exiting program. Goodbye!\n");
                printf("=========================\n");
                break;
            default:
                printf("=========================\n");
                printf("Invalid choice. Try again.\n");
                printf("=========================\n");
        }
    } while (choice != 11); // Selama user tidak input 11, maka program akan terus berjalan

    return 0;
}
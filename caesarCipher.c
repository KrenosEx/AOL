#include <stdio.h>
#include <string.h> // Untuk strcpy dalam manipulasi string

// Fungsi menu ketika ingin mengulang program
void menu(int *choice) {
    printf("=====================================\n");
    printf("Welcome to the Caesar Cipher Program!\n");
    printf("   Please Choose an Option Again!\n");
    printf("=====================================\n");
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("3. Exit The Program\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
    scanf("%d", choice); getchar();
}

// Fungsi untuk menunggu enter dari user untuk lanjut
void waitForEnter() {
    printf("Press Enter to continue..."); getchar(); 
}

// Fungsi untuk enkripsi
void encrypt() {
    char plaintext[100];
    char ciphertext[100];
    int key;

    printf("======================\n");
    printf("Welcome to Encryption!\n");
    printf("======================\n");
    printf("Please Enter plaintext: ");
    scanf("%99[^\n]", plaintext); getchar(); // input user dengan batas maksimum 99 karakter
    printf("Please Enter the Cipher Key: ");
    scanf("%d", &key); getchar(); // berisi angka yang akan digunakan sebagai kunci enkripsi berapa kali
    // Untuk mengatasi adanya huruf besar dan kecil, maka kami gunakan if untuk membandingkan huruf besar dan kecil
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') { 
            plaintext[i] = ((plaintext[i] - 'a' + key) % 26) + 'a'; 
            // Menambahkan key ke plaintext dan mengembalikan ke plaintext berdasarkan ASCII
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {  
            plaintext[i] = ((plaintext[i] - 'A' + key) % 26) + 'A';
        }
    }
    strcpy(ciphertext, plaintext); // Menyalin plaintext ke ciphertext
    printf("The Ciphertext: %s\n", ciphertext);
    puts("");
}

// Fungsi untuk dekripsi
void decrypt() {
    char ciphertext[100];
    char plaintext[100];
    int key;

    printf("======================\n");
    printf("Welcome to Decryption!\n");
    printf("======================\n");
    printf("Please Enter ciphertext: ");
    scanf("%99[^\n]", ciphertext); getchar(); 

    printf("Please Enter the cipher key: ");
    scanf("%d", &key); getchar(); 

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') { 
            ciphertext[i] = ((ciphertext[i] - 'a' - key + 26) % 26) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {  
            ciphertext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
        }
    }
    strcpy(plaintext, ciphertext);
    printf("The Plaintext: %s\n", plaintext);
    puts("");
}

// Fungsi untuk membersihkan terminal ketika dipanggil
void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    int choice = 0;

    printf("=====================================\n");
    printf("Welcome to the Caesar Cipher Program!\n");
    printf("=====================================\n");
    waitForEnter();
    clearTerminal();
    printf("=============================\n");
    printf("Menu Of Caesar Cipher Program\n");
    printf("=============================\n");
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("3. Exit The Program\n");
    printf("=============================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice); getchar();

    while (choice != 3) { // Selama user tidak input 3, maka program akan terus berjalan  
        clearTerminal();

        switch (choice) {
            case 1:
                encrypt();
                waitForEnter();
                clearTerminal();
                menu(&choice);
                break;

            case 2:
                decrypt();
                waitForEnter();
                clearTerminal();
                menu(&choice);
                break;
                
            default:
                printf("Invalid choice. Please try again!\n");
                puts("");
                waitForEnter();
                clearTerminal();
                menu(&choice);
                break;
        }
    } 
    clearTerminal();
    printf("=====================\n");
    printf("Goodbye and Thankyou!\n");
    printf("=====================\n"); 
    return 0;
}

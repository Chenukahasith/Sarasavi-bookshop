#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BOOKS 100
#define STOCK_THRESHOLD 5
//for sleep function
#include <windows.h> 
#include <unistd.h>

//check this is windows
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

//add color to increse UI
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define YELLOW  "\x1b[33m"
#define RED "\x1b[31m"
#define RESET   "\x1b[0m"

//Define Book Structure
struct book{
    int id;
    char title[100];
    char author[100];
    float price;
    int stockqty;
};

struct Bill {
    int billID;
    char bookTitle [100];
    int quantity;
    float unitPrice;
    float total;
    };


typedef struct{
    int id;
    char title[100];
    int quantity;
}Books;

Books bookList[MAX_BOOKS];
int totalBooks=0;

// Global book array and book count
struct book* books = NULL;

//Global Veriable
char usersName[50];
int bookCount = 0;

//Frist time menu error Fix
int i=0;

//Function PhotoType
void mainMenu();
void addNewBook();
int validateID(int validID);
void viewAllBooks();
void deleteBook();
void sellBookAndGenerateBill();
void updateBookInformation();
void searchBook();
void viewSalesReport ();
void viewLowStockAlerts();

int main() {
    //Frist user Interface
    printf("\n");
    printf("\n");
    printf(CYAN);
    printf(" __      __           .__                                        \n");
    printf("/  \\    /  \\   ____   |  |     ____     ____     _____     ____  \n");
    printf("\\   \\/\\/   / _/ __ \\  |  |   _/ ___\\   /  _ \\   /     \\  _/ __ \\ \n");
    printf(" \\        /  \\  ___/  |  |__ \\  \\___  (  <_> ) |  Y Y  \\ \\  ___/ \n");
    printf("  \\__/\\  /    \\___  > |____/  \\___  >  \\____/  |__|_|  /  \\___  >\n");
    printf("       \\/         \\/              \\/                 \\/       \\/ \n");
    printf(RESET);
    
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Booting system...\n");
    sleep(2);

    printf("\n");
    printf(RED "[OK] " RESET "Books loaded\n");
    sleep(1);
    
    printf("\n");
    printf(RED "[OK] " RESET "Sales database connected\n\n");
    sleep(1);

    // Login User
    printf("\n");
    printf("ENTER YOUR FIRST NAME TO LOGIN:\n");
    printf(">> ");
    scanf("%s",usersName);

    //Now create first interface
    system(CLEAR);
    printf("\n");
    printf("\n=====================================================================\n");
    printf(RED"\n                      SARASAVI BOOK STORE                       \n "RESET);
    printf(GREEN"   [ Hello, %s! Time to stack stories and sell dreams ]\n",usersName);
    printf(RESET"\n=====================================================================\n");
    mainMenu();
    return 0;
}




//check Valid Id
int validateID(int validID){
    int digit=0;
    int temp= validID;
    if(temp==0){
        digit=1;
    }else{
        while(temp>0){
            temp/=10;
            digit++;
        }
    }
    return digit;
}

//main menu implement
void mainMenu(){
    int chooseNumber;
    char yesOrNo='Y';

    do{
        
        if(i==1){
            system(CLEAR);
            printf("\n");
            printf("\n=====================================================================\n");
            printf(RED"\n                        SARASAVI BOOK STORE                       \n "RESET);
            printf(GREEN"   [ Hello, %s! Time to stack stories and sell dreams ]\n",usersName);
            printf(RESET"\n=====================================================================\n");
            printf("\n");
        }

        
        i=1;
        printf("\n");
        printf(YELLOW"1. Add New Book\n");
        printf("\n2. View All Books\n");
        printf("\n3. Search Book by Title or ID\n");
        printf("\n4. Delete a Book\n");
        printf("\n5. Sell Book / Generate Bill\n");
        printf("\n6. View Sales Report\n");
        printf("\n7. Update Book Information\n");
        printf("\n8. View Low Stock Alerts\n");
        printf("\n9. Exit\n"RESET);
        printf("\n");
        
        //End the creating interface
        printf("\nChoose an option, %s [1-9]: ",usersName);
        scanf("%d",&chooseNumber);

        //User choose Number Validation
        switch (chooseNumber){
        case 1:
        addNewBook();
            break;
        case 2:
            viewAllBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            deleteBook();
            break;
            case 5:
            sellBookAndGenerateBill();
            break;
        case 6:
            viewSalesReport ();
            break;
        case 7:
            updateBookInformation();
            break;
        case 8:
            viewLowStockAlerts();
            break;
        case 9:
            printf(GREEN"\n[ Goodbye, %s! Thank you for visiting Sarasavi Book Store. ]\n\n"RESET, usersName);
            exit(0);
        default:
            printf(RED"\n[ Oops! That's not on our menu. Please choose a valid option. ]\n"RESET);
            while(getchar() != '\n');
            continue;
        }

        //get input from user
        printf("\nWould you like to return to the main menu? (y/n): ");
        scanf(" %c",&yesOrNo);
        
    }while(yesOrNo=='y' || yesOrNo=='Y');

    printf(GREEN"\n[Session ended. Thank you! ]\n"RESET);
    printf("\n");
    exit(1);
}

//Add New Book
void addNewBook(){
    unsigned int bookID;
    int error=0;
    char yesOrNo;
    char choice=0;

    FILE *file;


    //Interface
    system(CLEAR);
    printf("\n");
    printf("\n");
    printf("----------------------------------------------------------------------\n");
    printf(RED"\n                            ADD NEW BOOK                             \n"RESET);
    printf("\n----------------------------------------------------------------------\n");

    //End The header


    do {
        struct book newBook;

        while (1) {
            printf("\n");
            printf("\n");
            printf("\n\x1b[33mEnter Book ID [4 digits] : \x1b[0m");
            scanf("%d", &bookID);

            error = validateID(bookID);
            if (error == 4) {
                newBook.id = bookID;
                break;
            } else {
                printf("\n\x1b[31m[ Please enter a valid 4-digit Book ID \x1b[0m]\n");
                printf("\nWould you like to try again? [y/n]: ");
                scanf(" %c", &yesOrNo);
                if (yesOrNo == 'n' || yesOrNo == 'N') {
                    printf("\n[ Returning to main menu... ]\n");
                    return;
                }
            }
        }



        // Get other book info
        printf("\n\x1b[33mEnter Book Title         : \x1b[0m");
        getchar(); // clear newline from buffer
        fgets(newBook.title, sizeof(newBook.title), stdin);
        newBook.title[strcspn(newBook.title, "\n")] = 0;

        printf("\n\x1b[33mEnter Author Name        : \x1b[0m");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = 0;

        printf("\n\x1b[33mEnter Book Price         : \x1b[0m");
        scanf("%f", &newBook.price);

        printf("\n\x1b[33mEnter Stock Quantity    : \x1b[0m");
        scanf("%d", &newBook.stockqty);

        books = realloc(books, (bookCount + 1) * sizeof(struct book));
        if (books == NULL) {
            printf("\x1b[31mMemory allocation failed.\n\x1b[0m");
            exit(1);
        }

        books[bookCount] = newBook;
        bookCount++;

        // Save in file
        file = fopen("books.txt", "a");
        if (file == NULL) {
            printf("\n\x1b[31m[ Error opening file! Data not saved. ]\n\x1b[0m");
        } else {
            fprintf(file, "%d,%s,%s,%.2f,%d\n", newBook.id, newBook.title, newBook.author, newBook.price, newBook.stockqty);
            fclose(file);
        }

        //added succes interface
        printf(GREEN"\n ------------------------------------");
        printf("\n|     Book added successfully!       |\n");
        printf(" ------------------------------------\n"RESET);

        // Ask to add another
        printf("\nDo you want to add another book? (y/n): ");
        scanf(" %c", &choice);
        if(choice == 'n' || choice == 'N'){
            mainMenu();
        }

    } while (choice == 'y' || choice == 'Y');
}

//view all book

void viewAllBooks() {
    system(CLEAR);
    FILE *file = fopen("books.txt", "r");
    struct book tempBook;
    
    if (file == NULL) {
        printf("\n[ No book records found! Please add books first. ]\n");
        return;
    }

    printf("\n");
    printf("\n------------------------------------------------------------------------------\n");
    printf(RED"\n                             SARASAVI'S BOOKSHELF                         \n"RESET);
    printf(GREEN"                       [ Where Every Book Finds a Home! ]\n"RESET);
    printf("\n------------------------------------------------------------------------------\n");
    printf("\n");
    printf("\n");
    printf("--------------------------------------------------------------------------------\n");
    printf(GREEN"%-10s %-30s %-20s %-10s %-10s\n", "Book ID", "Title", "Author", "Price", "Stock"RESET);
    printf("--------------------------------------------------------------------------------\n");
    printf("\n");


    while (fscanf(file,"%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
        printf(YELLOW"%-10d %-30s %-20s %-10.2f   %-10d\n\n"RESET, tempBook.id, tempBook.title, tempBook.author, tempBook.price, tempBook.stockqty);
    }

    fclose(file);
}


//search books

void searchBook() {
    system(CLEAR);
    int searchID, found = 0;
    char searchTitle[100];
    char choice;

    struct book tempBook;
    FILE *file = fopen("books.txt", "r");

    if (file == NULL) {
        printf("\n[ No book records found! Please add books first. ]\n");
        return;
    }

    printf("\n----------------------------------------------------------------------\n");
    printf(RED"\n                    SEARCH BOOK BY TITLE OR ID\n"RESET);
    printf(GREEN"              [ Find it. Love it. Return for More! ]\n"RESET);
    printf("\n----------------------------------------------------------------------\n");

    printf(GREEN"\nSearch by:"RESET);
    printf(YELLOW"\n\n1. Book ID\n");
    printf("\n2. Book Title\n"RESET);
    printf("\n\nChoose an option [1/2]:");
    scanf(" %c", &choice);

    if (choice == '1') {
        printf(YELLOW"\n\nEnter Book ID: "RESET);
        scanf("%d", &searchID);

        while (fscanf(file, "%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
            if (tempBook.id == searchID) {
                found = 1;

                printf("\n");
                printf(GREEN" -----------------\n");
                printf("|                 |\n");
                printf("|   Book Found!   |\n");
                printf("|                 |\n");
                printf(" -----------------\n"RESET);
                printf("\n");


                printf(YELLOW"ID     : %d\n", tempBook.id);
                printf("\n");
                printf("Title  : %s\n", tempBook.title);
                printf("\n");
                printf("Author : %s\n", tempBook.author);
                printf("\n");
                printf("Price  : %.2f\n", tempBook.price);
                printf("\n");
                printf("Stock  : %d\n"RESET, tempBook.stockqty);
                printf("\n");
                break;
            }
        }

    } else if (choice == '2') {
        printf("\nEnter Book Title: ");
        getchar(); // clear buffer
        fgets(searchTitle, sizeof(searchTitle), stdin);
        searchTitle[strcspn(searchTitle, "\n")] = 0;

        while (fscanf(file, "%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
            if (strcasecmp(tempBook.title, searchTitle) == 0) {
                found = 1;
                printf("\n");
                printf(GREEN" -----------------\n");
                printf("|                 |\n");
                printf("|   Book Found!   |\n");
                printf("|                 |\n");
                printf(" -----------------\n"RESET);
                printf("\n");

                printf(YELLOW"ID     : %d\n", tempBook.id);
                printf("\n");
                printf("Title  : %s\n", tempBook.title);
                printf("\n");
                printf("Author : %s\n", tempBook.author);
                printf("\n");
                printf("Price  : %.2f\n", tempBook.price);
                printf("\n");
                printf("Stock  : %d\n"RESET, tempBook.stockqty);
                printf("\n");
                break;
            }
        }
    } else {
        printf(RED"\n[ Invalid choice. Please try again. ]\n"RESET);
    }

    if (!found) {
        printf(RED"\n[ Book not found. ]\n"RESET);
    }

    fclose(file);
}



//DELETE BOOK
void deleteBook() {
    system(CLEAR);
    int deleteID, found = 0;
    struct book tempBook;
    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("\n[ Error opening files. ]\n");
        return;
    }

    printf("\n");
    printf("\n-------------------------------------------------------------------------------\n");
    printf(RED"\n                             DELETE A BOOK                        \n"RESET);
    printf(GREEN"              [ Removing a book permanently from the inventory! ]\n"RESET);
    printf("\n-------------------------------------------------------------------------------\n");
    printf("\n");

    printf(YELLOW"\nEnter the Book ID to delete: "RESET);
    scanf("%d", &deleteID);

    while (fscanf(file, "%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
        if (tempBook.id == deleteID) {
            found = 1;
            continue; // skip writing this book to temp file
        }
        fprintf(tempFile, "%d,%s,%s,%.2f,%d\n", tempBook.id, tempBook.title, tempBook.author, tempBook.price, tempBook.stockqty);
    }

    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf(GREEN"\n[ Book deleted successfully! ]\n"RESET);

    else
        printf(RED"\n[ Book ID not found. ]\n"RESET);
}



//Option -05 Impliment

void sellBookAndGenerateBill() {
    system(CLEAR);
    FILE *file = fopen("books.txt", "r");
    FILE *saleFile = fopen("sales.txt", "a");
    int bookID, quantity, found = 0;
    float totalPrice = 0;
    struct book tempBook;

    if (file == NULL || saleFile == NULL) {
        printf("\n" RED "[ Error opening files! Ensure books exist before selling. ]" RESET "\n");
        return;
    }

    printf("\n");
    printf("\n----------------------------------------------------------------------\n");
    printf(RED "                     SELL BOOK / GENERATE BILL                        \n" RESET);
    printf("\n----------------------------------------------------------------------\n");

    printf("\n\x1b[33mEnter Book ID to sell:\x1b[0m ");
    scanf("%d", &bookID);
    printf("\n");

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf(RED "\n[ Error creating temporary file. ]\n" RESET);
        fclose(file);
        fclose(saleFile);
        return;
    }

    while (fscanf(file, "%d,%[^,],%[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
        if (tempBook.id == bookID) {
            found = 1;

            printf(GREEN "\n -----------------\n");
            printf("|                 |\n");
            printf("|   Book Found!   |\n");
            printf("|                 |\n");
            printf(" -----------------\n" RESET);

            printf(CYAN"\nID     : %d\n", tempBook.id);
            printf("\n");
            printf("Title  : %s\n", tempBook.title);
            printf("\n");
            printf("Author : %s\n", tempBook.author);
            printf("\n");
            printf("Price  : %.2f\n", tempBook.price);
            printf("\n");
            printf("Stock  : %d\n\n" RESET, tempBook.stockqty);

            printf("\n");
            printf("\x1b[33mEnter quantity to sell:\x1b[0m ");
            scanf("%d", &quantity);
            printf("\n");
            printf("\n");

            if (quantity <= tempBook.stockqty) {
                totalPrice = tempBook.price * quantity;
                tempBook.stockqty -= quantity;

                // Print Bill
                printf("\n----------------------------------------------------------------------\n");
                printf(GREEN "                        SARASAVI BOOK STORE                         \n" RESET);
                printf(GREEN "                         [ Bill for %s ]                            \n" RESET, usersName);
                printf("----------------------------------------------------------------------\n\n");

                printf("Book ID          : %d\n", tempBook.id);
                printf("\n");
                printf("Book Title       : %s\n", tempBook.title);
                printf("\n");
                printf("Author           : %s\n", tempBook.author);
                printf("\n");
                printf("Unit Price (Rs.) : %.2f\n", tempBook.price);
                printf("\n");
                printf("Quantity         : %d\n", quantity);
                printf("\n");
                printf("----------------------------------------------------------------------\n");
                printf(YELLOW "Total Price (Rs.): %.2f\n" RESET, totalPrice);
                printf("======================================================================\n");

                // Write to sales.txt
                fprintf(saleFile, "%d,%s,%s,%.2f,%d,%.2f\n", tempBook.id, tempBook.title, tempBook.author, tempBook.price, quantity, totalPrice);
            } else {
                printf(RED "\nStock is not available! Only %d available.\n" RESET, tempBook.stockqty);
            }
        }

        fprintf(tempFile, "%d,%s,%s,%.2f,%d\n", tempBook.id, tempBook.title, tempBook.author, tempBook.price, tempBook.stockqty);
    }

    fclose(file);
    fclose(saleFile);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found) {
        printf(RED "\n[ Book ID not found! ]\n" RESET);
    }

    char choiceLetter;
    printf("\nWould you like to return to the main menu? (y/n): ");
    scanf(" %c", &choiceLetter);
    if (choiceLetter == 'y' || choiceLetter == 'Y') {
        mainMenu();
    } else {
        printf(GREEN "\n[ Thank you for shopping! ]\n",RESET);
    }
}

        

//Option 06 Implement-View Sale Report

void viewSalesReport() {
    system(CLEAR);
    FILE *fptr = fopen("sales.txt", "r");
    if (fptr == NULL) {
        printf("\n[!] No sales records found.\n");
        return;
    }

    struct Bill bill;
    int totalBookSold = 0;
    float grandTotal = 0.0;

    printf("\n----------------------------------------------------------------------\n");
    printf(RED"\n                             SALE REPORT                              \n"RESET);
    printf("\n----------------------------------------------------------------------\n");

    printf("\n");
    printf("\n");
    printf(YELLOW"\n----------------------------------------------------------------------\n"RESET);
    printf("| %-4s | %-25s | %-5s | %-10s | %-10s |\n",
           "ID", "Book Title", "Qty", "Unit Price", "Total");
    printf(YELLOW"----------------------------------------------------------------------\n"RESET);

    while (fscanf(fptr, "%d,%99[^,],%*[^,],%f,%d,%f\n",
                  &bill.billID, bill.bookTitle,
                  &bill.unitPrice, &bill.quantity, &bill.total) == 5) {
        printf(YELLOW"| %-4d | %-25s | %-5d | %-10.2f | %-10.2f |\n"RESET,
               bill.billID, bill.bookTitle,
               bill.quantity, bill.unitPrice, bill.total);
        totalBookSold += bill.quantity;
        grandTotal += bill.total;
    }

    printf(YELLOW"----------------------------------------------------------------------\n"RESET);
    printf("\n");
    printf(GREEN"Total Books Sold : %d\n", totalBookSold);

    printf("Total Income     : Rs %.2f\n"RESET, grandTotal);
    printf("\n");
    printf("----------------------------------------------------------------------\n");

    fclose(fptr);

    FILE *report = fopen("sales_report.txt", "w");
    if (report != NULL) {
        fprintf(report, "Total Sales: %d\n", totalBookSold);
        fprintf(report, "Total Income: Rs %.2f\n", grandTotal);
        fclose(report);
        printf(YELLOW"\n[*] Sales report saved to 'sales_report.txt'\n"RESET);
    } else {
        printf("\n[!] Failed to create sales report file.\n");
    }
}


//Option 07 Function Implement



void updateBookInformation() {
    system(CLEAR);
    int updateID, found = 0;
    struct book tempBook;
    FILE *file = fopen("books.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    printf("\n----------------------------------------------------------------------\n");
    printf(RED"\n                              UPDATE A BOOK                       \n"RESET);
    printf("\n----------------------------------------------------------------------\n");

    if (file == NULL || tempFile == NULL) {
        printf(RED"\n[ Error opening files. ]\n"RESET);
        return;
    }

    printf(YELLOW"\nEnter the Book ID to update: "RESET);
    scanf("%d", &updateID);
    printf("\n");

    while (fscanf(file, "%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title, tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
        if (tempBook.id == updateID) {
            found = 1;
            printf(GREEN"\nBook found: %d | %s | %s | %.2f | %d\n"RESET, tempBook.id, tempBook.title, tempBook.author, tempBook.price, tempBook.stockqty);
            printf("\n");

            printf(YELLOW"Enter new title (press Enter to keep unchanged): "RESET);
            getchar(); // clear newline from buffer
            char newTitle[100];
            fgets(newTitle, sizeof(newTitle), stdin);
            newTitle[strcspn(newTitle, "\n")] = 0;
            if (strlen(newTitle) > 0) {
                strcpy(tempBook.title, newTitle);
            }
            printf("\n");
            printf(YELLOW"Enter new author (press Enter to keep unchanged): "RESET);
            char newAuthor[100];
            fgets(newAuthor, sizeof(newAuthor), stdin);
            newAuthor[strcspn(newAuthor, "\n")] = 0;
            if (strlen(newAuthor) > 0) {
                strcpy(tempBook.author, newAuthor);
            }
            printf("\n");
            printf(YELLOW"Enter new price (press -1 to keep unchanged): "RESET);
            float newPrice;
            scanf("%f", &newPrice);
            if (newPrice >= 0) {
                tempBook.price = newPrice;
            }
            printf("\n");
            printf(YELLOW"Enter new stock quantity (press -1 to keep unchanged): "RESET);
            int newQty;
            scanf("%d", &newQty);
            if (newQty >= 0) {
                tempBook.stockqty = newQty;
            }
        }

        fprintf(tempFile, "%d,%s,%s,%.2f,%d\n", tempBook.id, tempBook.title, tempBook.author, tempBook.price, tempBook.stockqty);
    }

    fclose(file);
    fclose(tempFile);

    remove("books.txt");
    rename("temp.txt", "books.txt");

    printf("\n");
    if (found) {
        printf(GREEN"\n[ Book information updated successfully! ]\n"RESET);
    } else {
        printf(RED"\n[ Book ID not found. ]\n"RESET);
    }
    printf("\n");
}


//Option 08 Function Implement

void viewLowStockAlerts() {
    system(CLEAR);
    FILE *file = fopen("books.txt", "r");
    if (!file) {
        printf("\n[ Error: Cannot open books.txt. ]\n");
        return;
    }

    struct book tempBook;
    int found = 0;

    printf("\n----------------------------------------------------------------------\n");
    printf(RED"                     LOW STOCK ALERTS (Below %d Units)\n"RESET, STOCK_THRESHOLD);
    printf("----------------------------------------------------------------------\n");
    printf(GREEN"\n%-10s %-30s %-10s\n"RESET, "Book ID", "Title", "Stock");
    printf("----------------------------------------------------------------------\n");

    while (fscanf(file, "%d,%99[^,],%99[^,],%f,%d\n", &tempBook.id, tempBook.title,
                  tempBook.author, &tempBook.price, &tempBook.stockqty) == 5) {
        if (tempBook.stockqty < STOCK_THRESHOLD) {
            printf(YELLOW"%-10d %-30s %-10d\n\n"RESET, tempBook.id, tempBook.title, tempBook.stockqty);
            found = 1;
        }
    }

    if (!found) {
        printf(RED"\nAll books have sufficient stock.\n"RESET);
    }

    fclose(file);
}

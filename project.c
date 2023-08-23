#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

int count=0;

struct node
{
    char account[100];
    char username[100];
    char password[100];
    struct node *next;
};
struct node *head = NULL;

COORD coord = { 0, 0 };

int main();

void encrypt(char text[100]) 
{
    int i;
    char ch;
    int key = 3;

    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        if (ch >= 33 && ch <= 126) {
            ch = ((ch - 33 + key) % 94) + 33;
        }

        text[i] = ch;
    }
}

void decrypt(char text[100]) 
{
    int i;
    char ch;
    int key = 3;

    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        if (ch >= 33 && ch <= 126) {
            ch = ((ch - 33 - key + 94) % 94) + 33;
        }

        text[i] = ch;
    }
}

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void create_a_password() 
{
    char checker;
    do {
        system("cls");
        struct node *newnode, *temp;
        newnode = (struct node *)malloc(sizeof(struct node));
        gotoxy(17, 5);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(17, 20);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(22, 8);
        printf("Enter the Website/Application Name: ");
        scanf(" %[^\n]s ", newnode->account);

        gotoxy(22, 11);
        printf("Enter the Username/E-mail: ");
        scanf(" %[^\n]s ", newnode->username);

        gotoxy(22, 14);
        printf("Enter the password: ");
        scanf(" %[^\n]s ", newnode->password);

        gotoxy(22, 18);
        printf("Record saved!\n\n");

        newnode->next = NULL;
        if (head == NULL) {
            head = newnode;
        } 
        else {
            temp = head;
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }

        // Save password to file
        FILE *file = fopen("passwords.txt", "a");
        encrypt(newnode->account);
        encrypt(newnode->username);
        encrypt(newnode->password);
        if (file != NULL) {
            fprintf(file, "%s %s %s\n", newnode->account, newnode->username, newnode->password);
            fclose(file);
        } 
        else {
            printf("Failed to save password to file.\n");
        }

        gotoxy(22, 22);
        printf("Do You Want To Save Another Password? Y / N: ");

        scanf(" %c", &checker);
        checker = toupper(checker);
        system("cls");
    } while (checker == 'Y');

    if (checker == 'N') {
        main();
    } 
    else {
        do {
            system("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 20);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(18, 8);
            printf(">>> Wrong Input! Please Enter Y Or N Only! <<<");

            gotoxy(19, 12);
            printf("Do You Want To Save Another Password? Y / N: ");
            scanf(" %c", &checker);
            checker = toupper(checker);
        } while (checker != 'Y' && checker != 'N');

        if (checker == 'Y') {
            create_a_password();
        }

        if (checker == 'N') {
            system("cls");
            main();
        }
        system("cls");
    }
}

void search_password() 
{
    char checker;
    do {
        char search[100];
        system("cls");
        gotoxy(17, 5);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(17, 20);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(17, 7);
        printf("Enter Account Name or Username: ");
        scanf(" %[^\n]s", search);

        FILE *file = fopen("passwords.txt", "r");
        if (file == NULL) {
            gotoxy(17, 12);
            printf("Password file does not exist!");
            fclose(file);
            return;
        }

        char account[100], username[100], password[100];
        int found = 0;
        
        

        while (fscanf(file, "%s %s %s", account, username, password) == 3) 
        {
            decrypt(account);
            decrypt(username);
            decrypt(password);
            if (strcmp(search, account) == 0 || strcmp(search, username) == 0) {
                gotoxy(17, 11);
                printf("Account: %s", account);
                gotoxy(17, 13);
                printf("Username: %s", username);
                gotoxy(17, 15);
                printf("Password: %s", password);
                found = 1;
                break;
            }
        }

        if (found == 0) {
            gotoxy(17, 12);
            printf("No matching record found!");
        }

        fclose(file);

        gotoxy(22, 22);
        printf("Do You Want To Search Another Password? Y / N: ");
        scanf(" %c", &checker);
        checker = toupper(checker);
        system("cls");
    } while (checker == 'Y');

    if (checker == 'N') {
        main();
    } 
    else {
        do {
            system("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 20);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(18, 8);
            printf(">>> Wrong Input! Please Enter Y Or N Only! <<<");

            gotoxy(19, 12);
            printf("Do You Want To Search Another Password? Y / N: ");
            scanf(" %c", &checker);
            checker = toupper(checker);
        } while (checker != 'Y' && checker != 'N');

        if (checker == 'Y') {
            search_password();
        }

        if (checker == 'N') {
            system("cls");
            main();
        }
        system("cls");
    }
}

void edit_credentials() 
{
    char checker;
    do {
        char search[100];
        system("cls");
        gotoxy(17, 5);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(17, 20);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

        gotoxy(17, 7);
        printf("Enter Account Name or Username: ");
        scanf(" %[^\n]s", search);

        FILE *file = fopen("passwords.txt", "r+");
        if (file == NULL) {
            gotoxy(17, 12);
            printf("Password file does not exist!");
            fclose(file);
            return;
        }

        char account[100], username[100], password[100];
        int found = 0;

        while (fscanf(file, "%s %s %s", account, username, password) == 3) 
        {
            decrypt(account);
            decrypt(username);
            decrypt(password);
            if (strcmp(search, account) == 0 || strcmp(search, username) == 0) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            gotoxy(17, 12);
            printf("No matching record found!");
        } 
        else {
            gotoxy(17, 11);
            printf("Account: %s", account);
            gotoxy(17, 13);
            printf("Username: %s", username);
            gotoxy(17, 15);
            printf("Password: %s", password);

            fseek(file, -strlen(account) - strlen(username) - strlen(password) - 2, SEEK_CUR);

            gotoxy(17, 17);
            printf("Enter New Account Name: ");
            scanf(" %[^\n]s", account);
            encrypt(account);

            gotoxy(17, 18);
            printf("Enter New Username: ");
            scanf(" %[^\n]s", username);
            encrypt(username);

            gotoxy(17, 19);
            printf("Enter New Password: ");
            scanf(" %[^\n]s", password);
            encrypt(password);

            // fseek(file, -strlen(account) - strlen(username) - strlen(password) - 2, SEEK_CUR);
            fprintf(file, "%s %s %s", account, username, password);
            fflush(file);

            gotoxy(17, 21);
            printf("Credentials updated successfully!");
        }

        fclose(file);

        gotoxy(22, 23);
        printf("Do You Want To Edit Another Password? Y / N: ");
        scanf(" %c", &checker);
        checker = toupper(checker);
        system("cls");
    } while (checker == 'Y');

    if (checker == 'N') {
        main();
    } 
    else {
        do {
            system("cls");

            gotoxy(17, 5);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(17, 20);
            printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

            gotoxy(18, 8);
            printf(">>> Wrong Input! Please Enter Y Or N Only! <<<");

            gotoxy(19, 12);
            printf("Do You Want To Edit Another Password? Y / N: ");
            scanf(" %c", &checker);
            checker = toupper(checker);
        } while (checker != 'Y' && checker != 'N');

        if (checker == 'Y') {
            edit_credentials();
        }

        if (checker == 'N') {
            system("cls");
            main();
        }
        system("cls");
    }
}

void display_passwords() 
{
    system("cls");
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n\n");
    printf("==============================================\n");
    printf("| %-15s | %-15s | %-15s |\n", "Account", "Username", "Password");
    printf("==============================================\n");

    struct node* current = head;

    while (current != NULL) 
    {
        decrypt(current->account);
        decrypt(current->username);
        decrypt(current->password);
        printf("| %-15s | %-15s | %-15s |\n", current->account, current->username, current->password);
        current = current->next;
    }

    printf("==============================================\n\n");
}

void clear_passwords() 
{
    struct node* current = head;
    struct node* next;

    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}

void load_passwords() 
{
    clear_passwords();

    FILE* file = fopen("passwords.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    char account[100], username[100], password[100];
    while (fscanf(file, "%s %s %s", account, username, password) == 3) {
        struct node* newnode = (struct node*)malloc(sizeof(struct node));
        strcpy(newnode->account, account);
        strcpy(newnode->username, username);
        strcpy(newnode->password, password);
        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
        } 
        else {
            struct node* temp = head;
            while (temp->next != NULL) 
            {
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    fclose(file);
}

void retrieve_passwords()
{
    char enter;
    load_passwords();
    display_passwords();
    scanf("%c",&enter);

}

void generatePassword() 
{
    char checker;
    system("cls");
    gotoxy(17, 4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(17, 23);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    int length, lowercase, uppercase, numbers, special, totalChars;
    gotoxy(17, 7);
    printf("Enter the length of the password: ");
    scanf("%d", &length);
    gotoxy(17, 10);
    printf("Include lowercase characters? (1 for Yes, 0 for No): ");
    scanf("%d", &lowercase);
    gotoxy(17, 13);
    printf("Include uppercase characters? (1 for Yes, 0 for No): ");
    scanf("%d", &uppercase);
    gotoxy(17, 16);
    printf("Include numbers? (1 for Yes, 0 for No): ");
    scanf("%d", &numbers);
    gotoxy(17, 19);
    printf("Include special characters? (1 for Yes, 0 for No): ");
    scanf("%d", &special);
    const char lowercaseChars[] = "abcdefghijklmnopqrstuvwxyz";
    const char uppercaseChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbersChars[] = "0123456789";
    const char specialChars[] = "!@#$%&";
    totalChars = lowercase + uppercase + numbers + special;
    char password[length + 1];
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        char randomChar;
        int choice = rand() % totalChars;
        if (choice < lowercase && lowercase > 0) {
            randomChar = lowercaseChars[rand() % (sizeof(lowercaseChars) - 1)];
        } 
        else if (choice < lowercase + uppercase && uppercase > 0) {
            randomChar = uppercaseChars[rand() % (sizeof(uppercaseChars) - 1)];
        }
        else if (choice < lowercase + uppercase + numbers && numbers > 0) {
            randomChar = numbersChars[rand() % (sizeof(numbersChars) - 1)];
        }
         else if (special > 0) {
            randomChar = specialChars[rand() % (sizeof(specialChars) - 1)];
        }
        else {
            randomChar = '?';
        }
        password[i] = randomChar;
    }
    password[length] = '\0'; 
    gotoxy(17, 21);
    printf("Generated Password: %s\n", password);
    scanf("%c",&checker);
}

void login()
{
    char adminusername[100] = "ShivaKumar";
    char adminpassword[100] = "qaz@okm";
    int count = 0;
    char Username[100],Password[100];
    while(count <=3)
    {
        if(count>=3)
        {
            printf("Too many tries, access denied");
            exit(0);
        }
        gotoxy(5,5);
        printf("enter Admin Username: ");
        scanf("%s",&Username);
        gotoxy(5,10);
        printf("enter Admin Password: ");
        scanf("%s",&Password);
        if(strcmp(adminusername,Username) == 0 && strcmp(adminpassword,Password) == 0)
        {
            break;
        }
        else
        {
            printf("Incorrect Details Enter again\n");
            
            count++;
        }
    } 
        
}

int main()
{
    system("cls");
    if(count==0){
        login();
        count++;
    }
    int choice; 
    system("cls");  
    gotoxy(17, 4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 PASSWORD VAULT \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(17, 22);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(26, 6);
    printf("Welcome to your password vault");

    gotoxy(26, 8);
    printf("1. Save a Password");

    gotoxy(26, 10);
    printf("2. Find a Password");

    gotoxy(26, 12);
    printf("3. Edit a Password");

    gotoxy(26, 14);
    printf("4. Generate a Password");

    gotoxy(26, 16);
    printf("5. View all Passwords");

    gotoxy(26, 18);
    printf("6. Exit");

    gotoxy(26, 24);
    printf("Please Enter Your Choice : ");
    scanf(" %d", &choice);
    
    switch (choice) 
    {
      case 1:
        create_a_password();
        break;
      case 2:
        search_password();
        break;
      case 3:
        edit_credentials();
        break;
      case 4:
        char checker;
        generatePassword();
        printf("\t\tpress enter to continue");
        scanf("%c",&checker);
        main();
        break;
      case 5:
        char enter;
        retrieve_passwords();
        gotoxy(17,23);
        printf("press enter to continue");
        scanf("%c",&enter);
         main();
        break;
      case 6:
        break;
      default:
        system("cls");
        main();
        printf("\nError!!Enter correct choice..");
    }
    return (0);
}


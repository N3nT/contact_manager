#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct contact {
    char first_name[20];
    char last_name[20];
    int phone_number;
    char email[40];
} CONTACT;

void print_menu();
void menu();
int count_lines();
CONTACT *create_arr(int size);
void first_load(CONTACT *arr, int size);
void show_contacts(CONTACT *arr, int size);
void add_contacts(CONTACT *arr, int size);
void delete_contacts();
void search_contacts();

//search_contacts subfunction
CONTACT search_by_string(FILE *file, int type, char *string);
CONTACT search_by_number(FILE *file, int number);

void load_from_file();
void export();

int main(void) {
    CONTACT *arr;
    while(1) {
        int lines_of_file = count_lines();
        free(arr);
        arr = create_arr(lines_of_file+2);
        first_load(arr, lines_of_file);
        print_menu();
        menu(arr, lines_of_file);
    }
    free(arr);
}

void print_menu() {
    printf("---------------\n");
    printf("1. Show contacts\n");
    printf("2. Add contact\n");
    printf("3. Delete contact\n");
    printf("4. Search contact\n");
    printf("5. Load contacts from file\n");
    printf("6. Export\n");
    printf("7. Exit\n");
    printf("---------------\n\n");
}

void menu(CONTACT *arr, int size) {
    int option;
    printf("Option: ");
    scanf(" %d", &option);
    switch (option) {
        case 1: show_contacts(arr, size); break;
        case 2: add_contacts(arr, size); break;
        case 3: delete_contacts(); break;
        case 4: search_contacts(); break;
        case 5: load_from_file(); break;
        case 6: export(); break;
        case 7: exit(1);
        default: printf("Wrong option\n"); break;
    }
}

int count_lines() {
    FILE *file = fopen("contacts.txt", "r");
    int lines = 0;
    char buf[200];
    while (fgets(buf, 200, file) != NULL) {
        lines++;
    }
    fclose(file);
    return lines;
}

CONTACT *create_arr(int size) {
    CONTACT *arr = malloc(size * sizeof(CONTACT));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return arr;
}

void first_load(CONTACT *arr, int size) {
    FILE *file = fopen("contacts.txt", "r");
    if(file == NULL) {
        printf("File could not be opened\n");
    }
    for (int i = 0; i < size; i++) {
        char buffer[100];
        if (fgets(buffer, 100, file) == NULL) {
            printf("Error reading line\n");
            break;
        }
        sscanf(buffer, "%19[^;];%19[^;];%d;%39s",
            arr[i].first_name,
            arr[i].last_name,
            &arr[i].phone_number,
            arr[i].email);
    }
    fclose(file);
}

void show_contacts(CONTACT *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d. %s %s %d %s\n", i+1, (arr+i) -> first_name, (arr+i) -> last_name, (arr+i) -> phone_number, (arr+i) -> email);
    }
}
void add_contacts(CONTACT *arr, int size) {
    FILE *file = fopen("contacts.txt", "a");
    CONTACT add = {};
    printf("Enter name: ");
    scanf("%s", add.first_name);
    printf("Enter last name: ");
    scanf("%s", add.last_name);
    printf("Enter phone number: ");
    scanf("%d", &add.phone_number);
    printf("Enter email: ");
    scanf("%s", add.email);

    int result = fprintf(file, "%s;%s;%d;%s\n", add.first_name, add.last_name, add.phone_number, add.email);

    if (result > 0) {
        printf("Contact added\n");
    } else {
        printf("Error");
    }
    fclose(file);
}
void delete_contacts() {
    FILE *file = fopen("contacts.txt", "a+");
    FILE *temp = fopen("temp.txt", "w");
    int index;
    int current_line = 1;
    char buffer[100];
    printf("Enter index of contact to delete: ");
    scanf("%d", &index);
    if (index <= 0 && index > count_lines()) {
        printf("Wrong index\n");
    } else {
        while (fgets(buffer, 100, file) != NULL) {
            if(current_line != index) {
                fputs(buffer, temp);
            }
            current_line++;
        }
        fclose(file);
        fclose(temp);
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");
    }
}
void search_contacts() {
    FILE *file = fopen("contacts.txt", "r");
    int answer, number;
    char *search;
    CONTACT found = {};
    printf("Search by:\n"
           "1. First name\n"
           "2. Last name\n"
           "3. Phone number\n"
           "4. Email\n"
           "5. Exit\n");
    scanf("%d", &answer);
    switch(answer) {
        case 1: {
            printf("Enter name: ");
            scanf("%s", search);
            found = search_by_string(file, 1, search);
        } break;
        case 2: {
            printf("Enter lastname: ");
            scanf("%s", search);
            found = search_by_string(file, 2, search);
        } break;
        case 3: {
            printf("Enter phone number: ");
            scanf("%d", &number);
            found = search_by_number(file, number);
        }break;
        case 4: {
            printf("Enter email: ");
            scanf("%s", search);
            found = search_by_string(file, 3, search);
        }break;
        case 5:printf("Exit\n");break;
        default:printf("Wrong answer\n");break;
    }
    if(strcmp(found.first_name, "") == 0) {
        printf("Not found\n");
    } else {
        printf("%s %s %d %s\n", found.first_name, found.last_name, found.phone_number, found.email);
    }
    fclose(file);
}
void load_from_file() {}
void export(){}

//search_contacts subfunctions
//TO-DO maybe one function is enough
CONTACT search_by_string(FILE *file, int type, char *string) {
    //types: 1-firstname 2-lastname 3-email
    //TO-DO case sensitivity
    char buffer[100];
    CONTACT search = {};
    while (fgets(buffer, 100, file) != NULL) {
        sscanf(buffer, "%19[^;];%19[^;];%d;%39s",
            search.first_name,
            search.last_name,
            &search.phone_number,
            search.email);
        if (type == 1) {
            if (strcmp(search.first_name, string) == 0) {
                return search;
            }
        } else if (type == 2) {
            if (strcmp(search.last_name, string) == 0) {
                return search;
            }
        } else if (type == 3) {
            if (strcmp(search.email, string) == 0) {
                return search;
            }
        }
    }
    memset(&search, 0, sizeof(search));
    strcpy(search.first_name, "");
    return search;
}
CONTACT search_by_number(FILE *file, int number) {
    char buffer[100];
    CONTACT search = {};
    while (fgets(buffer, 100, file) != NULL) {
        sscanf(buffer, "%19[^;];%19[^;];%d;%39s",
            search.first_name,
            search.last_name,
            &search.phone_number,
            search.email);
        if (number == search.phone_number) {
            return search;
        }
    }
    memset(&search, 0, sizeof(search));
    strcpy(search.first_name, "");
    return search;
}
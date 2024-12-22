#include <stdio.h>
#include <stdlib.h>

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
void add_contacts();
void delete_contacts();
void search_contacts();
void load_from_file();

int main(void) {
    int lines_of_file = count_lines();
    CONTACT *arr = create_arr(lines_of_file);
    first_load(arr, lines_of_file);
    while(1) {
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
    printf("6. Exit\n");
    printf("---------------\n\n");
}

void menu(CONTACT *arr, int size) {
    int option;
    printf("Option: ");
    scanf(" %d", &option);
    switch (option) {
        case 1: show_contacts(arr, size); break;
        case 2: add_contacts(); break;
        case 3: delete_contacts(); break;
        case 4: search_contacts(); break;
        case 5: load_from_file(); break;
        case 6: exit(1); break;
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
void add_contacts() {}
void delete_contacts() {}
void search_contacts() {}
void load_from_file() {}
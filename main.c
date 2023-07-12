#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_SIZE 1000

typedef struct{
    char name[100];
    char roll[100];
    char subject[100];
    char marks[5];
}Student;

Student record[MAX_SIZE];
int size = 0;

// Declaring Functions.
FILE *openFile(FILE *, char);
int menu();
void update(FILE *);
void list();
int duplicateRoll(char []);
void add(FILE *);
int search(FILE *);
int change(FILE *);
int delete(FILE *);

int main(){
    FILE *fptr;

    fptr = openFile(fptr, 'r');
    // Checking if file exists or not if not we create it.
    if(fptr == NULL){
        fclose(fptr);
        fptr = openFile(fptr, 'w');
    }

    fclose(fptr);

    int choice, val;

    while(1){

        update(fptr);
        
        choice = menu();

        if(choice == 1){
            if(size == MAX_SIZE){
                printf("\nMaximum Limit Reached!");
                continue;
            }
            add(fptr);
        }
        else if(choice == 2){
            if(size == 0){
                printf("\nRecords empty!");
                continue;
            }
            val = search(fptr);

            if(val == -1){
                printf("\nRecord not Found!");
            }
            else{
                printf("\n-----------Details-----------");
                printf("\n\tName : %s", record[val].name);
                printf("\n\tRoll : %s", record[val].roll);
                printf("\n\tSubject : %s", record[val].subject);
                printf("\n\tMarks : %s", record[val].marks);
                printf("\n-----------------------------");
            }
        }
        else if(choice == 3){
            if(size == 0){
                printf("\nRecords empty!");
                continue;
            }
            val = change(fptr);
            if(val == -1){
                printf("\nRecord Not Found!");
            }
        }
        else if(choice == 4){
            if(size == 0){
                printf("\nRecords empty!");
                continue;
            }
            val = delete(fptr);

            if(val == -1){
                printf("\nRecord Not Found!");
            }
        }
        else if(choice == 5){
            if(size == 0){
                printf("\nRecords empty!");
                continue;
            }
            list();
        }
        else if(choice == 6){
            printf("\n\nExit. . .");
            break;
        }
        else{
            printf("\nInvalid Choice!");
        }
    }

    return 0;
}

// Function to open the students file in the required form.
FILE *openFile(FILE *fptr, char ch){
    if(ch == 'r'){
        fptr = fopen("students.txt", "r");
    }
    else if(ch == 'w'){
        fptr = fopen("students.txt", "w");
    }
    else if(ch == 'a'){
        fptr = fopen("students.txt", "a");
    }

    return fptr;
}

// Function to display the Menu.
int menu(){
    printf("\n\n-----------MENU------------");
    printf("\n\t1. Add");
    printf("\n\t2. Search");
    printf("\n\t3. Change");
    printf("\n\t4. Delete");
    printf("\n\t5. List");
    printf("\n\t6. Exit");
    printf("\n---------------------------");
    printf("\nEnter your choice : ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

// Function to set the record array's elements value to default.
void freeup(int size){
    for(int i=0; i<size; i++){
        strcpy(record[i].name, "\0");
        strcpy(record[i].roll, "\0");
        strcpy(record[i].subject, "\0");
        strcpy(record[i].marks, "\0");
    }
}

// Function to update the record array with the current values from the File.
void update(FILE *fptr){
    freeup(size);
    fptr = openFile(fptr, 'r');
    char s[100];
    int c = 1, i = 0;
    while(fgets(s, 100, fptr) != NULL){
        strtok(s, "\n");
        if(c == 1){
            strcpy(record[i].name, s); 
        }
        else if(c == 2){
            strcpy(record[i].roll, s);
        }
        else if(c == 3){
            strcpy(record[i].subject, s);
        }
        else{
            strcpy(record[i++].marks, s);
            c = 0;
        }
        c++;
    }
    size = i;
    fclose(fptr);
}

// Function to list the details of the students.
void list(){
    printf("\n\t    LIST");
    for(int i=0; i<size; i++){
        printf("\n-----------------------------");
        printf("\n\tName : %s", record[i].name);
        printf("\n\tRoll : %s", record[i].roll);
        printf("\n\tSubject : %s", record[i].subject);
        printf("\n\tMarks : %s", record[i].marks);
    }
    printf("\n-----------------------------");
}

// Function to check if the roll matches with the database.
int duplicateRoll(char roll[]){
    for(int i=0; i<size; i++){
        if(strcmp(roll, record[i].roll) == 0){
            return 1;
        }
    }
    return 0;
}

// Function to add record in the students file.
void add(FILE *fptr){
    char name[100];
    char roll[100];
    char subject[10];
    char marks[5];
    printf("\nEnter the name : ");
    scanf("\n");
    fgets(name, 100, stdin);
    printf("\nEnter the roll : ");
    scanf("\n");
    fgets(roll, 100, stdin);
    printf("\nEnter the subject : ");
    scanf("\n");
    fgets(subject, 10, stdin);
    printf("\nEnter the marks : ");
    scanf("\n");
    fgets(marks, 5, stdin);
    char rollCopy[100];
    strcpy(rollCopy, roll);
    if(duplicateRoll(rollCopy)){
        fclose(fptr);
        return;
    }
    fptr = openFile(fptr, 'a');
    fprintf(fptr, "%s%s%s%s", name, roll, subject, marks);
    fclose(fptr);
    printf("\nAdded Record Successfully!");
}

// Function to search for the specific record in the records.
int search(FILE *fptr){
    char roll[100];
    fptr = openFile(fptr, 'r');
    printf("\nEnter the roll you want to search for : ");
    scanf("\n");
    fgets(roll, 100, stdin);
    strtok(roll, "\n");

    for(int i=0; i<size; i++){
        if(strcmp(record[i].roll, roll) == 0){
            return i;
        }
    }
    return -1;
}

// Function to change the detail of specific record.
int change(FILE *fptr){
    char roll[100];
    printf("\nEnter the roll you want to change details for : ");
    scanf("\n");
    fgets(roll, 100, stdin);
    strtok(roll, "\n");

    int pos = -1;

    for(int i=0; i<size; i++){
        if(strcmp(record[i].roll, roll) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        return pos;
    }

    char name[100], newRoll[100], subject[10], marks[5];

    // Initialize.
    strcpy(name, record[pos].name);
    strcpy(newRoll, record[pos].roll);
    strcpy(subject, record[pos].subject);
    strcpy(marks, record[pos].marks);
    
    printf("\n\n-----------EDIT MENU------------");
    printf("\n\t1. Name");
    printf("\n\t2. Roll");
    printf("\n\t3. Subject and Marks");
    printf("\n\t4. All");
    printf("\n----------------------------------");
    printf("\nEnter your choice : ");
    int choice;
    scanf("%d", &choice);
    if(choice == 1){
        printf("\nEnter the new Name : ");
        scanf("\n");
        fgets(name, 100, stdin);
        strtok(name, "\n");
        strcpy(record[pos].name, name);
    }
    else if(choice == 2){
        printf("\nEnter the new Roll : ");
        scanf("\n");
        fgets(newRoll, 100, stdin);
        strtok(newRoll, "\n");
        char rollCopy[100];
        strcpy(rollCopy, newRoll);
        if(duplicateRoll(rollCopy)){
            printf("\nDuplicate Roll Number can't be entered!");
            return 0;
        }
        strcpy(record[pos].roll, newRoll);
    }
    else if(choice == 3){
        printf("\nEnter the new Subject : ");
        scanf("\n");
        fgets(subject, 10, stdin);
        strtok(subject, "\n");
        printf("\nEnter the new Marks : ");
        scanf("\n");
        fgets(marks, 5, stdin);
        strtok(marks, "\n");
        strcpy(record[pos].subject, subject);
        strcpy(record[pos].marks, marks);
    }
    else if(choice == 4){
        printf("\nEnter the new Name : ");
        scanf("\n");
        fgets(name, 100, stdin);
        strtok(name, "\n");
        printf("\nEnter the new Roll : ");
        scanf("\n");
        fgets(newRoll, 100, stdin);
        strtok(newRoll, "\n");
        char rollCopy[100];
        strcpy(rollCopy, newRoll);
        if(duplicateRoll(rollCopy)){
            printf("\nDuplicate Roll Number can't be entered!");
            return 0;
        }
        printf("\nEnter the new Subject : ");
        scanf("\n");
        fgets(subject, 10, stdin);
        strtok(subject, "\n");
        printf("\nEnter the new Marks : ");
        scanf("\n");
        fgets(marks, 5, stdin);
        strtok(marks, "\n");
        strcpy(record[pos].name, name);
        strcpy(record[pos].roll, newRoll);
        strcpy(record[pos].subject, subject);
        strcpy(record[pos].marks, marks);
    }
    else{
        printf("\nInvalid Choice!");
        return 0;
    }

    // Copy the new Data in the File.
    fptr = openFile(fptr, 'w');
    fclose(fptr);
    fptr = openFile(fptr, 'a');
    for(int i=0; i<size; i++){
        fprintf(fptr, "%s\n%s\n%s\n%s\n", record[i].name, record[i].roll, record[i].subject, record[i].marks);
    }
    fclose(fptr);
    printf("\nEdited Record Successfully!");

    return 1;
}

// Function to delete a specific record.
int delete(FILE *fptr){
    char roll[100];
    printf("\nEnter the roll you want to delete record for : ");
    scanf("\n");
    fgets(roll, 100, stdin);
    strtok(roll, "\n");

    int pos = -1;

    for(int i=0; i<size; i++){
        if(strcmp(record[i].roll, roll) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        return pos;
    }

    // Copy the new Data in the File ignoring the one to be deleted.
    fptr = openFile(fptr, 'w');
    fclose(fptr);
    fptr = openFile(fptr, 'a');
    for(int i=0; i<size; i++){
        if(i == pos) continue;
        fprintf(fptr, "%s\n%s\n%s\n%s\n", record[i].name, record[i].roll, record[i].subject, record[i].marks);
    }
    fclose(fptr);
    printf("\nDeleted Record Successfully!");

    return 1;
}
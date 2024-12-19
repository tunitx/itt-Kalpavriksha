#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//? added macro for the buffer

#define MAX_SIZE 500

struct Record {
    int userID;
    char userName[MAX_SIZE];
    int userAge;
};

void ensureFileExists() {
    FILE *dataFile = fopen("userRecords.txt", "a");
    if (dataFile) fclose(dataFile);
}

//? added a function which displays records to increase code reusability 

void displayRecord(struct Record record) {
    printf("User ID: %d\n", record.userID);
    printf("Name: %s\n", record.userName);
    printf("Age: %d\n", record.userAge);
    printf("--------------------------\n");
}

void addRecord() {
    struct Record record;
    FILE *dataFile = fopen("userRecords.txt", "r");

    if (!dataFile) {
        printf("Error: Could not access the file.\n");
        return;
    }

    //? added a check for negative user id.
    do {
        printf("Enter user ID: ");
        scanf("%d", &record.userID);
        getchar();
        if (record.userID < 0) {
            printf("Error: ID cannot be negative.\n");
        }
    } while (record.userID < 0);

    char buffer[MAX_SIZE];

    //? added a check which reads the file line by line into buffer array and then copies the line into a duplicate record
    // ?and then checks if entered user id is matching to the current lines user id.

    struct Record existingRecord;
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        sscanf(buffer, "%d,%49[^,],%d", &existingRecord.userID, existingRecord.userName, &existingRecord.userAge);
        if (existingRecord.userID == record.userID) {
            printf("Error: A record with this ID already exists.\n");
            fclose(dataFile);
            return;
        }
    }
    fclose(dataFile);

    dataFile = fopen("userRecords.txt", "a");
    if (!dataFile) {
        printf("Error: Could not access the file.\n");
        return;
    }

    printf("Enter Name: ");
    fgets(record.userName, sizeof(record.userName), stdin);
    record.userName[strcspn(record.userName, "\n")] = '\0';

    //? negative age check for age
    do {
        printf("Enter Age: ");
        scanf("%d", &record.userAge);
        if (record.userAge < 0) {
            printf("Error: Age cannot be negative.\n");
        }
    } while (record.userAge < 0);

    fprintf(dataFile, "%d,%s,%d\n", record.userID, record.userName, record.userAge);
    fclose(dataFile);

    printf("Record added successfully.\n");
}

void viewRecords() {
    FILE *dataFile = fopen("userRecords.txt", "r");
    if (!dataFile) {
        printf("Error: Could not access the file.\n");
        return;
    }

    char buffer[MAX_SIZE];
    struct Record record;
    printf("\nExisting Records:\n");
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        sscanf(buffer, "%d,%49[^,],%d", &record.userID, record.userName, &record.userAge);
        displayRecord(record);
    }

    fclose(dataFile);
}


void modifyRecord() {
    int lookupID, isFound = 0;
    struct Record record;

    printf("Enter the ID to modify: ");
    scanf("%d", &lookupID);
    getchar();

    FILE *dataFile = fopen("userRecords.txt", "r");
    if (!dataFile) {
        printf("Error: Unable to open file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_records.txt", "w");
    if (!tempFile) {
        printf("Error: Unable to create temp file.\n");
        fclose(dataFile);
        return;
    }

    char buffer[MAX_SIZE];
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        sscanf(buffer, "%d,%49[^,],%d", &record.userID, record.userName, &record.userAge);
        if (record.userID == lookupID) {
            isFound = 1;
            printf("\nCurrent Record:\n");
            displayRecord(record);

            printf("Enter new Name: ");
            fgets(record.userName, sizeof(record.userName), stdin);
            record.userName[strcspn(record.userName, "\n")] = '\0';

        //? check for negative age
        
            do {
                printf("Enter new Age: ");
                scanf("%d", &record.userAge);
                if (record.userAge < 0) {
                    printf("Error: Age cannot be negative.\n");
                }
            } while (record.userAge < 0);
        }

        fprintf(tempFile, "%d,%s,%d\n", record.userID, record.userName, record.userAge);
    }

    fclose(dataFile);
    fclose(tempFile);

    if (isFound) {
        remove("userRecords.txt");
        rename("temp_records.txt", "userRecords.txt");
        printf("Record updated successfully.\n");
    } else {
        remove("temp_records.txt");
        printf("No matching ID found.\n");
    }
}


void deleteRecord() {
    int lookupID, isFound = 0;
    struct Record record;

    printf("Enter the ID to delete: ");
    scanf("%d", &lookupID);

    FILE *dataFile = fopen("userRecords.txt", "r");
    if (!dataFile) {
        printf("Error: Unable to access file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_records.txt", "w");
    if (!tempFile) {
        printf("Error: Unable to create temp file.\n");
        fclose(dataFile);
        return;
    }

    char buffer[MAX_SIZE];
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        sscanf(buffer, "%d,%49[^,],%d", &record.userID, record.userName, &record.userAge);
        if (record.userID != lookupID) {
            fprintf(tempFile, "%d,%s,%d\n", record.userID, record.userName, record.userAge);
        } else {
            isFound = 1;
        }
    }

    fclose(dataFile);
    fclose(tempFile);

    if (isFound) {
        remove("userRecords.txt");
        rename("temp_records.txt", "userRecords.txt");
        printf("Record deleted successfully.\n");
    } else {
        remove("temp_records.txt");
        printf("No matching ID found.\n");
    }
}


int main() {
    int option;

    ensureFileExists();

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Record\n");
        printf("2. View Records\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                addRecord();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                modifyRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid option. Please choose a valid option.\n");
        }
    }

    return 0;
}

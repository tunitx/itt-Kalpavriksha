#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int userID;
    char userName[50];
    int userAge;
};

void ensureFileExists() {
    FILE *dataFile = fopen("user_records.txt", "a");
    if (dataFile) fclose(dataFile);
}

void addRecord() {
    struct Record record;
    FILE *dataFile = fopen("user_records.txt", "a");

    if (!dataFile) {
        printf("Error: Could not access the file.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &record.userID);
    getchar();
    printf("Enter Name: ");
    fgets(record.userName, sizeof(record.userName), stdin);
    record.userName[strcspn(record.userName, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &record.userAge);

    fprintf(dataFile, "%d,%s,%d\n", record.userID, record.userName, record.userAge);
    fclose(dataFile);

    printf("Record added successfully.\n");
}

void viewRecords() {
    FILE *dataFile = fopen("user_records.txt", "r");
    if (!dataFile) {
        printf("Error: Could not access the file.\n");
        return;
    }

    char buffer[500];
    printf("\nExisting Records:\n");
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        printf("%s", buffer);
    }

    fclose(dataFile);
}

void modifyRecord() {
    int lookupID, isFound = 0;
    struct Record record;

    printf("Enter the ID to modify: ");
    scanf("%d", &lookupID);
    getchar();

    FILE *dataFile = fopen("user_records.txt", "r");
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

    char buffer[500];
    while (fgets(buffer, sizeof(buffer), dataFile)) {
        sscanf(buffer, "%d,%49[^,],%d", &record.userID, record.userName, &record.userAge);
        if (record.userID == lookupID) {
            isFound = 1;
            printf("Enter new Name: ");
            fgets(record.userName, sizeof(record.userName), stdin);
            record.userName[strcspn(record.userName, "\n")] = '\0';

            printf("Enter new Age: ");
            scanf("%d", &record.userAge);
        }

        fprintf(tempFile, "%d,%s,%d\n", record.userID, record.userName, record.userAge);
    }

    fclose(dataFile);
    fclose(tempFile);

    if (isFound) {
        remove("user_records.txt");
        rename("temp_records.txt", "user_records.txt");
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
    FILE *dataFile = fopen("user_records.txt", "r");
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

    char buffer[500];
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
        remove("user_records.txt");
        rename("temp_records.txt", "user_records.txt");
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

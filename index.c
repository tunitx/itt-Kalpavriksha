#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct patient {
    int patient_id;
    char severity[10];
    struct patient* next;
} patient;

patient* create_patient(int id, char* severity) {
    patient* new_patient = (patient*)malloc(sizeof(patient));
    new_patient->patient_id = id;
    strcpy(new_patient->severity, severity);
    new_patient->next = NULL;
    return new_patient;
}

void insert_patient(patient** head, int id, char* severity) {
    patient* new_patient = create_patient(id, severity);
    if (*head == NULL) {
        *head = new_patient;
        return;
    }
    patient* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_patient;
}

int get_severity_priority(char* severity) {
    if (strcmp(severity, "Critical") == 0) return 1;
    if (strcmp(severity, "Serious") == 0) return 2;
    return 3;
}

void sort_patients(patient** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    int swapped;
    patient *ptr1, *lptr = NULL;
    do {
        swapped = 0;
        ptr1 = *head;
        while (ptr1->next != lptr) {
            if (get_severity_priority(ptr1->severity) > get_severity_priority(ptr1->next->severity)) {
                int temp_id = ptr1->patient_id;
                char temp_severity[10];
                strcpy(temp_severity, ptr1->severity);
                ptr1->patient_id = ptr1->next->patient_id;
                strcpy(ptr1->severity, ptr1->next->severity);
                ptr1->next->patient_id = temp_id;
                strcpy(ptr1->next->severity, temp_severity);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_patients(patient* head) {
    while (head != NULL) {
        printf("%d %s\n", head->patient_id, head->severity);
        head = head->next;
    }
}

int is_valid_number(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int is_valid_severity(char* str) {
    return strcmp(str, "Critical") == 0 || strcmp(str, "Serious") == 0 || strcmp(str, "Stable") == 0;
}

int is_unique_id(patient* head, int id) {
    while (head != NULL) {
        if (head->patient_id == id) return 0;
        head = head->next;
    }
    return 1;
}

int main() {
    int n;
    char input[100];

    while (1) {
        printf("enter number of patients: ");
        scanf("%s", input);
        if (is_valid_number(input)) {
            n = atoi(input);
            break;
        }
        printf("invalid input. Please enter a valid integer.\n");
    }

    patient* head = NULL;
    for (int i = 0; i < n; i++) {
        int id;
        char severity[10];

        while (1) {
            printf("enter unique patient ID: ");
            scanf("%s", input);
            if (is_valid_number(input)) {
                id = atoi(input);
                if (is_unique_id(head, id)) break;
                printf("patient ID already exists. Enter a unique ID.\n");
            } else {
                printf("invalid ID. Please enter a valid integer.\n");
            }
        }

        while (1) {
            printf("enter severity (Critical/Serious/Stable): ");
            scanf("%s", severity);
            if (is_valid_severity(severity)) break;
            printf("invalid severity. Enter 'Critical', 'Serious', or 'Stable'.\n");
        }

        insert_patient(&head, id, severity);
    }

    sort_patients(&head);
    print_patients(head);

    return 0;
}

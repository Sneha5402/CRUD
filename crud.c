#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    float marks;
};

struct Student *database = NULL; 
int current_size = 0; 
int max_size = 0;


void createRecord(int id, const char *name, float marks) {

    struct Student *newRecord = (struct Student *)malloc(sizeof(struct Student));
    if (newRecord == NULL) {
        printf("Memory allocation failed. Cannot create record.\n");
        return;
    }

    newRecord->id = id;
    strcpy(newRecord->name, name);
    newRecord->marks = marks;

    
    if (current_size >= max_size) {
        max_size += 10;
        database = (struct Student *)realloc(database, max_size * sizeof(struct Student));
        if (database == NULL) {
            printf("Memory allocation failed. Cannot expand database.\n");
            free(newRecord);
            return;
        }
    }

    
    database[current_size] = *newRecord;
    current_size++;
    free(newRecord);

    printf("Record with ID %d created successfully.\n", id);
}


void readRecords() {
    if (current_size == 0) {
        printf("Database is empty.\n");
        return;
    }
    printf("ID\tName\tMarks\n");
    for (int i = 0; i < current_size; ++i) {
        printf("%d\t%s\t%.2f\n", database[i].id, database[i].name, database[i].marks);
    }
}


void updateRecord(int id, const char *name, float marks) {
    for (int i = 0; i < current_size; ++i) {
        if (database[i].id == id) {
            strcpy(database[i].name, name);
            database[i].marks = marks;
            printf("Record with ID %d updated successfully.\n", id);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}                 


void deleteRecord(int id) {
    for (int i = 0; i < current_size; ++i) {
        if (database[i].id == id) {
            // Shift records to fill the gap
            for (int j = i; j < current_size - 1; ++j) {
                database[j] = database[j + 1];
            }
            current_size--;
            printf("Record with ID %d deleted successfully.\n", id);
            return;
        }
    }
    printf("Record with ID %d not found.\n", id);
}


void cleanup() {
    if (database != NULL) {
        free(database);
        database = NULL;
    }
}

int main() {
    int choice, id;
    char name[50];
    float marks;

 
    max_size = 10;
    database = (struct Student *)malloc(max_size * sizeof(struct Student));
    if (database == NULL) {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }

    do {
        printf("\n*** CRUD Operations Menu ***\n");
        printf("1. Create Record\n");
        printf("2. Read Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter ID, Name, Marks (separated by space): ");
                scanf("%d %s %f", &id, name, &marks);
                createRecord(id, name, marks);
                break;
            case 2:
                readRecords();
                break;
            case 3:
                printf("Enter ID, New Name, New Marks (separated by space): ");
                scanf("%d %s %f", &id, name, &marks);
                updateRecord(id, name, marks);
                break;
            case 4:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                deleteRecord(id);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
                break;
        }

    } while (choice != 5);

    
    cleanup();

    return 0;
} 

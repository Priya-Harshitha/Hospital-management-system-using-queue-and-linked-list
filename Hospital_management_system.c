#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    struct Patient *next;
};


struct Appointment {
    int patientID;
    char name[50];
    struct Appointment *next;
};


struct Patient *head = NULL;
struct Appointment *front = NULL, *rear = NULL;
int patientIDCounter = 1;


void addPatient() {
    struct Patient *newPatient = (struct Patient *)malloc(sizeof(struct Patient));
    newPatient->id = patientIDCounter++;
    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", newPatient->name);
    printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    printf("Enter Disease: ");
    scanf(" %[^\n]s", newPatient->disease);
    newPatient->next = head;
    head = newPatient;
    printf("Patient Added Successfully! ID: %d\n", newPatient->id);
}

void searchPatient() {
    int id;
    printf("Enter Patient ID to Search: ");
    scanf("%d", &id);
    struct Patient *temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nPatient Found: \nID: %d\nName: %s\nAge: %d\nDisease: %s\n", 
                   temp->id, temp->name, temp->age, temp->disease);
            return;
        }
        temp = temp->next;
    }
    printf("Patient Not Found!\n");
}


void deletePatient() {
    int id;
    printf("Enter Patient ID to Delete: ");
    scanf("%d", &id);
    
    struct Patient *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Patient Not Found!\n");
        return;
    }
    
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    
    free(temp);
    printf("Patient Deleted Successfully!\n");
}
void addAppointment() {
    int id;
    printf("Enter Patient ID for Appointment: ");
    scanf("%d", &id);
    
    struct Patient *temp = head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Patient Not Found!\n");
        return;
    }
    
    struct Appointment *newApp = (struct Appointment *)malloc(sizeof(struct Appointment));
    newApp->patientID = id;
    strcpy(newApp->name, temp->name);
    newApp->next = NULL;
    
    if (rear == NULL) {
        front = rear = newApp;
    } else {
        rear->next = newApp;
        rear = newApp;
    }
    
    printf("Appointment Booked for Patient ID: %d (%s)\n", id, temp->name);
}


void serveNextPatient() {
    if (front == NULL) {
        printf("No Appointments in Queue!\n");
        return;
    }
    
    struct Appointment *temp = front;
    printf("Serving Patient ID: %d, Name: %s\n", temp->patientID, temp->name);
    
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    
    free(temp);
}
void displayPatients() {
    struct Patient *temp = head;
    if (temp == NULL) {
        printf("No Patients Registered!\n");
        return;
    }
    
    printf("\n----- Patient Records -----\n");
    while (temp != NULL) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s\n", 
               temp->id, temp->name, temp->age, temp->disease);
        temp = temp->next;
    }
}


void displayAppointments() {
    struct Appointment *temp = front;
    if (temp == NULL) {
        printf("No Pending Appointments!\n");
        return;
    }
    
    printf("\n----- Appointment Queue -----\n");
    while (temp != NULL) {
        printf("Patient ID: %d | Name: %s\n", temp->patientID, temp->name);
        temp = temp->next;
    }
}


int main() {
    int choice;
    while (1) {
        printf("\n==== Hospital Management System ====\n");
        printf("1. Add Patient\n2. Search Patient\n3. Delete Patient\n");
        printf("4. Add Appointment\n5. Serve Next Patient\n6. Display Patients\n");
        printf("7. Display Appointments\n8. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addPatient(); break;
            case 2: searchPatient(); break;
            case 3: deletePatient(); break;
            case 4: addAppointment(); break;
            case 5: serveNextPatient(); break;
            case 6: displayPatients(); break;
            case 7: displayAppointments(); break;
            case 8: exit(0);
            default: printf("Invalid Choice! Try Again.\n");
        }
    }
    return 0;
}

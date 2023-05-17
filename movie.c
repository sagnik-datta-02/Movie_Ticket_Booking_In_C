#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SEATS 100
#define FILENAME "bookings.txt"

typedef struct {
    int id;
    bool booked;
    char name[50];
    char phoneNumber[20];
} Seat;

void initializeSeats(Seat seats[]) {
    for (int i = 0; i < MAX_SEATS; i++) {
        seats[i].id = i + 1;
        seats[i].booked = false;
        seats[i].name[0] = '\0';
        seats[i].phoneNumber[0] = '\0';
    }
}

void displayMenu() {
    printf("\n\t\t\t\t\t=== Movie Ticket Booking System ===\n");
    printf("\t\t\t\t\tMOVIE : PAATHAN (Shahrukh Khan)\n");
    printf("\t\t\t\t\t1. View Available Seats\n");
    printf("\t\t\t\t\t2. Book a Ticket\n");
    printf("\t\t\t\t\t3. Cancel a Ticket\n");
    printf("\t\t\t\t\t4. View Booked Tickets\n");
    printf("\t\t\t\t\t5. Specify Ticket Price before Ticket Selling/Modify Ticket Price \n");
    printf("\t\t\t\t\t6. Exit\n");
}

void saveSeatsToFile(Seat seats[]) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < MAX_SEATS; i++) {
        fprintf(file, "%d %d %s %s\n", seats[i].id, seats[i].booked, seats[i].name, seats[i].phoneNumber);
    }

    fclose(file);
}

void loadSeatsFromFile(Seat seats[]) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int id, booked;
    char name[50], phoneNumber[20];
    for (int i = 0; i < MAX_SEATS; i++) {
        if (fscanf(file, "%d %d %s %s\n", &id, &booked, name, phoneNumber) == 4) {
            seats[i].id = id;
            seats[i].booked = booked;
            strcpy(seats[i].name, name);
            strcpy(seats[i].phoneNumber, phoneNumber);
        }
    }

    fclose(file);
}

void viewAvailableSeats(Seat seats[]) {
    printf("\n\t\t\t\t\t--- Available Seats ---\n\t\t\t\t\t");
  
    for (int i = 0; i < MAX_SEATS; i++) {
        if (!seats[i].booked) {
            printf("%d  ", seats[i].id);

        }
        else{
            printf("*  ");
        }
        if(i!=0 && i%9==0)
        printf("\n\t\t\t\t\t");
    }
}

void changeTicketPrice() {
    float newPrice;
    printf("\t\t\t\t\tEnter the new ticket price: ");
    scanf("%f", &newPrice);

    FILE *file = fopen("price.txt", "w");
    if (file == NULL) {
        printf("\t\t\t\t\tError opening file for writing.\n");
        return;
    }

    fprintf(file, "%.2f", newPrice);
    fclose(file);

    printf("\t\t\t\t\tTicket price changed successfully.\n");
}

float getTicketPrice() {
    float price;
    FILE *file = fopen("price.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return 0.0;
    }

    fscanf(file, "%f", &price);
    fclose(file);

    return price;
}
void bookTicket(Seat seats[]) {
    int seatId;
    printf("\t\t\t\t\tEnter the seat number you want to book: ");
    scanf("%d", &seatId);

    if (seatId < 1 || seatId > MAX_SEATS) {
        printf("\t\t\t\t\tInvalid seat number.\n");
        return;
    }

    if (seats[seatId - 1].booked) {
        printf("\t\t\t\t\tSeat already booked.\n");
        return;
    }

    printf("\t\t\t\t\tEnter your name: ");
    scanf("%s", seats[seatId - 1].name);

    printf("\t\t\t\t\tEnter your phone number: ");
    scanf("%s", seats[seatId - 1].phoneNumber);

    seats[seatId - 1].booked = true;
   // printf("Seat %d booked successfully.\n", seatId);
   // printf("Ticket Price :%f\n",getTicketPrice());
    printf("\n\n");
        printf("\t\t\t\t\t-----------------MOVIE TICKET BOOKED----------------\n");
        printf("\t\t\t\t\t============================================================\n");
        printf("\t\t\t\t\tBooking ID : %s \t\t\tShow Name : PAATHAN (SRK) \n",seats[seatId - 1].phoneNumber);
        printf("\t\t\t\t\tCustomer  : %s\n",seats[seatId - 1].name);
        printf("\t\t\t\t\t\t\t\t\t\tDate      : 19-05-2023\n");
        printf("\t\t\t\t\t\t\t\t\t\tTime      : 08:00pm\n");
        printf("\t\t\t\t\t\t\t\t\t\t\tHall      : 02\n");
        printf("\t\t\t\t\t\t\t\t\t\tSeat No. : %d  \n",seatId);
        printf("\t\t\t\t\t\t\t\t\t\tPrice . : %f  \n\n",getTicketPrice());
		//person[count].id=id2;
        printf("\t\t\t\t\t============================================================\n");
    saveSeatsToFile(seats);
}

void cancelTicket(Seat seats[]) {
    int seatId;
    printf("\t\t\t\t\tEnter the seat number you want to cancel: ");
    scanf("%d", &seatId);

    if (seatId < 1 || seatId > MAX_SEATS) {
        printf("\t\t\t\t\tInvalid seat number.\n");
        return;
    }

    if (!seats[seatId - 1].booked) {
        printf("\t\t\t\t\tSeat is not booked.\n");
        return;
    }

    seats[seatId - 1].booked = false;
    seats[seatId - 1].name[0] = '\0';
    seats[seatId - 1].phoneNumber[0] = '\0';
    printf("\t\t\t\t\tSeat %d booking canceled.\n", seatId);
    saveSeatsToFile(seats);
}

void viewBookedTickets(Seat seats[]) {
    printf("\n\t\t\t\t\t--- Booked Tickets ---\n");
    for (int i = 0; i < MAX_SEATS; i++) {
        if (seats[i].booked) {
            printf("\t\t\t\t\tSeat %d: %s, %s\n", seats[i].id, seats[i].name, seats[i].phoneNumber);
        }
    }
}



int main() {
    Seat seats[MAX_SEATS];
    initializeSeats(seats);
    loadSeatsFromFile(seats);

    int choice;
    do {
        displayMenu();
        printf("\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewAvailableSeats(seats);
                break;
            case 2:
                bookTicket(seats);
                break;
            case 3:
                cancelTicket(seats);
                break;
            case 4:
                viewBookedTickets(seats);
                break;
            case 5:
                changeTicketPrice();
                break;
            case 6:
                printf("\t\t\t\t\tThank you for using the Movie Ticket Booking System.\n");
                break;
            default:
                printf("\t\t\t\t\tInvalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

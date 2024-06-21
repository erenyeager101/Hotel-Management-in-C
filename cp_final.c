#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char name[50];
    int roomNumber;
    int stayDuration;
    float billAmount;
    float roomRent;
    char bookingDate[11];
} Guest;

typedef struct {
    int roomNumber;
    char roomType[30];
    float rent;
} Room;

void addGuest();
void viewGuests();
void viewGuestBillingStatus();
void saveGuestsToFile();
void loadGuestsFromFile();
void displayAdminMenu();
void displayGuestMenu();
void bookRoom();
void checkOut();
void modifyGuestInfo();
int findGuestByID(int id);
int isRoomOccupied(int roomNumber);
void getCurrentDate(char *date);
void viewReceipt();

Guest guests[100];
int guestCount = 0;

Room rooms[6] = {
    {101, "Single Room", 3000.0},
    {102, "Double Room", 5000.0},
    {103, "Suite", 8000.0},
    {104, "Deluxe Suite", 10000.0},
    {105, "Family Room", 12000.0},
    {106, "Presidential Suite", 18000.0}
};

int main() {
    loadGuestsFromFile();
    int choice;

    while (1) {
        printf("\nWelcome to Enrise Hotels\n");
        printf("1. Admin\n");
        printf("2. Guest\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAdminMenu();
                break;
            case 2:
                displayGuestMenu();
                break;
            case 3:
                saveGuestsToFile();
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addGuest() {
    if (guestCount < 100) {
        Guest newGuest;
        newGuest.id = guestCount + 1;
        printf("Enter guest name: ");
        scanf("%s", newGuest.name);
        printf("Enter room number: ");
        scanf("%d", &newGuest.roomNumber);
        printf("Enter stay duration (days): ");
        scanf("%d", &newGuest.stayDuration);
        printf("Enter bill amount: ");
        scanf("%f", &newGuest.billAmount);
        newGuest.roomRent = 0;  
        getCurrentDate(newGuest.bookingDate); 

        guests[guestCount++] = newGuest;
        printf("Guest added successfully.\n");
    } else {
        printf("Guest list is full.\n");
    }
}

void viewGuests() {
    if (guestCount == 0) {
        printf("No guests to display.\n");
    } else {
        for (int i = 0; i < guestCount; i++) {
            printf("Guest ID: %d\n", guests[i].id);
            printf("Name: %s\n", guests[i].name);
            printf("Room Number: %d\n", guests[i].roomNumber);
            printf("Stay Duration: %d days\n", guests[i].stayDuration);
            printf("Bill Amount: INR%.2f\n", guests[i].billAmount);
            printf("Room Rent: INR%.2f\n", guests[i].roomRent);
            printf("Booking Date: %s\n", guests[i].bookingDate);
            printf("\n");
        }
    }
}

void viewGuestBillingStatus() {
    int id;
    printf("Enter guest ID: ");
    scanf("%d", &id);

    int index = findGuestByID(id);
    if (index != -1) {
        printf("Guest ID: %d\n", guests[index].id);
        printf("Name: %s\n", guests[index].name);
        printf("Room Number: %d\n", guests[index].roomNumber);
        printf("Stay Duration: %d days\n", guests[index].stayDuration);
        printf("Bill Amount: INR%.2f\n", guests[index].billAmount);
        printf("Room Rent: INR%.2f\n", guests[index].roomRent);
        printf("Booking Date: %s\n", guests[index].bookingDate);
    } else {
        printf("Guest ID not found.\n");
    }
}

void saveGuestsToFile() {
    FILE *file = fopen("guests.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%-4s %-10s %-11s %-13s %-10s %-8s %-12s\n", 
            "ID", "Name", "RoomNumber", "StayDuration", "BillAmount", "RoomRent", "BookingDate");

    for (int i = 0; i < guestCount; i++) {
        fprintf(file, "%-4d %-10s %-11d %-13d %-10.2f %-8.2f %-12s\n", 
                guests[i].id, 
                guests[i].name, 
                guests[i].roomNumber,
                guests[i].stayDuration, 
                guests[i].billAmount, 
                guests[i].roomRent, 
                guests[i].bookingDate);
    }

    fclose(file);
}

void loadGuestsFromFile() {
    FILE *file = fopen("guests.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file);

    guestCount = 0;
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %49s %d %d %f %f %10s",
                   &guests[guestCount].id, 
                   guests[guestCount].name, 
                   &guests[guestCount].roomNumber,
                   &guests[guestCount].stayDuration, 
                   &guests[guestCount].billAmount, 
                   &guests[guestCount].roomRent, 
                   guests[guestCount].bookingDate) == 7) {
            guestCount++;
        }
    }

    fclose(file);
}

void displayAdminMenu() {
    int choice;

    while (1) {
        printf("\nAdmin Menu\n");
        printf("1. View All Guests\n");
        printf("2. Add Guest\n");
        printf("3. View Guest Billing Status\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewGuests();
                break;
            case 2:
                addGuest();
                break;
            case 3:
                viewGuestBillingStatus();
                break;
            case 4:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void displayGuestMenu() {
    int choice;

    while (1) {
        printf("\nGuest Menu\n");
        printf("1. Book Room\n");
        printf("2. Check Out\n");
        printf("3. Modify Guest Information\n");
        printf("4. View Receipt\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                checkOut();
                break;
            case 3:
                modifyGuestInfo();
                break;
            case 4:
                viewReceipt();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void bookRoom() {
    if (guestCount < 100) {
        Guest newGuest;
        newGuest.id = guestCount + 1;
        printf("Enter your name: ");
        scanf("%s", newGuest.name);

        printf("Available rooms:\n");
        for (int i = 0; i < 6; i++) {
            printf("%d. %s - INR%.2f per night\n", i + 1, rooms[i].roomType, rooms[i].rent);
        }

        int roomChoice;
        printf("Enter the room type number: ");
        scanf("%d", &roomChoice);

        if (roomChoice < 1 || roomChoice > 6) {
            printf("Invalid room type selected.\n");
            return;
        }

        int selectedRoomNumber = rooms[roomChoice - 1].roomNumber;
        if (isRoomOccupied(selectedRoomNumber)) {
            printf("Selected room is already occupied. Please choose another room.\n");
            return;
        }

        newGuest.roomNumber = selectedRoomNumber;
        newGuest.roomRent = rooms[roomChoice - 1].rent;

        printf("Enter stay duration (days): ");
        scanf("%d", &newGuest.stayDuration);

        newGuest.billAmount = newGuest.roomRent * newGuest.stayDuration;
        getCurrentDate(newGuest.bookingDate);

        guests[guestCount++] = newGuest;
        printf("Room booked successfully. Your guest ID is %d.\n", newGuest.id);
    } else {
        printf("Guest list is full.\n");
    }
}

int isRoomOccupied(int roomNumber) {
    for (int i = 0; i < guestCount; i++) {
        if (guests[i].roomNumber == roomNumber) {
            return 1;
        }
    }
    return 0;
}

void checkOut() {
    int id;
    printf("Enter your guest ID: ");
    scanf("%d", &id);

    int index = findGuestByID(id);
    if (index != -1) {
        printf("Billing Status:\n");
        printf("Guest ID: %d\n", guests[index].id);
        printf("Name: %s\n", guests[index].name);
        printf("Room Number: %d\n", guests[index].roomNumber);
        printf("Stay Duration: %d days\n", guests[index].stayDuration);
        printf("Room Rent: INR%.2f\n", guests[index].roomRent);
        printf("Total Bill Amount: INR%.2f\n", guests[index].billAmount);
        printf("Booking Date: %s\n", guests[index].bookingDate);

        int payChoice;
        printf("Do you want to pay the bill? (1 for Yes / 0 for No): ");
        scanf("%d", &payChoice);

        if (payChoice == 1) {
            for (int i = index; i < guestCount - 1; i++) {
                guests[i] = guests[i + 1];
            }
            guestCount--;
            printf("Payment successful. Checked out successfully.\n");
        } else {
            printf("Check out cancelled.\n");
        }
    } else {
        printf("Guest ID not found.\n");
    }
}

void modifyGuestInfo() {
    int id;
    printf("Enter your guest ID: ");
    scanf("%d", &id);

    int index = findGuestByID(id);
    if (index != -1) {
        printf("Enter new name: ");
        scanf("%s", guests[index].name);
        printf("Enter new room number: ");
        scanf("%d", &guests[index].roomNumber);
        printf("Enter new stay duration (days): ");
        scanf("%d", &guests[index].stayDuration);

        guests[index].billAmount = guests[index].roomRent * guests[index].stayDuration;

        printf("Guest information updated successfully.\n");
    } else {
        printf("Guest ID not found.\n");
    }
}

int findGuestByID(int id) {
    for (int i = 0; i < guestCount; i++) {
        if (guests[i].id == id) {
            return i;
        }
    }
    return -1;
}

void getCurrentDate(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

void viewReceipt() {
    int id;
    printf("Enter your guest ID: ");
    scanf("%d", &id);

    int index = findGuestByID(id);
    if (index != -1) {
        printf("\n--- Receipt ---\n");
        printf("Guest ID: %d\n", guests[index].id);
        printf("Name: %s\n", guests[index].name);
        printf("Room Number: %d\n", guests[index].roomNumber);
        printf("Stay Duration: %d days\n", guests[index].stayDuration);
        printf("Room Rent: INR%.2f\n", guests[index].roomRent);
        printf("Total Bill Amount: INR%.2f\n", guests[index].billAmount);
        printf("Booking Date: %s\n", guests[index].bookingDate);
        printf("Check-out Date: ");
        
        char checkOutDate[11];
        getCurrentDate(checkOutDate);
        printf("%s\n", checkOutDate);

        char fileName[20];
        sprintf(fileName, "receipt%d.txt", guests[index].id);
        FILE *file = fopen(fileName, "w");
        if (file == NULL) {
            printf("Error opening file.\n");
            return;
        }

        fprintf(file, "--- Receipt ---\n");
        fprintf(file, "Guest ID: %d\n", guests[index].id);
        fprintf(file, "Name: %s\n", guests[index].name);
        fprintf(file, "Room Number: %d\n", guests[index].roomNumber);
        fprintf(file, "Stay Duration: %d days\n", guests[index].stayDuration);
        fprintf(file, "Room Rent: INR%.2f\n", guests[index].roomRent);
        fprintf(file, "Total Bill Amount: INR%.2f\n", guests[index].billAmount);
        fprintf(file, "Booking Date: %s\n", guests[index].bookingDate);
        fprintf(file, "Check-out Date: %s\n", checkOutDate);

        fclose(file);

        printf("Receipt saved to %s\n", fileName);
    } else {
        printf("Guest ID not found.\n");
    }
}

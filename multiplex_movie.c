#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

// using define macro to create a name for a numerical, character, or string constant... that'd be better as we'd using this throughout the code.

#define NUMBER_OF_HALLS 4
#define CAPACITY_OF_HALL 30
#define FRONT_RING 6
#define REAR_RING CAPACITY_OF_HALL - FRONT_RING // 30 - 6
#define FRONT 0
#define REAR 1 // FRONT = 0 and REAR = 1 implies that initially the queue is empty...

typedef struct Customer
{
    char name[20];
    int age;
    int movie; // The movie variable is used to identify the specific hall from which the customer should be removed
    struct Customer *next;
} Customer;

typedef struct CustomerQueue
{
    Customer *head;
    Customer *tail;
    int count; // The count variable is used to keep track of the number of customers added to each hall
    int capacity;
} CustomerQueue;

typedef struct Seat
{
    int number;
    int ring;
    int occupied;
} Seat;

typedef struct Hall
{
    int capacity;
    Seat seats[CAPACITY_OF_HALL];
    CustomerQueue Customers;
    int count;
} Hall;

// Helper functions
void initCustomerQueue(CustomerQueue *customers, int capacity);
void addCustomer(CustomerQueue *customers, Customer *customer);
void createCustomerList(Hall *hall, CustomerQueue customers, int movie);
void printCustomerList(Hall hall, int movie);
void removeCustomer(Hall *hall, CustomerQueue *customers, char name[20], int age, int movie);
int compareCustomer(Customer *customer, char name[20], int age, int movie);

int main(int argc, char **argv) // functions inside the int main functions are called command line arguments. 
{

    CustomerQueue customers; // list of all customers
    system("cls");
    // Create an empty queue
    initCustomerQueue(&customers, NUMBER_OF_HALLS * CAPACITY_OF_HALL);

    // Create halls of the movie
    Hall halls[NUMBER_OF_HALLS];

    // Initialize halls, clear all seats, set which seat is in which ring
    for (int i = 0; i < NUMBER_OF_HALLS; i++)
    {
        halls[i].capacity = CAPACITY_OF_HALL;
        halls[i].count = 0;
        initCustomerQueue(&halls[i].Customers, CAPACITY_OF_HALL);
        for (int j = 0; j < CAPACITY_OF_HALL; j++)
        {
            halls[i].seats[j].number = j;
            if (j < FRONT_RING)
            {
                halls[i].seats[j].ring = FRONT;
            }
            else
            {
                halls[i].seats[j].ring = REAR;
            }
            halls[i].seats[j].occupied = 0;
        }
    }

    // variables to hold user inputs
    int numberOfTickets = 0;
    char c; // used to take choice 
    int movie; // used to select the Hall for watching desired movie... Similar to choice variable(locally declared)
    int h = 0;
    char name[20];
    int age;
    do
    {
        printf("\t\t\t\t\nWelcome to the Multiplex Movie ticket reservation program!\n\n");

        // Print main menu
        printf("\n\n\t\t\t\t*************Main menu*************\n\n");
        printf("----------------------------------------\n\n");
        printf("\t1. Ticket booking\n");
        printf("\t2. Ticket cancellation\n");
        printf("\t3. Print hall's customer list\n");
        printf("\t4. Quit\n\n");
        printf("----------------------------------------\n\n");
        printf("\n\tEnter your choice [1-4]: ");
        scanf(" %c", &c);

        switch (c)
        {
        // Ticket booking
        case '1':
            printf("\nTicket booking\n");

            // prompt user for number of tickets
            printf("Please enter the number of tickets you want to book ");
            scanf("%d", &numberOfTickets);

            // Check if valid input
            if ((numberOfTickets > 0) && (numberOfTickets <= CAPACITY_OF_HALL))
            {
                int chosen = 0; // initially no tickets are booked or no hall is Choosen

                // Loop
                do
                {

                    // Prompt user to enter which movie he wants
                    // Print menu
                    printf("Please enter the movie (hall) you want to make reservations\n");
                    for (int i = 1; i < 5; i++) // loop which we'd be using for showing up the Hall list....
                    {
                        printf("%d. Hall %d\n", i, i);
                    }
                    printf("5. Exit reservation\n");
                    printf("Enter your choice [1-5]: ");
                    movie = 0;
                    scanf("%d", &movie); 

                    // Check if valid input (from 1 - 5)
                    if ((movie > 0) && (movie < 6))
                    {

                        // Check if exit is pressed
                        if (movie != 5)
                        {
                            movie--;

                            // Check if hall can accept number of tickets
                            if (numberOfTickets <= halls[movie].capacity - halls[movie].count) // Here halls[movie].capacity - halls[movie].count represents the available seats in a particular movie hall. (halls[movie].capacity is the total seating capacity of the movie hall, halls[movie].count represents the current number of occupied seats in the movie hall )
                            {

                                // Loop to input customers
                                for (int i = 0; i < numberOfTickets; i++) // number of tickets which is needed to booked would be taken as input from the user
                                {
                                    printf("\nCustomer name (no spaces allowed): ");
                                    scanf("%s", name);
                                    printf("Customer age: ");
                                    scanf("%d", &age);

                                    // Create a new customer using link List
                                    Customer *customer = (Customer *)malloc(sizeof(Customer)); 
                                    customer->movie = movie;
                                    strcpy(customer->name, name);
                                    customer->age = age;
                                    customer->next = NULL;

                                    // Add customer to queue
                                    addCustomer(&customers, customer);

                                    // Book a seat for customer in hall
                                    halls[movie].seats[halls[movie].count].occupied = 1;
                                    halls[movie].count++;

                                    // Check if hall reached 50% of capacity
                                    if (halls[movie].count >= halls[movie].capacity / 2)
                                    {
                                        // Create customer list sorted by seniority
                                        createCustomerList(&halls[movie], customers, movie);
                                    }
                                    chosen = 1; // Indicates that seat is already Booked and the selection is failed
                                }
                            }
                            else
                            {
                                // Suggest user to choose another movie
                                printf("Sorry, that hall can't accept that amount of tickets.\n You may choose another movie or cancel the process.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid input!\n");
                    }

                } while ((chosen == 0) && (movie != 5));
            }
            else
            {
                printf("\nInvalid number entered, valid range is 1-%d\n", CAPACITY_OF_HALL);
            }
            break;
        case '2':
            // Canceling already booked ticket
            printf("\nTicket canceling\n");

            // Prompt user for customer name, age and which movie he booked
            printf("Customer name: ");
            scanf("%s", name);
            printf("Customer age: ");
            scanf("%d", &age);
            printf("Movie: ");
            scanf("%d", &movie);

            // Remove customer from queue and free its seat in hall
            removeCustomer(&halls[movie - 1], &customers, name, age, movie - 1);
            break;
        case '3':
            // Print customer list for a hall if exist
            h = 0;
            do
            {
                // Prompt user to enter the hall
                printf("\nPlease enter the hall for which you want to print the list\n");
                for (int i = 1; i < 5; i++)
                {
                    printf("%d. Hall %d\n", i, i);
                }
                printf("5. Exit\n");
                printf("Enter your choice [1-5]: ");
                scanf("%d", &h);

                // Check if valid input
                if ((h > 0) && (h < 5))
                {

                    // Check if customer list exist for the hall
                    if (halls[h - 1].Customers.head != NULL)
                    {
                        // Print customer list
                        printCustomerList(halls[h - 1], h - 1); // as we use zero based indexing in array, so we follow (h - 1)th indexing
                    }
                    else
                    {
                        // Print message if there is no list
                        printf("Customer list is not formed yet for hall %d because it is more than half empty.\n", h);
                    }
                }
                else if (h > 5)
                {
                    printf("Invalid input.\n");
                    h = 0;
                }
            } while (h == 0);
            break;
        case '4':
            // Quit program
            break;
        default:
            printf("Invalid input!\n");
            break;
        }
    } while (c != '4');

    // Free the allocated memory
    Customer *customer = customers.head;
    while (customer != NULL)
    {
        Customer *tmp = customer;
        customer = customer->next;
        free(tmp);
    }

    return (EXIT_SUCCESS); // predefined in standard library function... terminates the program after success
}

// Initialize an empty queue
void initCustomerQueue(CustomerQueue *customers, int capacity)
{
    customers->capacity = capacity;
    customers->count = 0;
    customers->head = NULL;
    customers->tail = NULL;
}

// Add customer to queue or list
void addCustomer(CustomerQueue *customers, Customer *customer)
{
    if (customers->head == NULL)
    {
        customers->head = customer;
        customers->tail = customer;
    }
    else
    {
        customers->tail->next = customer;
        customers->tail = customer;
    }
    customers->count++;
}

// Create a sorted customer list for a hall
 void createCustomerList(Hall *hall, CustomerQueue customers, int movie)
{

    // Initialise an empty queue
    initCustomerQueue(&hall->Customers, CAPACITY_OF_HALL);

    // Iterate queue of all customers and copy the customers which belong to this hall
    Customer *customer = customers.head;    //structure calling of head
    while (customer != NULL)
    {
        if (customer->movie == movie)
        {
            addCustomer(&hall->Customers, customer);
        }
        customer = customer->next;
    }

    // Sort the customer list of the hall
    // Adapted bubble sort by age
    int sorted = 0; // flag to indicate that the list is sorted
    while (!sorted)
    {
        sorted = 1; // set flag to sorted
        customer = hall->Customers.head;

        // Iterate all elements of the list except the last one
        while (customer->next != NULL)
        {

            // Compare age with next customer in list, if les then swap customers
            if (customer->age < customer->next->age)
            {
                int tmp1 = customer->age;
                char tmp2[20];
                strcpy(tmp2, customer->name);
                customer->age = customer->next->age;
    
                strcpy(customer->name, customer->next->name);
                customer->next->age = tmp1;
                
                strcpy(customer->next->name, tmp2);
                sorted = 0; // set flag to not sorted
            }
            customer = customer->next;
        }
    }
}

// Prints the customer list for the hall
void printCustomerList(Hall hall, int movie)
{
    Customer *customer = hall.Customers.head;
    printf("\nList of customers in hall %d\n", movie + 1);
    int cnt = 0; //the cnt variable is used to keep track of the number of available seats in a particular movie hall.
    char ring[6]; // ring array is updated whenever a seat is booked or selected by the user.the ring array is used to calculate the number of available seats in a particular movie hall
    while (customer != NULL)
    {
        if (hall.seats[cnt].ring == FRONT)
        {
            strcpy(ring, "FRONT");
        }
        else
        {
            strcpy(ring, "REAR");
        }
        printf("\nSeat: %d\nRing: %s\nCustomer name: %s\nCustomer age: %d\n", cnt + 1, ring, customer->name, customer->age);
        customer = customer->next;
        cnt++;
    }
}

// Remove the customer from customer queue and from hall
void removeCustomer(Hall *hall, CustomerQueue *customers, char name[20], int age, int movie)
{

    // Check if queue is empty
    int found = 0; // found(kinda Flag variable) It allows you to remember and check whether a certain condition has been met or not, and perform different actions based on the result.
    if (customers->head != NULL)
    {
        // Check if head should be removed
        if (compareCustomer(customers->head, name, age, movie))
        {
            Customer *tmp = customers->head;

            // Set next element to be head
            customers->head = tmp->next;
            free(tmp);

            // Check if list is empty now
            if (customers->head == NULL)
            {

                // Set tail to NULL if list is empty
                customers->tail = NULL;
            }
            found = 1;
        }
        else
        {
            // The customer is not the head
            Customer *customer = customers->head->next;
            Customer *prev = customers->head;
            found = 0;

            // Iterate all elements until found or end
            while ((!found) && (customer != NULL))
            {

                // Compare customer
                if (compareCustomer(customer, name, age, movie))
                {

                    // Set flag to found
                    found = 1;

                    // Exclude customer from list
                    prev->next = customer->next;
                    free(customer);

                    // Set tail if needed
                    if (prev->next == NULL)
                    {
                        customers->tail = prev;
                    }
                }
                else
                {
                    prev = customer;
                    customer = customer->next;
                }
            }
        }
        if (!found)
        {
            printf("Customer not found!\n");
        }
        else
        {
            // Free seat in hall
            hall->seats[hall->count - 1].occupied = 0;
            hall->count--;

            // Check if hall capacity is at least 50% after removal
            if (hall->count >= hall->capacity / 2)
            {
                // Create list
                createCustomerList(hall, *customers, movie);
            }
            else
            {
                // Delete list
                initCustomerQueue(&hall->Customers, CAPACITY_OF_HALL);
            }
        }
    }
    else
    {
        printf("Customers queue is empty.\n");
    }
}

// Compare customer to name, age and movie booked.
// If all equal return 1, else return 0
int compareCustomer(Customer *customer, char name[20], int age, int movie)
{
    int result = 0;
    if ((strcmp(customer->name, name) == 0) && (customer->age == age) && (customer->movie == movie))
    {
        result = 1;
    }
    return result;
}
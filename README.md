🎬 **Multiplex Movie Ticket Reservation System**
This project simulates a simple movie ticket reservation system for a multiplex with multiple halls. It allows customers to book, cancel, and view tickets using linked lists and queue data structures to manage customer data effectively.

📌 **Features**
The program offers a menu-driven interface with the following functionalities:
  1. Ticket Booking
     Users can book tickets for up to 4 movie halls.
     It checks seat availability.
     If more than 50% of a hall is booked, a sorted customer list by age is created (elders appear first).
  
  2. Ticket Cancellation
     Cancels a booked ticket based on the customer's name, age, and selected hall.
     Frees up the seat and updates the sorted customer list accordingly.
  
  3. Print Customer List (per Hall)
     Displays the list of customers in a hall if more than 50% of the hall is occupied.
      Shows:
      
      Seat number
      
      Ring section (FRONT or REAR)
      
      Customer name and age

  4. Exit
     Cleanly exits the application and frees all dynamically allocated memory.

🛠️ **Data Structures Used**
🔁 **Singly Linked List**
Used to store the dynamic list of customers.

Each node contains:

  name

  age

  movie (hall number)

next pointer to the next customer

📚 **Queue (Custom Linked Queue)**
Maintains a first-in, first-out (FIFO) order for booking customers.

Each hall has its own customer queue.

A global queue holds all customers across halls for management.

🎫 **Structures**
**Customer:** Represents each customer.

**CustomerQueue:** Handles the queue of customers.

**Seat:** Tracks each seat’s number, ring type, and whether it's occupied.

**Hall:** Represents a movie hall with:

  1.A queue of customers

  2.An array of Seat structures

  3.Tracking variables for capacity and bookings.


🧮 **Constants and Configurations**
Defined using #define macros:

#define NUMBER_OF_HALLS 4
#define CAPACITY_OF_HALL 30
#define FRONT_RING 6
#define REAR_RING (CAPACITY_OF_HALL - FRONT_RING)
FRONT_RING seats: Premium seats (first 6).

REAR_RING seats: Regular seats.

Seat assignment is based on booking order.

📋 **Code Summary**
Component	Description
initCustomerQueue ->	Initializes a queue
addCustomer ->	Adds a new customer to a queue
createCustomerList ->	Filters and sorts customers by age
printCustomerList ->	Prints seat and customer details per hall
removeCustomer ->	Cancels ticket and updates data structures
compareCustomer	Helper to match customer details

🧪 **Sample Usage Flow**
> Welcome to the Multiplex Movie ticket reservation program!

Main Menu:
1. Ticket booking
2. Ticket cancellation
3. Print hall's customer list
4. Quit
The user can book tickets, choose which hall, and enter customer details. Once bookings exceed 50%, they can view sorted customer details per hall.

🔄 **Sorting Mechanism**
Bubble sort is used to sort the customer list in descending order of age (seniority).

This ensures older people are shown first on the list once more than 50% of seats are booked.

🧹 **Memory Management**
All customers are dynamically allocated using malloc.

Memory is freed at the end of the program or during ticket cancellation using free() to avoid leaks.

🖥️ **Platform Compatibility**
Uses <conio.h> and system("cls") (Windows specific).

Can be compiled using any C compiler like GCC or Turbo C.

Requires basic terminal input/output.

📌 **Suggestions for Future Improvements**
Add seat selection feature (currently, seats are auto-assigned).

Implement password-protected admin mode.

Store data in files for persistence across runs.

Add support for multiple customers booking at once.

👨‍💻 **Author**
This project is written in C as a basic demonstration of using linked lists, queues, and struct-based design for managing real-world systems like a movie booking platform.

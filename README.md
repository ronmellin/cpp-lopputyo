# Hotel Management System (C++ Basics Final)

**Student:** Ron Mellin

**Graded:** 5/5 points

## Overview

This is a console application that simulates a reservation system for a hotel. It handles everything from reserving, searching, error handling to data persistence.

When program is ran, it checks if a local storage fiel exists, if it doesn't, it automatically generates a hotel structure with a random number of rooms (between 40 and 300, must be even). The data is then saved automatically to the existing local storage file, to ensure that reservations are kept between sessions.

## Technical Implementation

* **Data Structure:** Uses a `Room` struct to store ID, type, reservation status, and guest details.
* **File Input/Output:** Reads and writes room states to a text file to prevent data loss.
* **Search:** Implements search to find reservations by Name or Reservation Number.
* **Randomization:** Used for room count generation and a discount feature.

## Logic

The system has two room types. A random discount (0%, 10%, or 20%) is calculated at the moment of booking.

| Room Type | Base Price (Per Night) |
| :--- | :--- |
| **Single Bed** | 100 EUR |
| **Double Bed** | 150 EUR |

*Max stay duration: 21 nights.*

## Build Instructions

1.  **Compile:**
    ```bash
    g++ hotel.cpp -o hotel
    ```

2.  **Run:**
    ```bash
    ./hotel
    ```

**Note:** The application uses `system("cls")` to handle UI updates, which is specific to Windows consoles.

## Problems

* **Input Handling:** There is a known issue where entering multiple integers with spaces (e.g., "1 1 1") in the main menu causes the program to skip prompts. This happens because the input buffer is not cleared between states.

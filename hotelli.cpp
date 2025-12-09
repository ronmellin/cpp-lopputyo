// Ron Mellin
// 4-5 point assignment

// TODO:
// If user enters multiple numbers with spaces in between,
// it allows the user to answer questions prematurely. Add a check to fix this.
// This "bug" can be recreated in the main menu, by entering "1 1 1 1" for example.

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Room {
    int id;    // room identifier
    int type;  // room type
    bool reserved;
    int reservationNumber;
    int price;
    int nights;
    string reservee;  // reservee name
};

// function to generate a reservation number,
// checks if the reservation number is in use,
// then generates new ones until it generates one that isn't in use
int generateReservationNumber(const vector<Room>& rooms) {
    while (true) {
        int num = rand() % 90000 + 10000;

        bool used = false;

        // goes through rooms checking if any object has the same reservation number
        for (const auto& r : rooms) {
            if (r.reservationNumber == num) {
                used = true;
                break;
            }
        }

        if (!used)
            return num;
    }
}

// simple function to generate a discount of either 0%, 10% or 20% when booking a room
int generateDiscount() {
    int dice = rand() % 3;
    switch (dice) {
        case 0:
            return 0;
        case 1:
            return 10;
        case 2:
            return 20;
    }
    return 0;
}

// main menu
void showMenu() {
    cout << "\n//////////////////////////////////////////\n";
    cout << "1) Reserve a room\n";
    cout << "2) Search for reservation\n";
    cout << "3) Exit\n";
    cout << "///////////////////////////////////////////\n";
}

// function to save the rooms to the file,
// making sure that we dont create a copy of the file
void saveRooms(const vector<Room>& rooms, const string& filename) {
    ofstream out(filename);
    for (const auto& r : rooms) {
        out << r.id << " " << r.type << " " << r.reserved << " " << r.reservationNumber << " "
            << r.price << " " << r.nights << " " << r.reservee << "\n";
    }
}

// function to search for a reservation with either
// reservee name or reservation number
//
void searchReservation(const vector<Room>& rooms) {
    system("cls");  // clearing the UI for clarity
    int choice;
    cout << "\nDo you want to search for a reservation with:\n";
    cout << "1) Your reservation number\n";
    cout << "2) The name the reservation is under\n";
    cout << "3) Back to menu\n";

    // input check
    while (true) {
        cout << "\nChoice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect input, choose either 1, 2 or 3\n";
        }
        if (choice >= 1 && choice <= 3) {
            break;
        }
        cout << "Incorrect input, choose either 1, 2 or 3\n";
    }
    cin.ignore();

    if (choice == 1) {
        // asking user for reservation number input and searching through rooms to match to a
        // reservation
        int num;
        cout << "Input reservation number: ";
        cin >> num;

        for (const auto& r : rooms) {
            if (r.reserved && r.reservationNumber == num) {
                system("cls");
                cout << "\nReservation found!\n";
                cout << "\nRoom number: " << r.id << "\n";
                cout << "Room type: " << (r.type == 1 ? "Single" : "Double") << "\n";
                cout << "Reservee: " << r.reservee << "\n";
                cout << "Nights: " << r.nights << "\n";
                cout << "Price: " << r.price << "\n";
                cout << "Price per night: " << r.price / r.nights << "\n";
                return;
            }
        }
        cout << "A reservation wasn't found with the given reservation number.\n";

    } else if (choice == 2) {
        // asking user for name input and searching through rooms to match to a reservation
        string name;
        cout << "Input name: ";
        getline(cin, name);

        bool found = false;
        for (const auto& r : rooms) {
            if (r.reserved && r.reservee == name) {
                system("cls");
                cout << "\nReservation found!\n";
                cout << "\nRoom number: " << r.id << "\n";
                cout << "Room type: " << (r.type == 1 ? "Single" : "Double") << "\n";
                cout << "Reservee: " << r.reservee << "\n";
                cout << "Nights: " << r.nights << "\n";
                cout << "Price: " << r.price << "\n";
                cout << "Price per night: " << r.price / r.nights << "\n";
                found = true;
            }
        }

        if (!found)
            cout << "A reservation wasn't found with the given name.\n";

    } else if (choice == 3) {
        // back to menu
        system("cls");
        return;
    } else {
        cout << "Incorrect input.\n";
    }
}

// function to book a room, and then save it to rooms
void bookRoom(vector<Room>& rooms) {
    system("cls");
    int type;
    int nights;
    int price;

    // input check
    while (true) {
        cout << "Choose room type (1 for single, 2 for double): ";
        cin >> type;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect input, input either 1 for single bed or 2 for double bed.\n";
        }
        if (type == 1 || type == 2) {
            break;
        }

        cout << "Incorrect input, input either 1 for single bed or 2 for double bed.\n";
    }

    // another one, should probably make an input check function
    while (true) {
        cout << "How many nights? (maximum of 21 days): ";
        cin >> nights;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Incorrect input, input a number between 1 and 21.\n";
        }

        if (nights >= 1 && nights <= 21) {
            break;
        }

        cout << "Incorrect input, input a number between 1 and 21.\n";
    }

    // this is where booking the room happens, and we get all the other information like discounts,
    // prices etc.
    for (auto& r : rooms) {
        if (r.type == type && !r.reserved) {
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, r.reservee);

            r.reserved = true;
            r.reservationNumber = generateReservationNumber(rooms);
            int pricePerNight = (r.type == 1) ? 100 : 150;
            int totalPrice = pricePerNight * nights;

            int discount = generateDiscount();
            int totalDiscounted = totalPrice - (totalPrice * discount / 100);

            r.nights = nights;
            r.price = totalDiscounted;

            system("cls");

            // nice looking output for user
            cout << "\n///Successfully Booked!///\n\n";
            cout << "Room " << r.id << " booked successfully for " << nights << " nights "
                 << "under reservation number " << r.reservationNumber << "\n";

            cout << nights << " nights, base price " << totalPrice << " Euro\n";
            cout << "Discount applied: " << discount << "%\n";
            cout << "Final price: " << totalDiscounted << " Euro for a "
                 << (r.type == 1 ? "single bed\n" : "double bed\n");

            cout << "\n///See you soon " << r.reservee << "!///\n";

            return;
        }
    }

    cout << "No available rooms of the selected type.\n";
}

// function to load the rooms from a file if it already exists
vector<Room> loadRooms(const string& filename) {
    vector<Room> rooms;
    ifstream in(filename);

    Room r;
    while (in >> r.id >> r.type >> r.reserved >> r.reservationNumber >> r.price >> r.nights) {
        in.ignore();
        getline(in, r.reservee);
        rooms.push_back(r);
    }
    return rooms;
}

// function the initialize the rooms, checks if there already is a rooms.txt file in the directory,
// if there isn't, generates a random number between 40-300 and generates a file with that many
// rooms, first half being single bed rooms, second half being double bed rooms
vector<Room> initRooms(const string& file) {
    ifstream test(file);  // checking for file
    if (test.good()) {
        return loadRooms(file);  // returning rooms from the file
    }

    int n = (rand() % 131) * 2 + 40;
    vector<Room> rooms;
    rooms.reserve(n);

    for (int i = 0; i < n; i++) {
        Room r;
        r.id = i + 1;
        r.type = (i < n / 2) ? 1 : 2;
        r.reserved = false;
        r.reservationNumber = 0;
        r.reservee = "";
        r.price = 0;
        r.nights = 0;
        rooms.push_back(r);
    }

    saveRooms(rooms, file);  // saving rooms to file
    return rooms;
}

// main function with main menu
int main() {
    srand(time(0));
    vector<Room> rooms = initRooms("rooms.txt");

    // input check
    while (true) {
        showMenu();

        int choice;
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            cout << "Incorrect input, choose either 1, 2 or 3\n";
        }

        switch (choice) {
            case 1:
                bookRoom(rooms);
                saveRooms(rooms, "rooms.txt");
                break;

            case 2:
                searchReservation(rooms);
                break;

            case 3:
                cout << "shutting down\n";
                system("cls");
                return 0;

            default:
                cout << "Invalid input, try again.\n";
                break;
        }
    }
}

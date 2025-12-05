#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// room structure to hold room information
struct Room {
    int id;                 // room number
    int type;               // 1 for single, 2 for double
    bool reserved;          // whether the room is reserved or not
    int reservationNumber;  // reservation number
    string reservee;        // name of the person who reserved the room, empty if not reserved

}

// checking if a file exists
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// menu display function
void showMenu() {
    cout << "\n//////////////////////////////////////////\n";
    cout << "1) Reserve a room\n";
    cout << "2) Search room by reservation number\n";
    cout << "3) Exit\n";
    cout << "///////////////////////////////////////////\n";
}

// function to pull the rooms from a "rooms.txt" file using ifstream
// returns a file format of [ID, type, reserved, reservationNumber, reservee]
vector<Room> loadRooms(const string& filename) {
    vector<Room> rooms;
    ifstream in(filename);

    Room r;
    while (in >> r.id >> r.type >> r.reserved >> r.reservationNumber) {
        in.ignore();
        getline(in, r.reservee);
        rooms.push_back(r);
    }
    return rooms;
}

// function to save the rooms to a "rooms.txt" file using ofstream
void saveRooms(const vector<Room>& rooms, const string& filename) {
    ofstream out(filename);
    for (const auto& r : rooms) {
        out << r.id << " " << r.type << " " << r.reserved << " " << r.reservationNumber << " "
            << r.reservee << "\n";
    }
}

// function to initialize the rooms
// if a file doesnt exist yet, creates a file with 40-300 rooms (even number)
// if the file exists, it loads the rooms from the file
// whatever happens, it returns a vector of rooms
vector<Room> initRooms(const string& filename) {
    if (fileExists(filename)) {
        cout << "rooms from file\n";
        return loadRooms(filename);
    }

    cout << "no file, creating\n";
    int n = (rand() % 131) * 2 + 40;  // even number between 40 and 300
    vector<Room> rooms;
    rooms.reserve(n);

    for (int i = 0; i < n; i++) {
        Room r;
        r.id = i + 1;
        r.type = (i < n / 2) ? 1 : 2;
        r.reserved = false;
        r.reservationNumber = 0;
        r.reservee = "";
        rooms.push_back(r);
    }

    saveRooms(rooms, filename);
    return rooms;
}

// generating a random reservation number
int generateReservationNumber() {
    return rand() % 90000 + 10000;  // 10000–99999
}

// function to book a room
// searches for the first available room of the selected type
// if found, marks it as reserved and assigns a reservation number
// if not found, informs the user
void bookRoom(vector<Room>& rooms) {
    int type;
    cout << "Choose room type (1 for single, 2 for double): ";
    cin >> type;

    if (type != 1 && type != 2) {
        cout << "Invalid room type selected. Enter 1 or 2. \n";
        return;
    }

    for (auto& r : rooms) {
        if (r.type == type && !r.reserved) {
            cin.ignore();
            cout << "Enter your name: ";
            getline(cin, r.reservee);
            r.reserved = true;
            r.reservationNumber = generateReservationNumber();

            cout << "\nSuccessfully booked!\n";
            cout << "Room " << r.id << " booked succesfully under reservation number "
                 << r.reservationNumber << "\n";
            return;
        }
    }
    cout << "No available rooms of the selected type.\n";
}

int main() {
    srand(time(0));
    vector<Room> rooms = initRooms("rooms.txt");

    showMenu();
    int choice;
    cin >> choice;

    if (choice == 1) {
        bookRoom(rooms);
        saveRooms(rooms, "rooms.txt");
    } else if (choice == 2) {
        // TODO search by reservation number and reservee name
    } else if (choice == 3) {
        cout << "Poistutaan ohjelmasta...\n";
        break;
    } else {
        cout << "Virheellinen valinta.\n";
    }

    return 0;
}
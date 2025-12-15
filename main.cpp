#include <iostream>
#include <cctype>
#include <iomanip>

using namespace std;

enum Choice { REGISTER = 1, SEARCH, UPDATE, DELETE, DISPLAY, EXIT };

int getValidInteger(int from, int to)
{
  int input;
  while (!(cin >> input) || cin.peek() != '\n' || input < from || input > to)
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid Input!\nEnter valid number: ";
  }
  return input;
}

class Hotel
{
private:
  class Room
  {
  public:
    int number;
    string guestName;
    char type;
    string checkInDate;
    int stayDuration;
    Room *next;
    Room *prev;
    Room()
    {
      next = NULL;
      prev = NULL;
    }
  };

  Room *head;
  const int ROOM_MIN = 101;
  const int ROOM_MAX = 599;
  const int DURATION_MAX = 90; // Same as booking.com

  bool isEmpty()
  {
    return (head == NULL);
  }

  int calcTotalAmount(char roomType, int stayDuration)
  {
    int pricePerNight = 0;
    switch (roomType)
    {
    case 'S':
      pricePerNight = 50;
      break;
    case 'D':
      pricePerNight = 80;
      break;
    case 'T':
      pricePerNight = 120;
      break;
    }
    return pricePerNight * stayDuration;
  }

  string getRoomType(char type)
  {
    switch (type)
    {
    case 'S':
      return "Single";
    case 'D':
      return "Double";
    case 'T':
      return "Twin";
    default:
      return "Unknown";
    }
  }

  Room *findRoom(int roomNum)
  {
    Room *current = head;

    while (current != NULL)
    {
      if (current->number == roomNum)
        return current;

      current = current->next;
    }
    return NULL;
  }

  void printRoom(Room *room)
  {
    cout << "\n----------- ROOM RECORD FOUND -----------\n";
    cout << "Room Number   : " << room->number << '\n';
    cout << "Guest Name    : " << room->guestName << '\n';
    cout << "Room Type     : " << getRoomType(room->type) << '\n';
    cout << "Check-In Date : " << room->checkInDate << '\n';
    cout << "Stay Duration : " << room->stayDuration << " nights\n";
    cout << "-----------------------------------------\n\n";
  }

public:
  Hotel()
  {
    head = NULL;
  }

  void registerRoom()
  {
    int roomNumber;

    while (true)
    {
      cout << "Enter Room Number: ";
      roomNumber = getValidInteger(ROOM_MIN, ROOM_MAX);

      if (findRoom(roomNumber) != NULL)
        cout << "\n>> Room " << roomNumber << " already has an active registration! <<\n";
      else
        break;
    }

    Room *newRoom = new Room();
    if (!isEmpty())
    {
      newRoom->next = head;
      head->prev = newRoom;
    }
    head = newRoom;
    newRoom->number = roomNumber;

    cout << "Enter Guest Name: ";
    cin.ignore();
    getline(cin, newRoom->guestName);

    cout << "Enter Room Type (S/D/T): ";
    cin >> newRoom->type;
    newRoom->type = toupper(newRoom->type);

    cout << "Enter Check-In Date (DD-MM-YYYY): ";
    cin.ignore(1000, '\n');
    cin >> newRoom->checkInDate;

    cout << "Enter Stay Duration: ";
    newRoom->stayDuration = getValidInteger(1, DURATION_MAX);

    cout << "\n>> Total amount: $" << calcTotalAmount(newRoom->type, newRoom->stayDuration);
    cout << "\n>> Room " << newRoom->number << " registered successfully. <<\n\n";
  }

  void searchRoom()
  {
    if (isEmpty())
    {
      cout << "\n>> The hotel room list is EMPTY! <<\n\n";
      return;
    }

    cout << "Enter Room Number: ";
    int roomNum = getValidInteger(ROOM_MIN, ROOM_MAX);

    Room *room = findRoom(roomNum);

    if (room != NULL)
      printRoom(room);
    else
      printf("\n>> Room %d has no active registration. <<\n\n", roomNum);
  }

  void updateRoom()
  {
    if (isEmpty())
    {
      cout << "\n>> The hotel room list is EMPTY! <<\n\n";
      return;
    }

    cout << "Enter Room Number: ";
    int roomNum = getValidInteger(ROOM_MIN, ROOM_MAX);

    Room *room = findRoom(roomNum);

    if (room == NULL)
    {
      cout << "\n>> Room not found! <<\n\n";
      return;
    }

    cout << "Enter New Guest Name: ";
    cin.ignore();
    getline(cin, room->guestName);

    cout << "Enter New Check-In Date (DD-MM-YYYY): ";
    cin >> room->checkInDate;

    cout << "Enter New Stay Duration: ";
    room->stayDuration = getValidInteger(1, DURATION_MAX);

    cout << "\n>> Total amount: $" << calcTotalAmount(room->type, room->stayDuration);
    cout << "\n>> Room updated successfully. <<\n\n";
  }

  void deleteRoom()
  {
    if (isEmpty())
    {
      cout << "\n>> The hotel room list is EMPTY! <<\n\n";
      return;
    }

    cout << "Enter Room Number: ";
    int roomNum = getValidInteger(ROOM_MIN, ROOM_MAX);

    Room *current = findRoom(roomNum);

    if (current == NULL)
    {
      cout << "\n>> Room " << roomNum << " not found! <<\n\n";
      return;
    }

    if (current == head)
    {
      head = current->next;
      if (head != NULL)
        head->prev = NULL;
    }
    else
    {
      current->prev->next = current->next;
      if (current->next != NULL)
        current->next->prev = current->prev;
    }

    delete current;
    cout << "\n>> Room " << roomNum << " removed successfully. <<\n\n";
  }

  void display()
  {
    if (isEmpty())
    {
      cout << "\n>> The hotel room list is EMPTY! <<\n\n";
      return;
    }

    cout << "\n\n\t\t\t\t--- ALL ROOM RECORDS ---\n";
    cout << setfill('-') << setw(85) << "" << setfill(' ') << '\n';

    cout << left
         << setw(15) << "Room Number"
         << setw(25) << "Guest Name"
         << setw(15) << "Room Type"
         << setw(15) << "Check-In Date"
         << setw(12) << "Stay Duration" << '\n';

    cout << setfill('-') << setw(85) << "" << setfill(' ') << '\n';

    Room *current = head;
    while (current != NULL)
    {
      cout << left
           << setw(15) << current->number
           << setw(25) << current->guestName
           << setw(15) << getRoomType(current->type)
           << setw(15) << current->checkInDate;
      printf("%02d nights\n", current->stayDuration);
      current = current->next;
    }
    cout << setfill('-') << setw(85) << "" << setfill(' ') << "\n\n";
  }

  ~Hotel()
  {
    Room *current = head;
    while (current != NULL)
    {
      Room *temp = current;
      current = current->next;
      delete temp;
    }
  }
};

void displayMenu()
{
  cout << "----------------------------\n"
       << "  HOTEL MANAGEMENT SYSTEM  \n"
       << "----------------------------\n"
       << "[1] Register Room\n"
       << "[2] Search Room\n"
       << "[3] Update Room\n"
       << "[4] Delete Room\n"
       << "[5] Display Rooms\n"
       << "[6] Exit System\n"
       << "----------------------------\n"
       << "Enter your choice: ";
}

void runSystem()
{
  Hotel hotel;
  while (true)
  {
    displayMenu();
    int choice = getValidInteger(1, EXIT);
    Choice enChoice = Choice(choice);

    switch (enChoice)
    {
    case Choice::REGISTER:
      hotel.registerRoom();
      break;
    case Choice::SEARCH:
      hotel.searchRoom();
      break;
    case Choice::UPDATE:
      hotel.updateRoom();
      break;
    case Choice::DELETE:
      hotel.deleteRoom();
      break;
    case Choice::DISPLAY:
      hotel.display();
      break;
    case Choice::EXIT:
      return;
    }
  }
}

int main()
{
  runSystem();

  return 0;
}

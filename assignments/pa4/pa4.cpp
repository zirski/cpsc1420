// Toby Hammond
//  pa4.cpp
//  November 13, 2023
//  Purpose:

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Part {
  char name[10];
  char manufacturer[11];
  int actual_quantity;
  int min_quantity;
  double unit_price;
};

int DisplayMenu();
int ReadPartInfo(Part[], ifstream &, double &);
void DisplayInventoryReport(Part[], int, double);
void DisplayReorderReport(Part[], int, double);
void SellPart(Part[], int, double &);
void OrderPart();
int ProcessSale(Part[], int);

int main() {
  ifstream in("inventory.dat");

  Part parts[150];
  double balance;
  int num_parts = ReadPartInfo(parts, in, balance);

  while (true) {
    switch (DisplayMenu()) {
    case 1:
      DisplayInventoryReport(parts, num_parts, balance);
      break;
    case 2:
      DisplayReorderReport(parts, num_parts, balance);
      break;
    case 3:
      SellPart(parts, num_parts, balance);
      break;
    case 4:
      break;
    default:
      exit(0);
      break;
    }
  }
}

int DisplayMenu() {
  cout << "==========================================" << endl;
  cout << "\tMini Electronics Inventory Management" << endl;
  cout << "\t\t1 - Inventory report" << endl;
  cout << "\t\t2 - Reorder report" << endl;
  cout << "\t\t3 - Sell parts" << endl;
  cout << "\t\t4 - Order parts" << endl;
  cout << "\t\t5 - Quit" << endl;
  cout << "==========================================" << endl;
  cout << "Your choice [1-5]: ";

  int input;
  while (true) {
    if (cin >> input && input > 0 && input < 6) {
      return input;
    } else {
      cout << "Please enter a choice between 1 and 5: ";
      cin.clear();
      fflush(stdin);
    }
  }
}

int ReadPartInfo(Part array[], ifstream &file_stream, double &bank_balance) {
  int num_parts;
  file_stream >> num_parts >> bank_balance;
  for (int i = 0; i < num_parts; i++) {
    file_stream >> array[i].name >> array[i].manufacturer >>
        array[i].actual_quantity >> array[i].min_quantity >>
        array[i].unit_price;
  }
  return num_parts;
}

void DisplayInventoryReport(Part array[], int num_parts, double bank_balance) {
  cout << "--------------------------------------- Inventory Report "
          "--------------------------------------"
       << endl;
  cout << setw(20) << left << "Item" << setw(20) << "Manufacturer" << setw(20)
       << "Quantity" << setw(20) << "Unit Price($)" << setw(20)
       << "Total Value($)" << endl;

  int total_quantity = 0;
  double total_value = 0;
  for (int i = 0; i < num_parts; i++) {
    cout << setw(20) << array[i].name << setw(20) << array[i].manufacturer
         << setw(20) << array[i].actual_quantity << setw(20)
         << array[i].min_quantity << setw(20)
         << array[i].unit_price * array[i].actual_quantity << endl;

    total_quantity += array[i].actual_quantity;
    total_value += array[i].unit_price * array[i].actual_quantity;
  }

  cout << endl;
  cout << "Number of parts: " << num_parts << endl;
  cout << "Total quantity: " << total_quantity << endl;
  cout << "Total value($): " << fixed << setprecision(2) << total_value << endl;
  cout << "Bank Balance($): " << bank_balance << endl;
}

void DisplayReorderReport(Part array[], int num_parts, double bank_balance) {
  cout << "--------------------------------------- Reorder Report "
          "---------------------------------------"
       << endl;
  cout << setw(20) << left << "Item" << setw(20) << "Manufacturer" << setw(20)
       << "Quantity" << setw(20) << "Minimum Quantity" << setw(20)
       << "Unit Price($)" << endl;

  int num_understocked = 0;
  int to_order = 0;
  double total_cost = 0;
  for (int i = 0; i < num_parts; i++) {
    if (array[i].actual_quantity < array[i].min_quantity) {
      cout << setw(20) << array[i].name << setw(20) << array[i].manufacturer
           << setw(20) << array[i].actual_quantity << setw(20)
           << array[i].min_quantity << setw(20) << array[i].unit_price << endl;
      num_understocked++;
      to_order += array[i].min_quantity - array[i].actual_quantity;
      total_cost += array[i].unit_price *
                    (array[i].min_quantity - array[i].actual_quantity) * 0.8;
    }
  }

  cout << endl;
  cout << "Number of understocked parts: " << num_understocked << endl;
  cout << "Total number to order: " << to_order << endl;
  cout << "Total cost($): " << fixed << setprecision(2) << total_cost << endl;
  cout << "Bank Balance($): " << bank_balance << endl;
}

void SellPart(Part array[], int num_parts, double &balance) {
  int part_i = ProcessSale(array, num_parts);
  int quant;
  cout << "Please input the quantity[0 - " << array[part_i].actual_quantity
       << "]: ";
  while (true) {
    if (cin >> quant && quant > 0 && quant < array[part_i].actual_quantity) {
      array[part_i].actual_quantity -= quant;
      balance += quant * array[part_i].unit_price;
      break;
    } else {
      cin.clear();
      fflush(stdin);
      cout << "Please input the quantity[0 - " << array[part_i].actual_quantity
           << "]: ";
    }
  }
}

void OrderPart(Part array[], int num_parts, double &balance) {}

int ProcessSale(Part array[], int num_parts) {
  cout << "Input the part name: ";
  char input_name[10];
  char input_manufacturer[11];

  while (true) {
    // If cin can read the user's input into a string
    if (cin >> input_name) {
      // Iterate through all the parts to look for a match
      for (int i = 0; i < num_parts; i++) {
        // If the part name exists, prompt user for the manufacturer name
        if (!(strcmp(input_name, array[i].name))) {
          cout << "Input the part manufacturer: ";
          while (true) {
            if (cin >> input_manufacturer) {
              // Iterate through all the parts again, this time to look for the
              // name-manufacturer match the user wants
              for (int j = 0; j < num_parts; j++) {
                if (!(strcmp(input_name, array[j].name)) &&
                    !(strcmp(input_manufacturer, array[j].manufacturer))) {
                  return j;
                }
              }
            } else {
              cout << "Invalid part manufacturer!" << endl
                   << "Input the part manufacturer: ";
              cin.clear();
              fflush(stdin);
            }
          }
        }
      }
      // If no part was found, try again
      cout << "Invalid part name!" << endl << "Input the part name: ";
      fflush(stdin);
      // If the user inputted something cin couldn't read into a char[10], then
      // try again
    } else {
      cout << "Invalid part name!" << endl << "Input the part name: ";
      cin.clear();
      fflush(stdin);
    }
  }
}
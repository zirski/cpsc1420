// Toby Hammond
//  pa4.cpp
//  November 13, 2023
//  Purpose:

#include <cstdio>
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
    if (!(cin >> input)) {
      cin.clear();
      fflush(stdin);
      cout << "Please enter a choice between 1 and 5: ";
    } else if (input < 1 || input > 5) {
      cout << "Please enter a choice between 1 and 5: ";
    } else {
      return input;
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

void SellPart(Part array[], int num_parts, double &bank_balance) {
  cout << "Input the part name: ";
  // For some reason I need to leave one empty array element for these
  // c-strings; otherwise it screws up the formatting in DisplayOrderReport (and
  // I assume DisplayReorderReport, though the largest-named parts dont show up
  // in that list so you can't see the problem there.)
  char part_name[10];
  char part_manu[11];
  const int PART_INDICES_SIZE = 2;
  int poss_part_indices[PART_INDICES_SIZE];
  int part_index;
  while (true) {
    if (!(cin >> part_name)) {
      cin.clear();
      fflush(stdin);
      cout << "Invalid part name!" << endl << "Input the part name: ";
    } else {
      bool is_found;
      int x = 0;
      // compares inputted part name with list of parts; for every time it
      // matches, store the index in poss_part_indices[].
      for (int i = 0; i < num_parts; i++) {
        if (!(strcmp(part_name, array[i].name))) {
          is_found = true;
          poss_part_indices[x++] = i;
        }
      }
      if (!is_found) {
        cout << "Invalid part name!" << endl << "Input the part name: ";
      } else {
        break;
      }
    }
  }
  cout << "Input the part manufacturer: ";
  while (true) {
    if (!(cin >> part_manu)) {
      cin.clear();
      fflush(stdin);
      cout << "Invalid part manufacturer!" << endl
           << "Input the part manufacturer: ";
    } else {
      bool is_found;
      for (int i = 0; i < PART_INDICES_SIZE; i++) {
        // I'm using this rather clunky for loop for the sole reason that it
        // doesn't give me a warning in the compiler :b
        if (!(strcmp(part_manu, array[poss_part_indices[i]].manufacturer))) {
          part_index = poss_part_indices[i];
          break;
        } else {
          fflush(stdin);
          cout << "Invalid part manufacturer!" << endl
               << "Input the part manufacturer: ";
        }
      }
      break;
    }
  }
  int quantity;
  cout << "Please input the quantity[0 - " << array[part_index].actual_quantity
       << "]: ";
  if ((!(cin >> quantity)) ||
      (quantity < 1 || quantity >= array[part_index].actual_quantity)) {
    cin.clear();
    fflush(stdin);
    cout << "Please input the quantity[0 - "
         << array[part_index].actual_quantity << "]: ";
  } else {
    array[part_index].actual_quantity -= quantity;
    bank_balance += quantity * array[part_index].unit_price;
  }
}

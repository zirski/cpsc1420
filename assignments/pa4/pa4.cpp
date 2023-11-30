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

const double SELL_PRICE_OFFSET = 0.8;

struct Part {
  char name[10];
  char manufacturer[11];
  int actual_q;
  int min_q;
  double uprice;
};

int DisplayMenu();
int ReadPartInfo(Part[], ifstream &, double &);
void DisplayInventoryReport(Part[], int, double);
void DisplayReorderReport(Part[], int, double);
void SellPart(Part[], int, double &);
void OrderPart(Part[], int, double &);
int ProcessQuery(Part[], int);

int main() {
  ifstream in("inventory.dat");

  Part parts[150];
  double balance;
  // Reads Part data from inventory.dat into Parts, num_parts and balance, for
  // use later.
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
      OrderPart(parts, num_parts, balance);
      break;
    default:
      exit(0);
      break;
    }
  }
}

int DisplayMenu() {
  cout << "==========================================" << endl;
  cout << "  Mini Electronics Inventory Management" << endl;
  cout << "    1 - Inventory report" << endl;
  cout << "    2 - Reorder report" << endl;
  cout << "    3 - Sell parts" << endl;
  cout << "    4 - Order parts" << endl;
  cout << "    5 - Quit" << endl;
  cout << "==========================================" << endl;
  cout << "Your choice [1-5]: ";

  int input;
  // Handy input validation control flow used ubiquitously througout the
  // program. Firstly, checks if cin can read into its variable with no errors;
  // if it can't give the user an error message and try again. cin.clear()
  // clears all state flags which might have been tripped during the function,
  // and fflush(stdin) flushes the buffer.
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
  // First two tokens of inventory.dat are the number of parts and the balance;
  // quickly load those in before doing anything else.
  file_stream >> num_parts >> bank_balance;
  for (int i = 0; i < num_parts; i++) {
    // Per line, load data into their respective fields.
    file_stream >> array[i].name >> array[i].manufacturer >>
        array[i].actual_q >> array[i].min_q >> array[i].uprice;
  }
  return num_parts;
}

void DisplayInventoryReport(Part array[], int num_parts, double bank_balance) {
  // I love setw
  cout << "--------------------------------------- Inventory Report "
          "--------------------------------------"
       << endl;
  cout << setw(20) << left << "Item" << setw(20) << "Manufacturer" << setw(20)
       << "Quantity" << setw(20) << "Unit Price($)" << setw(20)
       << "Total Value($)" << endl;

  int total_quantity = 0;
  double total_value = 0;
  // Iterate through all the parts to tally some totals, as well as display the
  // parts themselves on the screen.
  for (int i = 0; i < num_parts; i++) {
    cout << setw(20) << array[i].name << setw(20) << array[i].manufacturer
         << setw(20) << array[i].actual_q << setw(20) << array[i].uprice
         << setw(20) << array[i].uprice * array[i].actual_q << endl;

    total_quantity += array[i].actual_q;
    total_value += array[i].uprice * array[i].actual_q;
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
    // Check to see if a given part's on-hand quantity is less than the minimum
    // listed in inventory.dat; if so, display it in the report
    if (array[i].actual_q < array[i].min_q) {
      cout << setw(20) << array[i].name << setw(20) << array[i].manufacturer
           << setw(20) << array[i].actual_q << setw(20) << array[i].min_q
           << setw(20) << array[i].uprice << endl;
      num_understocked++;
      to_order += array[i].min_q - array[i].actual_q;
      // According to the rules, the listed "unit price" actually only regards
      // the sell price. The buying price is 20% less.
      total_cost += array[i].uprice * (array[i].min_q - array[i].actual_q) *
                    SELL_PRICE_OFFSET;
    }
  }

  cout << endl;
  cout << "Number of understocked parts: " << num_understocked << endl;
  cout << "Total number to order: " << to_order << endl;
  cout << "Total cost($): " << fixed << setprecision(2) << total_cost << endl;
  cout << "Bank Balance($): " << bank_balance << endl;
}

void SellPart(Part array[], int num_parts, double &balance) {
  // Input validation for the desired part.
  int part_i = ProcessQuery(array, num_parts);
  int quant;
  // The maximum quantity of a particular part one can sell is 1 less than the
  // on-hand quantity, since we don't want to exhaust the store's supply on any
  // one part.
  cout << "Please input the quantity[0 - " << array[part_i].actual_q - 1
       << "]: ";
  // Another instance of our trusty input validation algorithm.
  while (true) {
    if (cin >> quant && quant > 0 && quant < array[part_i].actual_q) {
      // If desired quantity sold is within bounds, update the part data and our
      // bank balance accordingly.
      array[part_i].actual_q -= quant;
      // As noted above, the selling price is just the unit price listed in
      // inventory.dat
      balance += quant * array[part_i].uprice;
      break;
    } else {
      cin.clear();
      fflush(stdin);
      cout << "Please input the quantity[0 - " << array[part_i].actual_q - 1
           << "]: ";
    }
  }
}

void OrderPart(Part array[], int num_parts, double &balance) {
  // index for the most understocked part
  int part_index;
  Part lowest = array[0];
  // Counter for how many understocked parts there are; if there's 0, we ask the
  // user which one they want to order, instead of choosing for them based on
  // necessity.
  int ct = 0;

  for (int i = 0; i < num_parts; i++) {
    // if part is not understocked (the on-hand quantity is greater than the
    // minimum quantity), skip it and move on. This greatly speeds things up,
    // also the workaround mentioned below doesn't work if either of the
    // operands are negative.
    if (array[i].min_q <= array[i].actual_q) {
      continue;
    } else {
      // Workaround for floating-point comparison. According to the assignment
      // sheet, comparing a/b and c/d is the same as comparing a * d and b * c.
      // Not sure why, but frankly it's too late in the evening to be
      // questioning the assignment description.
      //
      // Anyways, this case handles when the selected Part's score is higher
      // than the one in lowest.
      if (((array[i].min_q - array[i].actual_q) * lowest.min_q) >
          ((lowest.min_q - lowest.actual_q) * array[i].min_q)) {
        lowest = array[i];
        part_index = i;
        ct++;
        // Handles case when Part scores are equal; first break ties by name,
        // then by manufacturer.
      } else if (((array[i].min_q - array[i].actual_q) * lowest.min_q) ==
                 ((lowest.min_q - lowest.actual_q) * array[i].min_q)) {
        // If part names are equal, evaluate the manufacturer names for equality
        if (!(strcmp(array[i].name, lowest.name))) {
          // It doesn't really matter if the manufacturer names are equal, since
          // the assignment description doesn't provide any course of action
          // given this case.
          if (strcmp(array[i].manufacturer, lowest.manufacturer) == -1) {
            lowest = array[i];
            part_index = i;
            ct++;
          }
        } else {
          if (strcmp(array[i].name, lowest.name) == -1) {
            lowest = array[i];
            part_index = i;
            ct++;
          }
        }
      }
    }
  }

  // Since we have a base case at the top, if we have no understocked parts it
  // should be pretty quick to get to this point. This case handles letting the
  // user pick a part name and manufacturer, as well as the quantity desired.
  if (ct == 0) {
    part_index = ProcessQuery(array, num_parts);
    int max_quantity = static_cast<int>(
        balance / (array[part_index].uprice * SELL_PRICE_OFFSET));
    cout << "Please input the quantity [0 - " << max_quantity << "]: ";

    int quantity;
    // Yet another input validation instance. Same algorithm, applied elsewhere.
    while (true) {
      if (cin >> quantity && quantity > 0 && quantity < max_quantity) {
        array[part_index].actual_q += quantity;
        balance -= array[part_index].uprice * quantity;
        break;
      } else {
        cout << "Please enter a valid quantity [0 - " << max_quantity << "]: ";
        cin.clear();
        fflush(stdin);
      }
    }
    // This case chooses the part for the user, the part in question computed by
    // that mass of logic above.
  } else {
    int max_quantity = static_cast<int>(
        balance / (array[part_index].uprice * SELL_PRICE_OFFSET));

    cout << "Order Part " << array[part_index].name << " from "
         << array[part_index].manufacturer << endl;
    cout << "You may order quantity [0 - " << max_quantity << "]: ";

    int quantity;
    while (true) {
      if (cin >> quantity && quantity > 0 && quantity < max_quantity) {
        array[part_index].actual_q += quantity;
        balance -= array[part_index].uprice * SELL_PRICE_OFFSET * quantity;
        break;
      } else {
        cout << "Please enter a valid quantity [0 - " << max_quantity << "]: ";
        cin.clear();
        fflush(stdin);
      }
    }
  }
}

int ProcessQuery(Part array[], int num_parts) {
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
              cout << "Invalid part manufacturer!" << endl
                   << "Input the part manufacturer: ";
              cin.clear();
              fflush(stdin);
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
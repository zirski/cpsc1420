// Toby Hammond
// pa1.cpp
// Purpose: reads and parses employee financial data from `payroll.dat`, then 
// totals all employees' info and displays it; filters out corrupted entries.

#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

// Number of operable tokens per line (all data excluding employee number)
const int NUM_TOKENS = 4;

int main() {
  ifstream in("payroll.dat");

  if (in) {
    double gross_pay, tax_s, tax_f, fica_wholdings;
    int token_check;
    int valid_entries;

    // There's probably a better way to do this; right now however I'm just
    // checking if the ifstream can read another token and storing that value
    // in a dummy variable.
    while (in >> token_check) {
      // NEW plan: 0 = gross pay; 1 = state tax; 2 = federal tax; 3 = fica
      // withholdings.
      double emp_items[NUM_TOKENS];
      bool entry_is_valid = true;

      // Loads the data from a given line into an array for processing.
      for (int i = 0; i < NUM_TOKENS; i++) {
        in >> emp_items[i];
      }

      for (int i = 0; i < NUM_TOKENS; i++) {
        // checks whether any elements are negative
        if (emp_items[i] < 0) {
          entry_is_valid = false;
        }
      }

      // checks if any of the following are greater than gross pay: state tax,
      // federal tax, or fica withholdings.
      if ((emp_items[0] < emp_items[1]) || (emp_items[0] < emp_items[2]) ||
          (emp_items[0] < emp_items[3])) {
        entry_is_valid = false;

        // checks if the sum of state tax, federal tax, and fica withholdings is
        // greater than gross pay.
      } else if (emp_items[0] < (emp_items[1] + emp_items[2] + emp_items[3])) {
        entry_is_valid = false;
      }

      // If all checks are passed, add the values from the array into their
      // respective variables, and start again with the next line.
      if (entry_is_valid) {
        gross_pay += emp_items[0];
        tax_s += emp_items[1];
        tax_f += emp_items[2];
        fica_wholdings += emp_items[3];
        valid_entries++;
      }
    }

    cout << endl;
    cout << "Valid payroll records:" << right << setw(27) << valid_entries
         << endl;
    cout << left << setw(36) << "Total gross pay:"
         << "$" << right << setw(12) << setprecision(2) << fixed << gross_pay
         << endl;
    cout << left << setw(36) << "Total state tax:"
         << "$" << right << setw(12) << setprecision(2) << fixed << tax_s
         << endl;
    cout << left << setw(36) << "Total federal tax:"
         << "$" << right << setw(12) << setprecision(2) << fixed << tax_f
         << endl;
    cout << left << setw(36) << "Total FICA withholdings:"
         << "$" << right << setw(12) << setprecision(2) << fixed
         << fica_wholdings << endl;
    cout << left << setw(36) << "Total net pay:"
         << "$" << right << setw(12) << setprecision(2) << fixed
         << gross_pay - (tax_f + tax_s + fica_wholdings) << endl;
    cout << endl;

    return 0;
  } else {
    cout << "Error in opening the file!\nNo payroll report is created." << endl;
    return 1;
  }
}
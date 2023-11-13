// Toby Hammond
// lab3.cpp
// October 1, 2023
/*Purpose: Calculates gross and net profit of movie a movie theater based on
  the number of tickets sold (entered by the user) and fixed ticket prices
  (hard-coded). Also calculates money given to distribution based on a
  hard-coded percentage of the gross profit.
*/

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

const double REVENUE_PERCENT = 0.20;
const double TICKET_PRICE_ADULT = 10.0;
const double TICKET_PRICE_CHILD = 6.0;

int main() {
  // some variables to store the user input
  string movie_name;
  int tickets_sold_adult;
  int tickets_sold_child;
  double gross_profit;
  double net_profit;
  double amount_paid = gross_profit - net_profit;

  cout << "Enter movie name:" << endl;
  cin >> movie_name;
  cout << "Amount of adult tickets sold?" << endl;
  cin >> tickets_sold_adult;
  cout << "Amount of child tickets sold?" << endl;
  cin >> tickets_sold_child;

  gross_profit = (tickets_sold_adult * TICKET_PRICE_ADULT) +
                 (tickets_sold_child * TICKET_PRICE_CHILD);
  net_profit = gross_profit * REVENUE_PERCENT;

  cout << endl;
  cout << left << setw(40) << "Movie Name:" << right << setw(12) << movie_name
       << endl;
  cout << left << setw(40) << "Adult Tickets Sold:" << right << setw(12)
       << tickets_sold_adult << endl;
  cout << left << setw(40) << "Child Tickets Sold:" << right << setw(12)
       << tickets_sold_child << endl;
  cout << left << setw(40) << "Gross Box Office Profit:"
       << "$ " << right << setw(10) << setprecision(2) << fixed << gross_profit
       << endl;
  cout << left << setw(40) << "Net Box Office Profit:"
       << "$ " << right << setw(10) << setprecision(2) << net_profit << endl;
  cout << left << setw(40) << "Amount Paid to Distribution:"
       << "$ " << right << setw(10) << setprecision(2)
       << (gross_profit - net_profit) << endl;
  cout << endl;

  return 0;
}

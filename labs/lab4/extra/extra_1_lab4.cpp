#include <iostream>
#include <iomanip>

using namespace std;

const int PACKAGE_PRICE = 99;
int main() {
  int num_units;
  double discount;

  cout << "Enter number of units sold: " << endl;
  cin >> num_units;
  if (num_units < 0) {
    cout << "Negative number entered. Sorry!\n";
    exit(1);
  }

  switch (num_units) {
    case 10 ... 19: 
      discount = 0.2;
    case 20 ... 49:
      discount = 0.3;
    case 50 ... 99:
      discount = 0.4;
    default:
      discount = 0.5;
  } 

  cout << "Total cost: $ " << fixed << setprecision(2) << num_units * PACKAGE_PRICE * discount << endl;
  return 0;
}

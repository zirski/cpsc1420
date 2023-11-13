#include <iostream>
#include <string>
using namespace std;

int main() {
  double mileage_city, mileage_highway;
  mileage_city = 11.5;
  mileage_highway = 19.25;
  
  int tank_size = 24;
  string owner_name = "Jerry Smith";

  double range_city = mileage_city * tank_size;
  double range_highway = mileage_highway * tank_size;

  cout << "Jerry owns a 24-gallon tank Lamborghini sports car." << endl;
  cout << "The distance the car can travel on one tank of gas is " << range_city << " miles when driven in city." << endl;
  cout << "The distance the car can travel on one tank of gas is " << range_highway << " miles when driven on the highway."<< endl;
}

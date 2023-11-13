// Yingwu Zhu
// area.cpp
// 7/4/23

// Purpose: This program calculates the area of a circle.

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

const double PI = 3.1415926535898; // constant pi
const int OUTPUT_PRECISION = 3; // number of decimal places to show
const char YES = 'y';

// Returns area of circle given the radius
// pre: radius must be positive
double CircleArea(double radius);

int main() {
  double radius = 0; // radius entered by user
  string units; // units for the radius, entered by user
  char more = 'y'; // does the user want more?
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(OUTPUT_PRECISION);
  while (tolower(more) == YES) {
    cout << "What is the radius of the circle? ";
		cin >> radius;
		if (radius < 0) {
      cout << "The radius can't be negative!" << endl;
		} else {
			cout << "In what units? ";
			cin >> units;
			cout << "The area of the circle is " << CircleArea(radius)
           << " square " << units << endl;
		}
		cout << endl; // blank line after each result
		cout << "Another circle? (y/n) ";
		cin >> more;
		cout << endl;
  }
  cout << "Good bye!" << endl;
  return 0;
}

double CircleArea(double radius) {
  return PI * radius * radius;
}

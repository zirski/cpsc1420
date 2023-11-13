// Toby Hammond
// lab4.cpp
// October 3, 2023

// Purpose: Gathers information about a person's height, weight and biological
// sex and computes their BMI, as well as evaluates whether the person in
// question is underweight, optimal, or overweight.

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int height;
  int weight;
  char sex;
  string weight_category;

  cout << endl;
  cout << "Enter the person's sex (m/f)." << endl;
  cin >> sex;
  cout << "Enter the person's height (in inches) and weight (in lbs), "
          "separated by a space."
       << endl;
  cin >> height >> weight;

  double bmi = (weight * 703) / pow(height, 2);

  //logic to determine appropriate optimal BMI ranges for given sex
  if (sex == 'm') {
    if (bmi >= 18.5 && bmi <= 25) {
      weight_category = "optimal";
    } else if (bmi < 18.5) {
      weight_category = "underweight";
    } else {
      weight_category = "overweight";
    }
  } else {
    if (bmi >= 18.5 && bmi <= 25) {
      weight_category = "optimal";
    } else if (bmi < 18.5) {
      weight_category = "underweight";
    } else {
      weight_category = "overweight";
    }
  }

  cout << endl;
  cout << "The person's BMI is " << setprecision(1) << fixed << bmi << "."
       << endl;
  cout << "The person's weight is considered to be " << weight_category << "."
       << endl;
  cout << endl;

  return 0;
}

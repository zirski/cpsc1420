#include <iostream>

using namespace std;

int main() {
  int size_of_square = 0;

  while (size_of_square < 1 || size_of_square > 15) {
    cout << "Enter the desired size of the square." << endl;
    cin >> size_of_square;    

    if (size_of_square > 1 && size_of_square < 15) {
      break;
    }
    cout << "Error: please enter a positive integer less than 15.\n" << endl;
  }

  cout << endl;
  for (int i = 0; i < size_of_square; i++) {
    for (int j = 0; j < size_of_square; j++) {
      cout << "X";
    }
    cout << endl;
  }
  cout << endl;
}

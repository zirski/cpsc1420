// Toby Hammond
//  pa3.cpp
//  November 1, 2023
//  Purpose: Checks the validity of sudoku solutions. Takes a file of completed
//  sudoku boards sudoku.in, then evaluates the rows, columns and subgrids of
//  each solution.

#include <fstream>
#include <iostream>

using namespace std;

bool RowChecker(int[][9], int);
bool ColumnChecker(int[][9], int);
bool SubgridChecker(int[][9]);
void GridChecker(int[][9], ofstream &);

const int ARR_SIZE = 9;

int main() {
  ifstream in("sudoku.in");
  ofstream out("sudoku.out");

  if (in) {
    int num_grids;
    in >> num_grids;

    // populates grid(s) from file
    for (int i = 0; i < num_grids; i++) {
      int grid[ARR_SIZE][ARR_SIZE];
      for (int j = 0; j < ARR_SIZE; j++) {
        for (int k = 0; k < ARR_SIZE; k++) {
          in >> grid[j][k];
        }
      }
      GridChecker(grid, out);
    }
  } else {
    cerr << "Error opening the file.";
    return 1;
  }
  in.close();
  out.close();
  return 0;
}

// This function avoids extraneous function calls to SubGridChecker(), since you
// can return early from the function if SubgridChecker() returns false, instead
// of having to include it with the other function calls. There's probably a
// better way to do this, but I find this method makes main() more concise
// anyway.
void GridChecker(int grid[][9], ofstream &out) {
  if (!SubgridChecker(grid)) {
    out << "NO" << endl;
    return;
  } else {
    for (int i = 0; i < ARR_SIZE; i++) {
      if (!RowChecker(grid, i) || !ColumnChecker(grid, i)) {
        out << "NO " << endl;
        return;
      }
    }
  }
  out << "YES" << endl;
}

bool RowChecker(int grid[][ARR_SIZE], int row) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < ARR_SIZE; i++) {
    for (int j = 0; j < ARR_SIZE; j++) {
      if (grid[row][i] == arr[j]) arr[j] = 0;
    }
  }
  int arr_sum = 0;
  for (int i = 0; i < ARR_SIZE; i++) arr_sum += arr[i];
  return arr_sum == 0;
}

bool ColumnChecker(int grid[][ARR_SIZE], int col) {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < ARR_SIZE; i++) {
    for (int j = 0; j < ARR_SIZE; j++) {
      if (grid[i][col] == arr[j]) arr[j] = 0;
    }
  }
  int arr_sum = 0;
  for (int i = 0; i < ARR_SIZE; i++) arr_sum += arr[i];
  return arr_sum == 0;
}

// This function walks through all subgrids horizontally, then vertically. To
// explain, let's express the entire grid as a matrix of x's, where each x
// represents a subgrid:
//
// [ x1 x2 x3 ]
// [ x4 x5 x6 ]
// [ x7 x8 x9 ]
//
// The function walks through the subgrids sequentially: x1, x2, x3 . . . x9.
bool SubgridChecker(int grid[][ARR_SIZE]) {
  // i represents the horizontal "index" of the subgrid.
  for (int i = 0; i <= 6; i += 3) {
    // j represents the same thing, but vertically.
    for (int j = 0; j <= 6; j += 3) {
      // nums acts as a register for the needed digits in a given subgrid for
      // that subgrid to be a valid sudoku solution There needs to be one copy
      // of each element in nums in each subgrid for that subgrid to be valid.
      int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      // k represents the horizontal position of each element in a given
      // subgrid.
      for (int k = 0; k < 3; k++) {
        // j serves the same purpose as k, just vertically.
        for (int l = 0; l < 3; l++) {
          // Goes through all the possible valid digits in nums to check if each
          // digit in the subgrid exists. Basically "ticks" them off one by one
          // until there are only 0s in nums.
          for (int m = 0; m < 9; m++) {
            if (grid[k + i][l + j] == nums[m]) nums[m] = 0;
          }
        }
      }
      int sum;
      // If the solution of a given subgrid is valid, all the values in nums
      // have been changed to 0s, and sum will evaluate to 0. Otherwise, the
      // entire sudoku solution is invalid and the function terminates,
      // returning false.
      for (int v : nums) sum += v;
      if (sum != 0) return false;
    }
  }
  return true;
}
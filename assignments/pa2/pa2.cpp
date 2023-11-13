// Toby Hammond
// pa2.cpp
// October 23, 2023
// Purpose:

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// prototypes
string GetPlayerName();
int Play(string, int, int &);

int main() {
  srand(time(NULL));
  int p1_pos = 0, p2_pos = 0;
  int card = 1;

  cout << "==== Welcome to the 2-player Board Game ====" << endl;
  string p1_name = GetPlayerName();
  string p2_name = GetPlayerName();

  // main gameplay loop: each player plays, then their position is checked to
  // see if they have won.
  while (true) {
    if ((p1_pos = Play(p1_name, p1_pos, card)) >= 90) {
      cout << "The game is over. " << p1_name << " won the game!" << endl;
      return 0;
    }
    if ((p2_pos = Play(p2_name, p2_pos, card)) >= 90) {
      cout << "The game is over. " << p2_name << " won the game!" << endl;
      return 0;
    }
  }
}

string GetPlayerName() {
  static int player_num = 1;
  string name;
  cout << "Player " << player_num << ": Enter a player name:" << endl;
  getline(cin, name);

  // error handling for empty names; apparently length() ignores the delimiter
  // when inputting cin into the string, causing the string to be of length 0.
  while (name.length() == 0) {
    cout << "Please enter a player name:" << endl;
    getline(cin, name);
  }

  player_num++;
  return name;
}

int Play(string player, int pos, int &card_pos) {
  cout << "Press Enter key to roll the virtual dice" << endl;
  cin.get();
  int dice = rand() % 11 + 2;
  pos += dice;
  cout << player << " rolls the dice and gets a value of " << dice
       << ", landing on space " << pos << "." << endl;

  switch (pos) {
    case 10:
    case 60:
    case 70:
    case 80:
      switch (card_pos) {
        case 1:
          pos -= 9;
          break;
        case 2:
          pos = 0;
          break;
        case 3:
          pos -= 3;
          break;
        case 4:
          pos -= 8;
          break;
        case 5:
          pos += 2;
          break;
        case 6:
          pos += 1;
          break;
        case 7:
          pos += 3;
          break;
        case 8:
          pos = 0;
          break;
        case 9:
          pos -= 4;
          break;
        default:
          pos += 6;
      }
      cout << player << " picks the card " << card_pos << ", landing on space "
           << pos << "." << endl;

      // updates the card number, stopping only if we've gone through all the
      // cards.
      card_pos++;
      if (card_pos == 9) card_pos = 0;
      break;
    case 30:
      pos = 69;
      cout << player << " takes the shortcut to 69." << endl;
  }
  return pos;
}

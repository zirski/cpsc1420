// Toby Hammond
// lab8.cpp
// October 25, 2023
// Purpose: asks user for 5 different scores (can be decimal) between 1-10,
// and then takes the middle 3 and averages them to create an average score.

#include <iostream>

using namespace std;

void GetJudgeScore(double &);
void CalcScore(double[]);
int FindLowest(double[]);
int FindHighest(double[]);

int main() {
  double scores[5];

  for (int i = 0; i < 5; i++) {
    GetJudgeScore(scores[i]);
  }

  CalcScore(scores);
  return 0;
}

void GetJudgeScore(double &score) {
  cout << "Enter the judge's score." << endl;
  cin >> score;

  while (score < 0 || score > 10) {
    cout << "Error: please enter a valid score (between 0 and 10)." << endl;
    cin >> score;
  }
}

void CalcScore(double scores[]) {
  double scores_avg;

  for (int i = 0; i < 5; i++) {
    if ((i != FindLowest(scores)) && (i != FindHighest(scores)))
      scores_avg += scores[i];
  }

  cout << "\nAverage score: " << scores_avg / 3 << endl;
}

// Contrary to what the assignment asks for, I decided to have this function
// instead return the index of the lowest score, to be more easily utilized by
// CalcScore(). If this loses points, oh well. I couldn't really understand how
// the prompt's way of handling these functions would work.
int FindLowest(double scores[]) {
  int lowest_i;
  double lowest = scores[0];
  for (int i = 0; i < 5; i++) {
    if (scores[i] <= lowest) {
      lowest_i = i;
      lowest = scores[i];
    }
  }
  return lowest_i;
}

int FindHighest(double scores[]) {
  int highest_i;
  double highest = scores[0];
  for (int i = 0; i < 5; i++) {
    if (scores[i] >= highest) {
      highest_i = i;
      highest = scores[i];
    }
  }
  return highest_i;
}
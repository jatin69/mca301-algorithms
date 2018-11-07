/*
 * Author : Jatin Rohilla
 * Date   : Nov-2018
 *
 * Editor   : Dev c++ 5.11
 * Compiler : g++ 5.1.0
 * flags    : -std=c++14
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

// checks if B is a subSequence of A
bool isSubsequence(vector<string> B, vector<string> A) {

  int m = A.size();
  int n = B.size();

  if (m < n) {
    return false;
  }

  int j = 0;
  for (int i = 0; i < m && j < n; ++i) {
    if (A[i].compare(B[j]) == 0) {
      j++;
    }
  }

  return (j == n);
}

int main() {

  ifstream iob;
  string temp;

  vector<string> A;
  cout << "\nReading events A from file ... ";
  iob.open("eventsA.txt");
  while (getline(iob, temp)) {
    A.push_back(temp);
  }
  iob.close();

  vector<string> B;
  cout << "\nReading events B from file ... ";
  iob.open("eventsB.txt");
  while (getline(iob, temp)) {
    B.push_back(temp);
  }
  iob.close();

  if (isSubsequence(B, A)) {
    cout << "\n\nYes. List of events B is a subsequence of events A.\n";
  } else {
    cout << "\n\nNo. List of events B is not a subsequence of event A.\n";
  }

  return 0;
}

/*
 * Author : Jatin Rohilla
 * Date   : Nov-2018
 *
 * Editor   : Dev c++ 5.11
 * Compiler : g++ 5.1.0
 * flags    : -std=c++14
 *
 */

#include <iostream>
using namespace std;

void printSolution(int **board, int N, int solNo) {

  cout << "\n\n";
  cout << "==============================="
  	   << " Solution " << solNo
       << " ===============================";
  cout << "\n\n";

 cout << "\t";
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (board[i][j])
        cout << "Q";
      else
        cout << "-";
    }
    cout << "\n\t";
  }

  cout << "\n";
  cout << "======================================";
  cout << "======================================";
  cout << "\n";
  
}

bool isSafe(int **board, int N, int row, int col) {

  // Check this row on left side
  for (int i = 0; i < col; i++)
    if (board[row][i])
      return false;

  // Check upper diagonal on left side
  for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    if (board[i][j])
      return false;

  // Check lower diagonal on left side
  for (int i = row, j = col; i < N && j >= 0; i++, j--)
    if (board[i][j])
      return false;

  return true;
}

bool NQueenHelper(int **board, int N, int col, int &solNo) {

  if (col == N) {

    printSolution(board, N, ++solNo);

    cout << "\nPress 'y' N times to see next N Solutions or Press 'n' to exit : ";
    char choice;
    cin >> choice;
    if (choice != 'y') {
      exit(0);
    }

    return true;
  }

  bool res = false;
  for (int row = 0; row < N; row++) {
    // check at board[i][col]
    if (isSafe(board, N, row, col)) {
      board[row][col] = 1;
      res = NQueenHelper(board, N, col + 1, solNo) || res;
      board[row][col] = 0; // backtrack
    }
  }

  return res;
}

void solveNQueen(int N) {

  // allocate board
  int **board = new int *[N];
  for (int i = 0; i < N; i++) {
    board[i] = new int[N]{0};
  }

  int noOfSolutions = 0;
  int startingCol = 0;
  if (!NQueenHelper(board, N, startingCol, noOfSolutions)) {
    cout << "\n\nSolution does not exist.\n";
  }

  if (noOfSolutions) {
    cout << "\n\nTotal " << noOfSolutions << " solutions found.";
  }

  // de-allocate board
  for (int i = 0; i < N; ++i) {
    delete[] board[i];
  }
  delete[] board;
}

int main() {
	
  cout << "\n\t****** N-Queens Problem ******\n\n";

  cout << "Enter n: ";
  int n;
  cin >> n;

  solveNQueen(n);
  return 0;
}

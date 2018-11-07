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

int billboardConst(int M, int n, int x, int position[], int revenue[]) {

  // store revenue at each mile
  int maxRev[M + 1]{0};

  int next = 0;
  for (int i = 1; i <= M; i++) {

    // check if all billboards are already placed.
    if (next < n) {

      // check if we have billboard at this position
      // If not, simply used the previous value
      if (position[next] != i) {
        maxRev[i] = maxRev[i - 1];
      } else {

        // if current pos <= x, then we can have only one billboard.
        if (i <= x) {
          maxRev[i] = max(maxRev[i - 1], revenue[next]);
        } else {
          // place next bill board, or, not place it
          maxRev[i] = max(maxRev[i - x - 1] + revenue[next], maxRev[i - 1]);
        }
        next++;
      }
    } else {
      maxRev[i] = maxRev[i - 1];
    }
  }

  return maxRev[M];
}

int main() {

  cout << "\n ***** Highway Billboard Problem *****\n\n";
  cout << "Enter the length of Highway ( M )        : ";
  int M;
  cin >> M;
  //  M = 20;

  cout << "Enter min distance between 2 billboards  : ";
  int x;
  cin >> x;
  //  x = 5;
  cout << "Enter Number of billboards ( n )         : ";
  int n;
  cin >> n;
  //  n = 4;
  int position[n]; //  {6, 7, 12, 14};
  int revenue[n];  // {5, 6, 5, 1};

  cout << "\n";
  for (int i = 0; i < n; i++) {
    cout << "Position of BillBoard " << i + 1 << " : ";
    cin >> position[i];
    cout << "Revenue  of BillBoard " << i + 1 << " : ";
    cin >> revenue[i];
    cout << "\n";
  }
  cout << "\nMaximum Revenue from billboards : "
       << billboardConst(M, n, x, position, revenue);
  return 0;
}

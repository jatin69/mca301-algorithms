/*
 * Author : Jatin Rohilla
 * Date   : 23-10-2018
 *
 * Editor   : Dev c++ 5.11
 * Compiler : g++ 5.1.0
 * flags    : -std=c++14
 *
 * Objective     : Classic Matrix chain multiplication Problem
 * Major Inputs  : Array of Matrix orders and  Array of Matrix names
 * Major Outputs : Minimum multiplication cost and order of parenthesis
 *
 */

#include <iostream>         // cin, cout
#include <limits.h>         // INT_MAX
#include <vector>           // vector
#include <algorithm>        // iota

using namespace std;

void print2D(vector<vector<int>>& A) {
  if (A.empty()) {
    cout << "Array empty \n";
    return;
  }
  int m = A.size();
  int n = A[0].size();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << A[i][j] << "  ";
    }
    cout << "\n";
  }
  cout << "\n\n";
}

void print1D(vector<int>& A){
  if (A.empty()) {
    cout << "Array empty \n";
    return;
  }
  int m = A.size();
  for (int i = 0; i < m; ++i) {
  	cout << A[i] << " ";
  }
  cout <<"\n\n";
}

void printParenthesisHelper(vector<vector<int>>& brackets, int i, int j, auto& name){
	if(i==j){
		cout << " A" << *name << " " ;
		name++;
		return;
	}
	cout << "(";
	printParenthesisHelper(brackets, i, brackets[i][j], name);
	printParenthesisHelper(brackets, brackets[i][j] + 1, j, name);
	cout << ")";
}

void printParenthesis(vector<vector<int>>& brackets){
	int noOfMatricies = brackets[0].size()-1;

	vector<int> names(noOfMatricies);
	std::iota(names.begin(), names.end(), 1);
	auto it = names.begin();
	printParenthesisHelper(brackets, 1, noOfMatricies, it );
}

int matrixChainMultiplication(vector<int>& order) {

  // no of matricies : from 1 to n
  int n = order.size() - 1;

  // Table rows and columns are labelled from 1 to n
  // so for simplicity allocate n+1 rows and columns
  vector<vector<int>> memo(n + 1, vector<int>(n + 1));
  vector<vector<int>> brackets(n + 1, vector<int>(n + 1));

  // chainSize range is : m[1,1] => m[1,2] => m[1,3] => ... => m[1,n]

  // for chainSize = 1  : m[1,1] .. m[2,2] .. m[n,n] :: multiplication cost = 0
  for (int i = 1; i <= n; ++i) {
    memo[i][i] = 0;
  }

  // for chainSize = 2 to n
  for (int chainSize = 2; chainSize <= n; ++chainSize) {

    // establish an interval (start..end) of size = chainSize
    // and loop through all possible intervals of size = chainSize
    for (int start = 1; start + chainSize - 1 <= n; ++start) {

      int end = start + chainSize - 1;

      int minCostOfInterval = INT_MAX;
      int partitionIndex;

      // partition current interval into subintervals (start..part), (part+1,
      // end) and find out which of them costs minimum
      for (int part = start; part + 1 <= end; ++part) {

        int currentSubIntervalCost =
            memo[start][part] + memo[part + 1][end] +
            order[start - 1] * order[part] * order[end];

        if (currentSubIntervalCost < minCostOfInterval) {
          minCostOfInterval = currentSubIntervalCost;
          partitionIndex = part;
        }
      }
      memo[start][end] = minCostOfInterval;
      brackets[start][end] = partitionIndex;
    }
  }

//  print2D(brackets);
  cout << "\nMultiplication order is : " ; printParenthesis(brackets);
  return memo[1][n];
}

int main() {

  /*
	Matrix number  -         1      2       3        4
	Matricies are  -      (40x20) (20x30) (30x10) (10x30)
	Order Array is - (40,   20,     30,    10,      30)

	Therefore, order of matrix 'i' is given by order[i-1] x order[i]
  */

  	/*
	//   test cases
	1, 2, 3, 4 				 // 18
	40, 20, 30, 10, 30  	 // 260000
	5, 4, 6, 2, 7 			// 158

	*/

	bool shouldContinue ;
	
	do{
		shouldContinue = false;
		cout << "\t****** Matrix Multiplication Program ******\n\n";
		int n;
		cout << "Enter Number of Matricies : " ;
		cin>>n;
		
		vector<int> order;
		int prevDim, rows, columns;

		cout << "\nEnter order of Matrix A" << "1" << " : ";
		cin >> rows >> columns;
		
		order.push_back(rows);
		order.push_back(columns);
		prevDim = columns;

		
		try{
			for(int i=1;i<n;++i){
				cout << "Enter order of Matrix A" << i+1 << " : ";
				cin >> rows >> columns;
				if(rows == prevDim){
					order.push_back(columns);
					prevDim = columns;
				}
				else{
					throw "\nError : Matricies not compatible, Retry ! \n";
				}
			}
			
			cout << "\nMultiplication Cost is  : " << matrixChainMultiplication(order);
		}
		catch(const char* err){
			cout << err;
			shouldContinue = true;
		}
		cout << "\n\n";
	}while(shouldContinue);

  return 0;
}

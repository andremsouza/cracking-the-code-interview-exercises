// Write an algorithm such that if an element in an MxN matrix is 0, its entire
// row and column are set to 0

#include <iostream>
#include <unordered_map>
#include <vector>

// ? Assuming there is a N in the input
// ? Assuming that the four bytes are integers
// ? For convenience, reading integers from text files

// * Solution time complexity: O(n^2)
// * Solution space complexity: O(1)

using namespace std;

void nullifyRow(vector<vector<int> > &t_mat, const int t_row) {
  for (int j = 0; j < (int)t_mat[t_row].size(); j++) {
    t_mat[t_row][j] = 0;
  }
}

void nullifyCol(vector<vector<int> > &t_mat, const int t_col) {
  for (int i = 0; i < (int)t_mat.size(); i++) {
    t_mat[i][t_col] = 0;
  }
}

// receives a square matrix. if an element element is 0, write its entire row
// and column to 0. Changes are in place.
void zeroMatrix(vector<vector<int> > &t_mat) {
  const int n_rows = t_mat.size();
  const int n_cols = (*(t_mat.begin())).size();
  bool row_zero = false, col_zero = false;

  // using first row and column to flag value updates
  for (int j = 0; j < n_cols; j++) {
    if (!t_mat[0][j]) {
      row_zero = true;
      break;
    }
  }
  for (int i = 0; i < n_rows; i++) {
    if (!t_mat[i][0]) {
      col_zero = true;
      break;
    }
  }

  // storing rows and columns of 0 values
  for (int i = 1; i < n_rows; i++) {
    for (int j = 1; j < n_cols; j++) {
      if (!t_mat[i][j]) {
        t_mat[i][0] = 0;  // setting a flag in the first row
        t_mat[0][j] = 0;  // setting a flag in the first column
      }
    }
  }

  // for each row and column found, set values to 0
  for (int i = 1; i < n_rows; i++) {
    if (!t_mat[i][0]) {
      nullifyRow(t_mat, i);
    }
  }
  for (int j = 1; j < n_cols; j++) {
    if (!t_mat[0][j]) {
      nullifyCol(t_mat, j);
    }
  }

  // nullifying first row and column, if necessary
  if (row_zero) {
    nullifyRow(t_mat, 0);
  }
  if (col_zero) {
    nullifyCol(t_mat, 0);
  }
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  // getting dimension from stdin
  int n_rows, n_cols;
  cin >> n_rows >> n_cols;

  // initializing matrix
  vector<vector<int> > mat(n_rows, vector<int>(n_cols));

  // getting input from stdin
  for (auto i = mat.begin(); i < mat.end(); i++)
    for (auto j = (*i).begin(); j < (*i).end(); j++) cin >> *j;

  zeroMatrix(mat);
  // output to stdout
  for (auto i = mat.begin(); i < mat.end(); i++) {
    for (auto j = (*i).begin(); j < (*i).end(); j++) {
      cout << *j << " ";
    }
    cout << endl;
  }

  return 0;
}

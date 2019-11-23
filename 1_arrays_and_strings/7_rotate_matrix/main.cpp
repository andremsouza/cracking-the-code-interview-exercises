// Given an image represented by an NxN matrix, where each pixel in the image is
// 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
// place?

// ? Assuming there is a N in the input
// ? Assuming that the four bytes are integers
// ? For convenience, reading integers from text files

// * Solution time complexity: O(n^2)

#include <iostream>
#include <vector>

using namespace std;

// receives a square matrix. rotates in place
void rotateMatrix(vector<vector<int> > &t_mat) {
  int N = t_mat.size();
  for (int i = 0; i < N / 2; i++) {
    // int first = layer, last = N - 1 - layer;
    for (int j = i; j < N - 1 - i; j++) {
      int top = t_mat[i][j];              // storing top temporarily
      t_mat[i][j] = t_mat[j][N - 1 - i];  // top <- right
      t_mat[j][N - 1 - i] = t_mat[N - 1 - i][N - 1 - j];  // right <- bottom
      t_mat[N - 1 - i][N - 1 - j] = t_mat[N - 1 - j][i];  // bottom <- left
      t_mat[N - 1 - j][i] = top;                          // left <- top
    }
  }
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  // getting dimension from stdin
  int N;
  cin >> N;

  // initializing matrix
  vector<vector<int> > mat(N, vector<int>(N));

  // getting input from stdin
  for (auto i = mat.begin(); i < mat.end(); i++)
    for (auto j = (*i).begin(); j < (*i).end(); j++) cin >> *j;

  rotateMatrix(mat);

  // output to stdout
  for (auto i = mat.begin(); i < mat.end(); i++) {
    for (auto j = (*i).begin(); j < (*i).end(); j++) {
      cout << *j << " ";
    }
    cout << endl;
  }

  return 0;
}

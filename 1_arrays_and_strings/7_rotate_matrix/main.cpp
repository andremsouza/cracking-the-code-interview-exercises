// Given an image represented by an NxN matrix, where each pixel in the image is
// 4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
// place?

// ? Assuming there is a N in the input
// ? Assuming that the four bytes are integers
// ? For convenience, reading integers from text files

// * Solution time complexity: O(n^2)

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Rotates a matrix 90 degrees
 *
 * @details Rotates a matrix 90 degrees. The matrix is represented by a vector
 * of vectors. The rotation is done in place.
 *
 * @param mat Matrix to be rotated
 *
 * @return void
 */
void RotateMatrix(std::vector<std::vector<int> > &mat) {
  auto N = mat.size();
  for (auto i = 0; i < (int)N / 2; i++) {
    // int first = layer, last = N - 1 - layer;
    for (auto j = i; j < (int)N - 1 - i; j++) {
      auto top = mat[i][j];                           // storing top temporarily
      mat[i][j] = mat[j][N - 1 - i];                  // top <- right
      mat[j][N - 1 - i] = mat[N - 1 - i][N - 1 - j];  // right <- bottom
      mat[N - 1 - i][N - 1 - j] = mat[N - 1 - j][i];  // bottom <- left
      mat[N - 1 - j][i] = top;                        // left <- top
    }
  }
}

int main(int argc, char **argv) {
  // matrix smart pointer
  auto mat = std::make_unique<std::vector<std::vector<int> > >();
  if (argc > 1) {  // if parameters are given, read from argv
    auto N = std::atoi(argv[1]);
    // Check if N is a valid number
    if (N <= 0) {
      std::cerr << "Invalid N" << std::endl;
      return 1;
    }
    // Read matrix from argv
    mat = std::make_unique<std::vector<std::vector<int> > >(
        N, std::vector<int>(N));
    // read all next parameters into one string, then get integers from it
    auto str = std::make_unique<std::string>();

    for (auto i = 2; i < argc; i++) *str += argv[i] + std::string(" ");
    auto pos = (size_t)0;

    for (auto i = 0; i < N; i++)
      for (auto j = 0; j < N; j++) {
        (*mat)[i][j] = std::stoi(*str, &pos);
        while (pos < str->size() && std::isspace((*str)[pos])) pos++;
        str->erase(0, pos);
      }
  } else {  // else, read from stdin
    auto N = 0;
    std::cin >> N;
    mat = std::make_unique<std::vector<std::vector<int> > >(
        N, std::vector<int>(N));
    for (auto i = 0; i < N; i++)
      for (auto j = 0; j < N; j++) std::cin >> (*mat)[i][j];
  }

  RotateMatrix(*mat);

  // output to stdout
  for (const auto &i : *mat) {
    for (const auto &j : i) std::cout << j << " ";
    std::cout << std::endl;
  }

  return 0;
}

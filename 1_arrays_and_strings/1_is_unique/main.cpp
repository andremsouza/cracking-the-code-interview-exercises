// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

// Solution 1: using a bit vector
// Solution complexity: O(n) time, O(1) space

#include <array>
#include <cstring>
#include <iostream>
#include <string>

// #define ASCII_SIZE 256
constexpr ushort kAsciiSize = 256;

/**
 * @brief Check if a string has all unique characters.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of arguments passed to the program.
 * @return int Return 0 if successful.
 */
int main(int argc, char const *argv[]) {
  std::array<bool, kAsciiSize> charset = {
      false};                 // bit vector initialized with zeros
  auto is_all_unique = true;  // output flag
  unsigned char c;            // input character

  // Check if parameter is passed
  if (argc > 1) {
    // read input parameter and check bit vector
    for (auto i = 0; i < (int)std::strlen(argv[1]); i++) {
      c = argv[1][i];
      if (charset[c]) {
        is_all_unique = false;
        break;
      }
      charset[c] = true;
    }
  } else {
    // read input from stdin and check bitvector
    while (std::cin >> c) {
      if (charset[c]) {
        is_all_unique = false;
        break;
      }
      charset[c] = true;
    }
  }

  // Print output to stdout
  std::cout << is_all_unique << std::endl;

  return 0;
}

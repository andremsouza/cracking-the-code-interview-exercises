// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

// Solution 1: using a bit vector
// Solution complexity: O(n) time, O(1) space

#include <array>
#include <iostream>
#include <string>

// #define ASCII_SIZE 256
constexpr ushort kAsciiSize = 256;

// int main(int argc, char const *argv[]) { // not using argc/argv
int main() {
  std::array<bool, kAsciiSize> charset = {
      false};                 // bit vector initialized with zeros
  auto is_all_unique = true;  // output flag
  unsigned char c;            // input character

  // read input from stdin and check bitvector
  while (std::cin >> c) {
    if (charset[c]) {
      is_all_unique = false;
      break;
    }
    charset[c] = true;
  }

  // Print output to stdout
  std::cout << "Unique: " << is_all_unique << std::endl;

  return 0;
}
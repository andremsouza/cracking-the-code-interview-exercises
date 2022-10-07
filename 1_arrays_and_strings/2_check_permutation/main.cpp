// Given two strings, write a method to decide if one is a permutation of the
// other.

#include <array>
#include <iostream>
#include <string>

constexpr ushort kAsciiSize = 256;

// Receives two strings (a and b), and check if b is a permutation of a
// Solution complexity (worst case): O(n) time, O(1) space
// Best case: O(1) time, O(1) space
bool IsPermutation(const std::string &a, const std::string &b) {
  // a permutation should have the same number of characters
  if (a.length() != b.length()) return false;
  // using counter vector for each possible character (ASCII)
  std::array<int, kAsciiSize> count_vector = {0};

  // counting number of characters of each string (a and b)
  for (auto i = 0; i < (int)a.length(); i++)
    count_vector[a[i]]++, count_vector[b[i]]--;

  // checking if any index on the counter is "unbalanced", i.e., != 0
  for (const auto &count : count_vector)
    if (count) return false;

  return true;
}

int main(int argc, char **argv) {
  std::string a, b;  // storing strings from input

  // reading strings from input
  if (argc > 2) {  // if two strings are passed as arguments
    a = argv[1];
    b = argv[2];
  } else {  // if no arguments are passed, read from stdin
    std::getline(std::cin, a);
    std::getline(std::cin, b);
  }

  std::cout << IsPermutation(a, b) << std::endl;

  return 0;
}

// Given a string, write a function to check if it is a permutation of a
// palindrome. A palindrome is a word or phrase that is the same forwards and
// backwards. A permutation is a rearrangement of letters. The palindrome does
// not need to be limited to just dictionary words.
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat", "atco cta", etc.)

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

constexpr ushort kAsciiSize = 256;

/**
 * @brief Check if a string is a permutation of a palindrome.
 *
 * @details Defining palindrome properties:
 *  1. The string is a palindrome if it has even number of each character.
 *  2. If the string has an odd length, only one character count is odd
 *  4. The string is a permutation of a palindrome if it satisfies the above
 *  Solution complexity: O(n) time, O(1) space
 *
 * @param str String to check.
 * @return true If the string is a permutation of a palindrome.
 * @return false If the string is not a permutation of a palindrome.
 */
bool IsPalindromePermutation(const std::string& str) {
  ushort count_vector[kAsciiSize] = {0};
  for (const auto& c : str)
    if (c != ' ') count_vector[c]++;

  auto one_odd = false;
  for (const auto& c : count_vector) {
    if (c % 2 != 0) {  // Check if the character count is odd
      if (one_odd) {   // If we already have one odd, return falset
        return false;
      }
      one_odd = true;  // If we don't have one odd, set it to true
    }
  }
  return true;
}

/**
 * @brief Main function.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of arguments passed to the program.
 * @return int Return 0 if successful.
 */
int main(int argc, char** argv) {
  std::unique_ptr<std::string> str = std::make_unique<std::string>();
  if (argc > 1) {  // If a string is passed as argument
    *str = argv[1];
  } else {  // If no arguments are passed, read from stdin
    std::getline(std::cin, *str);
  }
  // convert to lowercase
  std::transform(str->begin(), str->end(), str->begin(), ::tolower);

  // print result
  std::cout << IsPalindromePermutation(*str) << std::endl;
  // Note: str is automatically deleted when it goes out of scope
  return 0;
}

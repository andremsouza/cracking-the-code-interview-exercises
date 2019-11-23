// Given a string, write a function to check if it is a permutation of a
// palindrome. A palindrome is a word or phrase that is the same forwards and
// backwards. A permutation is a rearrangement of letters. The palindrome does
// not need to be limited to just dictionary words.
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat", "atco cta", etc.)

// * Solution time complexity: O(n), n -> string size
// * Solution space complexity: O(1), ignoring the string size

#include <algorithm>
#include <iostream>
#include <string>

#define ASCII_SIZE 256

using namespace std;

// This function receives a string, and checks if it's a permutation of a
// palindrome.
// defining palindrome properties:
// 1. the count of characters is always even, if the string has an even length
// 2. if the string has an odd length, only one character count is odd
bool isPalindromePermutation(string t_str) {
  // removing spaces to count characters
  // converting string to lowercase. ignoring character case
  t_str.erase(std::remove(t_str.begin(), t_str.end(), ' '), t_str.end());
  transform(t_str.begin(), t_str.end(), t_str.begin(),
            [](unsigned char c) { return tolower(c); });

  int count_vec[ASCII_SIZE] = {0};
  int size = t_str.length();
  bool is_pp = true, one_odd = false;

  // counting each character from the string
  for (int i = 0; i < size; i++) {
    count_vec[(int)t_str[i]]++;
  }

  // verifying is the string is a palindrome permutation
  for (int i = 0; i < ASCII_SIZE; i++) {
    if (size % 2) {
      if (count_vec[i] % 2) {
        if (one_odd) {
          is_pp = false;
          break;
        } else {
          one_odd = true;
        }
      }
    } else if (count_vec[i] % 2) {
      is_pp = false;
      break;
    }
  }

  return is_pp;
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  string str;

  // receiving string from stdin
  getline(cin, str);

  cout << "isPalindromePermutation = " << isPalindromePermutation(str) << endl;

  return 0;
}

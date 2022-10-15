// There are three types of edits that can be performed on strings: insert a
// character, remove a character, or replace a character. Given two strings,
// write a function to check if they are one edit (or zero edits) away
// EXAMPLE
// pale, ple -> true
// pales, pale -> true
// pale, bale -> true
// pale, bake -> false
// ple, pale

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Check if a string is one replacement away from another.
 *
 * @param str1 First string.
 * @param str2 Second string.
 * @return true If the strings are one replacement away.
 * @return false If the strings are not one replacement away.
 */
bool IsReplaceChar(std::string str1, std::string str2) {
  auto isReplaceChar = false;
  if (str1.length() != str2.length()) return false;
  for (int i = 0; i < (int)str1.length(); i++)
    if (str1[i] != str2[i]) {
      if (isReplaceChar) return false;
      isReplaceChar = true;
    }

  return true;
}

/**
 * @brief Check if a string is one insertion or deletion away from another
 *
 * @param str1 First string
 * @param str2 Second string
 * @return true If the strings are one insertion or deletion away
 * @return false If the strings are not one insertion or deletion away
 */
bool IsInsertChar(std::string str1, std::string str2) {
  auto index1 = 0, index2 = 0;
  if (str1.length() + 1 != str2.length()) return false;
  while (index1 < (int)str1.length() && index2 < (int)str2.length())
    if (str1[index1] != str2[index2]) {
      if (index1 != index2) return false;
      index2++;
    } else {
      index1++;
      index2++;
    }

  return true;
}

/**
 * @brief Check if a string is one edit away from another string.
 *
 * @details Defining edit properties:
 *  1. The string is one edit away if it has the same length.
 *  2. The string is one edit away if it has one character replaced.
 *  3. The string is one edit away if it has one character inserted.
 *  Solution complexity: O(n) time, O(1) space
 *
 * @param str1 First string.
 * @param str2 Second string.
 * @return true If the string is one edit away from another string.
 * @return false If the string is not one edit away from another string.
 */
bool IsOneEditAway(std::string str1, std::string str2) {
  if (str1 == str2) return true;  // if strings are equal, return true
  if (str1.length() == str2.length())
    return IsReplaceChar(str1, str2);
  else if (str1.length() + 1 == str2.length())
    return IsInsertChar(str1, str2);
  else if (str1.length() - 1 == str2.length())
    return IsInsertChar(str2, str1);
  return false;  // if strings are not equal and not one edit away, return false
}

/**
 * @brief Main function.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of arguments passed to the program.
 * @return int Return 0 if successful.
 */
int main(int argc, char *argv[]) {
  auto str1 = std::make_unique<std::string>();
  auto str2 = std::make_unique<std::string>();

  if (argc > 2) {  // If a string is passed as argument
    *str1 = argv[1];
    *str2 = argv[2];
  } else {  // If no arguments are passed, read from stdin
    std::getline(std::cin, *str1);
    std::getline(std::cin, *str2);
  }

  // print result
  std::cout << IsOneEditAway(*str1, *str2) << std::endl;

  return 0;
}

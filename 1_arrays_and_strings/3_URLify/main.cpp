// Write a method to replace all spaces in a string with '%20'. You may assume
// that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string. (Note: If
// implementing in Java, please use a character array so that you can perform
// this operation in place.)
//
// Using cstring to simulate exercise limitations
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>  // for smart pointers
#include <string>

/**
 * @brief Convert a string to a URL
 * @details Spaces are replaced with '%20'. The function replaces the original
 *  character array, so the size of the array must be at least the size of the
 *  original string. Solution is O(n) time and O(1) space.
 *
 * @param str Pointer to the character array to be URLified
 * @param size The size of the original string
 */
void URLify(char *str, const int &size) {
  auto count_spaces = 0;
  // counting number of spaces to calculate new size of the array
  for (auto i = 0; i < size; i++)
    if (str[i] == ' ') count_spaces++;
  // calculating new size and inserting terminating character '\0'
  auto index = size + count_spaces * 2;
  str[index] = '\0';

  // replacing spaces with "%20", from the end to the beginning
  for (auto i = size - 1; i >= 0; i--) {
    if (str[i] == ' ') {
      str[index-- - 1] = '0';
      str[index-- - 1] = '2';
      str[index-- - 1] = '%';
    } else {
      str[index-- - 1] = str[i];
    }
  }
}

// int main(int argc, char **argv) { // not using argc/argv
/**
 * @brief Main function
 *
 * @return int Code of execution
 */
int main(void) {
  std::string str;
  int size;
  // getting string and "real" size from stdin
  // using string to read from stdin for convenience
  std::getline(std::cin, str);
  std::cin >> size;
  // creating char array from string
  auto cstr = std::make_unique<char[]>(str.size() + 1);
  std::strncpy(cstr.get(), str.c_str(), str.length() + 1);
  cstr[str.length()] = '\0';  // adding terminating character for safety

  // URLifying the string
  URLify(cstr.get(), size);

  // printing URLified string
  std::cout << cstr.get() << std::endl;

  // NOTE: cstr will be automatically deleted when it goes out of scope
  return EXIT_SUCCESS;
}

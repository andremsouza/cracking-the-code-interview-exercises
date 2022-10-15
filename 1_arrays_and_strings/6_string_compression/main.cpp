// Implement a method to perform basic string compression using the counts of
// repeated characters. For example, the string aabcccccaaa would become
// a2b1c5a3. If the "compressed" string would not become smaller than the
// original string, your method should return the original string. You can
// assume the string has only uppercase and lowercase letters (a-z).

// * Solution time complexity: O(n). The string concatenation also has a
// *  linear complexity.
// * Solution space complexity: O(n). At the worst case, the resulting string
// *  will need 2 * n characters.

#include <iostream>
#include <memory>
#include <string>

/**
 * @brief Compresses a string using the counts of repeated characters.
 *
 * @details The function iterates over the string and counts the number of
 *  repeated characters. If the compressed string would not become smaller than
 *  the original string, the function returns the original string.
 *  Solution complexity: O(n) in time and O(n) in space.
 *
 * @param str The string to be compressed.
 * @return The compressed string.
 */
std::string compressString(const std::string &str) {
  if (!str.length()) return str;  // if string is empty, return it
  auto cur = str.front();         // stores current character from string
  auto cur_freq = 0;              // stores frequency of current character
  auto ret = std::string();       // stores the resulting string

  for (const auto &c : str)
    // if character changes, write current character and count to ret string
    // then, begin counting the new character
    // else, increment count of current character
    if (c != cur) {
      ret += cur + std::to_string(cur_freq);
      if (ret.length() >= str.length()) return str;
      cur = c;
      cur_freq = 1;
    } else {
      cur_freq++;
    }

  ret += cur + std::to_string(cur_freq);
  return ret.length() < str.length() ? ret : str;
}

int main(int argc, char **argv) {
  auto str = std::make_unique<std::string>();

  if (argc > 1)
    *str = argv[1];
  else
    std::getline(std::cin, *str);

  // print result
  std::cout << compressString(*str) << std::endl;
  return 0;
}

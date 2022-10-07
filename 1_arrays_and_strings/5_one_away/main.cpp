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
#include <string>

bool IsReplaceChar(std::string str1, std::string str2) {
  auto isReplaceChar = false;
  if (str1.length() != str2.length()) return false;
  for (int i = 0; i < str1.length(); i++) {
    if (str1[i] != str2[i]) {
      if (isReplaceChar) {
        return false;
      }
      isReplaceChar = true;
    }
  }
  return true;
}

bool IsInsertChar(std::string str1, std::string str2) {
  auto index1 = 0, index2 = 0;
  if (str1.length() + 1 != str2.length()) return false;
  while (index1 < str1.length() && index2 < str2.length()) {
    if (str1[index1] != str2[index2]) {
      if (index1 != index2) {
        return false;
      }
      index2++;
    } else {
      index1++;
      index2++;
    }
  }
  return true;
}

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

// int main(int argc, char *argv[]) { // not using argc and argv for now
int main(void) {
  std::string str1, str2;

  // read input strings from stdin
  std::cin >> str1 >> str2;

  // print result
  std::cout << IsOneEditAway(str1, str2) << std::endl;

  return 0;
}

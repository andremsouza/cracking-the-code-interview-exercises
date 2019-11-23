// Assume you have a method isSubstring which checks if one word is a substring
// of another. Given two strings, s1 and s2, write code to check if s2 is a
// rotation of s1 using only one call to isSubstring (e.g., "waterbottle" is a
// rotation of "erbottlewat").

// * Solution time complexity: O(n), from string.find()
// * Solution space complexity: O(n), from duplication of the second string

#include <bitset>
#include <iostream>
#include <string>
#include <vector>

#define ASCII_SIZE 256

using namespace std;

bool isRotation(string t_a, string t_b) {
  // trivial case: compare lengths of strings
  if (t_a.length() == t_b.length() && t_a.length() > 0) {
    // duplicating second string
    const string b_dup = t_b + t_b;
    // using "isSubstring" once
    if (b_dup.find(t_a) != b_dup.npos) return true;
  }
  return false;
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  string a, b;

  // receiving input strings from stdin
  getline(cin, a);
  getline(cin, b);

  cout << isRotation(a, b) << endl;

  return 0;
}

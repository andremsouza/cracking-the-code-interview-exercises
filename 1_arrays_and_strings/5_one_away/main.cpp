// There are three types of edits that can be performed on strings: insert a
// character, remove a character, or replace a character. Given two strings,
// write a function to check if they are one edit (or zero edits) away
// EXAMPLE
// pale, ple -> true
// pales, pale -> true
// pale, bale -> true
// pale, bake -> false
// ple, pale

// * Solution time complexity: O(n), n -> length of shorter string
// * Solution space complexity: O(1)

#include <iostream>
#include <string>

using namespace std;

bool isReplace(string t_a, string t_b) {
  bool one_replace = false;
  // checking length of each string
  if (t_b.length() == t_a.length()) {
    // comparing character by character
    for (int i = 0; i < (int)t_a.length(); i++) {
      // if character is different, check one_replace flag
      if (t_a[i] != t_b[i]) {
        if (one_replace) {
          // if a replacement was already detected before, return false
          return false;
        } else {
          one_replace = true;
        }
      }
    }
    return one_replace;
  } else {
    // if invalid length, return false
    return false;
  }
}

bool isAddition(string t_a, string t_b) {
  bool one_addition = false;
  int i = 0, j = 0;
  // checking length of each string
  if (t_b.length() == t_a.length() + 1) {
    // comparing character by character
    while (i < (int)t_a.length() && j < (int)t_b.length()) {
      // if char is different, advance on second string and set flag
      if (t_a[i] != t_b[j]) {
        j++;
        if (one_addition) {
          // if addition already detected, return false
          return false;
        } else {
          one_addition = true;
        }
      } else {
        i++, j++;
      }
    }
    // if the insertion is at the end of t_a
    if (i == (int)t_a.length()) {
      one_addition = true;
    }
    return one_addition;
  } else {
    // invalid length -> not an addition
    return false;
  }
}

bool isOneEdit(string t_a, string t_b) {
  // if strings are equal, return true
  if (!t_a.compare(t_b)) {
    return true;
  }
  if (t_b.length() == t_a.length()) {
    // checking replacement
    return isReplace(t_a, t_b);
  } else if (t_b.length() == t_a.length() + 1) {
    // checking addition
    return isAddition(t_a, t_b);
  } else if (t_b.length() == t_a.length() - 1) {
    // checking remove
    return isAddition(t_b, t_a);
  } else {
    // base case
    return false;
  }
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  string a, b;

  // reading string from stdin
  getline(cin, a);
  getline(cin, b);

  // checking and writing output to stdout
  cout << "isOneEdit = " << isOneEdit(a, b) << endl;

  return 0;
}

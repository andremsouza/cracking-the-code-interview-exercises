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
#include <string>

using namespace std;

string compressString(const string t_str) {
  // if string is empty, return it
  if (!t_str.length()) {
    return t_str;
  }
  char cur = t_str.front();  // stores current character from string
  int cur_freq = 0;          // stores frequency of current character
  string ret;                // stores returning string

  for (char const &c : t_str) {
    // if character changes, write current character and count to ret string
    // then, begin counting the new character
    // else, increment count of current character
    if (c != cur) {
      ret += cur + to_string(cur_freq);
      cur = c;
      cur_freq = 1;
    } else {
      cur_freq++;
    }
  }
  ret += cur + to_string(cur_freq);
  return ret.length() < t_str.length() ? ret : t_str;
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  string a;
  // getting string from stdin
  getline(cin, a);
  cout << compressString(a) << endl;
  return 0;
}

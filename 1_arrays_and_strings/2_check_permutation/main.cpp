// Given two strings, write a method to decide if one is a permutation of the
// other.

#include <iostream>
#include <string>

#define ASCII_SIZE 256

using namespace std;

// receives two strings, and check if b is a permutation of a
bool isPermutation(string t_a, string t_b) {
  // a permutation should have the same number of characters
  if (t_a.length() != t_b.length()) {
    return false;
  }
  // using counter vector for each possible character
  int countvec[ASCII_SIZE] = {0};

  // counting number of characters of each string
  for (int i = 0; i < (int)t_a.length(); i++) {
    countvec[(int)t_a[i]]++;
    countvec[(int)t_b[i]]--;
  }

  // checking if any index on the counter is "unbalanced"
  for (int i = 0; i < ASCII_SIZE; i++) {
    if (countvec[i]) {
      return false;
    }
  }

  return true;
}

// int main(int argc, char **argv){ // not using argc / argv
int main(void) {
  string a, b;

  getline(cin, a);
  getline(cin, b);

  cout << "Is_permutation = " << isPermutation(a, b) << endl;
  // main
  return 0;
}

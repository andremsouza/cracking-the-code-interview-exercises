// Write a method to replace all spaces in a string with '%20'. You may assume
// that the string has sufficient space at the end to hold the additional
// characters, and that you are given the "true" length of the string. (Note: If
// implementing in Java, please use a characer array so that you can perform
// this operation in place.)

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#define ASCII_SIZE 256

using namespace std;

// Gets an char *t_str, with at least t_size characters. Converts the original
// character array to an URLified version, replacing spaces ' ' with  "%20".
// ! NOTE: This operation is done in place of the original char *.
// ! The original array should have enough space to store the additional chars.
void URLify(char *t_str, int t_size) {
  int count_spaces = 0, index;
  // counting number of spaces to calculate new size of the array
  for (int i = 0; i < t_size; i++) {
    if (t_str[i] == ' ') {
      count_spaces++;
    }
  }

  // calculating new size and inserting terminating character '\0'
  index = t_size + count_spaces * 2;
  t_str[index] = '\0';

  // replacing spaces with "%20", from the end to the beggining
  for (int i = t_size - 1; i >= 0; i--) {
    if (t_str[i] == ' ') {
      t_str[index-- - 1] = '0';
      t_str[index-- - 1] = '2';
      t_str[index-- - 1] = '%';
    } else {
      t_str[index-- - 1] = t_str[i];
    }
  }
}

// int main(int argc, char **argv) { // not using argc/argv
int main(void) {
  string str;
  char *cstr;
  int size;

  // getting string and "real" size from stdin
  // using string to read from stdin for convenience
  getline(cin, str);
  cin >> size;

  // getting char array from string
  cstr = new char[str.length() + 1];
  strcpy(cstr, str.c_str());

  // getting URLified string
  URLify(cstr, size);

  // printing output string
  cout << string(cstr) << endl;

  delete[] cstr;
  return 0;
}

// Implement an algorithm to determine if a string has all unique characters.
// What if you cannot use additional data structures?

#include <cstdio>
#include <cstdlib>

#define ASCII_SIZE 256

using namespace std;

// int main(int argc, char const *argv[]) { // not using argc/argv
int main(void) {
  bool charset[ASCII_SIZE] = {0};  // bit vector initialized with zeros
  bool is_all_unique = true;
  char c;

  // reading input from stdin and checking bitvector
  while (scanf("%c", &c) != EOF) {
    if (charset[(int)c]) {
      is_all_unique = false;
      break;
    }
    charset[(int)c] = true;
  }

  // printing output to stdout
  printf("Unique: %d\n", is_all_unique);

  return 0;
}

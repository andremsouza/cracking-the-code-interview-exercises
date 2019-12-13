// You have two numbers represented by a linked list, where each node contains a
// single digit. The digits are stored in reverse order, such that the 1's digit
// is at the head of the list. Write a function that adds the two numbers and
// returns the sum as a linked list.
// EXAMPLE
// Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295
// Output: 2 -> 1 -> 9. That is, 912
// FOLLOW UP
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE
// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295
// Output: 9 -> 1 -> 2. That is, 912

// * Solution 1 (reverse) time complexity: O(n)
// * Solution 1 (reverse) space complexity: O(n)

// * Solution 2 time complexity: O(n)
// * Solution 2 space complexity: O(n)

#include <forward_list>
#include <iostream>
#include <string>

typedef unsigned char uchar;

using namespace std;

forward_list<uchar> sumListReverse(const forward_list<uchar> &t_a,
                                   const forward_list<uchar> &t_b) {
  forward_list<uchar> sum;
  auto it_sum = sum.before_begin();
  auto it_a = t_a.begin(), it_b = t_b.begin();
  uchar d_sum, carry = 0;

  // checking if any list is empty
  if (t_a.empty()) return t_b;
  if (t_b.empty()) return t_a;

  // iterating and calculating sum of each position, with carryover
  while (it_a != t_a.end() || it_b != t_a.end()) {
    d_sum = static_cast<uchar>((it_a == t_a.end() ? 0 : *it_a - '0') +
        (it_b == t_b.end() ? 0 : *it_b - '0') + carry);
    carry = static_cast<uchar>(d_sum / 10);
    d_sum = static_cast<uchar>(d_sum % 10);
    it_sum = sum.insert_after(it_sum, d_sum + '0');
    if (it_a != t_a.end()) it_a = next(it_a);
    if (it_b != t_a.end()) it_b = next(it_b);
  }

  // last carryover
  if (carry) {
    sum.insert_after(it_sum, carry + '0');
  }

  return sum;
}

void sumListRec(forward_list<uchar>& t_sum, const forward_list<uchar>& t_a,
                const forward_list<uchar>& t_b,
                const forward_list<uchar>::const_iterator t_it_a,
                const forward_list<uchar>::const_iterator t_it_b,
                int* t_carry) {
  // go recursively to the end of the lists
  if (t_it_a == t_a.end() && t_it_b == t_b.end()) {
    return;
  }
  if (t_it_a == t_a.end()) {
    sumListRec(t_sum, t_a, t_b, t_it_a, next(t_it_b), t_carry);
  } else if (t_it_b == t_b.end()) {
    sumListRec(t_sum, t_a, t_b, next(t_it_a), t_it_b, t_carry);
  } else {
    sumListRec(t_sum, t_a, t_b, next(t_it_a), next(t_it_b), t_carry);
  }
  int d_sum = (t_it_a == t_a.end() ? 0 : *t_it_a - '0') +
              (t_it_b == t_b.end() ? 0 : *t_it_b - '0') + *t_carry;
  // calculate sum and carry
  *t_carry = d_sum / 10;
  d_sum = d_sum % 10;
  // push to the front of the sum list
  t_sum.push_front(static_cast<uchar &&>(d_sum + '0'));
}

forward_list<uchar> sumList(forward_list<uchar> t_a, forward_list<uchar> t_b) {
  forward_list<uchar> sum;
  int carry = 0;

  // checking if any list is empty
  if (t_a.empty()) return t_b;
  if (t_b.empty()) return t_a;

  // padding shorter list with zeroes
  unsigned int count_a = 0, count_b = 0;
  auto it_a = t_a.begin(), it_b = t_b.begin();
  while (it_a != t_a.end() || it_b != t_a.end()) {
    if (it_a != t_a.end()) {
      it_a = next(it_a);
      count_a++;
    }
    if (it_b != t_a.end()) {
      it_b = next(it_b);
      count_b++;
    }
  }
  while (count_a < count_b) {
    t_a.push_front('0');
    count_a++;
  }
  while (count_b < count_a) {
    t_b.push_front('0');
    count_b++;
  }

  // calling recursive function
  sumListRec(sum, t_a, t_b, t_a.begin(), t_b.begin(), &carry);
  if (carry) sum.push_front(static_cast<uchar &&>(carry + '0'));

  return sum;
}

// int main(int argc, char **argv) { // not using argc/argv
int main() {
  forward_list<uchar> a, b, sum, sum_rev;
  auto it = a.before_begin();
  string str;

  // receiving lists from standard input

  getline(cin, str);
  for (const auto &c : str) {
    if (c < '0' || c > '9') {
      cout << "Invalid input character: " << c << endl;
      exit(1);
    }
    it = a.insert_after(it, (uchar &&) c);
  }

  it = b.before_begin();
  getline(cin, str);
  for (const auto& c : str) {
    if (c < '0' || c > '9') {
      cout << "Invalid input character: " << c << endl;
      exit(1);
    }
    it = b.insert_after(it, (uchar &&) c);
  }

  // calculating sum of lists a and b
  sum_rev = sumListReverse(a, b);
  sum = sumList(a, b);

  // writing output to standard output

  for (const auto& i : sum_rev) {
    cout << i << " ";
  }
  cout << endl;

  for (const auto& i : sum) {
    cout << i << " ";
  }
  cout << endl;

  return 0;
}

#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
  int i = 0, j = A.size() - 1, r = -1;

  while (i <= j) {
    int m = i + ((j - i) / 2);
    if (A[m] > k)
      j = m - 1;
    else if (A[m] == k) {
      r = m;
      j = m - 1;
    }
    else {
      i = m + 1;
    }
  }

  return r;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                         &SearchFirstOfK, DefaultComparator{}, param_names);
}

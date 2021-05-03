#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void rec_perm(vector<int> A, const int c, vector<vector<int>>& res) {
  if (c == A.size()) {
    res.emplace_back(A);
  }

  for(int i = c; i < A.size(); i++) {
    if (i != c) {
      std::swap(A[i], A[c]);
    }
    rec_perm(A, c + 1, res);
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  vector<vector<int>> res;
  rec_perm(A, 0, res);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}

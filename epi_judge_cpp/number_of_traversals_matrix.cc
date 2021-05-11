#include <algorithm>
#include <memory>
#include<vector>

using std::make_unique;
using std::vector;

#include "test_framework/generic_test.h"

int dfs(int i, int j, vector<vector<int>>* num_ptr) {
    vector<vector<int>> &num = *num_ptr;
    if(i == 0 && j == 0) {
        return 1;
    }
    if (num[i][j] == 0) {
        int n_i = i == 0 ? 0 : dfs(i - 1, j, num_ptr);
        int n_j = j == 0 ? 0 : dfs(i, j - 1, num_ptr);
        num[i][j] = n_i + n_j;
    }
    return num[i][j];
}


int NumberOfWays(int n, int m) {
  return dfs(n-1, m-1, make_unique<vector<vector<int>>>(n, vector<int>(m, 0)).get());
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}

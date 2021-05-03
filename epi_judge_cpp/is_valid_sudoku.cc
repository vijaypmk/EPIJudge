#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  bool row[9][9] = {false}, col[9][9] = {false}, box[9][9] = {false};
  for (int i = 0; i < 9; i++)
    for(int j = 0; j < 9; j++) {
        int num = partial_assignment[i][j] - 1;
        if (num < 0)
          continue;
        int k = (i / 3) * 3 + (j / 3);
        if (row[i][num] || col[j][num] || box[k][num])
          return false;
        row[i][num] = col[j][num] = box[k][num] = true;
    }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}

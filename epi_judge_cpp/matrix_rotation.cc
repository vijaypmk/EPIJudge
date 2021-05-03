#include <iostream>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  if (square_matrix_ptr == NULL)
    return;
  int i, j;
  vector<vector<int>>& matrix = *square_matrix_ptr;
  int n = matrix.size();
  if(n < 1)
    return;
  int m = matrix[0].size();
  // swap along diag
  for (i = 0; i < n; i++)
    for (j = i + 1; j < m;j++) {
        int t = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = t;
    }
  // reverse
  for (i = 0; i < n; i++) {
    std::reverse(matrix[i].begin(), matrix[i].end());
  }
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}

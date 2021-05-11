#include <algorithm>
#include <iterator>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::next;
using std::priority_queue;
using std::vector;


vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
  
  struct iter_check {
    bool operator<(const iter_check& that) const {
      return current > that.current;
    }

    int current, array_pos, in_array;
  };

  priority_queue<iter_check> min_heap;
  for (auto i = 0; i < sorted_arrays.size(); i++) {
    if (sorted_arrays[i].size() <= 0)
      continue;
    min_heap.push({sorted_arrays[i][0], i, 0});
  }

  vector<int> res;
  while (!min_heap.empty()) {
    auto [v, c, p] = min_heap.top();
    res.emplace_back(v);
    p++;
    if (p < sorted_arrays[c].size())
      min_heap.push({sorted_arrays[c][p], c, p});
    min_heap.pop();
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}

#include <algorithm>
#include <iterator>
#include <queue>
#include <vector>

#include "test_framework/generic_test.h"
using std::greater;
using std::next;
using std::priority_queue;
using std::vector;

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
  
  struct iter_check {
    bool operator< (const iter_check& that) const {
      return that.current < current;
    }

    int current, pos;
  };

  priority_queue<iter_check> min_heap;

  if (sequence_begin == sequence_end)
    return {};

  int i = 0;
  min_heap.push({*sequence_begin++, i++});

  vector<int> res;
  while (sequence_begin != sequence_end) 
  {
    auto [c, p] = min_heap.top();
    if (p >= k) {
      res.emplace_back(c);
      min_heap.pop();
    }
    min_heap.push({*sequence_begin++, i++});
  }

  while (!min_heap.empty()) {
    auto [c, p] = min_heap.top();
    res.emplace_back(c);
    min_heap.pop();
  }
  
  return res;
}

vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,
                                               int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}

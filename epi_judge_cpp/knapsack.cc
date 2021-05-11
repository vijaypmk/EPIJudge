#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item {
  int weight, value;
};

int dfs(const vector<Item>& items, int capacity, int k, vector<vector<int>>& p) {
  if (k < 0)
    return 0;

  if(p[k][capacity] < 0) {
    int without_item = dfs(items, capacity, k - 1, p);
    int with_item = capacity < items[k].weight ? 0 : dfs(items, capacity - items[k].weight, k - 1, p) + items[k].value;
    p[k][capacity] = std::max(without_item, with_item);
  }

  return p[k][capacity];
}

int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
  vector<vector<int>> vec(items.size(), vector<int>(capacity + 1, -1));
  return dfs(items, capacity, items.size() - 1, vec);
}
namespace test_framework {
template <>
struct SerializationTrait<Item> : UserSerTrait<Item, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}

#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;
using std::unordered_map;

int FindNearestRepetition(const vector<string>& paragraph) {
  unordered_map<string, int> h;

  int m = -1;
  for (int i = 0; i < paragraph.size(); i++) {
    if(!h.count(paragraph[i])) {
      h.insert({paragraph[i], i});
    }
    else {
      auto v = h.find(paragraph[i]);
      if (m < 0)
        m = 100000;
      m = m < (i - v->second) ? m : (i - v->second);
      v->second = i;
    }
  }

  return m;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}

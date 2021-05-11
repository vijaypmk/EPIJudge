#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_map;

bool CanFormPalindrome(const string& s) {
  unordered_map<int, int> h;
  for (auto i : s) {
    if (i == ' ')
      continue;
    if(h.count(i) == 0) {
      h.insert({i, 1});
    }
    else {
      auto t = h.find(i);
      t->second++;
    }
  }

  bool c = true;
  for (const auto & [k, v] : h) {
    if ((s.size() % 2) == 0) {
      if ((v % 2) == 1)
        return false;
    }
    else {
      if (c and (v % 2 == 1))
        c = false;
      else if (!c and (v % 2 == 1))
        return false;
    }
  }

  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}

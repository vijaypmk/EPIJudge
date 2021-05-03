#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;

void ReverseWords(string* s) {
  string &ss = *s;
  char sp = ' ';
  reverse(ss.begin(), ss.end());

  int i = -1, j = 0, n = ss.size();
  while (j < n) {
    if ((char)ss[j] == sp) {
      int t = j - 1;
      i++;
      while (i < t) {
        std::swap(ss[i], ss[t]);
        i++;
        t--;
      }
      i = j;
    }
    j++;
  }

  i++;j--;
  while (i < j) {
    std::swap(ss[i], ss[j]);
    i++;
    j--;
  }

  return;
}
string ReverseWordsWrapper(TimedExecutor& executor, string s) {
  string s_copy = s;

  executor.Run([&] { ReverseWords(&s_copy); });

  return s_copy;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "s"};
  return GenericTestMain(args, "reverse_words.cc", "reverse_words.tsv",
                         &ReverseWordsWrapper, DefaultComparator{},
                         param_names);
}

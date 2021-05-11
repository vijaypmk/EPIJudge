#include <algorithm>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;
using std::max;

struct Event {
  int start, finish;
};
int FindMaxSimultaneousEvents(const vector<Event>& A) {
  if (A.size() <= 0)
    return 0;

  struct Endpoint
  {
    int time;
    bool is_start;
  };
  
  vector<Endpoint> B;
  for (auto &i : A) {
    B.emplace_back(Endpoint{i.start, true});
    B.emplace_back(Endpoint{i.finish, false});
  }

  int r = 0, c = 0;

  sort(B.begin(), B.end(), [](const Endpoint& a, const Endpoint& b) {
    return a.time != b.time ? a.time < b.time : (a.is_start && !b.is_start);
  });

  for(auto &i : B) {
    if (i.is_start) {
      c++;
      r = max(c, r);
    }
    else {
      c--;
    }
  }

  return r;
}
namespace test_framework {
template <>
struct SerializationTrait<Event> : UserSerTrait<Event, int, int> {};
}  // namespace test_framework

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}

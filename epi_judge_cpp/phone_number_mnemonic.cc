#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

const vector<string> val = {"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

void rec_ph(const string& ph, const int c, vector<string>& res) {
  static string r;
  if (ph.size() == c) {
    res.emplace_back(r);
    return;
  }

  int p = ph[c] - '0';
  for (char i : val[p]) {
    r.push_back(i);
    rec_ph(ph, c + 1, res);
    r.pop_back();
  }
}


vector<string> PhoneMnemonic(const string& phone_number) {
  vector<string> res;
  rec_ph(phone_number, 0, res);
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}

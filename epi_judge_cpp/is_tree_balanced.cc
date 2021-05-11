#include <algorithm>
#include <cstdlib>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int trav(const unique_ptr<BinaryTreeNode<int>>& tree, int h) {
  if (tree == nullptr)
    return 0;
  
  int h1 = std::max(trav(tree->left, h + 1), h);
  if (h1 == 10000)
    return h1;
  int h2 = std::max(trav(tree->right, h + 1), h);

  if (std::abs(h1 - h2) > 1)
    return 10000;
  
  return std::max(h1, h2);
}


bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if (trav(tree, 0) == 10000)
    return false;
  else
    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}

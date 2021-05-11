#include <vector>
#include <unordered_map>
#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_map;
using std::make_unique;
using std::unique_ptr;

static int p = 0;
unique_ptr<BinaryTreeNode<int>> trav(int l, int r, unordered_map<int, int>& m, const vector<int>& pre) {
  if (l > r)
    return nullptr;
  unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(pre[p], nullptr, nullptr);
  p++;
  root->left = trav(l, m[root->data] - 1, m, pre);
  root->right = trav(m[root->data] + 1, r, m, pre);

  return root;
}


unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {
  unordered_map<int, int> m;
  p = 0;
  for (int i = 0; i < inorder.size(); i++) {
    m[inorder[i]] = i;
  }
  return trav(0, preorder.size() - 1, m, preorder);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}

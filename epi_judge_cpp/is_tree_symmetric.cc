#include "binary_tree_node.h"
#include "test_framework/generic_test.h"


bool trav(const unique_ptr<BinaryTreeNode<int>>& l, const unique_ptr<BinaryTreeNode<int>>& r) {
  if (!l && !r)
    return true;
  
  if((!l && r) || (l && !r))
    return false;
  
  if(l->data != r->data)
    return false;

  return trav(l->left, r->right) && trav(l->right, r->left);
}


bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(!tree)
    return true;
  return trav(tree->left, tree->right);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}

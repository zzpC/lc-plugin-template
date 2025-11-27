#include <iostream>
class TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}

 public:
  // 创建一个测试树：
  //     1
  //    / \
  //   2   3
  //  / \
  // 4   5
  static TreeNode* createTestTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    return root;
  }

  void traverse(TreeNode* root) {
    if (root == nullptr) {
      return;
    }
    // std::cout << root->val << " ";
    traverse(root->left);
    // std::cout << root->val << " ";
    traverse(root->right);
    std::cout << root->val << " ";
  }
};

int main() {
  TreeNode* tree= TreeNode::createTestTree();
  tree->traverse(tree);
  return 0;
}
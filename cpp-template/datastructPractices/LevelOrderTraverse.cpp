#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};
class LevelOrderTraverse {
 private:
  std::queue<TreeNode*> queue;
  int depth = 1;

 public:
  void levelOrderTraverse(TreeNode* root) {
    if (root != nullptr) {
      queue.push(root);
    }
    while (!queue.empty()) {
      TreeNode* p = queue.front();
      queue.pop();
      std::cout << p->val << " ";
      if (p->left != nullptr) {
        queue.push(p->left);
      }
      if (p->right != nullptr) {
        queue.push(p->right);
      }
    }
  }

  void levelOrderTraverse2(TreeNode* root) {
    if (root != nullptr) {
      queue.push(root);
    }
    while (!queue.empty()) {
      for (size_t i = 0; i < queue.size(); i++) {
        TreeNode* node = queue.front();
        queue.pop();
        std::cout << " depth: " << depth << " val: " << node->val << std::endl;
        if (node->left) {
          queue.push(node->left);
        }
        if (node->right) {
          queue.push(node->right);
        }
      }
      ++depth;
    }
  }
};

class TestHelper {
 public:
  // 创建测试树1: 普通二叉树
  //     1
  //    / \
    //   2   3
  //  / \   \
    // 4   5   6
  static TreeNode* createTestTree1() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    return root;
  }

  // 创建测试树2: 只有根节点
  static TreeNode* createTestTree2() { return new TreeNode(10); }

  // 创建测试树3: 左斜树
  //     1
  //    /
  //   2
  //  /
  // 3
  static TreeNode* createTestTree3() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    return root;
  }

  // 创建测试树4: 右斜树
  //   1
  //    \
    //     2
  //      \
    //       3
  static TreeNode* createTestTree4() {
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->right = new TreeNode(3);
    return root;
  }

  // 创建测试树5: 完全二叉树
  //       1
  //     /   \
    //    2     3
  //   / \   / \
    //  4   5 6   7
  static TreeNode* createTestTree5() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    return root;
  }

  // 释放二叉树内存
  static void deleteTree(TreeNode* root) {
    if (root == nullptr) return;

    // 使用层序遍历的方式删除节点
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
      TreeNode* current = q.front();
      q.pop();

      if (current->left != nullptr) {
        q.push(current->left);
      }
      if (current->right != nullptr) {
        q.push(current->right);
      }

      delete current;
    }
  }

  // 验证层序遍历结果
  static bool verifyLevelOrder(TreeNode* root,
                               const std::vector<int>& expected) {
    // 重定向cout到stringstream来捕获输出
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    LevelOrderTraverse traverser;
    traverser.levelOrderTraverse(root);

    // 恢复cout
    std::cout.rdbuf(old);

    // 检查输出是否符合预期
    std::string output = buffer.str();
    std::stringstream ss(output);
    std::vector<int> result;
    int num;

    while (ss >> num) {
      result.push_back(num);
    }

    if (result == expected) {
      std::cout << "✓ 测试通过: ";
      for (int val : result) std::cout << val << " ";
      std::cout << std::endl;
      return true;
    } else {
      std::cout << "✗ 测试失败: 期望 ";
      for (int val : expected) std::cout << val << " ";
      std::cout << "但得到 ";
      for (int val : result) std::cout << val << " ";
      std::cout << std::endl;
      return false;
    }
  }
};

class State {
  int depth;
  TreeNode* treeNode;
  State(TreeNode* treeNode, int depth) : depth(depth), treeNode(treeNode) {}

 public:
  void levelOrderTraverse(TreeNode* root) {
    std::queue<State> q;
    q.push(State(root, 1));
    while (!q.empty()) {
      State cur = q.front();
      q.pop();
      if (cur.treeNode->left) {
        q.push(State(cur.treeNode->left,cur.depth+1));
      }
      if (cur.treeNode->right)
      {
        q.push(State(cur.treeNode->right, cur.depth + 1));
      }
    }
  }
};
// 测试函数
void runTests() {
  std::cout << "=== 层序遍历测试开始 ===" << std::endl;

  // 测试1: 普通二叉树
  std::cout << "\n--- 测试1: 普通二叉树 ---" << std::endl;
  TreeNode* tree1 = TestHelper::createTestTree1();
  std::vector<int> expected1 = {1, 2, 3, 4, 5, 6};
  TestHelper::verifyLevelOrder(tree1, expected1);
  TestHelper::deleteTree(tree1);

  // 测试2: 只有根节点
  std::cout << "\n--- 测试2: 只有根节点 ---" << std::endl;
  TreeNode* tree2 = TestHelper::createTestTree2();
  std::vector<int> expected2 = {10};
  TestHelper::verifyLevelOrder(tree2, expected2);
  TestHelper::deleteTree(tree2);

  // 测试3: 空树
  std::cout << "\n--- 测试3: 空树 ---" << std::endl;
  TreeNode* tree3 = nullptr;
  std::vector<int> expected3 = {};
  TestHelper::verifyLevelOrder(tree3, expected3);

  // 测试4: 左斜树
  std::cout << "\n--- 测试4: 左斜树 ---" << std::endl;
  TreeNode* tree4 = TestHelper::createTestTree3();
  std::vector<int> expected4 = {1, 2, 3};
  TestHelper::verifyLevelOrder(tree4, expected4);
  TestHelper::deleteTree(tree4);

  // 测试5: 右斜树
  std::cout << "\n--- 测试5: 右斜树 ---" << std::endl;
  TreeNode* tree5 = TestHelper::createTestTree4();
  std::vector<int> expected5 = {1, 2, 3};
  TestHelper::verifyLevelOrder(tree5, expected5);
  TestHelper::deleteTree(tree5);

  // 测试6: 完全二叉树
  std::cout << "\n--- 测试6: 完全二叉树 ---" << std::endl;
  TreeNode* tree6 = TestHelper::createTestTree5();
  std::vector<int> expected6 = {1, 2, 3, 4, 5, 6, 7};
  TestHelper::verifyLevelOrder(tree6, expected6);
  TestHelper::deleteTree(tree6);

  std::cout << "\n=== 所有测试完成 ===" << std::endl;
}

// 手动演示函数（可以看到实时输出）
void manualDemo() {
  std::cout << "\n=== 手动演示 ===" << std::endl;

  // 创建测试树
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);

  // 预期输出: 1 2 3 4 5 6
  std::cout << "预期层序遍历结果: 1 2 3 4 5 6" << std::endl;
  std::cout << "实际层序遍历结果: ";

  LevelOrderTraverse traverser;
  traverser.levelOrderTraverse(root);
  std::cout << std::endl;

  TestHelper::deleteTree(root);
}

// 边界测试
void boundaryTests() {
  std::cout << "\n=== 边界测试 ===" << std::endl;

  // 测试大一点的树
  std::cout << "--- 较大二叉树测试 ---" << std::endl;
  TreeNode* bigTree = new TreeNode(1);
  TreeNode* current = bigTree;

  // 创建深度为4的树
  for (int i = 2; i <= 15; i++) {
    if (i % 2 == 0) {
      current->left = new TreeNode(i);
      current = current->left;
    } else {
      current->right = new TreeNode(i);
      current = current->right;
    }
  }

  std::cout << "较大树的层序遍历: ";
  LevelOrderTraverse traverser;
  traverser.levelOrderTraverse(bigTree);
  std::cout << std::endl;

  TestHelper::deleteTree(bigTree);
}

int main() {
  // 运行自动化测试
  runTests();

  // 运行手动演示
  manualDemo();

  // 运行边界测试
  boundaryTests();

  std::cout << "\n=== 代码分析 ===" << std::endl;
  std::cout << "您的层序遍历代码分析:" << std::endl;
  std::cout << "✓ 正确使用了队列数据结构" << std::endl;
  std::cout << "✓ 正确处理了空树的情况" << std::endl;
  std::cout << "✓ 按照层次顺序遍历节点" << std::endl;
  std::cout << "✓ 内存管理需要在外部处理（测试代码中已处理）" << std::endl;
  std::cout << "✓ 时间复杂度: O(n)，空间复杂度: O(w)，w为树的最大宽度"
            << std::endl;

  return 0;
}

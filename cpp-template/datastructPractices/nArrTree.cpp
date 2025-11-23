#include <iostream>
#include <queue>
#include <vector>
struct Node {
  int val;
  std::vector<Node*> children;
};

class NArrayTree {
 public:
  void traverse(Node* root) {
    for (size_t i = 0; i < root->children.size(); i++) {
      traverse(root->children[i]);
    }
  }
  void levelOrderTraverse(Node* root) {
    if (!root) {
      return;
    }

    queue.push(root);
    while (!queue.empty()) {
      Node* cur = queue.front();
      queue.pop();
      for (Node* node : cur->children) {
        queue.push(node);
      }
    }
  }

  void levelOrderTraverse2(Node* root) {
    if (!root) {
      return;
    }

    queue.push(root);
    while (!queue.empty()) {
      for (size_t i = 0; i < queue.size(); i++) {
        Node* cur = queue.front();
        queue.pop();
        for (Node* node : cur->children) {
          queue.push(node);
        }
      }
      ++depth;
    }
  }

  class State {
   public:
    Node* node;
    int depth;
    State(Node* node, int depth) : node(node), depth(depth) {}
  };

  void levelOrderTraverse3(Node* root) {
    states.push(State(root, 1));
    while (!states.empty()) {
      State state = states.front();
      states.pop();
      for (Node* node : state.node->children) {
        states.push(State(node, state.depth + 1));
      }
    }
  }

 private:
  std::queue<Node*> queue;
  int depth = 1;

  std::queue<State> states;
};

int main() { return 0; }

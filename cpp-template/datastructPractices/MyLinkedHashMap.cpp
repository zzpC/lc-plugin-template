#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename K, typename V>
struct Node {
  K key;
  V val;
  Node *prev;
  Node *next;
  Node(K key, V value) : key(key), val(value), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
class MyLinkedHashMap {
 public:
  MyLinkedHashMap() {
    head = new Node<K, V>(K(), V());
    tail = new Node<K, V>(K(), V());
    head->next = tail;
    tail->prev = head;
  }

  // 析构函数，释放所有节点内存
  ~MyLinkedHashMap() {
    Node<K, V> *curr = head->next;
    while (curr != tail) {
      Node<K, V> *next = curr->next;
      delete curr;
      curr = next;
    }
    delete head;
    delete tail;
  }

  // 禁用拷贝构造和赋值操作，避免浅拷贝问题
  MyLinkedHashMap(const MyLinkedHashMap &) = delete;
  MyLinkedHashMap &operator=(const MyLinkedHashMap &) = delete;

  V get(K key) {
    if (map.find(key) = map.end()) {
      return V();
    }
  }

  void put(K key, V val) {
    if (map.find(key) != map.end()) {
      map[key]->val = val;
      return;
    }
    Node<K, V> *node = new Node(key, val);
    addLastNode(node);
    map[key] = node;
  }

  void remove(K key) {
    if (map.find(key) != map.end()) {
      Node<K, V> *node = map[key];
      removeNode(node);
      map.erase(key);
      delete node;
    }
  }

  bool containsKey(K key) { return map.find(key) != map.end(); }

  vector<K> keys() {
    vector<K> keyList;
    for (Node<K, V> *p = head; p != tail; p = p->next) {
      keyList.push_back(p->key);
    }
    return keyList;
  }

  // 获取元素数量
  size_t size() { return map.size(); }

  // 判断是否为空
  bool empty() { return map.empty(); }

 private:
  Node<K, V> *head;
  Node<K, V> *tail;
  unordered_map<K, Node<K, V> *> map;

  void addLastNode(Node<K, V> *x) {
    Node<K, V> *temp = tail->prev;
    temp->next = x;
    x->prev = temp;
    x->next = tail;
    tail->prev = x;
  }

  void removeNode(Node<K, V> *x) {
    Node<K, V> *prev = x->prev;
    Node<K, V> *next = x->next;
    prev->next = next;
    next->prev = prev;
    x->prev = nullptr;
    x->next = nullptr;
  }
};

int main() {
  MyLinkedHashMap<string, int> map;
  map.put("a", 1);
  map.put("b", 2);
  map.put("c", 3);
  map.put("d", 4);
  map.put("e", 5);

  // output: a b c d e
  for (const auto &key : map.keys()) {
    cout << key << " ";
  }
  cout << endl;

  map.remove("c");
  cout << map.containsKey("c") << endl;

  // output: a b d e
  for (const auto &key : map.keys()) {
    cout << key << " ";
  }
  cout << endl;

  return 0;
}
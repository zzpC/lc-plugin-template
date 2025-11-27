#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename K, typename V>
class MyArrayHashMap {
  struct Node {
    K key;
    V val;

    Node(K key, V val) : key(key), val(val) {}
  };

  // 存储 key 和 key 在 arr 中的索引
  unordered_map<K, int> map;

  // 真正存储 key-value 的数组
  vector<Node> arr;

  // 随机数生成器
  default_random_engine e;

 public:
  MyArrayHashMap() { e.seed(random_device()()); }

  V get(K key) {
    if (!map.count(key)) {
      return V();  // int 0
    }
    int index = map[key];
    return arr[index].val;
  }

  void put(K key, V val) {
    if (containsKey(key)) {
      // 修改
      int i = map[key];
      arr[i].val = val;
      return;
    }

    // 新增
    arr.push_back(Node(key, val));
    map[key] = arr.size() - 1;
  }

  void remove(K key) {
    if (!map.count(key)) {
      return;
    }
    int index = map[key];
    Node node = arr[index];

    // 1. 最后一个元素 e 和第 index 个元素 node 换位置
    Node e = arr.back();
    swap(arr[index], arr.back());

    // 2. 修改 map 中 e.key 对应的索引
    map[e.key] = index;

    // 3. 在数组中删除最后一个元素
    arr.pop_back();

    // 4. 在 map 中删除 node.key
    map.erase(node.key);
  }

  // 随机弹出一个键
  K randomKey() {
    int n = arr.size();
    uniform_int_distribution<int> u(0, n - 1);
    int randomIndex = u(e);
    return arr[randomIndex].key;
  }

  bool containsKey(K key) { return map.count(key); }

  int size() { return map.size(); }
};

int main() {
  MyArrayHashMap<int, int> map;
  map.put(1, 1);
  map.put(2, 2);
  map.put(3, 3);
  map.put(4, 4);
  map.put(5, 5);

  cout << map.get(100) << endl;  // 1
  cout << map.randomKey() << endl;

  map.remove(4);
  cout << map.randomKey() << endl;
  cout << map.randomKey() << endl;

  return 0;
}
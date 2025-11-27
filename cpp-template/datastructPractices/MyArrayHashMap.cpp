#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

template <typename K, typename V>
class MyArrayHashMap {
  struct Node {
    K key;
    V val;
    Node(K k, V v) : key(k), val(v) {}
  };

 private:
  std::default_random_engine e;
  std::vector<Node> arr;
  std::unordered_map<K, int> map;

 public:
  MyArrayHashMap() { e.seed(std::random_device()()); }

  V get(K key) {
    if (map.find(key) == map.end()) {
      return V();
    }
    int index = map[key];
    return arr[index].val;
  }

  void put(K key, V val) {
    if (map.find(key) == map.end()) {
      Node node(key, val);
      arr.push_back(node);
      map[key] = arr.size() - 1;
      return;
    }
    int index = map[key];
    arr[index] = Node(key, val);
  }

  void remove(K key) {
    if (map.find(key) == map.end()) {
      return;
    }
    int index = map[key];
    Node e = arr.back();
    std::swap(arr[index], arr.back());
    map[e.key] = index;
    arr.pop_back();
    map.erase(e.key);
  }

  // 随机弹出一个键
  K randomKey() {
    int size = arr.size();
    std::uniform_int_distribution u(0, size - 1);
    int randomKey = u(e);
    return arr[randomKey].val;
  }

  bool containsKey(K key) { return map.find(key) != map.end(); }

  int size() { return map.size(); }
};

int main() {
  MyArrayHashMap<int, int> map;
  map.put(1, 1);
  map.put(2, 2);
  map.put(3, 3);
  map.put(4, 4);
  map.put(5, 5);

  std::cout << map.get(1) << std::endl;  // 1
  std::cout << map.randomKey() << std::endl;

  map.remove(4);
  std::cout << map.randomKey() << std::endl;
  std::cout << map.randomKey() << std::endl;

  return 0;
}
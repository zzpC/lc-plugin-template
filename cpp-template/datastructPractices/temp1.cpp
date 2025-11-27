#include <iostream>
using namespace std;

int main() {
  int num = 42;

  // 定义各级指针
  int* ptr = &num;                // 一级指针
  int** ptr_ptr = &ptr;           // 二级指针
  int*** ptr_ptr_ptr = &ptr_ptr;  // 三级指针

  // 打印变量地址
  cout << "变量 num 的地址: " << &num << endl;
  cout << "变量 num 的值: " << num << endl << endl;

  // 打印一级指针的信息
  cout << "一级指针 ptr 自己的地址: " << &ptr << endl;
  cout << "一级指针 ptr 存储的地址（指向的地址）: " << ptr << endl;
  cout << "通过 ptr 访问的值: " << *ptr << endl << endl;

  // 打印二级指针的信息
  cout << "二级指针 ptr_ptr 自己的地址: " << &ptr_ptr << endl;
  cout << "二级指针 ptr_ptr 存储的地址: " << ptr_ptr << endl;
  cout << "第一次解引用 *ptr_ptr: " << *ptr_ptr << endl;
  cout << "第二次解引用 **ptr_ptr: " << **ptr_ptr << endl << endl;

  // 打印三级指针的信息
  cout << "三级指针 ptr_ptr_ptr 自己的地址: " << &ptr_ptr_ptr << endl;
  cout << "三级指针 ptr_ptr_ptr 存储的地址: " << ptr_ptr_ptr << endl;
  cout << "第一次解引用 *ptr_ptr_ptr: " << *ptr_ptr_ptr << endl;
  cout << "第二次解引用 **ptr_ptr_ptr: " << **ptr_ptr_ptr << endl;
  cout << "第三次解引用 ***ptr_ptr_ptr: " << ***ptr_ptr_ptr << endl;

  return 0;
}
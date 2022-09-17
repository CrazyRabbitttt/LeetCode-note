
### HTTPS 
[这里是链接](https://www.nowcoder.com/discuss/1009213)


### Muduo中优秀思想分析地址
[这里是链接](https://zhuanlan.zhihu.com/p/495016351)

最后部分有对于RunInloop的分析



## 操作系统

#### 内核态用户态的切换
https://blog.csdn.net/qq_40276626/article/details/119979930

### 5种IO模型，很好的文章
> [链接在这里](https://zhuanlan.zhihu.com/p/115912936)

> 阻塞为什么会很消耗资源呢？

阻塞虽然是不消耗CPU，但是既然阻塞了就会让出来CPU给别的进程/线程，这个切换的消耗是比较高的
而非阻塞就不会进行切换, 但是轮询

### 指针和引用的区别
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#%E6%8C%87%E9%92%88%E5%92%8C%E5%BC%95%E7%94%A8%E7%9A%84%E5%8C%BA%E5%88%AB)

> - 底层汇编的实现的话，引用就是一个常量指针
> - 在C++中，指针和引用经常用于函数的参数传递，然而，指针传递参数和引用传递参数是有本质上的不同的：指针传递参数本质上是值传递的方式，它所传递的是一个地址值。值传递的特点是被调函数对形式参数的任何操作都是作为局部变量进行，不会影响主调函数的实参变量的值。而在引用传递过程中， 被调函数的形参虽然也作为局部变量在栈中开辟了内存空间，但是这时存放的是由主调函数放进来的实参变量的地址（指针放的是实参变量地址的副本）。


### 右值引用与move
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#%E6%8C%87%E9%92%88%E5%92%8C%E5%BC%95%E7%94%A8%E7%9A%84%E5%8C%BA%E5%88%AB)

- 普通的左值是否也能借助移动语义来优化性能呢？C++11为了解决这个问题，提供了std::move方法来将左值转换为右值，从而方便应用移动语义。move是将对象资源的所有权从一个对象转移到另一个对象，只是转移，没有内存的拷贝，这就是所谓的move语义。 move实际上它并不能移动任何东西，它唯一的功能是将一个左值强制转换为一个右值引用, 然后转移了资源的所有权
- 在MyString类中是深拷贝，但是如果传递的是"hahahah"：一个右值，那么深拷贝太浪费了，所以可以重载一个传递右值引用的参数 (MyString && m)


### 重载与 extern C
[这里是链接](https://www.nowcoder.com/discuss/1025870)

### 虚函数问题
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#c%E8%99%9A%E5%87%BD%E6%95%B0)

### 强制类型转换
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#c-%E5%9B%9B%E7%A7%8D%E5%BC%BA%E5%88%B6%E7%B1%BB%E5%9E%8B%E8%BD%AC%E6%8D%A2)


### 内存泄漏
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#%E5%86%85%E5%AD%98%E6%B3%84%E6%BC%8F%E5%87%BA%E7%8E%B0%E5%86%85%E5%AD%98%E6%B3%84%E6%BC%8F%E5%A6%82%E4%BD%95%E8%B0%83%E8%AF%95)


### C++11
[link](https://github.com/guaguaupup/cpp_interview/blob/main/%E9%9D%A2%E8%AF%95%E6%80%BB%E7%BB%93%E2%80%94C++.md#watermelonc11%E6%96%B0%E7%89%B9%E6%80%A7)

### 智能指针
[link](https://aijishu.com/a/1060000000286819)

> - unique_ptr 一般是不需要多个指向同一个对象的指针时使用，对象或方法内部使用时优先使用unique_ptr 
> - shared_ptr一般在需要多个执行同一个对象的指针使用。在我看来可以简单的理解：这个对象需要被多个 Class 同时使用的时候。

### shared_ptr循环引用问题
```cpp

struct A {
  shared_ptr<B> b;
};

struct B {
  shared_ptr<A> a;
};

shared_ptr<A> pa = make_shared<A>();
shared_ptr<B> pb = make_shared<B>();

pa->b = pb;
pb->a = pa;

```
> 用weak_ptr 解除循环引用问题


### C++单例模式
> 一般遇到的写进程池类、日志类、内存池（缓存数据的结构，一处写多出读或者多处写多处读）用到单例模式
> **实现方法：**全局只有一个实例也就意味着不能用new调用构造函数来创建对象，因此构造函数必须是虚有的。但是由于不能new出对象，所以类的内部必须提供一个函数来获取对象，而且由于不能外部构造对象，因此这个函数不能是通过对象调出来，换句话说这个函数应该是属于对象的，很自然我们就想到了用static。由于静态成员函数属于整个类，在类实例化对象之前就已经分配了空间，而类的非静态成员函数必须在类实例化后才能有内存空间。


** 要点总结**
> - 全局只有一个实例、使用static 进行设计、构造函数为私有（不能使用new创建）
> - 通过公用的接口获得
> - 线程安全
> - 禁止拷贝 or 赋值


### 懒汉单例设计模式
- 普通的懒汉式线程不安全
> 不加锁线程并发产生多个实例

```cpp
#include <iostream>
#include <mutex>
#include <pthread.h>

using namespace std;


class SingleInstance {
 public:
    
    static SingleInstance* GetInstance();

    // 释放单例模式的时候调用
    static void deleteSingle();

    // 打印单例地址
    void Print();

 private:
    SingleInstance();
    ~SingleInstance();

    SingleInstance(const SingleInstance& single);
    const SingleInstance& operator=(const SingleInstance& single);

    static SingleInstance *m_SingleInstance_;
};


// 进行初始化
SingleInstance* SingleInstance::m_SingleInstance_ = nullptr;

SingleInstance* SingleInstance::GetInstance() {
    if (m_SingleInstance_ == nullptr) {
        m_SingleInstance_ = new SingleInstance();
    }
    return m_SingleInstance_;
}


void SingleInstance::deleteSingle() {
    if (m_SingleInstance_) {
        delete m_SingleInstance_;
        m_SingleInstance_ = nullptr;
    }
}


```

### 双锁检测的单例模式
```cpp

class Singleton {
 private:
    Singleton();
    ~Singleton();
 public:
    static Singleton& GetInstance() {
        if (m_instance_ == nullptr) {
            std::unique_lock lock(m);
            
        }
    }

 private:
    static Singleton* m_instance_;
    static std::mutex m;
};


```


### 使用`local static`变量进行优雅的设置单例模式
C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。在C++11标准下，《Effective C++》提出了一种更优雅的单例模式实现，使用函数内的local static对象。这样，只有当第一次访问getInstance()方法时才创建实例。
```cpp
class Singleton;

class Singleton {
 private:
    Singleton();
    Singleton(const Singleton& );
 
 public:
    static Singleton& GetInstance() {
        // 使用局部静态变量保证安全
        static Singleton instance;
        return instance;
    }


 private:
    // class member

};
```


### SkipList（跳表的实现）
```cpp

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <ctime>
#include <initializer_list>
#include <iostream>
#include <random>

template <typename Key>
class Skiplist {
public:
  struct Node {
    Node(Key k) : key(k) {}
    Key key;
    Node* next[1];  // C语言中的柔性数组技巧
  };

private:
  int maxLevel;
  Node* head;

  enum { kMaxLevel = 12 };

public:
  Skiplist() : maxLevel(1)
  {
    head = newNode(0, kMaxLevel);
  }

  Skiplist(std::initializer_list<Key> init) : Skiplist()
  {
    for (const Key& k : init)
    {
      insert(k);
    }
  }

  ~Skiplist()
  {
    Node* pNode = head;
    Node* delNode;
    while (nullptr != pNode)
    {
      delNode = pNode;
      pNode = pNode->next[0];
      free(delNode);  // 对应malloc
    }
  }

  // 禁止拷贝构造和赋值
  Skiplist(const Skiplist&) = delete;
  Skiplist& operator=(const Skiplist&) = delete;
  Skiplist& operator=(Skiplist&&) = delete;

private:
  Node* newNode(const Key& key, int level)
  {
    /*
    * 开辟sizeof(Node) + sizeof(Node*) * (level - 1)大小的空间
    * sizeof(Node*) * (level - 1)大小的空间是给Node.next[1]指针数组用的
    * 为什么是level-1而不是level，因为sizeof(Node)已包含一个Node*指针的空间
    */ 
    void* node_memory = malloc(sizeof(Node) + sizeof(Node*) * (level - 1));
    Node* node = new (node_memory) Node(key);
    for (int i = 0; i < level; ++i)
      node->next[i] = nullptr;

    return node;
  }
  /*
  * 随机函数，范围[1, kMaxLevel]，越小概率越大
  */ 
  static int randomLevel()
  {
    int level = 1;
    while (rand() % 2 && level < kMaxLevel)
      level++;

    return level;
  }

public:
  Node* find(const Key& key)
  {
    // 从最高层开始查找，每层查找最后一个小于key的前继节点，不断缩小范围
    Node* pNode = head;
    for (int i = maxLevel - 1; i >= 0; --i)
    {
      while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
      {
        pNode = pNode->next[i];
      }
    }

    // 如果第一层的pNode[0]->key == key，则返回pNode->next[0]，即找到key
    if (nullptr != pNode->next[0] && pNode->next[0]->key == key)
      return pNode->next[0];

    return nullptr;
  }

  void insert(const Key& key)
  {
    int level = randomLevel();
    Node* new_node = newNode(key, level);
    Node* prev[kMaxLevel];
    Node* pNode = head;
    // 从最高层开始查找，每层查找最后一个小于key的前继节点
    for (int i = level - 1; i >= 0; --i)
    {
      while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
      {
        pNode = pNode->next[i];
      }
      prev[i] = pNode;
    }
    // 然后每层将新节点插入到前继节点后面
    for (int i = 0; i < level; ++i)
    {
      new_node->next[i] = prev[i]->next[i];
      prev[i]->next[i] = new_node;
    }

    if (maxLevel < level)  // 层数大于最大层数，更新最大层数
      maxLevel = level;
  }

  void erase(const Key& key)
  {
    Node* prev[maxLevel];
    Node* pNode = head;
    // 从最高层开始查找，每层查找最后一个小于key的前继节点
    for (int i = maxLevel - 1; i >= 0; --i)
    {
      while (pNode->next[i] != nullptr && pNode->next[i]->key < key)
        pNode = pNode->next[i];
      prev[i] = pNode;
    }
    
    // 如果找到key，
    if (pNode->next[0] != nullptr && pNode->next[0]->key == key)
    {
      Node *delNode = pNode->next[0];
      // 从最高层开始，如果当前层的next节点的值等于key，则删除next节点
      for (int i = maxLevel - 1; i >= 0; --i)
      {
        if (prev[i]->next[i] != nullptr && key == prev[i]->next[i]->key)
          prev[i]->next[i] = prev[i]->next[i]->next[i];
      }
      free(delNode);  // 最后销毁pNode->next[0]节点
    }
    
    // 如果max_level>1且头结点的next指针为空，则该层已无数据，max_level减一
    while (maxLevel > 1 && head->next[maxLevel] == nullptr)
    {
      maxLevel--;
    }
  }
};

#endif

```



### shared_ptr & weak_ptr多线程共享对象问题
[这里是链接🔗，自己要敲一敲看看](https://github.com/davidditao/DDmuduo/blob/master/C%2B%2B/%E6%99%BA%E8%83%BD%E6%8C%87%E9%92%88.md#62-%E5%A4%9A%E7%BA%BF%E7%A8%8B%E8%AE%BF%E9%97%AE%E5%85%B1%E4%BA%AB%E5%AF%B9%E8%B1%A1%E9%97%AE%E9%A2%98)


## **static 和const分别怎么用，类里面static和const可以同时修饰成员函数吗**

- **static**

  - static对于变量

    1. 局部变量

       在局部变量之前加上关键字static，局部变量就被定义成为一个局部静态变量。

       内存中的位置：data段

       初始化：局部的静态变量只能被初始化一次

       作用域：作用域仍为局部作用域，当定义它的函数或者语句块结束的时候，作用域随之结束。

       > 当static用来修饰局部变量的时候，它就**改变了局部变量的存储位置（从原来的栈中存放改为静态存储区）及其生命周期（局部静态变量在离开作用域之后，并没有被销毁，而是仍然驻留在内存当中，直到程序结束，只不过我们不能再对他进行访问），但未改变其作用域。**

    2. 全局变量

       在全局变量之前加上关键字static，全局变量就被定义成为一个全局静态变量。

       内存中的位置：静态存储区（静态存储区在整个程序运行期间都存在）

       初始化：未经初始化的全局静态变量会被程序自动初始化为0

       作用域：全局静态变量在声明他的文件之外是不可见的。准确地讲从定义之处开始到文件结尾。(只能在本文件中存在和使用)

       > 全局变量本身就是静态存储方式， 静态全局变量当然也是静态存储方式。两者的区别在于非静态全局变量的作用域是整个源程序， 当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的（在其他源文件中使用时加上extern关键字重新声明即可）。 而**静态全局变量则限制了其作用域， 即只在定义该变量的源文件内有效， 在同一源程序的其它源文件中不能使用它**。

  - static对于函数

    修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static。（和全局变量一样限制了作用域而已）

  - static对于类

    1. 成员变量

       用static修饰类的数据成员实际使其成为类的全局变量，会被类的所有对象共享，包括派生类的对象。

       因此，**static成员必须在类外进行初始化，而不能在构造函数内进行初始化。不过也可以用const修饰static数据成员在类内初始化 。**

    2. 成员函数

       用static修饰成员函数，使这个类只存在这一份函数，所有对象共享该函数，不含this指针。

       *** 静态成员是可以独立访问的，也就是说，无须创建任何对象实例就可以访问。 ***  这个在项目中的TimeStamp的now()函数用到

       **不可以同时用const和static修饰成员函数。**

- **const**

  1. const修饰变量：限定变量为不可修改。

  2. const修饰指针：指针常量和指向常量的指针

  3. const和函数：有以下几种形式

     ```
     const int& fun(int& a); //修饰返回值
     int& fun(const int& a); //修饰形参
     int& fun(int& a) const{} //const成员函数
     ```

  4. const和类：①const修饰成员变量，在某个对象的声明周期内是常量，但是对于整个类而言是可以改变的。因为类可以创建多个对象，不同的对象其const成员变量的值是不同的。切记，**不能在类内初始化const成员变量**，因为类的对象没创建前，编译器并不知道const成员变量是什么，因此const数据成员只能在初始化列表中初始化。②const修饰成员函数，主要目的是防止成员函数修改成员变量的值，即该成员函数并不能修改成员变量。③const对象，常对象，常对象只能调用常函数。

  5. 限定成员函数不可以修改任何数据成员

- static和const可以同时修饰成员函数吗?

  答：不可以。C++编译器在实现const的成员函数的时候为了确保该函数不能修改类的实例的状态，会在函数中添加一个隐式的参数const this*。但当一个成员为static的时候，该函数是没有this指针的。也就是说此时const的用法和static是冲突的。两者的语意是矛盾的。**static的作用是表示该函数只作用在类型的静态变量上，与类的实例没有关系；而const的作用是确保函数不能修改类的实例的状态**，与类型的静态变量没有关系。因此不能同时用它们。

## 


## 手撕的数据结构&模型等


### 哈希表
[这里是链接🔗](https://zhuanlan.zhihu.com/p/144296454)


### 冒泡排序

```cpp

void Bubble_Sort(int a[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (a[j] > a[j+1]) {
                swap(a[j], a[j+1]);
            }
        } 
    }
}


```



#### 快速排序
```cpp

void quickSort(int left, int right, vector<int>& arr) {
    if (left >= right) return ;
    int i, j, base = arr[left];
    i = left, j = right;

    while (i < j) {
        // 找小于基数的位置
        while (arr[j] >= base && i < j)  j--;
        while (arr[i] <= base && i < j)  i++;
        if (i < j) swap(arr[i], arr[j]);
    }

    swap(arr[i], arr[left]);            // 交换base 与 交汇点
    quickSort(left, i-1, arr);
    quickSort(i+1, right, arr);
}

```


#### 堆排序
> - 迭代调整最大堆
> - 交换堆顶到末尾实现排序，交换后调整堆的结构
```cpp
#include <iostream>
using namespace std;


// 递归进行大顶堆的调整
void adjust(int a[], int len, int index) {
    int left  = index * 2 + 1;
    int right = index * 2 + 2;

    int maxIdx = index;
    if (left < len && a[left] > a[maxIdx]) maxIdx = left;
    if (right <len && a[right]> a[maxIdx]) maxIdx = right;
    
    if (maxIdx != index) {
        swap(a[maxIdx], a[index]);     // 将比较大的数交换上去
        // 如果有子节点的话继续进行排序
        adjust(a, len, maxIdx);
    }
}


void heapSort(int a[], int size) {
    // 从最后一个非叶子结点进行大顶堆的构造
    for (int i = size / 2 - 1; i >= 0; i--) {
        adjust(a, size, i);
    }

    // 将顶上面的数据交换到底部
    for (int i = size - 1; i > 0; i--) {
        swap(a[i], a[0]);
        adjust(a, i, 0);
    }
}
    

int main() {
    int a[10] = { 21, 343, 122, 84, 5, 117, 4, 35, 90, 666 };
    int size = 10;
    heapSort(a, size);

    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
```


### MergeSort
> - 递归的将数组分成左右子数据，返回时是有序的
> - 将两个分别有序的字数组进行合并，用到一个临时数组进行合并

```cpp
#include <iostream>
using namespace std;

int tmp[500];

void merge_Sort(int a[], int l, int r) {

    if (l >= r) return ;
    // recursion将数组分成两半
    int mid = (l + r) >> 1;
    merge_Sort(a, l, mid), merge_Sort(a, mid+1, r);

    // 下面就是将两个字数组进行合并, 创建一个临时的数组

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r) {
        // 将比较小(大)的元素取出来放到临时数组
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else 
            tmp[k++] = a[j++];
    }

    // 如果还有元素没有取出来，将剩余的放到临时数组，   
    while (i <= mid) 
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];

    // 进行赋值
    for (int i = l, j = 0; i <= r; i++, j++) {
        a[i] = tmp[j];
    }

}

int main() {
    int a[10] = { 21, 343, 122, 84, 5, 117, 4, 35, 90, 666 };
    int size = 10;
    printf("Merge sort\n");
    merge_Sort(a, 0, size - 1);

    for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }
    return 0;
}

```

### 简单引用计数共享指针

```cpp

template<class T>

class Ref_count {
 
 public:
    Ref_count(T *t)
        : ptr_(t), count_(new int(1)) {}

    ~Ref_count() {
        decrease();
    }

    Ref_count(const Ref_count<T>& tmp) {
        // 进行拷贝构造, 指向相同的内容
        count_ = tmp->count_;
        ptr_   = tmp->ptr_;
        increase();
    }

    Ref_count<T>& operator=(const Ref_count& tmp) {
        // 左边的放弃，右边的+1
        if (tmp != this) {
            decrease();             // 左边的被decrease();
            ptr_    = tmp->ptr_;
            count_  = tmp->count_;
            increase();             // 右边的对应的引用计数加一
        }
        return *this;
    }

    void increase() {
        if (count_) {
            *(count_)++;
        }
    }

    T* operator->() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    void decrease() {
        if (count_) {
            *(count_)--;
            if (*count_ == 0) {
                // 引用计数为0，释放
                delete count_; count_ = nullptr;
                delete ptr_;   ptr_   = nullptr;
            }
        }
    }

    T* get() const {        // get raw pointer 
        return ptr_;
    }

    int get_count() const {
        if (!count_) return 0;
        return *count_;
    }
 private:
    T* ptr_;                // raw pointer
    int* count_;            // ref count

};

```

### 反转链表
```cpp

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur  = head;


        // a -> b -> c
        while (cur) {
            ListNode* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

```

### 递归反转链表

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};
```



### 二叉树先序遍历 1.迭代
> - 用栈进行存放，先放右边的才能保障左边的先出来

```cpp

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();
            result.push_back(node->val);            // 中
            if (node->right) st.push(node->right);
            if (node->left)  st.push(node->left);
        }
        return result;
    }
};

```

### 二叉树先序遍历（郭郭思路）
>  模拟一个节点走的路径的思路，核心代码都是相同的
```cpp

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*>st;
        Treenode* node = root;
        while (node || stack.size()) {
            // 尽可能向左，根左右
            while (node) {
                res.push_back(node->val);
                st.push(node);
                node = node->left;
            }
            // 遍历到最左边了，弹栈，向右
            TreeNode* cur = st.top(); st.pop();
            node = cur->right;
        }
        return res;   
    }
};

```


### 二叉树后序遍历 （郭郭思路）
> - 根右左的reverse版本，但是不能边遍历边处理，但是能够简化思路， 同上面类似


### 二叉树中序遍历 （郭郭思路）

>  中序遍历也是先向左，但是根结点是弹栈的时候才加入到res的
```cpp

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*>st;
        Treenode* node = root;
        while (node || st.size()) {
            // 不断的向左走
            while (node) {
                st.push(node);
                node = node->left;
            }
            node = st.top(); st.pop();
            res.push_back(node->val);
            root = root->right;
        }
    }
};

```

### Memcpy的实现，
> 不同于strcpy, 这是内存级别的拷贝，后者只是字符串的拷贝
> 需要考虑的点就是是否是有内存的重叠的情况，只需要判断下面这种情况就行

> `111111111`   src
>      `000000000`  dst
> 因为内存是重叠的，所以dst直接将src后面的覆盖掉了，没了。。。解决办法就是从后往前复制


```cpp

void* my_memcpy(void* dst, const void* src, size_t count) {
    if (dst == nullptr || src == nullptr)   return nullptr;
    char* tmp_dst = (char*)dst;
    char* tmp_src = (char*)src;
    if (tmp_dst > tmp_src && tmp_dst < tmp_src + count) {
        // 有内存的重叠
        tmp_dst = tmp_dst + count - 1;
        tmp_src = tmp_src + count - 1;
        while (count --) {
            *tmp_dst-- = *tmp_src--;
        }
    } else {
        while (count--) {
            *tmp_dst++ = *tmp_src++;
        }
    }
    return (void*)dst;
}

```


### 死锁的检测
> - 使用pstack <pid> 能够查看栈帧的调用情况
> - GDB 使用`info threads` 查看线程，`thread 2`切换线程，`bt`打印线程的调用栈信息，`print`具体查看变量的值

** 测试代码 **

```cpp
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex_A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_B = PTHREAD_MUTEX_INITIALIZER;


void *threadB_proc(void *data)
{
    printf("thread B waiting get ResourceB \n");
    pthread_mutex_lock(&mutex_B);
    printf("thread B got ResourceB \n");
    
    sleep(1);
    
    printf("thread B waiting  get ResourceA \n");
    pthread_mutex_lock(&mutex_A);
    printf("thread B got ResourceA \n");
    
    pthread_mutex_unlock(&mutex_A);
    pthread_mutex_unlock(&mutex_B);
    return (void *)0;
}


//线程函数 A
void *threadA_proc(void *data)
{
    printf("thread A waiting get ResourceA \n");
    pthread_mutex_lock(&mutex_A);
    printf("thread A got ResourceA \n");
    
    sleep(1);
    
    printf("thread A waiting get ResourceB \n");
    pthread_mutex_lock(&mutex_B);
    printf("thread A got ResourceB \n");

    pthread_mutex_unlock(&mutex_B);
    pthread_mutex_unlock(&mutex_A);
    return (void *)0;
}


int main() {
    pthread_t tidA, tidB;

    pthread_create(&tidA, NULL, threadA_proc, NULL);
    pthread_create(&tidB, NULL, threadB_proc, NULL);
    
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    
    printf("exit\n");
    
    return 0;
}


```




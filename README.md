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
#include <iostream>
using namespace std;

// 引用计数实现共享指针

// template <class T>
// class Ref_count {
//  private:
//     T* ptr_;             // 原始的指针
//     int* count;         // 引用计数器指针
//  public:

//     Ref_count(T* t)
//         :ptr_(t), count(new int(1)) {}
//     ~Ref_count() {
//         decrease();
//     }

//     // 拷贝构造
//     Ref_count(const Ref_count<T>& tmp) {
//         count = tmp->count();
//         ptr_  = tmp->ptr_;
//         increase();     // 引用计数➕1
//     }

//     // 智能指针需要表现的像一个指针，重载重要的符号
//     T* operator->() const {
//         return ptr;
//     }

//     T& operator *() const {
//         // *(ptr) = value;
//         return *ptr_;
//     }


//     void increase() {
//         if (count) {
//             *(count)++;
//         }
//     }

//     void decrease() {
//         if (count) {
//             *(count)--;
//             if (*count == 0) {
//                 // 如果说引用计数为0的话就删除数据对象的指针和count的指针
//                 delete ptr_;
//                 ptr_ = nullptr;
//                 delete count;
//                 count = nullptr;
//             }
//         }
//     }

//     T* get() const {
//         return ptr_;
//     }

//     int get_count() const {
//         if (!count) return 0;
//         return *count;
//     }


// };

template<class T> 
class Ref_count {
 public:
    Ref_count(T* ptr)
        :ptr_(ptr), count_(new int(1)) {}
    ~Ref_count() {
        decrease();
    }

    T* operator->() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    void increase() {
        if (count_) {
            *(count_)++;
        }
    }


    void decrease() {
        if (count_) {
            *(count)--
            if (*count_ == 0) {
                delete ptr_;
                ptr_ = nullptr;
                delete count_;
                count_ = nullptr;
            }
        }
    }

    T* get() const {
        return ptr_;
    }

    int get_count() const {
        if (!count_) return 0;
        return *count_;
    }


 private:
    T* ptr_;
    int* count_;
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


### 5种IO模型，很好的文章
> [链接在这里](https://zhuanlan.zhihu.com/p/115912936)

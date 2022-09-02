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

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

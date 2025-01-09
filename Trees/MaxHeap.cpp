#include <iostream>

using namespace std;

void sift_up(int a[], int n, int index) {
    if (index < 0 || index >= n)
        return;
    int parent = (index - 1) / 2;
    if (a[index] > a[parent]) {
        swap(a[index], a[parent]);
        sift_up(a, n, parent);
    }
}

void sift_down(int a[], int index, int size) {
    int child = 2 * index + 1;
    if (child >= size)
        return;

    if (a[child] < a[child + 1])
        child++;

    if (a[child] > a[index]) {
        swap(a[child], a[index]);
        sift_down(a, child, size);
    }
}

void insert(int a[], int& n, int item) {
    a[n++] = item;
    sift_up(a, n, n - 1);
}

void remove(int a[], int& n, int index) {
    if (n <= 0 || index < 0 || index >= n)
        return;
    swap(a[index], a[n - 1]);
    n--;
    sift_down(a, index, n - 1);
}

int get_max(int a[], int n) {
    if (n <= 0)
        return -1;
    return a[0];
}

int extract_max(int a[], int& n) {
    if (n <= 0)
        return -1;
    int ret = a[0];
    swap(a[0], a[n - 1]);
    n--;
    sift_down(a, 0, n - 1);
    return ret;
}

void heapify(int a[], int n) {
    for (int i = (n - 1) / 2; i > 0; i--)
        sift_down(a, 0, i);
}

void heap_sort(int a[], int n) {
    heapify(a, n);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        sift_down(a, 0, i - 1);
    }
}

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

int main() {
    int arr[20];
    int n = 0;

    for (int i = 0; i < 10; i++)
        insert(arr, n, i);

    printArr(arr, n);

    cout << "Max of heap: " << get_max(arr, n) << "\n";
    cout << "Max of heap(extracting): " << extract_max(arr, n) << "\n";
    remove(arr, n, 0);
    cout << "Array after extracting max twice: ";
    printArr(arr, n);
    cout << "\n";

    heap_sort(arr, n);
    cout << "Array after heap sort: ";
    printArr(arr, n);
    return 0;
}
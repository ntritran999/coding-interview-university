#include <iostream>

using namespace std;

void quickSort(int a[], int size, int left, int right) {
    if (left > right)
        return;

    int pivot = a[rand() % size];
    int i = left, j = right;
    while (i <= j) {
        while (a[i] <= pivot)
            i++;
        while (a[j] >= pivot)
            j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++; 
            j--;
        }
    }

    if (i < right)
        quickSort(a, size, i, right);
    if (j > left)
        quickSort(a, size, left, j);
}

int main() {
    int a[] = {5,4,3,2,1};
    int n = 5;
    quickSort(a, n, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    
    return 0;
}
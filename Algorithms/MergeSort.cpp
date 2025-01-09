#include <iostream>

using namespace std;

void merge(int result[], int a[], int na, int b[], int nb) {
    int nc = na + nb;
    int i = 0, j = 0;
    for (int k = 0; k < nc; k++) {
        if (j >= nb || (i < na && a[i] < b[j]))
            result[k] = a[i++];
        else
            result[k] = b[j++]; 
    }
}

void mergeSort(int a[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    int tmp[right - left + 1];
    merge(tmp, a + left, mid - left + 1, a + mid + 1, right - mid);
    
    for (int i = left; i <= right; i++)
        a[i] = tmp[i - left];
}

void mergeInPlace(int a[], int left, int mid, int right) {
    int n = right - left + 1;
    int tmp[n];
    
    int i = left, j = mid + 1;
    for (int k = 0; k < n; k++) {
        if (j > right || (i <= mid && a[i] < a[j]))
            tmp[k] = a[i]++;
        else
            tmp[k] = a[j++];
    }

    for (int k = n - 1; k >= 0; k--)
        a[left + k] = tmp[k];
}

void mergeSortInPlace(int a[], int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortInPlace(a, left, mid);
    mergeSortInPlace(a, mid + 1, right);

    mergeInPlace(a, left, mid, right);
}

int main() {
    int a[] = {5,4,3,2,1};
    int b[] = {5,4,3,2,1};
    int n = 5;
    int nb = 5;
    mergeSort(a, 0, n - 1);

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";

    mergeSortInPlace(b, 0, nb - 1);
    for (int i = 0; i < nb; i++)
        cout << b[i] << " ";
    cout << "\n";
    return 0;
}
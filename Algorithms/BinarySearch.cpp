#include <iostream>

using namespace std;

bool normalBinarySearch(int a[], int n, int target) {
    int left = 0, right = n - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (a[mid] == target)
            return true;
        else if (a[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

bool recursiveBinarySearch(int a[], int left, int right, int target) {
    if (left > right)
        return false;
    
    int mid = left + (right - left) / 2;
    if (a[mid] == target)
        return true;
    else if (a[mid] < target)
        return recursiveBinarySearch(a, mid + 1, right, target);
    return recursiveBinarySearch(a, left, mid - 1, target);
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int n = 5;

    cout << "Is value 3 in array: " << ((normalBinarySearch(a, n, 3)) ? "Yes" : "No") << "\n";
    cout << "Is value 3 in array: " << ((recursiveBinarySearch(a, 0, n - 1, 3)) ? "Yes" : "No") << "\n\n";

    cout << "Is value 10 in array: " << ((normalBinarySearch(a, n, 10)) ? "Yes" : "No") << "\n";
    cout << "Is value 10 in array: " << ((recursiveBinarySearch(a, 0, n - 1, 10)) ? "Yes" : "No") << "\n";
    return 0;
}
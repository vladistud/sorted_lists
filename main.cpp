#include <iostream>

using namespace std;

// Функция для вывода массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// 1. Сортировка Шелла
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// 2. Быстрая сортировка (Хоара)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 3. Сортировка слиянием
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 4. Сортировка подсчётом
void countingSort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int range = max - min + 1;
    int count[range], output[n];

    for (int i = 0; i < range; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[arr[i] - min]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

// 5. Блочная сортировка
void bucketSort(int arr[], int n) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    int bucketCount = n / 2; 
    if (bucketCount < 1) bucketCount = 1;
    int buckets[bucketCount][n];
    int sizes[bucketCount];

    for (int i = 0; i < bucketCount; i++) sizes[i] = 0;

    float range = (float)(max - min + 1) / bucketCount;

    for (int i = 0; i < n; i++) {
        int index = (arr[i] - min) / range;
        if (index >= bucketCount) index = bucketCount - 1;
        buckets[index][sizes[index]++] = arr[i];
    }

    for (int i = 0; i < bucketCount; i++) {
        if (sizes[i] > 1)
            shellSort(buckets[i], sizes[i]);
    }

    int k = 0;
    for (int i = 0; i < bucketCount; i++)
        for (int j = 0; j < sizes[i]; j++)
            arr[k++] = buckets[i][j];
}

// Основная функция для тестирования всех сортировок
int main() {
    int arr[] = {29, 10, 14, 37, 13, 7, 22, 17, 5, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    int arr1[n], arr2[n], arr3[n], arr4[n], arr5[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = arr[i];
        arr2[i] = arr[i];
        arr3[i] = arr[i];
        arr4[i] = arr[i];
        arr5[i] = arr[i];
    }

    cout << "Исходный массив: ";
    printArray(arr, n);

    shellSort(arr1, n);
    cout << "Сортировка Шелла: ";
    printArray(arr1, n);

    quickSort(arr2, 0, n - 1);
    cout << "Быстрая сортировка (Хоара): ";
    printArray(arr2, n);

    mergeSort(arr3, 0, n - 1);
    cout << "Сортировка слиянием: ";
    printArray(arr3, n);

    countingSort(arr4, n);
    cout << "Сортировка подсчётом: ";
    printArray(arr4, n);

    bucketSort(arr5, n);
    cout << "Блочная сортировка: ";
    printArray(arr5, n);

    return 0;
}

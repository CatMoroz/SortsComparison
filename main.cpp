#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

/*

В этом блоке находятся вспомогательные для сортировок функции

*/

// Функция для разделения массива
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Функция для разделения массива с двумя опорными элементами
int partition2(std::vector<int>& arr, int low, int high, int* lp) {
    if (arr[low] > arr[high]) {
        std::swap(arr[low], arr[high]);
    }

    int j = low + 1;
    int g = high - 1, k = low + 1;
    int p = arr[low], q = arr[high];

    while (k <= g) {
        if (arr[k] < p) {
            std::swap(arr[k], arr[j]);
            j++;
        } else if (arr[k] >= q) {
            while (arr[g] > q && k < g) {
                g--;
            }
            std::swap(arr[k], arr[g]);
            g--;
            if (arr[k] < p) {
                std::swap(arr[k], arr[j]);
                j++;
            }
        }
        k++;
    }

    j--;
    g++;

    std::swap(arr[low], arr[j]);
    std::swap(arr[high], arr[g]);

    *lp = j;
    return g;
}

// Функция для разделения массива с тремя опорными элементами
int partition3(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) std::swap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);

    int pivot = arr[mid];
    int i = low + 1;
    int j = high - 1;
    int k = i;

    while (k <= j) {
        if (arr[k] < pivot) {
            std::swap(arr[k], arr[i]);
            i++;
        } else if (arr[k] > pivot) {
            std::swap(arr[k], arr[j]);
            j--;
        } else {
            k++;
        }
    }

    std::swap(arr[mid], arr[j]);
    return j;
}

// Функция для слияния двух подмассивов
void merge(std::vector<int>& arr, int low, int mid, int high) {
    int len1 = mid - low + 1;
    int len2 = high - mid;

    std::vector<int> left(len1), right(len2);

    for (int i = 0; i < len1; i++)
        left[i] = arr[low + i];
    for (int j = 0; j < len2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

// Функция для создания максимального кучи
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

/* 

В этом блоке находятся все сортировки

*/

// Функция для сортировки Quick Sort | QuickSort(arr, 0, arr.size() - 1);
void QuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        QuickSort(arr, low, pivot - 1);
        QuickSort(arr, pivot + 1, high);
    }
}

// Функция для сортировки Dual Pivot QuickSort | DualPivotQuickSort(arr, 0, arr.size() - 1);
 void DualPivotQuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int lp, rp;
        rp = partition2(arr, low, high, &lp);
        DualPivotQuickSort(arr, low, lp - 1);
        DualPivotQuickSort(arr, lp + 1, rp - 1);
        DualPivotQuickSort(arr, rp + 1, high);
    }
} 

// Функция для сортировки Radix sort (MSD) | RadixSortMSD(arr);
void RadixSortMSD(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int digitPosition = 1;
    while (maxVal / digitPosition > 0) {
        std::vector<int> bucket(10, 0);
        std::vector<int> output(arr.size());

        for (int i = 0; i < arr.size(); i++)
            bucket[(arr[i] / digitPosition) % 10]++;

        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--)
            output[--bucket[(arr[i] / digitPosition) % 10]] = arr[i];

        arr = output;
        digitPosition *= 10;
    }
}

// Функция для сортировки Radix sort (LSD) | RadixSortLSD(arr);
void RadixSortLSD(std::vector<int>& arr) {
    int maxVal = *std::max_element(arr.begin(), arr.end());
    int digitPosition = 1;
    while (maxVal / digitPosition > 0) {
        std::vector<int> bucket(10, 0);
        std::vector<int> output(arr.size());

        for (int i = 0; i < arr.size(); i++)
            bucket[(arr[i] / digitPosition) % 10]++;

        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];

        for (int i = arr.size() - 1; i >= 0; i--)
            output[--bucket[(arr[i] / digitPosition) % 10]] = arr[i];

        arr = output;
        digitPosition *= 10;
    }
}

// Функция для сортировки вставками | InsertionSort(arr, 0, arr.size() - 1);
void InsertionSort(std::vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Функция Shell Sort | ShellSort(arr);
void ShellSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > temp; j -= interval) {
                arr[j] = arr[j - interval];
            }
            arr[j] = temp;
        }
    }
}

// Функция Merge Sort | MergeSort(arr, 0, arr.size() - 1);
void MergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Функция Heap Sort | HeapSort(arr);
void HeapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Функция Selection Sort | SelectionSort(arr);
void SelectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
    }
}

// Функция Bubble Sort | BubbleSort(arr);
void BubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool isUnsorted;
    do {
        isUnsorted = false;
        for (int i = 0; i < (n - 1); i++) {
            if (arr[i] > arr[i + 1]) {
                isUnsorted = true;
                for (; i < (n - 1); i++) {
                    if (arr[i] > arr[i + 1]) {
                        std::swap(arr[i], arr[i + 1]);
                    }
                }
            }
        }
    } while (isUnsorted);
}

// Функция для заполнения массива случайными числами
void fillWithRandomNumbers(std::vector<int>& arr) {
    std::generate(arr.begin(), arr.end(), []() {
        return rand(); // Генерация случайных неотрицательных чисел
    });
}

/* 

В функции main происходит замер времени сортировок

*/

int main() {
    std::vector<int> arr(1); // Начальный массив размером 1
    int increaseSize = 1; // Размер увеличения вектора
    int amount_of_replays = 50; // Количество повторений сортировок при одинаковом размере
    std::string filename = "times/random_little_data/SelectionSort.txt";
    std::cout << filename << std::endl;
    std::ofstream file(filename, std::ios::app); // Открываем файл в режиме добавления
    if (file.is_open()) {
        while (arr.size() < 10000) {
            if ((arr.size()) % 1000 == 0)
            {
                std::cout << arr.size() << std::endl;
            }
            double totalTime = 0.0;
            for (int i = 0; i < amount_of_replays; ++i) {
                // Заполняем массив случайными числами
                fillWithRandomNumbers(arr);
                // Замер времени сортировки
                auto start = std::chrono::high_resolution_clock::now();
                SelectionSort(arr);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                totalTime += elapsed.count();
            }

            // Вычисляем среднее значение времени
            double averageTime = totalTime / amount_of_replays;

            // Запись времени в файл
            file << averageTime << " ";

            // Увеличиваем размер массива
            if (arr.size() < 500) 
            {
                increaseSize = 1;
                amount_of_replays = 20; 
            } 
            else if (arr.size() < 100000)
            {
                increaseSize = 100;
                amount_of_replays = 10; 
            }
            else
            {
                increaseSize = 2500;
                amount_of_replays = 5;
            }
            arr.resize(arr.size() + increaseSize);
            }
    file.close();
    }
    return 0;
}

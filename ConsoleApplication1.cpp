#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <cstring>

template <typename T>
void babelkowe_Pana(T* arr, int n) {
    T* w1, * w2, temp;
    for (int i = 0; i < n; i++) {
        w1 = arr;
        w2 = w1 + 1;
        for (int j = 0; j < n - 1; j++) {
            if (*w2 < *w1) {
                temp = *w2;
                *w2 = *w1;
                *w1 = temp;
            }
            w1++;
            w2++;
        }
    }
}

template <typename T>
void bubblesort_for_for_pointer(T* arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                T temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

template <typename T>
void bubblesort_while_for_pointer(T* arr, int n) {
    int i = 0;
    while (i < n) {
        for (int j = 0; j < n - 1; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                T temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
        i++;
    }
}

template <typename T>
void bubblesort_while_shorten_for_pointer(T* arr, int n) {
    int i = 0;
    while (i < n) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                T temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
        i++;
    }
}

template <typename T>
void losowanko(T* arr, int n) {
    for (int h = 0; h < n; h++) {
        if constexpr (std::is_integral<T>::value) {
            arr[h] = rand() % 10 + 1;  // dla int
        }
        else {
            arr[h] = (rand() % 1000) / 100.0;  // dla float, liczby zmiennoprzecinkowe
        }
    }
}


template <typename T>
void test_algorytmy_sortowania() {
    srand(time(NULL));

    int rozmiary[] = { 100, 1000, 10000, 100000 };

    // nazwy kolumn
    std::cout << std::setw(30) << std::left << "Sposob sortowania";
    for (int i = 0; i < 4; i++) {
        std::cout << std::setw(15) << rozmiary[i];
    }
    std::cout << "\n";

    // testowanie algorytmow
    std::string algorytmy[] = { "Babelkowe Pana", "For-for pointer", "While-for pointer", "While shorten-for pointer" };
    void (*funkcje_sortujace[])(T*, int) = { babelkowe_Pana, bubblesort_for_for_pointer, bubblesort_while_for_pointer, bubblesort_while_shorten_for_pointer };

    for (int i = 0; i < 4; i++) {
        std::cout << std::setw(30) << std::left << algorytmy[i];

        for (int j = 0; j < 4; j++) {
            int n = rozmiary[j];

            T* arr = new T[n];

            losowanko(arr, n);

            // kopiujemy tablice przed kazdym algorytmem
            T* arr_copy = new T[n];
            std::memcpy(arr_copy, arr, n * sizeof(T));

            // mierzenie czasu wykonania sortowania
            auto start = std::chrono::high_resolution_clock::now();
            funkcje_sortujace[i](arr_copy, n);  // wywolanie wybranego algorytmu
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> czas = end - start;

            // wyswietlanie czasu
            std::cout << std::setw(15) << std::fixed << std::setprecision(6) << czas.count();

            delete[] arr_copy;
            delete[] arr;
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "FLOAT:\n";
    test_algorytmy_sortowania<float>();

    std::cout << "\nINT:\n";
    test_algorytmy_sortowania<int>();

    return 0;
}

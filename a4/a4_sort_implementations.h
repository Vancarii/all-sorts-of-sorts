// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Yecheng Wang 
// St.# : 301540271
// Email: ywa415@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "a4_base.h"
// #include <chrono>

using namespace std;

// using namespace std::chrono;


template <typename T>
bool is_sorted(vector<T> &v){

    int sz = v.size();

    for (int i = 1; i < sz; ++i){
        if (v[i] < v[i - 1]){
            return false;
        }
    }
    return true;
};

//  Bubble Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    // time_point start = high_resolution_clock::now();
    ulong num_comps = 0; 
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++;
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    SortStats stats = SortStats{"Bubble sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

    // cout << stats.to_csv() << endl;


    return stats;
}

//  Insertion Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats insertion_sort(vector<T> &v){

    ulong num_comps = 0;
    int n = v.size();

    clock_t start = clock();
    // time_point start = high_resolution_clock::now();

    for (int i = 1; i < n; ++i){
        T key = v[i];
        int j = i - 1;

        while (j >= 0)
        {
            num_comps++;

            if (v[j] > key)
            {
                v[j + 1] = v[j];
                j--;
            }
            else
            {
                break;
            }
        }
        v[j+1] = key;
    }

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Insertion sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

//  Selection Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats selection_sort(vector<T> &v){

    // time_point start = high_resolution_clock::now();
    clock_t start = clock();

    int n = v.size();

    ulong num_comps = 0;


    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;

        // Find the index of the minimum element in the unsorted part of the vector
        for (int j = i + 1; j < n; ++j)
        {
            num_comps++;
            if (v[j] < v[minIndex])
            {
                minIndex = j;
            }
        }

        // Swap the minimum element with the first element of the unsorted part
        swap(v[i], v[minIndex]);
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};


//  Merge Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void merge(vector<T> &v, int start, int mid, int end, ulong &num_comps)
{
    vector<T> temp(end - start + 1);
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
        num_comps++;
        if (v[i] <= v[j])
        {
            temp[k++] = v[i++];
        }
        else
        {
            temp[k++] = v[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = v[i++];
    }

    while (j <= end)
    {
        temp[k++] = v[j++];
    }

    for (int idx = start; idx <= end; ++idx)
    {
        v[idx] = temp[idx - start];
    }
}

template <typename T>
void mergeRec(vector<T> &v, int start, int end, ulong &num_comps)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        mergeRec(v, start, mid, num_comps);
        mergeRec(v, mid + 1, end, num_comps);
        merge(v, start, mid, end, num_comps);
    }
}

template <typename T>
SortStats merge_sort(vector<T> &v)
{
    // time_point start = high_resolution_clock::now();

    clock_t start = clock();

    ulong num_comps = 0;

    int n = v.size();
    if (n <= 1)
    {
        return SortStats();
    }

    mergeRec(v, 0, n - 1, num_comps);

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    SortStats stats = SortStats{"Merge sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

    return stats;
}

//  Quick Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int partition(vector<T> &v, int low, int high, ulong &num_comps)
{
    T pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        num_comps++;
        if (v[j] <= pivot)
        {
            ++i;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);
    return i + 1;
}

template <typename T>
void quickSort(vector<T> &v, int low, int high, ulong &num_comps)
{
    if (low < high)
    {
        int pivotIdx = partition(v, low, high, num_comps);

        quickSort(v, low, pivotIdx - 1, num_comps);
        quickSort(v, pivotIdx + 1, high, num_comps);
    }
}

template <typename T>
SortStats quick_sort(vector<T> &v){

    clock_t start = clock();
    // time_point start = high_resolution_clock::now();

    ulong num_comps = 0;

    int n = v.size();
    // if (n <= 1)
    // {
    //     return;
    // }

    quickSort(v, 0, n - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    return SortStats{"Quick sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}


//  Shell Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats shell_sort(vector<T> &v){

    clock_t start = clock();
    // time_point start = high_resolution_clock::now();

    ulong num_comps = 0;

    int n = v.size();

    // Start with a large gap and reduce it in each iteration by /2
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Perform insertion sort on elements at the gap intervals
        for (int i = gap; i < n; ++i)
        {
            T temp = v[i];
            int j;

            // Shift elements until the correct position for the current element is found
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
            {
                num_comps++;
                v[j] = v[j - gap];
            }

            v[j] = temp;
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    return SortStats{"Shell sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

//  iQuick Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int i_partition(vector<T> &v, int low, int high, ulong &num_comps)
{
    T pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        num_comps++;
        if (v[j] <= pivot)
        {
            ++i;
            swap(v[i], v[j]);
        }
    }

    swap(v[i + 1], v[high]);
    return i + 1;
}

template <typename T>
void iquickSort(vector<T> &v, int low, int high, ulong &num_comps)
{

    int threshold = 15;
    int sz = high - low;
    // cout << " v before: " << v << endl;

    if (low < high)
    {

        if (sz <= threshold){
            vector<T> v2;

            for (int i = low; i <= high; i++){
                v2.push_back(v[i]);
            }
            // cout << " v before: " << v << endl;
            // cout << "v2 before: " << v2 << endl;
            SortStats stats = insertion_sort(v2);
            num_comps += stats.num_comparisons;
            // cout << v2 << endl;
            int j = 0;
            for (int i = low; i <= high; i++){
                v[i] = v2[j];
                j++;
            }
                // cout << "v after: " << v << endl;
                // cout << "v2 after: " << v2 << endl << endl;
        } else {
            int pivotIdx = i_partition(v, low, high, num_comps);

            // cout << "pivot : " << v[pivotIdx] << endl;

            iquickSort(v, low, pivotIdx - 1, num_comps);
            iquickSort(v, pivotIdx + 1, high, num_comps);
        }
    }
}

template <typename T>
SortStats iquick_sort(vector<T> &v){


    clock_t start = clock();
    // time_point start = high_resolution_clock::now();

    ulong num_comps = 0;

    int n = v.size();
    // if (n <= 1)
    // {
    //     return;
    // }

    iquickSort(v, 0, n - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    // cout << "end: " << end << endl
    //      << "start: " << start << endl
    //      << "clock: " << CLOCKS_PER_SEC << endl;

    // time_point stop = high_resolution_clock::now();
    // auto duration = duration_cast<nanoseconds>(stop - start);
    // double elapsed_cpu_time_sec = duration.count() / (double)1e9;

    SortStats stats = SortStats{"iQuick sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

    // cout << stats.to_csv() << endl;

    return stats;
};


//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max){

    vector<int> v;

    srand((unsigned int)time(NULL));
    
    for (int i = 0; i < n; ++i){


        int num = (rand() % max) + min;
        v.push_back(num);
        
    }

    return v;

}; 



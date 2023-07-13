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

// Note: Using clock() would give the correct output on CSIL Linux system,
// and would not operate properly on my wsl terminal
// To run on wsl, I had to use chrono to have proper cpu run times
// my a4.xlsx is created using clock() running on CSIL Linux machines

using namespace std;


template <typename T>
bool is_sorted(vector<T> &v){

    int sz = v.size();

    // Array has one or no element
    if (sz == 0 || sz == 1){
        return true;
    }

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

    clock_t start = clock();
    ulong num_comps = 0; 


    // external loop iterates through array
    // each external loop iteration pushes another largest element to the right
    // which eventually sorts the array
    for (int i = 0; i < v.size(); i++)
    {
        // internal for loop goes from i to the end
        // after each time the internal for loop completes, the largest element 
        // is to the right most position
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++;
            // compares j and j+1
            // swapping the larger element to the right
            if (v[j] > v[j + 1])
            {
                swap(v[j], v[j+1]);
            }
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Bubble Sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

}

//  Insertion Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats insertion_sort(vector<T> &v){

    ulong num_comps = 0;
    int n = v.size();

    clock_t start = clock();

    // external loop through entire array
    for (int i = 1; i < n; ++i){
        T key = v[i];
        int j = i - 1;

        // This while loop is split into a loop and an if statement instead
        // of two conditions in the loop
        // This way we can increment the num_comps as long as numbers are compared,
        // and not only if they are swapped
        while (j >= 0)
        {
            num_comps++;

            // swapped elements if in incorrect order
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

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Insertion Sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

//  Selection Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats selection_sort(vector<T> &v){

    clock_t start = clock();

    int n = v.size();

    ulong num_comps = 0;


    // loops through the entire array
    // internal loop goes from i to end of array
    // finding the smallest element to place where i is
    // then increment i
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

    return SortStats{"Selection Sort",
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

    // loops through the array and saves the smaller value to temp and increments that index
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

    // at this part, we are done with one index var, so simply save all the rest from the other 
    // index variable to temp
    while (i <= mid)
    {
        temp[k++] = v[i++];
    }

    while (j <= end)
    {
        temp[k++] = v[j++];
    }

    // Now temp is sorted and merged 
    // save all of temp to v
    for (int idx = start; idx <= end; ++idx)
    {
        v[idx] = temp[idx - start];
    }
}

template <typename T>
void mergeRec(vector<T> &v, int start, int end, ulong &num_comps)
{
    // recursive definition of merge sort
    // continously splits the vector array in the middle,
    // calling merge on the smaller arrays
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
    clock_t start = clock();

    ulong num_comps = 0;

    int n = v.size();

    // checks input
    if (n <= 1)
    {
        return SortStats();
    }

    // Calls the main function to sort the array v
    // since the recursive definition needs to pass in more parameters,
    // a helper, mergeRec, is used instead of this current function
    mergeRec(v, 0, n - 1, num_comps);


    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Merge sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

}

//  Quick Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int partition(vector<T> &v, int low, int high, ulong &num_comps)
{

    // saves the pivot value to be compared 
    T pivot = v[high];
    int i = low - 1;

    // loops through the array and swaps indexes i and j if j is <= pivot
    // this makes it so the smaller values are in i's position, to the left
    // and larger values are to the right
    // then it swaps the pivot to the correct position between i and j values
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
    // recursive definition of quick sort
    // calls partition to split the array into smaller and larger value arrays 
    // recursive calls on the smaller and larger arrays to sort them
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

    ulong num_comps = 0;

    int n = v.size();
    if (n <= 1)
    {
        return SortStats();
    }

    // main sorting call
    quickSort(v, 0, n - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Quick Sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}


//  Shell Sort  //////////////////////////////////////////////////////////////////////////////////////

template <typename T>
SortStats shell_sort(vector<T> &v){

    clock_t start = clock();

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

    return SortStats{"Shell Sort",
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

    // loops through the array and swaps indexes i and j if j is <= pivot
    // this makes it so the smaller values are in i's position, to the left
    // and larger values are to the right
    // then it swaps the pivot to the correct position between i and j values
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

    // Setting the threshold to 15
    // So that sub arrays size 15 and smaller are sorted using insertion sort
    // else, larger sub arrays are sorted with quick sort
    int threshold = 15;
    int sz = high - low;

    if (low < high)
    {

        // checks if the size of the sub array is smaller than threshold
        // we create a new vector, and insert the values from v to v2,
        // between low and high
        // pass v2 into insertion sort, saving the num_comparisons
        // and save it back into the correct position into v
        if (sz <= threshold){
            vector<T> v2;

            for (int i = low; i <= high; i++){
                v2.push_back(v[i]);
            }

            SortStats stats = insertion_sort(v2);
            num_comps += stats.num_comparisons;

            int j = 0;

            for (int i = low; i <= high; i++){
                v[i] = v2[j];
                j++;
            }

        //  if the size is larger than threshold, run quicksort
        } else {

            int pivotIdx = i_partition(v, low, high, num_comps);

            iquickSort(v, low, pivotIdx - 1, num_comps);
            iquickSort(v, pivotIdx + 1, high, num_comps);
        }
    }
}

template <typename T>
SortStats iquick_sort(vector<T> &v){

    clock_t start = clock();

    ulong num_comps = 0;

    int n = v.size();
    if (n <= 1)
    {
        return SortStats();
    }

    // main sorting function
    iquickSort(v, 0, n - 1, num_comps);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"iQuick Sort",
                                v.size(),
                                num_comps,
                                elapsed_cpu_time_sec};

};


//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max){

    vector<int> v;

    // ensures the rand value is not duplicated, otherwise the same values are produced evertime
    srand((unsigned int)time(NULL));
    
    // loops through the given size, and creates a random value between max and min
    // push to v and return v
    for (int i = 0; i < n; ++i){

        int num = (rand() % max) + min;
        v.push_back(num);
        
    }

    return v;

}; 



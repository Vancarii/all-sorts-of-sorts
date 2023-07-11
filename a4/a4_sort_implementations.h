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

using namespace std;


//
// Put the implementations of all the functions listed in a4_base.h here.
//

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


template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
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

    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}




template <typename T>
SortStats insertion_sort(vector<T> &v){

    ulong num_comps = 0;
    int n = v.size();

    clock_t start = clock();

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

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Insertion sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};



template <typename T>
SortStats selection_sort(vector<T> &v){

    int n = v.size();

    ulong num_comps = 0;

    clock_t start = clock();

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

    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};







template <typename T>
void merge(vector<T> &v, int start, int mid, int end)
{
    vector<T> temp(end - start + 1);
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
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
void mergeRec(vector<T> &v, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;
        mergeRec(v, start, mid);
        mergeRec(v, mid + 1, end);
        merge(v, start, mid, end);
    }
}

template <typename T>
SortStats merge_sort(vector<T> &v)
{
    clock_t start = clock();

    ulong num_comps = 0;

    int n = v.size();
    // if (n <= 1)
    // {
    //     return;
    // }

    mergeRec(v, 0, n - 1);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Merge sort",
                        v.size(),
                        num_comps,
                        elapsed_cpu_time_sec};
}



template <typename T>
SortStats quick_sort(vector<T> &v);

template <typename T>
SortStats shell_sort(vector<T> &v);

template <typename T>
SortStats iquick_sort(vector<T> &v);

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max){

    vector<int> v;

    for (int i = 0; i < n; i++){
        
        int num = rand() % (max - 1) + (min + 1);

        if (num != min && num != max){
            v.push_back(num);
        }
        
    }

    return v;

}; 



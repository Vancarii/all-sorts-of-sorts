// test_sorts.cpp

//
// Test all the sorts in sort_implementation.h. 
//
// Ignores the SortStats object returned by the sort functions.
//

// #include "a4_base.h"
#include "a4_sort_implementations.h"
#include "test.h"
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


int main()
{

    vector<int> v;

    // v = rand_vec(2000 , 1, 2000);
    // cout << v << endl;
    // // assert(!is_sorted(v));
    // SortStats stats = quick_sort(v);
    // cout << v << endl;
    // assert(is_sorted(v));    
    // cout << stats.to_csv() << endl;

    ofstream filestream("sortsofsorts.txt");



    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = bubble_sort(v);
        cout << stats.to_csv() << endl;
        cout << setprecision(15);
        filestream << stats.to_csv() << endl;
    }



    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = insertion_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }
    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = selection_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }
    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = merge_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }
    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = quick_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }
    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = shell_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }
    for (int N = 2000; N <= 50000; N += 2000)
    {
        v = rand_vec(N, 1, N);
        SortStats stats = iquick_sort(v);
        cout << stats.to_csv() << endl;
        filestream << stats.to_csv() << endl;
    }

} // main

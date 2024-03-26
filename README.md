## Sorting

In this assignment, your task is to run performance experiments on 7 sorting
algorithms: *bubble* sort, *insertion* sort, *selection* sort, *merge* sort,
*quick* sort, *shell* sort, and a hybrid algorithm combining quick sort and
insertion sort that we'll call *iquick* sort. You'll create a spreadsheet to
report on your results.

*iquick* sort is regular quick sort, except when the sub-vectors being sorted
are shorter than some predetermined threshold length, insertion sort is used instead
of quick sort. If you choose a good threshold length, you can get better
average-time performance than regular quick sort. Do some experimentation to
find the best threshold length for *iquick* sort!

For this assignment, `num_comparisons` is the number of times `<` or `<=` is
called on the values in the vector. It's declared to be of type `ulong`
(`unsigned long`) because the comparison counts can get very large.

### Example: Bubble Sort

For example, you can implement bubble sort like this:

```cpp
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
```

### Timing Code in C++

As shown in `bubble_sort`, you can measure CPU time using `clock()` like this:

```cpp
#include <ctime>

void timed_experiment() {
    clock_t start = clock();

    //
    // ... do stuff ...
    //

    clock_t end = clock();

    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    cout << "It took " << elapsed_cpu_time_sec << " seconds to do stuff.\n";
}
```

[cpu_timer_example.cpp](cpu_timer_example.cpp) contains a complete example of
some timing code.


## Generating the Experimental Data

- For each of the 7 sorting algorithms, the following was done:
  - For *N* = 2000, 4000, 6000, ..., 50000 (25 different values of *N*) do the
    following:
    - create a vector of *N* random integers, where the numbers in the vectors
      range from 1 to *N*
    - run the sort on the vector of random integers
    - print the sort name, amount of data being sorted, number of comparisons
      that were done, and the CPU time (in seconds)

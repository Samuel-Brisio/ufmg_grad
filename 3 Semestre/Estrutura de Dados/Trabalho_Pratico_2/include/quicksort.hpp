#ifndef QUICKSORTHPP
#define QUICKSORTHPP

//https://www.geeksforgeeks.org/cpp-program-for-quicksort/

/* C implementation QuickSort */
#include<stdio.h>


namespace quick {

    // A utility function to swap two elements
    template <typename T>
    void swap(T &a, T &b)
    {
        T t = a;
        a = b;
        b = t;
    }

    /* This function takes last element as pivot, places
    the pivot element at its correct position in sorted
        array, and places all smaller (smaller than pivot)
    to left of pivot and all greater elements to right
    of pivot */
    template <typename T>
    int partition (T arr[], int low, int high)
    {
        T pivot = arr[high]; // pivot
        int i = (low - 1); // Index of smaller element

        for (int j = low; j <= high- 1; j++)
        {
            // If current element is larger
            if (arr[j] > pivot)
            {
                i++; // increment index of smaller element
                quick::swap(arr[i], arr[j]);
            }
        }
        quick::swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    /* The main function that implements QuickSort
    arr[] --> Array to be sorted,
    low --> Starting index,
    high --> Ending index */
    template <typename T>
    void quickSort(T arr[], int low, int high)
    {
        if (low < high)
        {
            /* pi is partitioning index, arr[p] is now
            at right place */
            int pi = partition(arr, low, high);

            // Separately sort elements before
            // partition and after partition
            quick::quickSort(arr, low, pi - 1);
            quick::quickSort(arr, pi + 1, high);
        }
    }

    /* Function to print an array */
    template <typename T>
    void printArray(T arr[], int size)
    {
        int i;
        for (i=0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

}

#endif
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <omp.h>

using namespace std;

typedef unsigned long long data_t;

void merge(vector <data_t>::iterator dest_start, int dest_size, vector <data_t>::iterator left_start, int left_size, vector <data_t>::iterator right_start, int right_size) {
    int index = dest_size - (left_size + right_size);

    if (left_size == 0 && right_size == 0) {
        return;
    } else if (left_size == 0) {
        *(dest_start + index) = *right_start;
        merge(dest_start, dest_size, left_start, left_size, right_start + 1, right_size - 1);
        return;
    } else if (right_size == 0) {
        *(dest_start + index) = *left_start;
        merge(dest_start, dest_size, left_start + 1, left_size - 1, right_start, right_size);
        return;
    }

    if (*left_start < *right_start) {
        *(dest_start + index) = *left_start;
        merge(dest_start, dest_size, left_start + 1, left_size - 1, right_start, right_size);
    } else {
        *(dest_start + index) = *right_start;
        merge(dest_start, dest_size, left_start, left_size, right_start + 1, right_size - 1);
    }
}

void merge_sort(vector <data_t>::iterator dest_start, vector <data_t>::iterator dest_end, vector <data_t>::iterator data_start, vector <data_t>::iterator data_end, int depth=0) {
    int n = data_end - data_start;
    int tn = omp_get_num_threads();
    if (n/2 > 1) {
        merge_sort(dest_start, dest_start + n/2, data_start, data_start + n/2, depth + 1);
    }
    if (n - (n/2) > 1) {
        merge_sort(dest_start + n/2, dest_end, data_start + n/2, data_end, depth + 1);
    }
   
    merge(dest_start, n, data_start, n/2, data_start + n/2, n - n/2);
    for (int i = 0; i < n; i++) {
        *(data_start + i) = *(dest_start + i);
    }
    
}

void psort(int n, data_t *data) {
    // FIXME: Implement a more efficient parallel sorting algorithm for the CPU,
    // using the basic idea of merge sort.
    vector <data_t> sorted(n);
    vector <data_t> unsorted(data, data + n);
    #pragma omp parallel
    {
        int tn = omp_get_num_threads();
        int window_size = max(2, n/tn);
        //cout << window_size << endl;

        #pragma omp for
        for (int i=0; i < min(n/window_size + (n % window_size != 0), tn); i++) {
            int start = i*window_size;
            int end = min(n, (i+1)*window_size);
            #pragma omp critical 
            {
                cout << start << " " << end << endl;
            }

            if (i==tn-1) {
                merge_sort(sorted.begin()+start, sorted.end(), unsorted.begin()+start, unsorted.end());
            } else {
                merge_sort(sorted.begin()+start, sorted.begin()+end, unsorted.begin()+start, unsorted.begin()+end);
            }
        }
    }
    
    
    
    for (int i=0; i < n; i++) {
        data[i] = sorted[i];
    }
}

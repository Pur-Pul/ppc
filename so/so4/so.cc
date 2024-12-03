#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

typedef unsigned long long data_t;

void merge(vector <data_t>::iterator dest_start, vector <data_t>::iterator dest_end, vector <data_t>::iterator left_start, vector <data_t>::iterator left_end, vector <data_t>::iterator right_start, vector <data_t>::iterator right_end) {
    int left_size = left_end - left_start;
    int right_size = right_end - right_start;
    int dest_size = dest_end - dest_start;
    int index = dest_size - (left_size + right_size) + 1;
    //cout << left_size << " " << right_size << " " << dest_size << endl;
    
    if (left_size == 0 && right_size == 0) {
        return;
    } else if (left_size == 0) {
        *(dest_start + index) = *right_end;
        merge(dest_start, dest_end, left_start, left_end, right_start, right_end - 1);
        return;
    } else if (right_size == 0) {
        *(dest_start + index) = *left_end;
        merge(dest_start, dest_end, left_start, left_end - 1, right_start, right_end);
        return;
    }

    if (*left_end < *right_end) {
        cout << index << endl;
        *(dest_start + index) = *left_end;
        merge(dest_start, dest_end, left_start, left_end - 1, right_start, right_end);
    } else {
        cout << index << endl;
        *(dest_start + index) = *right_end;
        merge(dest_start, dest_end, left_start, left_end, right_start, right_end - 1);
    }
}

void merge_sort(vector <data_t>::iterator dest_start, vector <data_t>::iterator dest_end, vector <data_t>::iterator data_start, vector <data_t>::iterator data_end) {
    int n = data_end - data_start;
    if (n/2 > 1) {
        merge_sort(dest_start, dest_start + n/2, data_start, data_start + n/2);
    }
    if (n - (n/2) > 1) {
        merge_sort(dest_start + n/2, dest_end, data_start + n/2, data_end);
    }
    merge(dest_start, dest_end, data_start, data_start + n/2, data_start + n/2, data_end);
}

void psort(int n, data_t *data) {
    // FIXME: Implement a more efficient parallel sorting algorithm for the CPU,
    // using the basic idea of merge sort.
    vector <data_t> sorted(n);
    vector <data_t> unsorted(n);

    for (int i = 0; i < n; i++) 
        unsorted.push_back(data[i]); 
    //std::sort(data, data + n);
    merge_sort(sorted.begin(), sorted.end(), unsorted.begin(), unsorted.end());
    for (int i=0; i < n; i++) {
        data[i] = sorted[i];
    }
}

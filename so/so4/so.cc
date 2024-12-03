#include <algorithm>
#include <vector>

using std::vector;

typedef unsigned long long data_t;

void merge(vector <data_t> *dest, vector <data_t> *left, vector <data_t> *right) {
    int index = (*dest).size() - ((*left).size() + (*right).size());
    if ((*left).empty() && (*right).empty()) {
        return;
    } else if ((*left).empty()) {
        (*dest)[index] = (*right).back();
        (*right).pop_back();
        merge(dest, left, right);
        return;
    } else if ((*right).empty()) {
        (*dest)[index] = (*left).back();
        (*left).pop_back();
        merge(dest, left, right);
    }

    if ((*left).back() < (*right).back()) {
        (*dest)[index] = (*left).back();
        (*left).pop_back();
        merge(dest, left, right);
    } else {
        (*dest)[index] = (*right).back();
        (*right).pop_back();
        merge(dest, left, right);
    }
}

void merge_sort(vector <data_t> *dest, vector <data_t> *data) {
    int n = (*data).size();

    vector <data_t> left((*data).begin(), (*data).begin()+n/2);
    vector <data_t> right((*data).begin()+n/2, (*data).end());
    if (left.size() > 1) {
        merge_sort(dest, &left);
    }
    if (right.size() > 1) {
        merge_sort(dest, &right);
    }
    merge(data, &left, &right);
}

void psort(int n, data_t *data) {
    // FIXME: Implement a more efficient parallel sorting algorithm for the CPU,
    // using the basic idea of merge sort.
    vector <data_t> sorted(n);
    vector <data_t> unsorted(data, data+n);
    //std::sort(data, data + n);
    merge_sort(&sorted, &unsorted);
    for (int i=0; i < n; i++) {
        data[i] = sorted[i];
    }
}

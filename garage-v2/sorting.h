#ifndef SORTING_H
#define SORTING_H
#include <vector>

template<typename T, typename Compare>
void insertionSort(std::vector<T> &v, Compare compare){
        for (size_t i = 1; i < v.size(); i++){
        T key = v[i];
        int j = static_cast<int>(i) - 1;
        while (j >= 0 && compare(key, v[j])) {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j+1] = key; 
    }
}

#endif
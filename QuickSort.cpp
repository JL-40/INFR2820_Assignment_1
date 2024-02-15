//
// Created by Jeffry - 100698915 on 2024-02-11.
//
#include "CommonIncludes.h"
#include "ProductData.cpp"

using namespace std;

class QuickSorter {
    size_t pivot{};
    Product productData;

    void Swap(vector<string>& array, int index1, int index2) {
        string tmp = array.at(index1);
        array.at(index1) = array.at(index2);
        array.at(index2) = tmp;
    }

    void MedianOfThree(vector<string>& array, int sortBy, int min, int max, bool ascending = true) {
        int median = (min + max) / 2;

        if (ascending)
        {
            // Swap min with median
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(min)).at(sortBy)) >
                stof(productData.ProductData(array.at(median)).at(sortBy))
                                           :
                productData.ProductData(array.at(min)).at(sortBy) >
                productData.ProductData(array.at(median)).at(sortBy))
            {
                Swap(array, min, median);
            }

            // Swap median with max
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(median)).at(sortBy)) >
                stof(productData.ProductData(array.at(max)).at(sortBy))
                                           :
                productData.ProductData(array.at(median)).at(sortBy) >
                productData.ProductData(array.at(max)).at(sortBy))
            {
                Swap(array, median, max);
            }

            // Swap min with median again
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(min)).at(sortBy)) >
                stof(productData.ProductData(array.at(median)).at(sortBy))
                                           :
                productData.ProductData(array.at(min)).at(sortBy) >
                productData.ProductData(array.at(median)).at(sortBy))
            {
                Swap(array, min, median);
            }
        }
        else
        {
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(min)).at(sortBy)) <
                stof(productData.ProductData(array.at(median)).at(sortBy))
                                           :
                productData.ProductData(array.at(min)).at(sortBy) <
                productData.ProductData(array.at(median)).at(sortBy))
            {
                Swap(array, min, median);
            }

            // Swap median with max
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(median)).at(sortBy)) <
                stof(productData.ProductData(array.at(max)).at(sortBy))
                                           :
                productData.ProductData(array.at(median)).at(sortBy) <
                productData.ProductData(array.at(max)).at(sortBy))
            {
                Swap(array, median, max);
            }

            // Swap min with median again
            if (sortBy == 0 || sortBy == 2 ?
                stof(productData.ProductData(array.at(min)).at(sortBy)) <
                stof(productData.ProductData(array.at(median)).at(sortBy))
                                           :
                productData.ProductData(array.at(min)).at(sortBy) <
                productData.ProductData(array.at(median)).at(sortBy))
            {
                Swap(array, min, median);
            }
        }

        pivot = median;
    }

    void Partition(vector<string>& array, int sortBy, int begin, int end, bool ascending = true) {
        MedianOfThree(array, sortBy,begin, end, ascending);

        while (begin <= end)
        {
            if (ascending) {
                if (sortBy == 0 || sortBy == 2 ?
                    stof(productData.ProductData(array.at(begin)).at(sortBy)) <
                    stof(productData.ProductData(array.at(pivot)).at(sortBy)) :
                    productData.ProductData(array.at(begin)).at(sortBy) <
                    productData.ProductData(array.at(pivot)).at(sortBy)) {
                    begin++;
                } else if (sortBy == 0 || sortBy == 2 ?
                           stof(productData.ProductData(array.at(end)).at(sortBy)) >
                           stof(productData.ProductData(array.at(pivot)).at(sortBy)) :
                           productData.ProductData(array.at(end)).at(sortBy) >
                           productData.ProductData(array.at(pivot)).at(sortBy)) {
                    end--;
                } else {
                    Swap(array, begin, end);
                    begin++;
                    end--;
                }
            }
            else {
                if (sortBy == 0 || sortBy == 2 ?
                    stof(productData.ProductData(array.at(begin)).at(sortBy)) >
                    stof(productData.ProductData(array.at(pivot)).at(sortBy)) :
                    productData.ProductData(array.at(begin)).at(sortBy) >
                    productData.ProductData(array.at(pivot)).at(sortBy)) {
                    begin++;
                } else if (sortBy == 0 || sortBy == 2 ?
                           stof(productData.ProductData(array.at(end)).at(sortBy)) <
                           stof(productData.ProductData(array.at(pivot)).at(sortBy)) :
                           productData.ProductData(array.at(end)).at(sortBy) <
                           productData.ProductData(array.at(pivot)).at(sortBy)) {
                    end--;
                } else {
                    Swap(array, begin, end);
                    begin++;
                    end--;
                }

            }
        }

        pivot = begin;
    }

    void QuickSort(vector<string>& array, int sortBy, int start, int end, bool ascending = true) {
        if (start < end) {
            Partition(array, sortBy, start, end, ascending);

            QuickSort(array, sortBy, start, pivot - 1, ascending);
            QuickSort(array, sortBy, pivot, end, ascending);
        }
    }

public:
    QuickSorter() : productData(", ") {}
    void SortAscending(vector<string>& array, int sortBy) {
        QuickSort(array, sortBy, 0, array.size()-1, true);
    }

    void SortDescending(vector<string>& array, int sortBy) {
        QuickSort(array, sortBy, 0, array.size()-1, false);
    }
};



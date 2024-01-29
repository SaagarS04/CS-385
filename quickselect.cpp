/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Saagar Shah
 * Pledge        : I pledge my Honor that I have abided by the Stevens Honor System.
 * Date          : 11/10/23
 * Description   : Implements the quickselect algorithm.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    size_t pivotIndex = (left + right) / 2; //Chooses the middle element as the pivot
    swap(array[pivotIndex], array[right]); //Swaps the pivot with the rightmost element
    int pivot = array[right]; //Sets the pivot to the rightmost element
    size_t s = left; //Sets the index of the smaller element to the leftmost element
    for (size_t i = left; i < right; i++) { //Iterates through the array
        if (array[i] <= pivot) { //If the current element is less than or equal to the pivot
            swap(array[i], array[s]); //Swap the current element with the smaller element
            s++; //Increment the index of the smaller element
        }
    }
    swap(array[s], array[right]); //Swap the smaller element with the pivot
    return s; //Return the index of the pivot
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    size_t s = lomuto_partition(array, left, right); //Runs lomuto_partition
    if (s == k - 1) { //If the pivot is the kth smallest element
        return array[s]; //Return the pivot
    } else if (s > k - 1) { //If the pivot is greater than the kth smallest element
        return quick_select(array, left, s - 1, k); //Run quick_select with the left and right bounds of the pivot
    } else { //If the pivot is less than the kth smallest element
        return quick_select(array, s + 1, right, k); //Run quick_select with the left and right bounds of the pivot
    }
    return 0;
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k); //Runs quick_select with the left and right bounds
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    if (num_values < k){ //If there are less values than k
        if (num_values == 1){ //If there is only one value
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value." << endl;
            return 1;
        } //If there are multiple values
        cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " values." << endl;
        return 1;
    
    }

    int kthSmallest = quick_select(&values[0], values.size(), k); //Runs quick_select
    cout << "Smallest element " << k << ": " << kthSmallest << endl; //Prints the kth smallest element
    return 0;
}
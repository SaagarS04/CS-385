/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Saagar Shah
 * Version     : 1.0
 * Date        : 11/18/23
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0; // Counts the number of inversions
    for (int i = 0; i < length; i++) { // Goes through each element in the array
        for (int j = i + 1; j < length; j++) { // Goes through each element after the current element
            if (array[i] > array[j]) {// If the current element is greater than the element after it, then it is an inversion
                count++; // Increments the count
            }
        }
    }
    return count; // Returns the number of inversions
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length]; // Creates a new array to store the sorted array
    long count = mergesort(array, scratch, 0, length - 1); // Calls mergesort to sort the array and count the number of inversions
    delete [] scratch; // Deletes the scratch array
    return count; // Returns the number of inversions
    // TODO
    // Hint: Use mergesort!
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0; // Counts the number of inversions
    if (low < high) { // If the low index is less than the high index, then there are still elements to sort
        int mid = low + (high - low) / 2; // Calculates the middle index
        count += mergesort(array, scratch, low, mid); // Recursively calls mergesort on the left half of the array
        count += mergesort(array, scratch, mid + 1, high); // Recursively calls mergesort on the right half of the array
        int L = low; // Left index
        int H = mid + 1; // Right index
        for (int k = low; k <= high; k++) { // Goes through each element in the array
            if (L <= mid && (H > high || array[L] <= array[H])) { // If the left index is less than the middle index and the right index is greater than the high index or the element at the left index is less than the element at the right index, then the element at the left index is less than the element at the right index
                scratch[k] = array[L]; // Sets the element at the left index to the kth element in the scratch array
                L++; // Increments the left index
            } else { // Otherwise, the element at the right index is less than the element at the left index
                scratch[k] = array[H]; // Sets the element at the right index to the kth element in the scratch array
                H++; // Increments the right index
                count += mid - L + 1; // Increments the count by the number of elements in the left half of the array
            }
        }
        for (int k = low; k <= high; k++) { // Goes through each element in the array
            array[k] = scratch[k]; // Sets the kth element in the array to the kth element in the scratch array
        }
    }
    return count; // Returns the number of inversions
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc == 2) { // If there is one command-line argument
        if (argv[1] != string("slow")){ // If the command-line argument is not "slow"
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl; // Prints an error message
            return 1; // Returns 1
        }
    }
    else if (argc > 2){ // If there is more than one command-line argument
        cerr << "Usage: ./inversioncounter [slow]" << endl; // Prints an error message
        return 1; // Returns 1
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush; // Prompts the user to enter a sequence of integers

    istringstream iss; // Creates an istringstream object
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
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
    if (values.empty()) { // If the vector is empty
        cerr << "Error: Sequence of integers not received." << endl; // Prints an error message
        return 1; // Returns 1
    }
    if (argc == 1) { // If there are no command-line arguments
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()); // Calls count_inversions_fast
        return 0; // Returns 0
    } else {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()); // Calls count_inversions_slow
        return 0; // Returns 0
    }

    return 0; // Returns 0
}

/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Saagar Shah
 * Date        : 10/15/23
 * Description : Lists the number of ways to climb n stairs.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<int> get_primes(int limit) {
    vector<bool> is_prime(limit + 1, true); // initialize all numbers as prime
    vector<int> primes; // vector to store the prime numbers

    // iterate over the numbers up to the limit
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i); // add the current number to the list of primes
            // mark all multiples of the current number as not prime
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return primes;
}

void find_ways(int num_stairs, vector<int> primes, vector<int> current, vector<vector<int>>& ways) {
    if (num_stairs == 0) { //Base Case
        ways.push_back(current);
        return;
    }
    
    for (int i = 0; i < int(primes.size()); i++) { //Iterating through all primes
        if (primes[i] <= num_stairs) { //If the prime is less than the number of stairs
            current.push_back(primes[i]); //Add the prime to the current vector
            find_ways(num_stairs - primes[i], primes, current, ways); //Recursively call the function with the new number of stairs
            current.pop_back(); //Remove the prime from the current vector
        }
    }
}

vector<vector<int>> get_ways(int num_stairs) { //Returns the number of ways to climb the stairs
    vector<int> primes = get_primes(num_stairs);
    vector<vector<int>> ways;
    vector<int> current;

    find_ways(num_stairs, primes, current, ways); //Calls the recursive function
    
    return ways;
}

int numDigits(int n){
    int count = 0;
    while (n > 0){
        count ++;
        n/= 10;
    }
    return count;
}

void display_ways(const vector< vector<int> > &ways) {
    int num_digits = numDigits(ways.size()); // get the number of digits in the largest index
    for (int i = 0; i < int(ways.size()); i++) {
        cout << setw(num_digits) << i + 1 << ". "; // print the index right-aligned
        for (int j = 0; j < int(ways[i].size()); j++) {
            if (j == 0) { // if first element
                cout << "["; // print opening bracket for the first element
            }
            cout << ways[i][j]; // access the jth element of the ith way
            if (j != int(ways[i].size()) - 1) { // if not the last element
                cout << ", "; // print space between elements
            } else {
                cout << "]"; // print closing bracket for the last element
            }
        }
        cout << endl; // print newline
    }
}



int main(int argc, char * const argv[]) {
    int numStairs;
    istringstream iss;
    if (argc != 2){ //Makes sure the correct number of arguments are given
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]); //Saves the first input argument
    if (!(iss >> numStairs) || numStairs <= 0){ //Checks if it is a positive number
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1; 
    }
    vector<vector<int>> ways = get_ways(numStairs);
    if (ways.size() == 1 && numStairs == 1){ //If there is only one way to climb one stair
        cout << "1 way to climb " << numStairs << " stair." << endl;
    }
    else if (ways.size() == 1 && numStairs == 2){ //If there is only one way to climb two stairs
        cout << "1 way to climb " << numStairs << " stairs." << endl;
    }
    else{ //If there are multiple ways to climb the stairs
        cout << ways.size() << " ways to climb " << numStairs << " stairs." << endl;
    }
    display_ways(ways); //Display the ways to climb the stairs
    return 0;
}

/*******************************************************************************
 * Filename: gcd.cpp
 * Author  : Saagar Shah
 * Version : 1.0
 * Date    : Sept 8, 2023
 * Description: Finds the greatest common divisor of two numbers, both iterativeley and recursiveley.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int gcd_iterative(int m, int n) //Iterativeley finds gcd
{
	while (n != 0){ //Based on euclid's algorithm, when n is not 0, continue the process
		int r = m % n; //Finds the remainder and stores it
		m = n; //Replaces the value of m with the value of n
		n = r; //Replaces the value of n with the remainer
	}
	return m; //Returns the value of m, will only reach here when n is 0 so the gcf is found
}

int gcd_recursive(int m, int n) //Recursively finds gcd
{
	if (n == 0){ //Base case for when n is 0
		return m; //Returns m when reaching the base case
	}
	int r = m % n; //Finds and stores the remainder
	m = n; //Replaces the value of m with the value of n
	n = r; //Replaces the value of n with the remainer
	return gcd_recursive(m, n); //Recursively calls the function with new values of m and n
}

int main(int argc, char* argv[]) {
	int m, n; //Values to store input
	istringstream iss; // input string stream variable

	if(argc != 3) { //Makes sure 3 arguments are given
		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl; //Throws error
		return 1;
	}
	iss.str(argv[1]); //Saves the first input argument
	if(!(iss >> m)) { //Checks if it is a number
		cerr << "Error: The first argument is not a valid integer." << endl; //Throws error
		return 1;
	}

	iss.clear(); //Clears input string stream to take another input
	iss.str(argv[2]); //Saves the second input argument
	if(!(iss >> n)) { //Checks if it is a number
		cerr << "Error: The second argument is not a valid integer." << endl; //Throws error
		return 1;
	}
	cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(abs(m), abs(n)) << endl; //Outputs the iterative result
	cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(abs(m), abs(n)) << endl; //OUtputs the recursive result
	return 0;
}
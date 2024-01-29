#include <iostream>
#include <sstream>

using namespace std;

int fact_iterative(int n){ //via iteration
    int result = 1;
    for(int i = n; i > 1; i --){
        result = result * i; //total = last prev. total * the current n
    }
    return result;
}

int fact_recursive(int n){ //via recursion
    if (n <= 1){ //base case: n = 1 (n will eventually hit 1)
        return 1;
    }
    return n * fact_recursive(n - 1);
}

int main(int argc, char* argv[]){
    int n; //holds a number
    istringstream iss; //input string stream variable

    //checks # of arguments
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <integer n>" << endl;
        return 1; //Return 1 instead of 0 for an error
    }

    iss.str(argv[1]); //reads input only
    if(!(iss >> n)){ //checks to see if input can write to int n
        cerr << "Error: The first argument is not a valid integer." << endl;
        return 1;
    }

    //at this point, n = ___
    iss.clear(); //if we were to read more things using iss

    //printing & calculating stuff
    cout << "n is: " << n << endl;
    cout << "Iterative: fact(" << n << ") = " << fact_iterative(abs(n)) << endl;
    cout << "Recursive: fact(" << n << ") = " << fact_recursive(abs(n)) << endl;

    return 0;
}
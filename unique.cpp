/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Saagar Shah
 * Date        : 9/26/23
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>


using namespace std;

bool is_all_lowercase(const string &s) { //Checks if all letters are lowercase
    for (int i = 0; i < int(s.length()); i ++){ //Loops through each letter
        if (s[i] - 'a' < 0 || s[i] - 'a' > 26){ //Checks if it is a valid lowercase letter
            return false; //Returns false if it is not a lowercase letter
        }
    }
    return true; //Returns true if all are lowercase letters
}

bool all_unique_letters(const string &s) {
    unsigned int vector = 0; //Initializes an unsigned int to be used to store values
    unsigned int setter; //Initializes an unsigned int to be used for each letter
    for (int i = 0; i < int(s.length()); i ++){ //Goes through each value of the string
        setter = 1 <<(s[i] - 'a'); //Sets the setter to have a 1 in the position of the distance between the letter and the beginning
        if ((vector & setter) != 0){ //Checks if vector has a 1 in the same value
            return false; //Returns false, because if it does the letter has already been seen
        }
        else{
            vector = vector | setter; //Adds a 1 to the vector at the same position
        }
        setter = 0; //Resets the setter
    }
    return true; //If none of the letters apear twice, returns true
}

int main(int argc, char * const argv[]) {
    istringstream iss; //Input string
    if (argc != 2){ //If there aren't two inputs, returns an error
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }
    const string s = argv[1]; //Stores the input string
    if (is_all_lowercase(s) == false){ //Returns an error if they are not all lowercase
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    if (all_unique_letters(s) == true){ //Checks if they are all unique and returns an output based on the result
        cout << "All letters are unique." << endl;
    }
    else{
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}

/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Saagar Shah
 * Date        : 10/3/23
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my Honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct PrimesEratosthenesSieve {
private:

    // Method declarations
    int count_num_primes() const;
    void run_sieve();
    static int max_prime_width(int num);
    bool checkBadDigit(int num, int bad_digit);

    // Instance variables
    vector<bool*> * is_prime_;
    const int lower_limit_, upper_limit_, bad_digit_;
    int num_primes_, max_prime_;
public:
    PrimesEratosthenesSieve(int lower_limit, int upper_limit, int bad_digit);

    ~PrimesEratosthenesSieve() {
        for (int i = 0; i < int(is_prime_->size()); i++) { //Deletes the values in the vector
            delete (*is_prime_)[i];
        }
        delete is_prime_; //Deletes the vector
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;
};

PrimesEratosthenesSieve::PrimesEratosthenesSieve(int lower_limit, int upper_limit, int bad_digit) :
          is_prime_{nullptr}, lower_limit_{lower_limit}, 
          upper_limit_{upper_limit}, bad_digit_{bad_digit} {

    is_prime_ = new vector<bool*>(upper_limit_ + 1); //Allocates memory for enough numbers
    for (int i = 0; i < int(is_prime_->size()); i++) { //Goes through each number
        (*is_prime_)[i] = new bool(true); //Initializes the value to true
    }
    
    // run the sieve
    run_sieve();
}

void PrimesEratosthenesSieve::display_primes() const {
    cout << "Number of good primes found: " << count_num_primes() << endl; //Outputs number of good primes
    cout << "Good primes between " << lower_limit_ << " and " << upper_limit_ << ":" << endl; //Outputs the range of primes
    int w = max_prime_width(max_prime_); //Stores the max width of the prime numbers
    int primesPerRow = 80/(w+1); //Stores the number of primes per row
    int count = 0; //Temp var for count to be used when printing
    int outputMax = 0; //Stores the max prime number that will be outputted
    for (int i = 0; i < int(is_prime_->size()); i++) { //Saves the output max
        if (*(*is_prime_)[i]) {
            int num = i;
            bool isBad = false;
            while (num > 0) {
                if (num % 10 == bad_digit_) {
                    isBad = true;
                    break;
                }
                num /= 10;
            }
            if(!isBad){
                outputMax = i; //Saves the output max
            }
        }
    }
    for (int i = lower_limit_; i < int(is_prime_->size()); i ++){ //Goes through the values
        if(*(*is_prime_).at(i)){ //If it is prime
            cout << setw(w) << i; //outputs
            count ++; //Adds one to count
            if (count != primesPerRow && i != outputMax){ //Adds a space if it is not the last number of the row or last number to be outputed
            cout << " ";
            }
        }
        if (count == primesPerRow){ //Goes to the next line and resets count
            cout << endl;
            count = 0;
        }
    }
}

int PrimesEratosthenesSieve::count_num_primes() const {
    int count = 0;
    for (int i = lower_limit_; i < int(is_prime_->size()); i++) { //Goes through every number
        if (*(*is_prime_).at(i)) {
            count++; //Adds to count
        }
    }
    return count;
}

void PrimesEratosthenesSieve::run_sieve() {
    // Loop through the vector and mark all multiples of prime numbers as false
    for (int i = 2; i <= sqrt(upper_limit_); i ++){ //Runs the sieve
        if(*(*is_prime_).at(i)){
            for (int j = i * i; j <= upper_limit_; j += i) {
                *((*is_prime_).at(j)) = false;
            }
        }
    }
    for (int i = 0; i < int(is_prime_->size()); i++) { //Stores the max prime number
        if (*(*is_prime_)[i]) {
            max_prime_ = i;
        }
    }
    for (int i = 0; i < int(is_prime_->size()); i ++){ //Checks bad digits of each of the primes and sets them to false, also sets the 0 and 1 to false
        if(i == 0 || i == 1){
            *((*is_prime_).at(i)) = false;
        }
        if(checkBadDigit(i, bad_digit_)){
            *((*is_prime_).at(i)) = false;
        }
    }
}

bool PrimesEratosthenesSieve::checkBadDigit(int num, int bad_digit) { //Checks if there is a bad digit
    if(bad_digit == num){
        return true;
    }
    while (num > 0) {
        if (num % 10 == bad_digit) { //Goes through the digits
            return true; //Returns if bad digit is found
        }
        num /= 10;
    }
    return false;
}

int PrimesEratosthenesSieve::max_prime_width(int num) {
    // Find the largest prime number
    int numDigits = 0; //Stores the number of digits
    while(num > 0){
        numDigits ++; //Adds one to the number of digits
        num = num / 10; //Divides by 10 to get the next digit
    }
    return numDigits; //Returns the number of digits
}

int main() {
    cout << "*********************** " <<  "Sieve of Eratosthenes (MODIFIED)" <<
            " ***********************" << endl;
    cout << "Search for good primes between: ";
    string lower_limit_str;
    cin >> lower_limit_str;
    int lower_limit;
    
    string upper_limit_str;
    cin >> upper_limit_str;
    int upper_limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(lower_limit_str);

    // Check for error.
    if ( !(iss >> lower_limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (lower_limit < 0) {
        cerr << "Error: Input must be an integer >= 0." << endl;
        return 1;
    }

    iss.clear();
    iss.str(upper_limit_str);

    // Check for error.
    if ( !(iss >> upper_limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (upper_limit < lower_limit) {
        cerr << "Error: Input must be an integer >= lower limit." << endl;
        return 1;
    }

    string bad_digit_str;
    cin >> bad_digit_str;
    int bad_digit;

    iss.clear();
    iss.str(bad_digit_str);

    // Check for error
    if ( !(iss >> bad_digit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (bad_digit < 0 || bad_digit > 9) {
        cerr << "Error: Input must be a digit." << endl;
        return 1;
    }
    cout << endl << "Bad digit: " << bad_digit << endl;

    // TODO: write code that uses your class to produce the desired output.
    PrimesEratosthenesSieve sieve(lower_limit, upper_limit, bad_digit); //Creates the sieve
    sieve.display_primes(); //Displays the primes
    return 0;
}
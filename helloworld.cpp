/*******************************************************************************
 * Filename: helloworld.cpp
 * Author  : Saagar Shah
 * Version : 1.0
 * Date    : Sept 7, 2023
 * Description: Prints "Hello World!".
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
	unsigned int a = 11;
	unsigned int b = (11 << 3 | 14);
	cout << b << endl;
	cout << (b  >> (a & 23)) << endl;
	return 0;
}

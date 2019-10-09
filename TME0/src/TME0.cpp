//============================================================================
// Name        : TME0.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int tab[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i = 0; i < 10; ++i) {
		cout << tab[i] << endl;
	}
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	for (size_t i=9; i > 0 ; i--) {
		if (tab[i] - tab[i - 1] != 1) {
			cout << "problem !";
		}
	}

	return 0;
}

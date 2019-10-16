//============================================================================
// Name        : TME4.cpp
// Author      : Nicolas le bg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <thread>
#include "banque.h"

using namespace std;

const size_t NB_THREAD = 10;
const size_t NB_COMPTE = 5;

void work(pr::Banque &banque) {
	size_t i = rand() % NB_COMPTE;
	size_t j = rand() % NB_COMPTE;
	int montant = rand() % 100 + 1;
	cout << i << " --" << montant << "-> " << j << endl;
	banque.transfert(i, j, montant);
	std::chrono::duration<double, std::milli> stime(rand() % 20);
	this_thread::sleep_for(stime);
}

int main() {
	pr::Banque banque(NB_COMPTE, 100);
	vector<thread> threads;
	threads.reserve(NB_THREAD);
	for (size_t i = 0; i < NB_THREAD; i++) {
		threads.emplace_back(work, ref(banque));
	}
	for (thread &t : threads) {
//		cout << "thread " << t.get_id() << " joined!" << endl;
		t.join();
	}
	return 0;
}
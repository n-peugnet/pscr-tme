//============================================================================
// Name        : TME4.cpp
// Author      : Nicolas le bg
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include "banque.h"

using namespace std;

const size_t NB_THREAD = 100;
const size_t NB_COMPTE = 5;
const int SOLDE_DEPART = 100;
const int ATTENDU = NB_COMPTE * SOLDE_DEPART;

atomic<bool> run(true);

void work(pr::Banque &banque) {
	size_t i = rand() % NB_COMPTE;
	size_t j = rand() % NB_COMPTE;
	int montant = rand() % 100 + 1;
	string success = banque.transfert(i, j, montant) ? "success" : "fail";
//	cout << i << " -" << montant << "-> " << j << endl;
	cout << success << endl;
	std::chrono::duration<double, std::milli> stime(rand() % 20);
	this_thread::sleep_for(stime);
}

void comptabiliser(pr::Banque &banque) {
	while(run) {
		if (!banque.comptabiliser(ATTENDU)) {

		}
	}
}

int main() {
	pr::Banque banque(NB_COMPTE, SOLDE_DEPART);
	thread th_comptable(comptabiliser, ref(banque));
	vector<thread> threads;
	threads.reserve(NB_THREAD);
	for (size_t i = 0; i < NB_THREAD; i++) {
		threads.emplace_back(work, ref(banque));
	}
	for (thread &t : threads) {
//		cout << "thread " << t.get_id() << " joined!" << endl;
		t.join();
	}
	run = false;
	th_comptable.join();
	return 0;
}

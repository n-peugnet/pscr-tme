/*
 * Compte.cpp
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#include <mutex>
#include "compte.h"

using namespace std;

namespace pr {

Compte::Compte(int solde) :
		solde(solde) {
}
Compte::Compte(const Compte &other) {
	other.m.lock();
	solde = other.solde;
	other.m.unlock();
}
void Compte::crediter(unsigned int val) {
	unique_lock<recursive_mutex> g(m);
	solde += val;
}
bool Compte::debiter(unsigned int val) {
	unique_lock<recursive_mutex> g(m);
	bool doit = solde >= (int) val;
	if (doit) {
		solde -= val;
	}
	return doit;
}
int Compte::getSolde() const {
	unique_lock<recursive_mutex> g(m);
	return solde;
}


//	Interface Lockable
void Compte::lock() const {
	m.lock();
}
void Compte::unlock() const {
	m.unlock();
}
bool Compte::try_lock() const {
	return m.try_lock();
}


} /* namespace pr */

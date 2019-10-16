/*
 * banque.cpp
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#include "banque.h"
#include <mutex>

namespace pr {

Banque::Banque(size_t ncomptes, size_t solde) :
		comptes(ncomptes, Compte(solde)) {
}
bool Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	bool success = false;
	Compte &debiteur = comptes[deb];
	Compte &crediteur = comptes[cred];
//	pr::ul ld(debiteur);
//	lock(, ul lc(crediteur));
	debiteur.lock();
	crediteur.lock();
	if (debiteur.debiter(val)) {
		if (crediteur.try_lock()) {
			crediteur.crediter(val);
			success = true;
			crediteur.unlock();
		}
	}
	debiteur.unlock();
	return success;
}
size_t Banque::size() const {
	return comptes.size();
}

}  // namespace pr


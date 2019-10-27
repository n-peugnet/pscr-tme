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
	Compte &debiteur = comptes[deb];
	Compte &crediteur = comptes[cred];
	ulrm lock_debiteur(debiteur.getMutex(), std::defer_lock);
	ulrm lock_crediteur(crediteur.getMutex(), std::defer_lock);
	std::lock(lock_debiteur, lock_crediteur);
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
		return true;
	}
	return false;
}
size_t Banque::size() const {
	return comptes.size();
}

}  // namespace pr


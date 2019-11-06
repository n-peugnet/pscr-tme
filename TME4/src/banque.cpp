/*
 * banque.cpp
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#include "banque.h"
#include <mutex>
#include <iostream>

using namespace std;

namespace pr {

Banque::Banque(size_t ncomptes, size_t solde) :
		comptes(ncomptes, Compte(solde)) {
}
bool Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte &debiteur = comptes[deb];
	Compte &crediteur = comptes[cred];
	ulrm lock_debiteur(debiteur.getMutex(), defer_lock);
	ulrm lock_crediteur(crediteur.getMutex(), defer_lock);
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

bool Banque::comptabiliser(int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const Compte &compte : comptes) {
		compte.lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde()
					<< endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	for (const Compte &compte : comptes) {
		compte.unlock();
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : "
				<< bilan << endl;
	}
	return bilan == attendu;
}

}  // namespace pr


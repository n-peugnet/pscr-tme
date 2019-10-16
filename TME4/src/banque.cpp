/*
 * banque.cpp
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#include "banque.h"

namespace pr {

Banque::Banque(size_t ncomptes, size_t solde) :
		comptes(ncomptes, Compte(solde)) {
}
void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte &debiteur = comptes[deb];
	Compte &crediteur = comptes[cred];
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
}
size_t Banque::size() const {
	return comptes.size();
}

}  // namespace pr


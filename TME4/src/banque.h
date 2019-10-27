/*
 * Banque.h
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#pragma once

#include <vector>
#include <mutex>
#include "compte.h"

namespace pr {

typedef std::unique_lock<std::recursive_mutex> ulrm;

class Banque {
	typedef std::vector<Compte> comptes_t;
	comptes_t comptes;
public:
	Banque(size_t ncomptes, size_t solde);
	bool transfert(size_t deb, size_t cred, unsigned int val);
	size_t size() const;
};

} /* namespace pr */

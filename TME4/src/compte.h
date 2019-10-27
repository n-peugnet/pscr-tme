/*
 * Compte.h
 *
 *  Created on: 16 oct. 2019
 *      Author: 3872867
 */

#pragma once
#include <mutex>

namespace pr {

class Compte {
	mutable std::recursive_mutex m;
	int solde;

public:
	Compte(int solde = 0);
	Compte(const Compte &other);
	void crediter(unsigned int val);
	bool debiter(unsigned int val);
	int getSolde() const;

	std::recursive_mutex & getMutex() const;

//	Interface Lockable
	void lock() const;
	void unlock() const;
	bool try_lock() const;
};

} /* namespace pr */

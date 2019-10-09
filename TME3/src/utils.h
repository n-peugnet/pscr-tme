/*
 * utils.h
 *
 *  Created on: 9 oct. 2019
 *      Author: 3872867
 */

#pragma once
#include <cstddef>

template<typename iterator>
size_t count(iterator begin, iterator end) {
	size_t i = 0;
	while(begin != end) {
		++begin;
		++i;
	}
	return i;
}

template<typename iterator, typename T>
size_t count_if_equal (iterator begin, iterator end, const T & val) {
	size_t i = 0;
	while(begin != end) {
		if (*begin == val) {
			break;
		}
		++begin;
		++i;
	}
	return i;

}


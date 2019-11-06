#pragma once
#include <cstddef>
#include <forward_list>
#include <vector>

namespace pr {

template<typename K, typename V>

class HashMap {
public:

	class Entry {
	public:
		const K key;
		V value;
		Entry(const K &key, const V &value) :
				key(key), value(value) {
		}
	};

private:
	typedef std::vector<std::forward_list<Entry>> buckets_t;
	typedef typename std::vector<std::forward_list<Entry>>::iterator v_it;
	typedef typename std::forward_list<Entry>::iterator l_it;
	buckets_t buckets;
	size_t s;

public:
	class iterator {
		buckets_t &buckets;
		v_it vit;
		l_it lit;

		void getnext() {
			while (lit == vit->end() && vit != buckets.end()) {
				++vit;
				lit = vit->begin();
			}
		}
	public:
		iterator(buckets_t &b, v_it v, l_it l) :
				buckets(b), vit(v), lit(l) {
			getnext();
		}
		iterator& operator++() {
			++lit;
			getnext();
			return *this;
		}

		bool operator!=(const iterator &other) {
			return vit != other.vit || lit != other.lit;
		}

		Entry& operator*() {
			return *lit;
		}

	};

	HashMap(size_t size) :
			buckets(size), s(0) {
		for (size_t i = 0; i < size; ++i) {
			buckets.push_back(std::forward_list<Entry>());
		}
	}

	V* get(const K &key) {
		size_t h = std::hash<K>()(key);
		size_t target = h % buckets.size();
		for (Entry &entry : buckets[target]) {
			if (entry.key == key) {
				return &entry.value;
			}
		}
		return nullptr;
	}

	bool put(const K &key, const V &value) {
		size_t h = std::hash<K>()(key);
		size_t target = h % buckets.size();
		for (Entry &entry : buckets[target]) {
			if (entry.key == key) {
				entry.value = value;
				return true;
			}
		}
		s++;
		buckets[target].emplace_front(key, value);
		return false;
	}

	size_t size() const {
		return s;
	}

	void grow() {
		HashMap other(buckets.size() * 2);
		for (auto &list : buckets) {
			for (Entry &entry : list) {
				other.put(entry.key, entry.value);
			}
		}
		buckets = other.buckets;
	}
	iterator begin() {
		return iterator(buckets, buckets.begin(), buckets.begin()->begin());
	}
	iterator end() {
		return iterator(buckets, buckets.end(), buckets.end()->end());
	}
};

} /* namespace pr */

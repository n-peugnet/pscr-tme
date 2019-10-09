#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include "utils.h"
#include "hashmap.h"

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("/tmp/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");

	// un vector pour stocker nos valeurs
	vector<pair<string,int>> vecteur;
	vecteur.reserve(6000000);

	pr::HashMap<string,int> hashmap(2<<17);

	// compteur de mots différents
	size_t wc = 0;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

//		bool found = false;
//		for(pair<string,int> &entry: vecteur)
//		{
//			if (entry.first == word)
//			{
//				found = true;
//				entry.second++;
//				break;
//			}
//		}
//		if (!found)
//		{
//			vecteur.push_back(pair<string,int>(word, 1));
//		}

		int * nb = hashmap.get(word);
		int new_nb = nb == nullptr ? 1 : *nb + 1;
		hashmap.put(word, new_nb);

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
    cout << "Vector size: " << hashmap.size()<< endl;
    cout << "Vector size: " << count(vecteur.begin(), vecteur.end()) << endl;
    cout << "Mots différent: " << wc << endl;
    cout << "Nb a: " << *hashmap.get("war") << endl;

    return 0;
}



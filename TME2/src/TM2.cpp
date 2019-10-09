#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>

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

	// compteur de mots différents
	size_t wc = 0;

	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		bool found = false;
		for(pair<string,int> &entry: vecteur)
		{
			if (entry.first == word)
			{
				found = true;
				entry.second++;
				break;
			}
		}
		if (!found)
		{
			vecteur.push_back(pair<string,int>(word, 1));
		}


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
    cout << "Vector size: " << vecteur.size() << "." << endl;
    cout << "Mots différent: " << wc << "." << endl;
    for (auto &entry: vecteur)
    {
    	if (entry.first == "war" || entry.first == "peace" || entry.first == "toto")
    		cout << entry.first << ", nb: " << entry.second << "." << endl;
    }

    return 0;
}



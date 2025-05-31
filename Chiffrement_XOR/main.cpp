/*
Chiffrement XOR

Par Adrien Gagnon, Hermann Ngandeu Ngotcho, Maxime Jeanson et Churchill Kouesso Fofou

*/

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

// Fonction qui retourne la lettre codée ascii associée à la lettre en entrée
char getCode(char lettre, char clef) {
	return lettre ^ clef;
}

// Fonction qui vérifie si la notation circonflexe est nécessaire pour l'affichage
void ajouterChar(char code, std::string& txtChiffre) {
	if (code < 32) {
		txtChiffre += '^';
		txtChiffre += static_cast<char>(code + 64);;
	}
	else {
		if (code == 127) {
			txtChiffre += "^?";
		}
		else {
			txtChiffre += code;
		}
	}
}

int main(){
	std::ifstream fmessage("message.txt");
	std::ifstream fclef("clef.txt");
	std::ofstream fchiffre("chiffre.txt");

	if (!fmessage.is_open() || !fclef.is_open() || !fchiffre.is_open()) {
		std::cerr << "Erreur en ouvrant les fichiers";
		return 1;
	}

	std::string clef;
	std::string clefComplete;

	// On itère sur les lignes du fichier clef (au cas où elle serait longue)
	while (std::getline(fclef, clef)) {
		clefComplete.append(clef);
	}

	std::string str;
	std::string txtChiffre;
	size_t positionClef = 0;
	bool premiereLigne = true;

	// On itère sur les lignes du fichier message
	while (std::getline(fmessage, str)){

		// On ajoute des sauts de ligne pour chaque nouvelle ligne apres la première
		if (premiereLigne) {
			premiereLigne = false;
		}
		else {
			fchiffre << '\n';
		}

		// On encode un caractère à la fois
		for (size_t i = 0; i < str.size(); i++){
			char c = getCode(str[i], clefComplete[positionClef]);
			ajouterChar(c, txtChiffre);
			positionClef = (1 + positionClef) % clefComplete.length();
		}

		// On ajoute la ligne encodée au fichier chiffre.txt
		fchiffre << txtChiffre;
	}

	fmessage.close();
	fclef.close();
	fchiffre.close();

	return 0;
}
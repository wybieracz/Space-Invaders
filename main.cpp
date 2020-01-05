#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include "funkcje.h"

using namespace std;

int main(int argc, char* argv[]) {

	string nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, miastoStartowe;
	int good = sprawdzArgumenty(argc, argv, nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, miastoStartowe);

	if (not good) {
		cout << "Podano bledne parametry!" << endl;
		pomoc();
	}

	else {

		ifstream plik;
		vector<string> vektorNazwMiast;
		vektorNazwMiast.push_back(miastoStartowe);

		plik.open("C:/Users/wybieracz/Documents/POLSL/PPK/20_Spedycja/20_Spedycja/" + nazwaPlikuWejsciowego);
		if (plik.fail()) {
			std::cout << "Input file error!" << endl;
		}

		string miasto1, miasto2;
		int odleglosc, iloscDrog = 0;

		while (true)
		{
			plik >> miasto1 >> miasto2 >> odleglosc;

			if (not plik.fail()) {

				if (not znajdzDuplikat(vektorNazwMiast, miasto1)) vektorNazwMiast.push_back(miasto1);
				if (not znajdzDuplikat(vektorNazwMiast, miasto2)) vektorNazwMiast.push_back(miasto2);

				iloscDrog++;
			}
			else break;

		}
		plik.close();


		int iloscMiast = vektorNazwMiast.size();
		sasiad** graf = new sasiad * [iloscMiast];
		sasiad* pw = nullptr, * rw = nullptr;
		miasto* miastoGlowa = nullptr;

		wczytajGraf("C:/Users/wybieracz/Documents/POLSL/PPK/20_Spedycja/20_Spedycja/" + nazwaPlikuWejsciowego, graf, iloscMiast, vektorNazwMiast);
		cout << endl;

		cout << "--------------" << endl;
		cout << "Ilosc wierzczolkow: " << iloscMiast << endl;
		cout << "Ilosc polaczen: " << iloscDrog << endl;
		cout << "--------------" << endl;
		for (int i = 0; i < iloscMiast; i++) {
			std::cout << i << " " << vektorNazwMiast[i] << endl;
		}

		for (int i = 0; i < iloscMiast; i++)
		{
			cout << "[ " << vektorNazwMiast[i] << " ] =";
			pw = graf[i];
			while (pw)
			{
				cout << vektorNazwMiast[pw->numerSasiada];
				pw = pw->next;
			}
			cout << endl;
		}

		stworzListeMiast(miastoGlowa, iloscMiast);

		wypiszMiasto(miastoGlowa);

		cout << "=====================================" << endl;

		dijkstra(miastoGlowa, graf);
	
		wypiszMiasto(miastoGlowa);

		// Usuwamy tablice dynamiczne

		for (int i = 0; i < iloscMiast; i++)
		{
			pw = graf[i];
			while (pw)
			{
				rw = pw;
				pw = pw->next;
				delete rw;
			}
		}

		delete[] graf;
	}

	return 0;
}

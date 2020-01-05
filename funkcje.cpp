#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include "funkcje.h"
using namespace std;

int sprawdzArgumenty(int argc, char* argv[], string& nazwaPlikuWejsciowego, string& nazwaPlikuWyjsciowego, string& miastoStartowe) {
	int ok = 0;
	if (argc <= 7) {
		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-i"))
			{
				nazwaPlikuWejsciowego = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-o"))
			{
				nazwaPlikuWyjsciowego = string(argv[i + 1]);
				ok++;
			}
			if (string(argv[i]) == string("-s"))
			{
				miastoStartowe = string(argv[i + 1]);
				ok++;
			}
		}
		if (ok == 3)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void pomoc() {
	cout << "Uwaga! Program nalezy uruchamiac z 3 parametrami:" << endl;
	cout << "-i nazwa pliku wejsciowego z danymi" << endl;
	cout << "-o nazwa pliku wyjsciowego" << endl;
	cout << "-s nazwa miasta startowego, centrali" << endl;
}

void wczytajGraf(string nazwaPliku, sasiad**& graf, int rozmiar, vector<string> wektorNazwMiast) {

	sasiad* nowySasiad;
	int numerMiasta1, numerMiasta2, odleglosc;
	string miasto1, miasto2;

	ifstream plik;
	plik.open(nazwaPliku, ios::in);
	if (plik.fail()) cout << "Input file error1!" << endl; //sprawdzenie poprawnosci wczytania pliku + komunikat

	for (int i = 0; i < rozmiar; i++) {
		graf[i] = nullptr;
	}

	while (true) //pêtla nieskoñczona
	{
		plik >> miasto1 >> miasto2 >> odleglosc;	// Odczytujemy krawêdŸ z wag¹

		numerMiasta1 = znajdzNumer(wektorNazwMiast, miasto1);
		numerMiasta2 = znajdzNumer(wektorNazwMiast, miasto2);

		if (not plik.fail()) {

			nowySasiad = new sasiad;             // Tworzymy element listy s¹siedztwa
			nowySasiad->numerSasiada = numerMiasta2;                    // Wierzcho³ek docelowy krawêdzi
			nowySasiad->koszt = odleglosc;                    // Waga krawêdzi
			nowySasiad->next = graf[numerMiasta1];
			graf[numerMiasta1] = nowySasiad;                 // Element do³¹czamy do listy
			
			nowySasiad = new sasiad;
			nowySasiad->numerSasiada = numerMiasta1;
			nowySasiad->koszt = odleglosc;
			nowySasiad->next = graf[numerMiasta2];
			graf[numerMiasta2] = nowySasiad;
		}

		else break;

	}
	plik.close();
}

bool znajdzDuplikat(vector<string> wektorNazwMiast, string szukana) {

	int rozmiar = wektorNazwMiast.size();

	for (int i = 0; i < rozmiar; i++) {
		if (szukana == wektorNazwMiast[i])
			return true;
	}
	return false;
}

int znajdzNumer(vector<string> wektorNazwMiast, string szukana) {

	int rozmiar = wektorNazwMiast.size();

	for (int i = 0; i < rozmiar; i++) {
		if (szukana == wektorNazwMiast[i])
			return i;
	}
	return -1;
}

void stworzListeMiast(miasto*& miastoGlowa, int iloscMiast) {

	const int niesk = 2147483647;
	miasto* noweMiasto = nullptr;

	for (int i = iloscMiast-1; i >= 0; i--) {

		noweMiasto = new miasto{ miastoGlowa, i, niesk, -1};
		miastoGlowa = noweMiasto;
	}

	miastoGlowa->koszt = 0;
}

void wypiszMiasto(miasto* miastoGlowa) {

	if (miastoGlowa) {
		cout << miastoGlowa->numerMiasta << ". " << "Koszt: " << miastoGlowa->koszt << " Poprzednik: " << miastoGlowa->poprzednik << endl;
		wypiszMiasto(miastoGlowa->next);
	}
}

void sortuj(miasto*& pierwszeQ, miasto* &miastoSortuj, miasto*& prev) {

	miasto* miastoGlowa = pierwszeQ;

	while (miastoGlowa) {

		if (miastoGlowa->next && miastoGlowa->next->koszt >= miastoSortuj->koszt) {

			if (miastoGlowa != miastoSortuj) break;

			prev->next = miastoSortuj->next;
			miastoSortuj->next = miastoGlowa->next;
			miastoGlowa->next = miastoSortuj;

			break;
		}

		miastoGlowa = miastoGlowa->next;
	}
}

void dijkstra(miasto*& miastoGlowa, sasiad** graf) {
	
	miasto* pierwszeQ = miastoGlowa;
	miasto* helpM = nullptr;
	miasto* prevM = nullptr;
	sasiad* helpS = nullptr;

	do {

		helpS = graf[pierwszeQ->numerMiasta];
		helpM = pierwszeQ;

		while (helpS) {

			while (helpM) {

				if (helpM->numerMiasta == helpS->numerSasiada) {
					break;
				}

				prevM = helpM;
				helpM = helpM->next;
			}

			if (helpM) {

				if (helpS->koszt + pierwszeQ->koszt < helpM->koszt) {

					helpM->koszt = helpS->koszt + pierwszeQ->koszt;
					helpM->poprzednik = pierwszeQ->numerMiasta;
				}
				cout << endl;
				wypiszMiasto(miastoGlowa);
				sortuj(pierwszeQ, helpM, prevM);
				cout << endl;
				wypiszMiasto(miastoGlowa);
				helpM = pierwszeQ;
			}

			helpS = helpS->next;
		}
		pierwszeQ = pierwszeQ->next;
		
	} while (pierwszeQ);

}
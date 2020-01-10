#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "funkcje.h"

using namespace std;

bool sprawdzArgumenty(int argc, char* argv[], string &nazwaPlikuWejsciowego, string &nazwaPlikuWyjsciowego, string &miastoStartowe) {

	int zlicz = 0;

	if (argc <= 7) {

		for (int i = 1; i < argc; i++)
		{
			if (string(argv[i]) == string("-i")){

				nazwaPlikuWejsciowego = string(argv[i + 1]);
				zlicz++;
			}

			if (string(argv[i]) == string("-o")){

				nazwaPlikuWyjsciowego = string(argv[i + 1]);
				zlicz++;
			}

			if (string(argv[i]) == string("-s")){

				miastoStartowe = string(argv[i + 1]);
				zlicz++;
			}
		}

		if (zlicz == 3) return true;

		else return false;
	}

	else return false;
}

void pomoc() {
	cout << "Uwaga! Program nalezy uruchamiac z 3 parametrami:" << endl;
	cout << "-i nazwa pliku wejsciowego z danymi" << endl;
	cout << "-o nazwa pliku wyjsciowego" << endl;
	cout << "-s nazwa miasta startowego, centrali" << endl;
}

vector<string> stworzVectorMiast(string nazwaPliku, string nazwaCentrali){

	ifstream plik;
	plik.open("C:/Users/wybieracz/Documents/POLSL/PPK/20_Spedycja_Dijkstra/20_Spedycja_Dijkstra/" + nazwaPliku, ios ::in);

	if (plik.fail()) {
		std::cout << "Input file error!" << endl;
	}

	vector<string> vektorNazwMiast;
	string miasto1, miasto2;
	int odleglosc;

	vektorNazwMiast.push_back(nazwaCentrali);

	while (true)
	{
		plik >> miasto1 >> miasto2 >> odleglosc;

		if (not plik.fail()) {

			if (not znajdzDuplikat(vektorNazwMiast, miasto1)) vektorNazwMiast.push_back(miasto1);
			if (not znajdzDuplikat(vektorNazwMiast, miasto2)) vektorNazwMiast.push_back(miasto2);
		}

		else break;
	}

	plik.close();

	return vektorNazwMiast;
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

void wczytajGraf(string nazwaPliku, sasiad** &graf, vector<string> vektorNazwMiast) {

	sasiad* nowySasiad;
	int numerMiasta1, numerMiasta2, odleglosc, rozmiar = vektorNazwMiast.size();
	string miasto1, miasto2;

	ifstream plik;
	plik.open(nazwaPliku, ios::in);

	if (plik.fail())
		cout << "Input file error1!" << endl;

	for (int i = 0; i < rozmiar; i++) {
		graf[i] = nullptr;
	}

	while (true)
	{
		plik >> miasto1 >> miasto2 >> odleglosc;

		numerMiasta1 = znajdzNumer(vektorNazwMiast, miasto1);
		numerMiasta2 = znajdzNumer(vektorNazwMiast, miasto2);

		if (not plik.fail()) {

			nowySasiad = new sasiad{ graf[numerMiasta1], numerMiasta2, odleglosc };
			graf[numerMiasta1] = nowySasiad;

			nowySasiad = new sasiad{ graf[numerMiasta2], numerMiasta1, odleglosc };
			graf[numerMiasta2] = nowySasiad;
		}

		else break;
	}

	plik.close();
}

void stworzListeMiast(miasto* &miastoGlowa, int iloscMiast) {

	const int niesk = 2147483647;
	miasto* noweMiasto = nullptr;

	for (int i = iloscMiast - 1; i >= 0; i--) {

		noweMiasto = new miasto{ miastoGlowa, i, niesk, -1 };
		miastoGlowa = noweMiasto;
	}

	miastoGlowa->koszt = 0;
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

				if (helpM->numerMiasta == helpS->numerSasiada)
					break;

				prevM = helpM;
				helpM = helpM->next;
			}

			if (helpM) {

				if (helpS->koszt + pierwszeQ->koszt < helpM->koszt) {

					helpM->koszt = helpS->koszt + pierwszeQ->koszt;
					helpM->poprzednik = pierwszeQ->numerMiasta;
				}

				sortuj(pierwszeQ, helpM, prevM);
			}

			helpM = pierwszeQ;
			helpS = helpS->next;
		}

		pierwszeQ = pierwszeQ->next;

	} while (pierwszeQ);

}

void sortuj(miasto* &pierwszeQ, miasto* &miastoSortuj, miasto* &prev) {

	miasto* miastoGlowa = pierwszeQ;

	while (miastoGlowa) {

		if (miastoGlowa->next && miastoGlowa->next->koszt >= miastoSortuj->koszt) {

			if (miastoGlowa == miastoSortuj) break;

			prev->next = miastoSortuj->next;
			miastoSortuj->next = miastoGlowa->next;
			miastoGlowa->next = miastoSortuj;

			break;
		}

		miastoGlowa = miastoGlowa->next;
	}
}

void przepiszListe(miasto* miastoGlowa, int* kosztDojscia, int* poprzednicy) {

	while (miastoGlowa)
	{
		kosztDojscia[miastoGlowa->numerMiasta] = miastoGlowa->koszt;
		poprzednicy[miastoGlowa->numerMiasta] = miastoGlowa->poprzednik;
		miastoGlowa = miastoGlowa->next;
	}
}

void wypiszTrasy(int* kosztDojscia, int* poprzednicy, int rozmiar, vector<string> vectorNazwMiast, string nazwaPliku) {

	int* stos = new int[rozmiar];
	int wskaznikStosu = 0;

	ofstream plik;
	plik.open(nazwaPliku, ios::out);

	for (int i = 1; i < rozmiar; i++)
	{
		for (int j = i; j > -1; j = poprzednicy[j]) {
			stos[wskaznikStosu] = j;
			wskaznikStosu++;
		}

		while (wskaznikStosu) {
			wskaznikStosu--;
			cout << vectorNazwMiast[stos[wskaznikStosu]] << " -> ";
			plik << vectorNazwMiast[stos[wskaznikStosu]] << " -> ";

		}

		cout << ": " << kosztDojscia[i] << endl;
		plik << ": " << kosztDojscia[i] << endl;
	}
	plik.close();
	delete[] stos;
}

void wypiszTrasyRekurencyjnie(miasto* miastoGlowa, miasto* miastoWypisz, int iloscMiast, vector<string> vectorNazwMiast) {

	if (miastoWypisz == nullptr) return;

	wypiszTrasyRekurencyjnie(miastoGlowa, miastoWypisz->next, iloscMiast, vectorNazwMiast);

	bool * droga = new bool [iloscMiast];
	miasto* help = miastoGlowa;

	for (int i = 0; i < iloscMiast; i++) {
		droga[i] = false;
	}

	droga[miastoWypisz->numerMiasta] = true;

	do {

		while (help) {

			if (help->numerMiasta == miastoWypisz->poprzednik) {

				droga[help->numerMiasta] = true;
				break;
			}

			help = help->next;
		}

		miastoWypisz = help;
		help = miastoGlowa;

	} while (miastoWypisz != miastoGlowa);

	while(help){

		if (droga[help->numerMiasta] == true) {

			miastoWypisz = help;

			if (help != miastoGlowa)
				cout << " -> ";

			cout << vectorNazwMiast[help->numerMiasta];
		}

		help = help->next;
	}

	cout << ": " <<  miastoWypisz->koszt << endl;
}

void usunListeMiast(miasto*& miastoGlowa) {

	if (miastoGlowa) {
		usunListeMiast(miastoGlowa->next);
		delete miastoGlowa;
	}
}

void usunTabliceDynamiczme(sasiad** &graf, int iloscMiast) {

	sasiad* sasiad = nullptr, *doUsuniecia = nullptr;

	for (int i = 0; i < iloscMiast; i++)
	{
		sasiad = graf[i];

		while (sasiad)
		{
			doUsuniecia = sasiad;
			sasiad = sasiad->next;
			delete doUsuniecia;
		}
	}

	delete[] graf;
}
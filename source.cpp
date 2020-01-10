#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "funkcje.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace std;

int main(int argc, char* argv[]) {

	string nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, nazwaCentrali;

	if (not sprawdzArgumenty(argc, argv, nazwaPlikuWejsciowego, nazwaPlikuWyjsciowego, nazwaCentrali)) {
		cout << "Podano bledne parametry!" << endl;
		pomoc();
	}

	else {

		vector<string> vektorNazwMiast = stworzVectorMiast(nazwaPlikuWejsciowego, nazwaCentrali);
		int iloscMiast = vektorNazwMiast.size();
		sasiad** graf = new sasiad *[iloscMiast];
		miasto* miastoGlowa = nullptr;
		int* kosztyDojscia = new int[iloscMiast];
		int* poprzednicy = new int[iloscMiast];


		wczytajGraf("C:/Users/wybieracz/Documents/POLSL/PPK/20_Spedycja_Dijkstra/20_Spedycja_Dijkstra/" + nazwaPlikuWejsciowego, graf, vektorNazwMiast);
		stworzListeMiast(miastoGlowa, iloscMiast);
		dijkstra(miastoGlowa, graf);
		//wypiszTrasyRekurencyjnie(miastoGlowa, miastoGlowa, iloscMiast, vektorNazwMiast);
		przepiszListe(miastoGlowa, kosztyDojscia, poprzednicy);
		usunListeMiast(miastoGlowa);
		wypiszTrasy(kosztyDojscia, poprzednicy, iloscMiast, vektorNazwMiast, "C:/Users/wybieracz/Documents/POLSL/PPK/20_Spedycja_Dijkstra/20_Spedycja_Dijkstra/" + nazwaPlikuWyjsciowego);
		usunTabliceDynamiczme(graf, iloscMiast);

		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		return 0;
	}
}
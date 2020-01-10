#pragma once

#include <iostream>
#include <string>

using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

/** Deklaracja sasiada (krawedzi grafu).
@author Michal Pawlowski
@date 2020-01-07
*/
struct sasiad {

	/** wskaznik na nastepny wezel w liscie sasiadow */
	sasiad* next;
	/** etykieta sasiada */
	int numerSasiada;
	/** koszt dojscia do sasiada */
	int koszt;
};

/**Deklaracja miasta (wierzcholka grafu).
@author Michal Pawlowski
@date 2020-01-07
*/
struct miasto {

	/** wskaznik na nastepny wezel w liscie miast */
	miasto* next;
	/** etykieta miasta */
	int numerMiasta;
	/**calkowity koszt dojscia */
	int koszt;
	/** etykieta sasiada */
	int poprzednik;
};

/** Funkcja odczytujaca parametry programu.
@author Michal Pawlowski
@date 2020-01-07
@param argc ilosc parametrow
@param argv parametry
@param nazwaPlikuWejsciowego nazwa pliku wejsciowego
@param nazwaPlikuWyjsciowego nazwa pliku wyjsciowego
@param miastoStartowe
@return prawde, jezeli ilosc argumentow jest poprawna
*/
bool sprawdzArgumenty(int argc, char* argv[], string &nazwaPlikuWejsciowego, string &nazwaPlikuWyjsciowego, string &miastoStartowe);

/** Funkcja wypisujaca pomoc.
@author Michal Pawlowski
@date 2020-01-07
*/
void pomoc();

/** Funkcja zwraca wektor zawierajacy nazwy miast.
@author Michal Pawlowski
@date 2020-01-07
@param nazwaPliku nazwa pliku zawierajacego dane wejsciowe
@param centrala miasto od ktorego bêd¹ wyznaczane najkrotsze trasy
@return wektor przechowywujacy nazwy miast
*/
vector<string> stworzVectorMiast(string nazwaPliku, string centrala);

/** Funkcja okresla czy wektor zawiera ju¿ dane miasto.
@author Michal Pawlowski
@date 2020-01-07
@param miasta wektor przechowywuj¹cy nazwy miast
@param szukana nazwa miasta ktore ma byc wyszukane
@return zwraca prawde, jezeli podane miasto juz figuruje w wektorze
*/
bool znajdzDuplikat(vector<string> miasta, string szukana);

/** Funkcja zwraca numer przypisany do danego miasta.
@author Michal Pawlowski
@date 2020-01-07
@param miasta wektor przechowywujacy nazwy miast
@param szukana nazwa miasta ktorego numer ma byæ wyszukany
@return numer przyporzadkowany danemu miastu
*/
int znajdzNumer(vector<string> miasta, string szukana);

/** Funkacja tworzy przedstawienie grafu.
@author Michal Pawlowski
@date 2020-01-07
@param nazwaPliku nazwa pliku danych wejsciowych
@param [in,out] graf adres pierwszego elementu tablicy list sasiadow
@param wektorNazwMiast wektor przechowywujacy nazwy miast
*/
void wczytajGraf(string nazwaPliku, sasiad** &graf, vector<string> wektorNazwMiast);

/** Funkacja tworzy liste zawierajaca miasta (wierzcholki grafu).
@author Michal Pawlowski
@date 2020-01-07
@param [in,out] miastoGlowa adres pierwszego elementu listy miast
@param iloscMiast liczba wierzcholkow grafu
*/
void stworzListeMiast(miasto* &miastoGlowa, int iloscMiast);

/** Funkacja wykonuje algorytm Dijkstry.
@author Michal Pawlowski
@date 2020-01-07
@param [in,out] miastoGlowa adres pierwszego elementu listy miast
@param graf adres pierwszego elementu tablicy list sasiadow
*/
void dijkstra(miasto*& miastoGlowa, sasiad** graf);

/** Funkacja sortuje element listy wsrod miast ktore nie zosta³y jeszcze przetworzone przez algorytm Dijkstry.
@author Michal Pawlowski
@date 2020-01-07
@param [in,out] pierwszeQ wskaznik pomocniczy
@param [in,out] miastoSortuj wskaznik na element ktory ma zostac posortowany
@param [in,out] prev wskaznik na element poprzedni
*/
void sortuj(miasto* &pierwszeQ, miasto* &miastoSortuj, miasto* &prev);

/** Funkcja przepisuje wyniki z listy do tablic.
@author Michal Pawlowski
@date 2020-01-07
@param miastoGlowa wskaznik pomocniczy
@param kosztDojscia wskaznik na tablice kosztow dojscia
@param poprzednicy wskaznik na tablice poprzednikow
*/
void przepiszListe(miasto* miastoGlowa, int* kosztDojscia, int* poprzednicy);

/** Funkcja wypisuje wynik dzialania programu na konsoli oraz w pliku wyjscia.
@author Michal Pawlowski
@date 2020-01-07
@param kosztDojscia wskaznik na tablice kosztow dojscia
@param poprzednicy wskaznik na tablice poprzednikow
@param rozmiar ilosc miast (wierzcho³kow)
@param wektorNazwMiast wektor przechowywuj¹cy nazwy miast
@param nazwaPliku nazwa pliku wyjsciowego
*/
void wypiszTrasy(int* kosztDojscia, int* poprzednicy, int rozmiar, vector<string> vectorNazwMiast, string nazwaPliku);

/** Funkcja wypisuje wynik dzialania programu na konsoli.
@author Michal Pawlowski
@date 2020-01-07
@param miastoGlowa wskaznik na pierwszy element tablicy miast
@param miastoWypisz miasto ktorego dane maj¹ zostac wyisane
@param ilosc miast (wierzcholkow)
@param wektorNazwMiast wektor przechowywujacy nazwy miast
*/
void wypiszTrasyRekurencyjnie(miasto* miastoGlowa, miasto* miastoWypisz, int iloscMiast, vector<string> vectorNazwMiast);

/** Funkcja usuwa liste miast.
@author Michal Pawlowski
@date 2020-01-07
@param [in,out] miastoGlowa adres pierwszego elementu listy miast
*/
void usunListeMiast(miasto* &miastoGlowa);

/** Funkcja usuwa liste sasiadow (graf)
@author Michal Pawlowski
@date 2020-01-07
@param [in,out] miastoGlowa adres pierwszego elementu listy sasiadow
@param iloscMiast liczba miast (wierzcholkow)
*/
void usunTabliceDynamiczme(sasiad** &graf, int iloscMiast);

#endif
#pragma once
#include <iostream>
#include <string>
using namespace std;

#ifndef FUNKCJE_H
#define FUNKCJE_H

struct sasiad
{
	sasiad* next;
	int numerSasiada, koszt;
};

struct miasto {

	miasto* next;
	int numerMiasta, koszt, poprzednik;
};

int sprawdzArgumenty(int argc, char* argv[], string& nazwaPlikuWejsciowego, string& nazwaPlikuWyjsciowego, string& miastoStartowe);

void pomoc();

void wczytajGraf(string nazwaPliku, sasiad**& graf, int rozmiar, vector<string> wektorNazwMiast);

bool znajdzDuplikat(vector<string> miasta, string szukana);

int znajdzNumer(vector<string> miasta, string szukana);

void stworzListeMiast(miasto*& miastoGlowa, int iloscMiast);

void wypiszMiasto(miasto* miastoGlowa);

void dijkstra(miasto*& miastoGlowa, sasiad** graf);

void sortuj(miasto*& pierwszeQ, miasto*& miastoSortuj, miasto*& prev);

void sortuj2(miasto*& pierwszeQ, miasto*& miastoSortuj, miasto*& prev);

//void znajdzNoweMiasto(miasto* miastoGlowa, miasto*& miastozZapis);
#endif
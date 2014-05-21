/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "program.hh"
#include "przykladowy_program.hh"
#include "tab_hash.hh"
#include "konfiguracja.hh"
#include "simplex.h"



using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytmem.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	Simplex zadanie;
	zadanie.stworz_tabele_simplex();
	zadanie.wyswietl_tabele_simplex();
	zadanie.znajdz_optimum();
	zadanie.wyswietl_tabele_simplex();
	zadanie.wypisz_rozwiazanie();
	return true;
};

bool Przykladowy_program::stworz_plik_testowy(int ilosc,char* nazwa){
	return true;
}


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
#include "plansza.hh"



using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytmem.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	Plansza morze;
	morze.stworz_plansze(15,20);
	for(int i=8;i<16;i++){
		morze.zwroc_pole(8,i)->zablokuj_pole();
	}
	for(int i=2;i<12;i++){
		morze.zwroc_pole(11,i)->zablokuj_pole();
	}
	morze.znajdz_droge(morze.zwroc_pole(2,5),morze.zwroc_pole(12,10));
	morze.wyswietl_droge();
	morze.wyswietl_parametry_drogi();
	
	return true;
};

bool Przykladowy_program::stworz_plik_testowy(int ilosc,char* nazwa){
	return true;
}


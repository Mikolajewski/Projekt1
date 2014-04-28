/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/

#include <iostream>
#include "program.hh"
#include "przykladowy_program.hh"
#include "stos_tablica.hh"
#include "konfiguracja.hh"
#include "stos.hh"
#include "kolejka.hh"

using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytme.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	Stos_lub_kolejka <int,kolejeczka> tablica_stos;
	int i;
	for(i=0;i<dane.dlugosc_tablicy;i++){
		tablica_stos.push(dane.tablica[i]);
	}

//Lista_stos <int> stos;
//	for(i=0;i<dane.dlugosc_tablicy;i++){
//		stos.lista.push(dane.tablica[i]);
//	}
//Lista_kolejka <int> kolejka;

//	for(i=0;i<dane.dlugosc_tablicy;i++){
//		kolejka.elementy.push(dane.tablica[i]);
//	}

return true;
};


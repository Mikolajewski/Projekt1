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
#include "sortowanie2.hh"

using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytme.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	Sortowanie <double> algorytm;
//	algorytm.quicksort((double*)dane.tablica,dane.tablica+dane.dlugosc_tablicy-1);
//	algorytm.merge((double*)dane.tablica,dane.tablica+dane.dlugosc_tablicy-1);
	algorytm.kopcowanie((double*)dane.tablica,dane.tablica+dane.dlugosc_tablicy-1);
return true;
};


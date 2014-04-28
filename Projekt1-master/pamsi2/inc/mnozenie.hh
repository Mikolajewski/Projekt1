/*!
\file
\brief Plik zawierajacy deklaracje klasy Mnozenie

*/

#ifndef MNOZENIE
#define MNOZENIE
#include "program.hh"

/*!
\brief Klasa Mnozenie

Klasa pochodna klasy bazowej Program wykonujaca mnozenie danych razy dwa.
*/
class Mnozenie: public Program{
	public:
/*!
\brief Metoda wykonaj_program 

Metoda nadpisana na metode klasy bazowej wykonujaca algorytm zgodny z funkcja klasy.
\return Zwraca wartosc true jezeli wykonano zadana operacje lub wartosc false jezeli operacja sie nie powiodla.
*/
		bool wykonaj_program();
};
#endif

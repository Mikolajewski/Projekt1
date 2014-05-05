/*!
\file
\brief Plik zawierajacy deklaracje klasy Przykladowy_program

*/
#ifndef PRZYKLADOWY_PROGRAM
#define PRZYKLADOWY_PROGRAM

#include "program.hh"
#include "tablica.hh"

/*!
\brief Klasa Przykladowy_program

Klasa odpowiedzialna za zastapienie metody klasy Program wlasna. Docelowo jest to plik w ktorym bedzie znajdowac sie wlasciwy algorytm.
*/
class Przykladowy_program: public Program{
	public:

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytme.
*/
		bool wykonaj_program(Tablica& dane);

/*!
\brief Metoda stworz_plik_testowy

Metoda zapisujaca do pliku dane, ktore moga byc wykorzystywane przy dzialaniu konkretnego programu jako dane wejsciowe.
*/
		bool stworz_plik_testowy(int ilosc,char* nazwa);
};
#endif

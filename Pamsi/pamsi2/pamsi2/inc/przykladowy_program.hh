/*!
\file
\brief Plik zawierajacy deklaracje klasy Przykladowy_program

*/
#ifndef PRZYKLADOWY_PROGRAM
#define PRZYKLADOWY_PROGRAM

#include "program.hh"

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
		bool wykonaj_program();
};
#endif

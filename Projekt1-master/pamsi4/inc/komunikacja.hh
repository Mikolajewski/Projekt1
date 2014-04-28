/*!
\file
\brief Plik zawierajacy deklaracje klasy Komunikacja.

*/

#ifndef KOMUNIKACJA
#define KOMUNIKACJA
#include <string>
#include "tablica.hh"
using namespace std;


/*!
\brief Klasa Komunikacja

Klasa odpowiedzialna za komunikacje pomiedzy program, a swiatem zewnetrznym (wpisywanymi tekstami na std:in oraz otwieranymi plikami)
*/
class Komunikacja{
	public:
/*!
\brief Metoda pytanie_tak_nie

Metoda wykorzystywana do sprawdzania czy urzydkownik odpowiedzial poprawnie.
\return Zwraca wartosc true jesli odpowiedz jest "tak" lub false gdy odpowiedz jest "nie"
*/
 	bool pytanie_tak_nie();
 	
/*!
\brief Metoda wczytaj_inty_do_tablicy

\param[in] Tablica do ktorej zostana wpisane liczby
\param[in] Nazwa pliku ktory zostanie otwarty 
\return  Zwraca wartosc true jesli zapis sie udal. Jesli nie zwracana jest wartosc false i odpowieni komunikat.
*/
 	bool wczytaj_inty_do_tablicy(Tablica& dane,string nazwa);
 	
/*!
\brief Metoda wczytaj_stringi_do_tablicy

\param[in] Tablica do ktorej zostana wpisane napisy.
\param[in] Nazwa pliku ktory zostanie otwarty.
\return  Zwraca wartosc true jesli zapis sie udal. Jesli nie zwracana jest wartosc false i odpowieni komunikat.
*/	
 	bool wczytaj_stringi_do_tablicy(Tablica& dane,string nazwa);
 	
/*!
\brief Metoda pobierz_int

Pobiera wartosci ze standardowego wejscia i sprawdza czy jest to liczba int
\return Jesli wpisano wartosc int to jest ona zwracana przez funkcje. Jesli nie wyswietlany jest odpowieni komunikat i czynnosci sa powtarzane.
*/
 	int pobierz_int();
};
#endif

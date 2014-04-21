/*!
\file
\brief Plik zawierajacy deklaracje klasy Operacje

*/

#ifndef OPERACJE
#define OPERACJE
#include "tablica.hh"


/*!
\brief Klasa Operacje

Klasa posiadajaca metody potrzebne do wykonywania operacji na Tablicach.
*/
class Operacje{
	public:
		
/*!
\brief Metoda zamien_elementy

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Numery zmiennych, ktore maja zostac zamienione.
\return Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool zamien_elementy(Tablica &dane,int i, int j);

/*!
\brief Metoda odwroc_tablice

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\return  Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool odwroc_tablice(Tablica &dane);

/*!
\brief Metoda mnozenie

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Liczba razy ktora nalezy pomnozyc.
*/
Tablica dodaj_element(Tablica &dane,int a);

/*!
\brief Metoda dodaj_element

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Element, ktory nalezy dodac na koniec.
\return Zwraca Tablice, na ktorej wykonywane byly operacje.
*/
void mnozenie(Tablica &dane,int mnoznik);

/*!
\brief Metoda dodaj_tablice

Metoda dodaje druga tablice na koniec pierwszej.
\param[in] Adresy Tablic w ktorych wpisane sa dane.
\return Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool dodaj_tablice(Tablica& dane,Tablica& dane2);
};
#endif

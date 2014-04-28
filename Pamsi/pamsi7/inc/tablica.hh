/*!
\file
\brief Plik zawierajacy deklaracje klasy Tablica

*/

#ifndef TABLICA
#define TABLICA
#include <string>
using namespace std;

/*!
\brief Klasa Program

Klasa w ktorej przechowywane sa dane oraz zawierajaca niektore metody na nich wykonywane.
*/
class Tablica{
	public:
		/*!
\brief Zmienna tablica

Zawiera wskaznik do dynamicznie tworzonej tablicy, w ktorej przechowywane sa dane uprzednio wczytane z podanego pliku.
*/
union{
		string* napisy;
		int* tablica;

};

/*!
\brief Zmienna klucze

Zawiera klucze do danych znajdujacych sie w tablicy. W najprostrzym wypadku dane powinny byc wpisane w tej samej kolejnosci.
*/
		string* klucze;
		
		string* klucze2;
/*!
\brief Zmienna dlugosc_tablicy

Zawiera liczbe swiadczaco o dlugosci utworzonej tablicy dynamicznej.
*/
		int dlugosc_tablicy;
		
/*!
\brief Przeciazenie operatora =

Wykonuje przepisanie wartosci z jednej Tablicy do drugiej 
*/
		Tablica operator =(const Tablica dane);
		
/*!
\brief Przeciazenie konstruktora bezparametrycznego
*/
		Tablica(){dlugosc_tablicy=0,tablica=NULL;};
		
/*!
\brief Przeciazenie konstruktora parametrycznego
*/
		Tablica(int ilosc){delete [] tablica,tablica=new int[ilosc],dlugosc_tablicy=ilosc;};
		
/*!
\brief Przeciazenie operatora ==

/return Zwraca wartosc true jesli Tablice sa zgodne. W przeciwnym wypadku wartosc false. 
*/
		bool operator ==(const Tablica dane);
};
#endif

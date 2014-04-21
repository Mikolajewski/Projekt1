/*!
\file
\brief Plik zawierajacy definicje metod klasy Operacje.

*/
#include "tablica.hh"
#include "operacje.hh"
#include <iostream>
using namespace std;

/*!
\brief Metoda zamien_elementy

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Numery zmiennych, ktore maja zostac zamienione.
\return Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool Operacje::zamien_elementy(Tablica& dane,int i, int j){
	int element;
	if(dane.dlugosc_tablicy>=i && dane.dlugosc_tablicy>=j){
		element=dane.tablica[i-1];
		dane.tablica[i-1]=dane.tablica[j-1];
		dane.tablica[j-1]=element;
		return true;
	}
	else
		cerr<<"Nie ma takiego elementu"<<endl;
	return false;
}


/*!
\brief Metoda odwroc_tablice

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\return  Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool Operacje::odwroc_tablice(Tablica& dane){
int i;
for(i=0;i<dane.dlugosc_tablicy/2;i++){
	if(zamien_elementy(dane,i+1,dane.dlugosc_tablicy-i)==false){
		cerr<<"Nie udalo sie odwrocic tablicy"<<endl;
		return false;
	}
}
return true;
}


/*!
\brief Metoda mnozenie

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Liczba razy ktora nalezy pomnozyc.
*/
void Operacje::mnozenie(Tablica& dane,int mnoznik){
	int i; 
	for(i=0;i<dane.dlugosc_tablicy;i++)
		dane.tablica[i]*=mnoznik;
}


/*!
\brief Metoda dodaj_element

\param[in] Adres Tablicy w ktorej sa wpisane dane.
\param[in] Element, ktory nalezy dodac na koniec.
\return Zwraca Tablice, na ktorej wykonywane byly operacje.
*/
Tablica Operacje::dodaj_element(Tablica& dane,int a){
Tablica pomocnicza;
int i;
pomocnicza=dane;
dane=Tablica(pomocnicza.dlugosc_tablicy+1);
for(i=0;i<pomocnicza.dlugosc_tablicy;i++)
	dane.tablica[i]=pomocnicza.tablica[i];
dane.tablica[dane.dlugosc_tablicy-1]=a;
return dane;
}


/*!
\brief Metoda dodaj_tablice

Metoda dodaje druga tablice na koniec pierwszej.
\param[in] Adresy Tablic w ktorych wpisane sa dane.
\return Metoda zwraca wartosc true jesli dzialanie sie powiedzie. W przeciwnym wypadku zwraca wartosc false i odpowiedni komunikat.
*/
bool Operacje::dodaj_tablice(Tablica& dane,Tablica& dane2){
	Tablica pomocnicza;
	int i;
	pomocnicza=dane;
	if(dane2.dlugosc_tablicy!=0){
		dane=Tablica(pomocnicza.dlugosc_tablicy+dane2.dlugosc_tablicy);
		for(i=0;i<pomocnicza.dlugosc_tablicy;i++)
			dane.tablica[i]=pomocnicza.tablica[i];
		for(i=0;i<dane2.dlugosc_tablicy;i++){
			dane.tablica[pomocnicza.dlugosc_tablicy+i]=dane2.tablica[i];
		}
		return true;
	}
	else{
		cerr<<"Druga tablica jest pusta"<<endl;
		return false;
	}
}




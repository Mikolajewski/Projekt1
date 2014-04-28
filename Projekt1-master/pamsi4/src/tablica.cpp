/*!
\file
\brief Plik zawierajacy definicje metod klasy Tablica

*/
#include "tablica.hh"

/*!
\brief Przeciazenie operatora =

Wykonuje przepisanie wartosci z jednej Tablicy do drugiej 
*/
Tablica Tablica::operator=(Tablica dane){
	int i;
	delete [] tablica;
	tablica= new double[dane.dlugosc_tablicy];
	dlugosc_tablicy=dane.dlugosc_tablicy;
	for(i=0;i<dlugosc_tablicy;i++)
		tablica[i]=dane.tablica[i];
	return *this;
}


/*!
\brief Przeciazenie operatora ==

/return Zwraca wartosc true jesli Tablice sa zgodne. W przeciwnym wypadku wartosc false. 
*/
bool Tablica::operator==(Tablica dane){
	int i;
	if(dane.dlugosc_tablicy!=dlugosc_tablicy)
		return false;
	for(i=0;i<dlugosc_tablicy;i++)
		if(tablica[i]!=dane.tablica[i])
			return false;
	return true;	
}

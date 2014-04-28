/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/
#define HASLO "c"
#include <iostream>
#include <string>
#include "program.hh"
#include "przykladowy_program.hh"
#include "drzewo.hh"
#include "element.hh"



using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytmem.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	Drzewo <Element<string,double>,string,double> struktura;
	int i;
	string haslo=HASLO;
	cout<<"poczatek programu"<<endl;
	for(i=0;i<dane.dlugosc_tablicy;i++){
		struktura.dodaj(dane.klucze[i],dane.tablica[i]);
	}
	struktura.pobierz(haslo);
	cout<<"Ilosc elementow: "<<struktura.zlicz_elementy()<<endl;
	struktura.usun(haslo);
	struktura.pobierz(haslo);
	cout<<"Ilosc elementow: "<<struktura.zlicz_elementy()<<endl;
return true;
};


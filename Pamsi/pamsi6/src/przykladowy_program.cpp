/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/
#define HASLO "r"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "program.hh"
#include "przykladowy_program.hh"
#include "drzewo.hh"
#include "element.hh"
#include "tab_hash.hh"
#include "konfiguracja.hh"



using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytmem.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	TYP <Element<string,double>,string,double> struktura;
	int i,j;
	for(i=0;i<dane.dlugosc_tablicy;i++){
		struktura.dodaj(dane.klucze[i],dane.tablica[i]);
	}
	zacznij_pomiar_czasu();
	for(j=0;j<ILE_RAZY_POWTORZYC;j++){
		for(i=0;i<dane.dlugosc_tablicy;i++){
			struktura.pobierz(dane.klucze[i]);
		}
	}
return true;
};

bool Przykladowy_program::stworz_plik_testowy(int ilosc,char* nazwa){
	fstream plik_wyjsciowy;
	int i,j;
	int wartosc;
	int dlugosc_slowa;
	string klucz;
    srand( time( NULL ));
	plik_wyjsciowy.open(nazwa,ios::out);
	if(plik_wyjsciowy.good()==false){
		cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
		return false;
	}

	plik_wyjsciowy<<ilosc<<endl;
	for(i=0;i<ilosc;i++){
		dlugosc_slowa=(rand()%MAKSYMALNA_DLUGOSC_SLOWA)+1;
		for(j=0;j<dlugosc_slowa;j++){
			if(j==0){
				klucz=(char)((rand()%ILOSC_MOZLIWYCH_ZNAKOW)+PIERWSZY_ZNAK);
			}
			else{
				klucz+=(char)((rand()%ILOSC_MOZLIWYCH_ZNAKOW)+PIERWSZY_ZNAK);
			}
		}
		wartosc=rand()%(MAKSYMALNA_WARTOSC-MINIMALNA_WARTOSC+1)+MINIMALNA_WARTOSC;
		plik_wyjsciowy<<klucz<<" "<<wartosc<<endl;
	}

	plik_wyjsciowy.close();
	cout<<"Dane zostaly poprawnie zapisane do pliku: "<<nazwa<<endl;
	return true;
}


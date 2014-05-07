/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "program.hh"
#include "przykladowy_program.hh"
#include "element.hh"
#include "tab_hash.hh"
#include "konfiguracja.hh"
#include "graf.hh"



using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytmem.
*/
bool Przykladowy_program::wykonaj_program(Tablica& dane){
	TYP <Element<string,int>,string> struktura;
	int i;
	wstrzymaj_pomiar_czasu();
	for(i=0;i<dane.dlugosc_tablicy;i++){
		struktura.dodaj_krawedz(dane.klucze[i],dane.klucze2[i],dane.tablica[i]);
	}
//	struktura.depth_first_search(dane.klucze[0]);
	cout<<"Graf wyglada nastepujaco."<<endl;
	struktura.wypisz();
	cout<<"------------------------Zaczynam------------------------"<<endl;
//	struktura.sasiedztwo(dane.klucze[0]);
//	struktura.czy_sasiad(dane.klucze[0],dane.klucze2[0]);
//	struktura.usun_krawedz(dane.klucze[0],dane.klucze2[0]);
//	struktura.sasiedztwo(dane.klucze[0]);
//	struktura.usun_wierzcholek(dane.klucze[0]);
//	struktura.sasiedztwo(dane.klucze[0]);
//	struktura.breadth_first_search(dane.klucze[0]);
	wznow_pomiar_czasu();
	struktura.best_first_search2(dane.klucze[0],dane.klucze[9]);
	wstrzymaj_pomiar_czasu();
	struktura.wypisz_droge();
	struktura.wypisz_parametry_drogi();
	cout<<"Odwiedzono: "<<struktura.zwroc_odwiedzonych()<<" ilosc krawedzi: "<<struktura.ilosc_krawedzi()<<endl;
	wznow_pomiar_czasu();
//	struktura.anty_depth_first_search(dane.klucze[0]);
//	cout<<"Odwiedzono: "<<struktura.zwroc_odwiedzonych()<<endl;
//	cout<<"Odwiedzono: "<<struktura.zwroc_odwiedzonych()<<endl;
//	struktura.dodaj_wierzcholek(dane.klucze[0]);
//	struktura.sasiedztwo(dane.klucze[0]);		
	return true;
};

bool Przykladowy_program::stworz_plik_testowy(int ilosc,char* nazwa){
	fstream plik_wyjsciowy;
	int i,j;
	int wartosc;
	int dlugosc_slowa;
	string klucz;
	string klucz2;
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
		
		dlugosc_slowa=(rand()%MAKSYMALNA_DLUGOSC_SLOWA)+1;
		for(j=0;j<dlugosc_slowa;j++){
			if(j==0){
				klucz2=(char)((rand()%ILOSC_MOZLIWYCH_ZNAKOW)+PIERWSZY_ZNAK);
			}
			else{
				klucz2+=(char)((rand()%ILOSC_MOZLIWYCH_ZNAKOW)+PIERWSZY_ZNAK);
			}
		}
		
		wartosc=rand()%(MAKSYMALNA_WARTOSC-MINIMALNA_WARTOSC+1)+MINIMALNA_WARTOSC;
		plik_wyjsciowy<<klucz<<" "<<klucz2<<" "<<wartosc<<endl;
	}

	plik_wyjsciowy.close();
	cout<<"Dane zostaly poprawnie zapisane do pliku: "<<nazwa<<endl;
	return true;
}


/*!
\file
\brief Plik zawierajacy definicje metod klasy benchmark.

*/

#include <iostream>
#include <ctime>
#include "program.hh"
#include "mnozenie.hh"
#include "benchmark.hh"

/*!
\brief Metoda wykonaj_sprawdzenie_algorytmu

\param[in] Ilosc wykonan algorytmu.
*/
void benchmark::wykonaj_sprawdzenie_algorytmu(int ile_razy){
	clock_t czas_trwania_programu;
	Mnozenie program;
	dlugosc_tablicy_czasow=0;
 	char* plik_wejsciowy=(char*)"dane.txt";
 	char* plik_wyjsciowy=(char*)"wynik.txt";
 	char* plik_sprawdzajacy=(char*)"sprawdzenie.txt";
 	int i;
 	dlugosc_tablicy_czasow=ile_razy;
 	
 	tablica_czasow=new double[ile_razy];
 	for(i=0;i<ile_razy;i++){
	 	program.wczytaj_plik(plik_wejsciowy);
 		program.zacznij_pomiar_czasu();
 		program.wykonaj_program();
 		czas_trwania_programu=program.zakoncz_pomiar_czasu();
 		program.zapisz_dane(plik_wyjsciowy);
   		//program.wypisz_dane();
   		if(program.porownaj_dane(plik_sprawdzajacy)==true){
   			tablica_czasow[i]=(double)czas_trwania_programu/CLOCKS_PER_SEC;
   			cout<<"Wykonanie programu zajelo "<<(float)czas_trwania_programu/CLOCKS_PER_SEC<<" sekundy"<<endl<<endl;	
   		}
   }
};

/*!
\brief Metoda oblicz_sredni_czas_wykonywania_algorytmu

\return Zwraca wartosc srednia potrzebna na wykonanie algorytmu w sekundach (liczba double).
*/
double benchmark::oblicz_sredni_czas_wykonywania_algorytmu(){
	double zmienna=0;
	srednia=0;
	int i;
	for(i=0;i<dlugosc_tablicy_czasow;i++){
		zmienna+=tablica_czasow[i];
	}
	srednia=(double)zmienna/dlugosc_tablicy_czasow;
	cout<<"Sredni czas wykonywania algorytmu to "<<srednia<<" sekundy"<<endl;
	return srednia;
};

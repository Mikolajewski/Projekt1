/*!
\file
\brief Plik zawierajacy deklaracje klasy benchmark.

*/
#ifndef BENCHMARK
#define BENCHMARK
#include "program.hh"

/*!
\brief Klasa benchmarek

Klasa wykonujaca sprawdzenie dlugosci wykonywania algorytmu okreslona ilosc razy oraz przedstawienie statystyk zwiazanych z wykonanymi pomiarami. Klasa ta bedzie rozbodowywany w ramach potrzeb przy nastepnych projektach.
*/
class benchmark{
	private:
		double* tablica_czasow;
		int dlugosc_tablicy_czasow;
		double srednia;
		Tablica dane;
	public:
/*!
\brief Metoda wykonaj_sprawdzenie_algorytmu

\param[in] Ilosc wykonan algorytmu.
*/
		bool wykonaj_sprawdzenie_algorytmu(int ile_razy);
		
/*!
\brief Metoda oblicz_sredni_czas_wykonywania_algorytmu

\return Zwraca wartosc srednia potrzebna na wykonanie algorytmu w sekundach (liczba double).
*/
		double oblicz_sredni_czas_wykonywania_algorytmu();
};
#endif

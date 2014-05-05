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

/*!
\brief Wskaznik tablica_czasow

Wskaznik bedacy odwolaniem do tablicy przechowujacej czasy w jakich wykonal sie algorytm
*/
		double* tablica_czasow;
		
/*!
\brief Zmienna dlugosc_tablicy_czasow

Zmienna przechowujaca informacje o ilosci czasow zapisanych w tablica_czasow
*/		
		int dlugosc_tablicy_czasow;
		
/*!
\brief Zmienna srednia

Zmienna zawierajaca dana o srednim czasie wykonywania algorytmu
*/
		double srednia;
		
/*!
\brief Zmienna dane

Zmienna przechowujaca dane wpisane do programu
*/
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
		
/*!
\brief Metoda wypisz_tablice_czasow

Metoda wypisujaca czasy w ktorych wykonal sie algorytm na standardowe wyjscie
*/
		void wypisz_tablice_czasow();
		
/*!
\brief Metoda zapisz_czasy_do_pliku

Metoda zapisujaca dane z tablica_czasow do pliku. Dzieki tej funkcji mozna w wygodny sposob skopiowac dane.
*/
		bool zapisz_czasy_do_pliku(char *nazwa);
		
/*!
\brief Metoda zapisz_graf_do_pliku_latex

Metoda zapisujaca dane do pliku obslugiwanego przez srodowisko latex. W pliku wynikowym tworzony jest graf analizowany podczas wykonywania programu.
*/
		bool zapisz_graf_do_pliku_latex(char* plik_latex,Tablica &dane);
};
#endif

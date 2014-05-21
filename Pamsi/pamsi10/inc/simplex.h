/*!
\file
\brief Plik deklaracje Klasy Simplex

*/
#include <iostream>
#include "komunikacja.hh"
#include "lista_posortowana.hh"
using namespace std;
/*!
\brief Klasa Simplex

Klasa sluzaca do wykonywania wyszukiwania optymalnego rozwiazania problemu liniowego.
*/
class Simplex{
/*!
\brief macierz_wspolczynnikow

Tablica w ktorej sa zawarte wspolczynniki z rownan
*/
	float**	macierz_wspolczynnikow;
/*!
\brief obliczony_koszt

Zmienna przechowywujaca informacje o wartosci jaka zostala znaleziona
*/
	float obliczony_koszt;
	
/*!
\brief wektor_b

Tablica wyrazow wolnych
*/
	float* wektor_b;
	
/*!
\brief wektor_funkcji_kosztu

Tablica w ktorej zapisane jest rowanie kosztu.
*/
	float* wektor_funkcji_kosztu;
	
/*!
\brief ilosc_zmiennych

Zmienna przechowujaca informacje o ilosci zmiennych wystepujacych w problemie
*/
	int ilosc_zmiennych;
	
/*!
\brief rodzaj_szukania

Zmienna przechowujaca informacje czy szukany jest najmniejsze czy najwieksze rozwiazanie
*/
	int rodzaj_szukania;
	
/*!
\brief ilosc_rownan

Informacja o ilosci rownan uzytych w problemi.
*/
	int ilosc_rownan;
	
/*!
\brief ilosc_kolumn

Zmienna zawierajaca liczbe kolumn tablicy z wagami rownan
*/
	int ilosc_kolumn;
	
/*!
\brief znajdz_max_x

Metoda znajdujaca maksimum w tablicy kosztu. Wykorzystywana do podazania w kierunku rozwiazania
*/
	int znajdz_max_x();
	
/*!
\brief znajdz_min_iloraz

Metoda znajdujaca zmienna ktora ma zostac zamieniona
*/
	int znajdz_min_iloraz(int kolumna);
	
/*!
\brief zamien

Metoda zamieniajaca dwie zmienne
*/
	void zamien(int poczatek,int koniec);
	
/*!
\brief koniec

Metoda sprawdzajaca czy znaleziono juz rozwiazanie
*/
	bool koniec();
	public:
/*!
\brief stworz_tabele_simplex

Metoda tworzaca tabele zawierajaca dane na temat testowanego przypadku
*/
		void stworz_tabele_simplex();
		
/*!
\brief wyswietl_tabele_simplex

Metoda ilustrujaca badany problem za pomoca tabeli
*/
		void wyswietl_tabele_simplex();
		
/*!
\brief znajdz_optimum

Metoda wyszukujaca najlepsze rozwiazanie
*/
		bool znajdz_optimum();
		
/*!
\brief wypisz_rozwiazanie

Metoda wypisujaca znalezione rozwiazanie
*/
		void wypisz_rozwiazanie();
};



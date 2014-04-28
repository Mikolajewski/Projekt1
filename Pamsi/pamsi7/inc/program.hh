/*!
\file
\brief Plik zawierajacy deklaracje klasy Program.

*/

#ifndef PROGRAM
#define PROGRAM
#include <fstream>
#include <ctime>
#include <cstdio>
#include "tablica.hh"
 using namespace std;

/*!
\brief Klasa Program

Klasa odpowiedzialana za wykonanie operacji zwiazanych z pomiarem czasu oraz obsluge plikow, na ktorych wykonywane sa dzialania. Jest to klasa bazowa dla poszczegolnych algorytmow, ktorych metody moga zostac nadpisane. 
*/
class Program{
		public:
		Tablica dane;
/*!
\brief Zmienna czas_rozpoczecia

Zawiera czas w ktorym zaczal wykonywac sie wlasciwy kod algorytmu (liczony od momentu uruchomienia programu). Do tej danej porownywany jest czas zakoczenia wykonywania algorytmu.
*/
		clock_t czas_rozpoczecia;
		
		clock_t czas_wstrzymania;
/*!
\brief Zmienna plik_wejsciowy

Zmienna przedstawiajaca otwarty plik jako strumien danych.
*/
		fstream plik_wejsciowy;
		
/*!
\brief Zmienna plik_wyjsciowy

Zmienna przedstawiajaca strumien danych po wykonaniu wlasiwego algorytmu.
*/
		fstream plik_wyjsciowy;
		
/*!
\brief Metoda zapisz_dane

\param[in] Wskaznik do nazwy pliku, pod ktorym ma zostac zapisany strumien wyjsciowy.
\return Zwraca
*/
		bool zapisz_dane(char *nazwa);
		
		bool zapisz_dane_posortowane(char *nazwa);
/*!
\brief Metoda wypisz_dane

Metoda, ktora wypisuje przetworzone dane na standardowym wyjsciu.
*/
		void wypisz_dane();
/*!
\brief Metoda porownaj_dane

Metoda porownujaca otrzymane dane ze spodziewanym wynikiem.
\param[in] Wskaznik do pliku zawierajacego poprawny wynik obliczen.
\return Metoda zwraca wartosc true jesli udalo sie otworzyc odpowiedni plik i dane sa zgodne z wynikajacymi z obliczen. W przeciwynym wypadku metoda zwraca wartosc false i wyswietla odpowiedni komunikat. 
*/
		bool porownaj_dane(char *nazwa);
/*!
\brief Metoda wykonaj_program

Metoda wykonujaca glowny algorytm programu.
\return Metoda zwraca wartosc false jesli nie zostala nadpisana inna metoda z klasy dziedziczacej i wyswietla odpowiedni komunikat.
*/
		virtual bool wykonaj_program();
		
		
		virtual bool stworz_plik_testowy(int ilosc,char* nazwa);
		
/*!
\brief Metoda zacznij_pomiar_czasu

Metoda zapisujaca czas rozpoczecia pomiaru w odpowiednim polu klasy.
\return Zwraca odczytany czas.
*/
		clock_t zacznij_pomiar_czasu();
/*!
\brief Metoda zakoncz_pomiar_czasu

\return Zwraca dlugosc czasu wykonania programu (ilosc taktow zegara podzielona przez preskaler).
*/
		clock_t zakoncz_pomiar_czasu();
		
		clock_t wstrzymaj_pomiar_czasu();
		
		clock_t wznow_pomiar_czasu();
};
#endif

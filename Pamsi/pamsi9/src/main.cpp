/*!
\mainpage 
Program sluzacy do wyznaczania skutecznosci algorytmu za pomoca pomiaru czasu

Aplikacja jest przykladem realizacji programu sluzacego do sprawdzania zlozonosci obliczeniowej algorytmu. Wykonuje ona pomiar czasu wykonywania zadanego programu. Aplikacja jest zbudowana na obiektach, dzieki czemu mozliwe jest szybkie wstawienie nowego algorytmu w postaci klasy dziedziczacej czesc metod po klasie bazowej. 

\section etykieta-ogolne-informacje Ogolne informacje

Program zostal wyposazony w funkcje wczytywania, wypisywania i zapisywania danych do pliku.
Aplikacja byla sprawdzana na systemie operacyjnym Windows.
Do poprawnego dzialania programu potrzebny jest plik z danymi zapisany w postaci: 
ilosc danych,
 wlasciwe dane.
Mozliwe jest rowniez otwieranie wielu plikow danych przy pomocy jednego pliku. Musi on zawierac dane w postaci:
ilosc sciezek do plikow,
sciezki do plikow. 
Program posiada rowniez funkcje automatycznego tworzenia pliku wejsciowego.
Sam Program_przykladowy powstal z mysla pokazania ze zadane operacje sa wykonywane poprawnie.

\section etykieta-algortym Algorytm
 
Algorytm realizuje wyszukiwanie najkrotszej drogi w tablicy o elementach Pole. Droga jest wyszukiwana za pomoca algorytmu A*. Algorytm wyswietla znaleziona droge na stdout wraz z tablica na ktorej odbywalo sie wyszukiwanie. Kazde wyswietlane pole zawiera informacje o przewidywanym koszcie jaki trzeba zaplacic za przejscie z poczatku do celu przez omawiane pole. Wartym podkreslenia jest ze algorytm nie dokonuje przeszacowania pozostalej drogi, co oznacza ze wyszukana sciezka jest najkrotsza z mozliwych.
*/

/*!
\file
\brief Plik zawierajacy glowna funkcje programu wykonujacego benchmark algorytmu.

*/
#include <iostream>
#include "komunikacja.hh"
#include "benchmark.hh"
using namespace std;
 
 /*!
 \brief Glowna funkcja programu
 
 Funkcja wykonujaca benchmark zadanego algorytmu na podstawie czasu wykonywania operacji.
 */
 int main(void){
	benchmark algorytm;
	Komunikacja dialog;
	int ile_razy_wykonac_algorytm=0;
	cout<<"Ile razy wykonac sprawdzenie algorytmu?"<<endl;
	ile_razy_wykonac_algorytm=dialog.pobierz_int();
	if(algorytm.wykonaj_sprawdzenie_algorytmu(ile_razy_wykonac_algorytm)){ 			//jesli algorytm wykonal sie poprawnie
		algorytm.oblicz_sredni_czas_wykonywania_algorytmu();               			//to wypisz statystyki np: srednia
	}
	return 0;
 }

/*!
\mainpage 
Program sluzacy do wyznaczania skutecznosci algorytmu za pomoca pomiaru czasu

Aplikacja jest przykladem realizacji programu sluzacego do sprawdzania zlozonosci obliczeniowej algorytmu. Wykonuje ona pomiar czasu wykonywania zadanego programu. Aplikacja jest zbudowana na obiektach, dzieki czemu mozliwe jest szybkie wstawienie nowego algorytmu w postaci klasy dziedziczacej czesc metod po klasie bazowej. 

\section etykieta-wazne-informacje Wazne informacje

Program zostal wyposazony w funkcje wczytywania, wypisywania i zapisywania danych do pliku.
Aplikacja byla sprawdzana na systemie operacyjnym Windows.
Do poprawnego dzialania programu potrzebny jest plik z danymi zapisany w postaci: 
ilosc danych,
wlasciwe dane.
*/

/*!
\file
\brief Plik zawierajacy glowna funkcje programu wykonujacego benchmark algorytmu.

*/
#include <iostream>
#include "benchmark.hh"
using namespace std;
 
 /*!
 \brief Glowna funkcja programu
 
 Funkcja wykonujaca benchmark zadanego algorytmu na podstawie czasu wykonywania operacji.
 */
 int main(void){
	benchmark algorytm;
	int ile_razy_wykonac_algorytm=0;
	while(ile_razy_wykonac_algorytm<1){
		cout<<"Ile razy wykonac sprawdzenie algorytmu?"<<endl;
		cin>>ile_razy_wykonac_algorytm;
	}	
	algorytm.wykonaj_sprawdzenie_algorytmu(ile_razy_wykonac_algorytm);
	algorytm.oblicz_sredni_czas_wykonywania_algorytmu();
	return 0;
 }

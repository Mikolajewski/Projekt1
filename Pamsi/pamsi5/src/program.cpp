/*!
\file
\brief Plik zawierajacy definicje metod klasy Program.

*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <ctime>
#include "program.hh"
#include "komunikacja.hh"
 using namespace std;



/*!
\brief Metoda wypisz_dane

Metoda, ktora wypisuje przetworzone dane na standardowym wyjsciu.
*/
void Program::wypisz_dane(){
	int i;
	for(i=0;i<dane.dlugosc_tablicy;i++){
		cout<<dane.tablica[i]<<endl;
	}
};

/*!
\brief Metoda zapisz_dane

\param[in] Wskaznik do nazwy pliku, pod ktorym ma zostac zapisany strumien wyjsciowy.
\return Zwraca
*/
bool Program::zapisz_dane(char *nazwa){
	int i;
	Komunikacja dialog;
	cout<<"Czy zapisac wynik obliczen? (t/n)"<<endl;
	if(dialog.pytanie_tak_nie()){	
		plik_wyjsciowy.open(nazwa,ios::out);
		if(plik_wyjsciowy.good()==false){
			cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
			return false;
		}
		for(i=0;i<dane.dlugosc_tablicy;i++)
			plik_wyjsciowy<<dane.tablica[i]<<endl;
		plik_wyjsciowy.close();
		cout<<"Dane zostaly poprawnie zapisane do pliku"<<endl;
	}	
	return true;
};

bool Program::zapisz_dane_posortowane(char *nazwa){
	double i;
	Komunikacja dialog;
//	cout<<"Czy zapisac wynik obliczen? (t/n)"<<endl;
	if(1){	
		plik_wyjsciowy.open(nazwa,ios::out);
		if(plik_wyjsciowy.good()==false){
			cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
			return false;
		}
		plik_wyjsciowy<<5000<<endl;
		for(i=5000;i>0;i--)
			plik_wyjsciowy<<i<<endl;
		plik_wyjsciowy.close();
		cout<<"Dane zostaly poprawnie zapisane do pliku"<<endl;
	}	
	return true;
};

/*!
\brief Metoda porownaj_dane

Metoda porownujaca otrzymane dane ze spodziewanym wynikiem.
\param[in] Wskaznik do pliku zawierajacego poprawny wynik obliczen.
\return Metoda zwraca wartosc true jesli udalo sie otworzyc odpowiedni plik i dane sa zgodne z wynikajacymi z obliczen. W przeciwynym wypadku metoda zwraca wartosc false i wyswietla odpowiedni komunikat. 
*/
bool Program::porownaj_dane(char *nazwa){
	string linia;
	int i;
	double liczba;
	plik_wejsciowy.close();
	plik_wejsciowy.open(nazwa,ios::in);
	if( plik_wejsciowy.good() == true ){
      	cout<<"Wynik porownania danych z plikiem podanym jako weryfikacyjny:" <<endl;
      	getline(plik_wejsciowy,linia);
      	istringstream iss(linia);
      	iss>>liczba;
		if(liczba != dane.dlugosc_tablicy){
			cerr<<"     Nie zgadzaja sie dlugosci tablicy"<<endl;
		return false;
		}
      	for(i=0;i<dane.dlugosc_tablicy;i++){
    		getline(plik_wejsciowy,linia);
      		istringstream iss(linia);
      		iss>>liczba;
			if(liczba != dane.tablica[i]){
				cerr<<"     Wyrazy "<<i+1<<" nie sa ze soba zgodne"<<endl;
				return false;
			}
      	}
      	cout<<"Porownywanie danych zakonczylo sie pomyslnie."<<endl;
	return true;
	}
	else{
     	 cerr<<"Dostep do pliku sprawdzajacego niepowiodl sie."<<endl;
    return false;
	}
};

/*!
\brief Metoda wykonaj_program

Metoda wykonujaca glowny algorytm programu.
\return Metoda zwraca wartosc false jesli nie zostala nadpisana inna metoda z klasy dziedziczacej i wyswietla odpowiedni komunikat.
*/
bool Program::wykonaj_program(){
cerr<<"Nie nadpisano odpowiedniego programu."<<endl;
return false;
};

/*!
\brief Metoda zacznij_pomiar_czasu

Metoda zapisujaca czas rozpoczecia pomiaru w odpowiednim polu klasy.
\return Zwraca odczytany czas.
*/
clock_t Program::zacznij_pomiar_czasu(){
	czas_rozpoczecia=clock();
	return czas_rozpoczecia;	
};

/*!
\brief Metoda zakoncz_pomiar_czasu

\return Zwraca dlugosc czasu wykonania programu (ilosc taktow zegara podzielona przez preskaler).
*/
clock_t Program::zakoncz_pomiar_czasu(){
	clock_t czas;
	czas=clock();
	return czas-czas_rozpoczecia;	
};

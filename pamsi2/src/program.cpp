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
 using namespace std;

/*!
\brief Metoda wczytaj_plik

\param[in] Wskaznik do nazwy pliku, ktory ma zostac otwarty.
\return Zwraca wartosc true, gdy operacja sie uda i plik zostanie poprawnie przepisany do strumienia lub wartosc false jesli operacja zakonczy sie niepowodzeniem.
*/
bool Program::wczytaj_plik(char *nazwa){
	string linia;
	int i;
	if( plik_wejsciowy.good() == true )
		plik_wejsciowy.close();
	plik_wejsciowy.open(nazwa,ios::in);
	if( plik_wejsciowy.good() == true ){
      	cout<<"Uzyskano dostep do pliku z danymi!" <<endl;
      	getline(plik_wejsciowy,linia);
      	istringstream iss(linia);
		iss >> dlugosc_tablicy;
      	tablica=new int[dlugosc_tablicy];
      	for(i=0;plik_wejsciowy.eof()!=true;i++){
    		getline(plik_wejsciowy,linia);
      		istringstream iss(linia);
			iss >> tablica[i];
      	}
	return true;
	}
	else{
     	 cerr<<"Dostep do pliku z danymi niepowiodl sie."<<endl;
    return false;
  }
};

/*!
\brief Metoda wypisz_dane

Metoda, ktora wypisuje przetworzone dane na standardowym wyjsciu.
*/
void Program::wypisz_dane(){
	int i;
	for(i=0;i<dlugosc_tablicy;i++){
		cout<<tablica[i]<<endl;
	}
};

/*!
\brief Metoda zapisz_dane

\param[in] Wskaznik do nazwy pliku, pod ktorym ma zostac zapisany strumien wyjsciowy.
\return Zwraca
*/
bool Program::zapisz_dane(char *nazwa){
	char znak='a';
	int koniec=0;
	string linia;
	int i;
	while(koniec==0){
		cout<<"Czy zapisac wynik obliczen? (t/n)"<<endl;
		cin>>znak;
		switch(znak){
		case 't':
			plik_wyjsciowy.open(nazwa,ios::out);
			if(plik_wyjsciowy.good()==false){
			cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
			return false;
			}
			for(i=0;i<dlugosc_tablicy;i++)
				plik_wyjsciowy<<tablica[i]<<endl;
			plik_wyjsciowy.close();
			cout<<"Dane zostaly poprawnie zapisane do pliku"<<endl;
			koniec=1;
			break;
		case 'n':
			koniec=1;
			break;	
		}
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
	int i,liczba;
	plik_wejsciowy.close();
	plik_wejsciowy.open(nazwa,ios::in);
	if( plik_wejsciowy.good() == true ){
      	cout<<"Uzyskano dostep do pliku sprawdzajacego!" <<endl;
      	getline(plik_wejsciowy,linia);
      	istringstream iss(linia);
      	iss>>liczba;
		if(liczba != dlugosc_tablicy){
			cerr<<"Nie zgadzaja sie dlugosci tablicy"<<endl;
		return false;
		}
      	for(i=0;i<dlugosc_tablicy;i++){
    		getline(plik_wejsciowy,linia);
      		istringstream iss(linia);
      		iss>>liczba;
			if(liczba != tablica[i]){
				cerr<<"Wyrazy "<<i+1<<" nie sa ze soba zgodne"<<endl;
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
	cerr<<"Nie nadpisano algorytmu programu!"<<endl;
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

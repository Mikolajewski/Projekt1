/*!
\file
\brief Plik zawierajacy definicje metod klasy Komunikacja.

*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <sstream>
#include "komunikacja.hh"
using namespace std;

/*!
\brief Metoda pytanie_tak_nie

Metoda wykorzystywana do sprawdzania czy urzydkownik odpowiedzial poprawnie.
\return Zwraca wartosc true jesli odpowiedz jest "tak" lub false gdy odpowiedz jest "nie"
*/
bool Komunikacja::pytanie_tak_nie(){
	int koniec_petli=0;
	string napis="a";
 	while(!koniec_petli){
 		cin.clear();
		cin>>napis;
		cout<<endl;
		if(napis=="nie"||napis=="tak")
			koniec_petli=1;
		else
			cerr<<"Bledna odpowiedz. Wybierz 'tak' lub 'nie'"<<endl<<endl;
	}
	return (napis=="tak")?true:false;
}


/*!
\brief Metoda wczytaj_inty_do_tablicy

\param[in] Tablica do ktorej zostana wpisane liczby
\param[in] Nazwa pliku ktory zostanie otwarty 
\return  Zwraca wartosc true jesli zapis sie udal. Jesli nie zwracana jest wartosc false i odpowieni komunikat.
*/
bool Komunikacja::wczytaj_inty_do_tablicy(Tablica& dane,string nazwa){
	fstream plik;
	string napis;
	int i,j,rozmiar;
	double pomocnicza;
	const char* wskaznik;
	if( plik.good() == true )
		plik.close();
	plik.open(nazwa.data(),ios::in);
	
	if( plik.good() == true ){
      	cout<<"Uzyskano dostep do pliku "<<nazwa<<endl<<endl;
		plik >> napis;
		wskaznik=napis.data();
		rozmiar=napis.size();
		for(i=0;i<rozmiar;i++){
			if(!isdigit(*(wskaznik+i))){
				cerr<<"W pliku znajduja sie bledne dane."<<endl;
				plik.close();
				return false;
			}
		}
		istringstream liczba(napis);
		liczba >> dane.dlugosc_tablicy;
      	dane.tablica=new double[dane.dlugosc_tablicy];
      	for(i=0;plik.eof()!=true;i++){     		
			plik >> napis;
			wskaznik=napis.data();
			rozmiar=napis.size();
			for(j=0;j<rozmiar;j++){
				if(!isdigit(*(wskaznik+j))){
					cerr<<"W pliku znajduja sie bledne dane."<<endl;
					return false;
				}
			}		
			istringstream liczba(napis);
			liczba >> pomocnicza;
			if(pomocnicza<0){
				cerr<<"W pliku znajduja sie bledne dane."<<endl;
				return false;
			}
			dane.tablica[i]=pomocnicza;
      	}
   	plik.close();
	return true;
	}
	else{
     	 cerr<<"Dostep do pliku z danymi niepowiodl sie. Probowano otworzyc plik "<<nazwa<<endl;
		plik.close();
    	return false;
  	}
}


/*!
\brief Metoda wczytaj_stringi_do_tablicy

\param[in] Tablica do ktorej zostana wpisane napisy.
\param[in] Nazwa pliku ktory zostanie otwarty.
\return  Zwraca wartosc true jesli zapis sie udal. Jesli nie zwracana jest wartosc false i odpowieni komunikat.
*/
bool Komunikacja::wczytaj_stringi_do_tablicy(Tablica& dane,string nazwa){
	fstream plik;
	string napis;
	int i,rozmiar;
	const char* wskaznik;
	if( plik.good() == true )
		plik.close();
	plik.open(nazwa.data(),ios::in);
	if( plik.good() == true ){
      	cout<<"Uzyskano dostep do pliku "<<nazwa<<endl;
		plik >> napis;
		wskaznik=napis.data();
		rozmiar=napis.size();
		for(i=0;i<rozmiar;i++){
			if(!isdigit(*(wskaznik+i))){
				cerr<<"Nie podano poprawnie ilosci sciezek w pliku."<<endl;
				return false;
			}
		}
		istringstream liczba(napis);
		liczba >> i;
		if((i>255||i<0)){
			cerr<<"Ilosc sciezek musi sie zawierac w przedziale <0,255>"<<endl;
			return false; 
		}
		dane.dlugosc_tablicy=i;
      	dane.napisy=new string[dane.dlugosc_tablicy];
      	for(i=0;plik.eof()!=true;i++){
			plik >> dane.napisy[i];
      	}
    plik.close();
	return true;
	}
	else{
     	 cerr<<"Dostep do pliku z danymi niepowiodl sie. Probowano otworzyc plik "<<nazwa<<endl;
     	plik.close();
    	return false;
  	}
}

/*!
\brief Metoda pobierz_int

Pobiera wartosci ze standardowego wejscia i sprawdza czy jest to liczba int
\return Jesli wpisano wartosc int to jest ona zwracana przez funkcje. Jesli nie wyswietlany jest odpowieni komunikat i czynnosci sa powtarzane.
*/
int Komunikacja::pobierz_int(){
	const char * wskaznik;
	int rozmiar,i;
	bool blad=true;
	string napis;
	while(blad==true){
		blad=false;
		cin>>napis;
		wskaznik=napis.data();
		rozmiar=napis.size();
		for(i=0;i<rozmiar;i++){
			if(!isdigit(*(wskaznik+i))&&blad==false){
				cerr<<"Wpisane znaki nie sa liczba."<<endl<<"Wpisz liczbe jeszcze raz."<<endl<<endl;
				blad=true;
			}
		}
		istringstream liczba(napis);
		liczba >> i;
		if((i>255||i<0)&&blad==false){
			cerr<<"Wpisana liczba nie jest int (0-255)."<<endl<<"Wpisz liczbe jeszcze raz."<<endl<<endl;
			blad=true;
		}
		cin.clear();
	}
	return i;
}


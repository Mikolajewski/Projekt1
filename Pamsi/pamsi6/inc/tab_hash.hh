/*!
\file
\brief Plik zawierajacy klase Tablica_hash.

*/
#ifndef TABLICA_HASH
#define TABLICA_HASH
#include <cmath>
#include <typeinfo>
#include "konfiguracja.hh"

/*!
\brief Klasa Tablica_hash

Klasa tworzaca tablice z hashowanie i wykonujaca na niej czynnosci zwiazane z zapisem i odczytem.
*/
template<class typ,class klucz,class dana>
class Tablica_hash{
/*!
\brief tablica

Tablica wskaznikow na pocz¹tki list elementow. Elementy zawieraja klucz i dane. 
*/
		typ** tablica;
/*!
\brief funkcja_hash

Metoda wykonujaca przydzielenie odpowiedniej komorki tablicy dla danego elementu
*/
		int funkcja_hash(klucz haslo);
/*!
\brief Zmienna ilosc_elementow

Zmienna przechowuj¹ca informacje o ilosci wpisanych elementow do struktury.
*/
		int ilosc_elementow;
	public:
/*!
\brief Metoda dodaj

Metoda dodaj¹ca element na odpowiednie miejsce w tabeli/liscie. Jesli element jest dodawany na liscie to umieszcza sie go w sposob posortowany.
*/
		void dodaj(klucz haslo,dana wartosc);
/*!
\brief Metoda pobierz

Metoda znajdujaca zadany element. 
\return Zwraca true jesli znaleziono element i false jesli nie uda³o sie znalezc elementu.
*/
		bool pobierz(klucz haslo);
/*!
\brief Konstruktor tablicy z hashowaniem

*/
		Tablica_hash<typ,klucz,dana>(){ilosc_elementow=0;tablica=new typ*[17576];for(int i=0;i<17576;tablica[i]=NULL,i++);};

/*!
\brief Metoda zlicz

\return Metoda zwraca ilosc elementow wpisanych do struktury.
*/
		int zlicz_elementy();
};

template<class typ,class klucz,class dana>
int Tablica_hash<typ,klucz,dana>::funkcja_hash(klucz haslo){
	int komorka=0;
	int i;
	char* haslo_tab=(char*)haslo.c_str();                                      //tylko string
	for(i=0;i<haslo.size()&&i<ILOSC_SPRAWDZANYCH_ZNAKOW;i++){
		komorka+=pow(ILOSC_MOZLIWYCH_ZNAKOW,i)*((int)haslo[i]-(int)PIERWSZY_ZNAK);
	}
//	cout<<"Dla klucza: "<<haslo<<" przydzielono wartosc: "<<komorka<<endl;
	return komorka;
}


template<class typ,class klucz,class dana>
void Tablica_hash<typ,klucz,dana>::dodaj(klucz haslo,dana wartosc){
	typ* pomocnicza;
	typ* wskaznik;
	typ* element=new typ[1];
	typ* ojciec;
	int numer_na_liscie=1;
	int komorka;
//	cout<<"Dodaje element"<<endl;
	element->wpisz_klucz(haslo);
	element->wpisz_wartosc(wartosc);
	komorka=funkcja_hash(haslo);
	ilosc_elementow++;
	if(tablica[komorka]!=NULL){
		pomocnicza=tablica[komorka];
		numer_na_liscie++;
		while(pomocnicza->zwroc_klucz()<=haslo&&pomocnicza->zwroc_wskaznik()!=NULL){      //szukanie miejsca w liscie do ktorego wpisac element
			pomocnicza=pomocnicza->zwroc_wskaznik();         
			numer_na_liscie++;
		}
		if(pomocnicza->zwroc_wskaznik()==NULL&&pomocnicza->zwroc_klucz()<=haslo){							//jesli jest to koniec listy
			pomocnicza->wpisz_wskaznik(element);
			element->wpisz_ojciec(pomocnicza);
			element->wpisz_wskaznik(NULL);
		}
		else{
			element->wpisz_wskaznik(pomocnicza);
			if(pomocnicza->zwroc_ojciec()!=NULL){                                             //jesli istnieje ojciec
				ojciec=pomocnicza->zwroc_ojciec();
				pomocnicza->wpisz_ojciec(element);
				ojciec->wpisz_wskaznik(element);
				element->wpisz_ojciec(ojciec);
			}
			else{																			  //jesli ojciec nie istnieje (wpisywanie na poczatek listy)
//				cout<<"nie ma ojca"<<endl;
				element->wpisz_ojciec(NULL);
				pomocnicza->wpisz_ojciec(element);
				tablica[komorka]=element;	
			}
		}
//		pomocnicza=tablica[komorka];
//		numer_na_liscie=1;
//		while(pomocnicza!=NULL){
//			cout<<"Wpisano element: "<<pomocnicza->zwroc_klucz()<<" "<<pomocnicza->zwroc_wartosc()<<" Numer na liscie: "<<numer_na_liscie<<endl;
//			numer_na_liscie++;
//			pomocnicza=pomocnicza->zwroc_wskaznik();
//		}
	}
	else{	
		element->wpisz_wskaznik(NULL);
		element->wpisz_ojciec(NULL);
		tablica[komorka]=element;
//		cout<<"Wpisano "<<ilosc_elementow<<" element: "<<tablica[komorka]->zwroc_klucz()<<" "<<tablica[komorka]->zwroc_wartosc()<<endl;  
	}
}


template<class typ,class klucz,class dana>
bool Tablica_hash<typ,klucz,dana>::pobierz(klucz haslo){
	typ* pomocnicza;
	int komorka;
	int numer_na_liscie=0;
	komorka=funkcja_hash(haslo);
	if(tablica[komorka]==NULL){
		return false;
	} 
	pomocnicza=tablica[komorka];
	while(pomocnicza!=NULL&&pomocnicza->zwroc_klucz()<haslo){
		numer_na_liscie++;
		pomocnicza=pomocnicza->zwroc_wskaznik();
	}
	while(pomocnicza!=NULL&&pomocnicza->zwroc_klucz()==haslo){
		numer_na_liscie++;
//		cout<<"Klucz: "<<pomocnicza->zwroc_klucz()<<" Wartosc: "<<pomocnicza->zwroc_wartosc()<<" Numer na liscie: "<<numer_na_liscie<<endl;
		pomocnicza=pomocnicza->zwroc_wskaznik();
	}
	return true;
}

template<class typ,class klucz,class dana>
int Tablica_hash<typ,klucz,dana>::zlicz_elementy(){
	return ilosc_elementow;
}
#endif

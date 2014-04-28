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

Metoda dodajaca element na odpowiednie miejsce w tabeli/liscie. Jesli element jest dodawany na liscie to umieszcza sie go w sposob posortowany.
*/
		bool dodaj(klucz haslo,klucz haslo2,dana wartosc);
/*!
\brief Metoda pobierz

Metoda znajdujaca zadany element. 
\return Zwraca true jesli znaleziono element i false jesli nie uda³o sie znalezc elementu.
*/
		bool pobierz(klucz haslo);

/*!
\brief Metoda pobierz

Metoda znajdujaca zadany element. 
\return Zwraca element na liscie jesli taki istniej. Jesli nie to zwraca NULL.
*/		
		typ* zwroc_element(klucz haslo);
/*!
\brief Konstruktor tablicy z hashowaniem

*/
		Tablica_hash<typ,klucz,dana>(){ilosc_elementow=0;tablica=new typ*[17576];for(int i=0;i<17576;tablica[i]=NULL,i++);};

/*!
\brief Metoda zlicz

\return Metoda zwraca ilosc elementow wpisanych do struktury.
*/
		int zlicz_elementy();

/*!
\brief usun_element

Metoda usuwajaca element, o zadanych kluczach.
*/		
		bool usun_element(klucz haslo,klucz haslo2);
		
/*!
\brief usun_klucz

Metoda usuwajaca wszystkie elementy o zadanym kluczu.
*/		
		bool usun_klucz(klucz haslo);
		
/*!
\brief nastepny

Metoda zwracajaca wskaznik do nastepnego w tablicy z hashowanie elementu o tym samym kluczu.
*/		
		typ* nastepny(typ* element);

/*!
\brief wypisz

Metoda wypisujaca cala tablice z hashowanie.
*/
		void wypisz();
};

template<class typ,class klucz,class dana>
int Tablica_hash<typ,klucz,dana>::funkcja_hash(klucz haslo){
	int komorka=0;
	int i;
	char* haslo_tab=(char*)haslo.c_str();                                      
	for(i=0;i<haslo.size()&&i<ILOSC_SPRAWDZANYCH_ZNAKOW;i++){
		komorka+=pow(ILOSC_MOZLIWYCH_ZNAKOW,i)*((int)haslo[i]-(int)PIERWSZY_ZNAK);
	}
	return komorka;
}


template<class typ,class klucz,class dana>
bool Tablica_hash<typ,klucz,dana>::dodaj(klucz haslo,klucz haslo2,dana wartosc){
	typ* pomocnicza;
	typ* wskaznik;
	typ* element=new typ[1];
	typ* ojciec;
	int numer_na_liscie=1;
	int komorka;
	element->wpisz_klucz(haslo);
	element->wpisz_klucz2(haslo2);
	element->wpisz_wage(wartosc);
	komorka=funkcja_hash(haslo);
	ilosc_elementow++;
	if(tablica[komorka]!=NULL){
		pomocnicza=tablica[komorka];
		numer_na_liscie++;
		while(pomocnicza->zwroc_klucz()<haslo&&pomocnicza->zwroc_wskaznik()!=NULL){      //szukanie miejsca w liscie do ktorego wpisac element
			pomocnicza=pomocnicza->zwroc_wskaznik();         
			numer_na_liscie++;
		}
#if TYP == GRAF
		while(pomocnicza->zwroc_klucz()==haslo&&pomocnicza->zwroc_wskaznik()!=NULL&&pomocnicza->zwroc_klucz2()<haslo2){     //dodatkowe wyszukiwanie jesli sa dwa hasla
			pomocnicza=pomocnicza->zwroc_wskaznik();         
			numer_na_liscie++;
		}
		if(pomocnicza!=NULL&&pomocnicza->zwroc_klucz()==haslo&&pomocnicza->zwroc_klucz2()==haslo2){
			pomocnicza->wpisz_wage(wartosc);
			ilosc_elementow--;
			return false;
		}
		if(pomocnicza->zwroc_klucz()!=haslo){
#endif
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
					element->wpisz_ojciec(NULL);
					pomocnicza->wpisz_ojciec(element);
					tablica[komorka]=element;	
				}
			}
#if TYP == GRAF
		}
		else{
			if(pomocnicza->zwroc_wskaznik()==NULL&&pomocnicza->zwroc_klucz2()<=haslo2){							//jesli jest to koniec listy
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
					element->wpisz_ojciec(NULL);
					pomocnicza->wpisz_ojciec(element);
					tablica[komorka]=element;	
				}
			}			
		}
#endif
	}
	else{	
		element->wpisz_wskaznik(NULL);
		element->wpisz_ojciec(NULL);
		tablica[komorka]=element; 
	}
	return true;
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
		pomocnicza=pomocnicza->zwroc_wskaznik();
	}
	return true;
}

template<class typ,class klucz,class dana>
typ* Tablica_hash<typ,klucz,dana>::zwroc_element(klucz haslo){
	typ* pomocnicza;
	int komorka;
	komorka=funkcja_hash(haslo);
	if(tablica[komorka]==NULL){
		return NULL;
	} 
	pomocnicza=tablica[komorka];
	while(pomocnicza!=NULL&&pomocnicza->zwroc_klucz()<haslo){
		pomocnicza=pomocnicza->zwroc_wskaznik();
	}
	if(pomocnicza!=NULL&&pomocnicza->zwroc_klucz()==haslo){
		return pomocnicza;
	}
	return NULL;
}

template<class typ,class klucz,class dana>
int Tablica_hash<typ,klucz,dana>::zlicz_elementy(){
	return ilosc_elementow;
}

template<class typ,class klucz,class dana>
typ* Tablica_hash<typ,klucz,dana>::nastepny(typ* element){
	if(element->zwroc_wskaznik()!=NULL && element->zwroc_klucz()==element->zwroc_wskaznik()->zwroc_klucz()){
		return element->zwroc_wskaznik();
	}
	return NULL;
}

template<class typ,class klucz,class dana>
bool Tablica_hash<typ,klucz,dana>::usun_klucz(klucz haslo){
	typ* pomocnicza=zwroc_element(haslo);
	if(pomocnicza==NULL){
		cerr<<"Nie znaleziono klucza "<<haslo<<endl;
		return false;
	}
	while(pomocnicza!=NULL){
		usun_element(pomocnicza->zwroc_klucz(),pomocnicza->zwroc_wartosc());
		pomocnicza=zwroc_element(haslo);
	}
	return true;
}

template<class typ,class klucz,class dana>
bool Tablica_hash<typ,klucz,dana>::usun_element(klucz haslo,klucz haslo2){
	typ* pomocnicza;
	typ* nastepny_element;
	typ* poprzedni_element;
	int komorka=funkcja_hash(haslo);
	pomocnicza=zwroc_element(haslo);
	ilosc_elementow--;
	while(pomocnicza!=NULL&&pomocnicza->zwroc_klucz2()!=haslo2){
		pomocnicza=nastepny(pomocnicza);
	}
	if(pomocnicza==NULL){
		cerr<<"Nie ma elementu o hasle: "<<haslo<<" i drugim hasle: "<<haslo2<<endl;
		return false;
	}
	else{                               										   //usuwanie elementu
		cout<<"Probuje usunac element o hasle: "<<pomocnicza->zwroc_klucz()<<" i wartosci: "<<pomocnicza->zwroc_klucz2()<<endl;
		nastepny_element=pomocnicza->zwroc_wskaznik();
		poprzedni_element=pomocnicza->zwroc_ojciec();
		if(poprzedni_element!=NULL){
			poprzedni_element->wpisz_wskaznik(nastepny_element);
		}
		else{
//			delete tablica[komorka];												//<--tutaj
			tablica[komorka]=nastepny_element;	
		}	
		if(nastepny_element!=NULL){
			nastepny_element->wpisz_ojciec(poprzedni_element);
		}
//		delete pomocnicza;															//<--tutaj
		return true;
	}
}

template<class typ,class klucz,class dana>
void Tablica_hash<typ,klucz,dana>::wypisz(){
	int i;
	typ* pomocnicza;
	for(i=0;i<ilosc_elementow;i++){
		if(tablica[i]!=NULL){
			cout<<"Wiersz: "<<i<<endl;
			pomocnicza=tablica[i];
			while(pomocnicza!=NULL){
				pomocnicza->wypisz();
				pomocnicza=pomocnicza->zwroc_wskaznik();
			}
			cout<<endl;
		}
	}
}

#endif

#ifndef LISTA
#define LISTA
#include "element.hh"
#include <iostream>

using namespace std;

enum sortowanie{posortowana,nieposortowana};

template<sortowanie rodzaj_sortowania,class typ,class waga>
class Lista{
/*!
\brief Wskaznik lista

Wskaznik na poczatek listy elementow przechowywanych wraz z wagami
*/
	Element <waga,typ> *lista;

/*!
\brief Zmienna dlugosc_listy

Zmienna zawierajaca informacje o ilosci elementow znajdujacych sie w liscie.
*/
	int dlugosc_listy;
	public:
/*!
\brief Metoda dodaj

Metoda dodajaca element z waga do listy.
*/
		void dodaj(typ* element,waga wartosc);
		
/*!
\brief Metoda znajdz

Metoda zwracajaca element znajdujacy sie na liscie (o ile takowy istnieje, w przeciwnym wypadku zwracane jest NULL). Wyszukiwanie odbywa sie po wadze.
*/
		typ* znajdz(waga wartosc);
		Element<waga,typ>* znajdz_element(waga wartosc);		
/*!
\brief Metoda usun

Metoda usuwajaca element o okreslonej wadze
*/
		bool usun(waga wartosc);
		
/*!
\brief Metoda zwroc

Metoda zwracajaca element znajdujacy sie na okreslonym miejscu w liscie. Jesli miejsce nie wystepuje w liscie zwracany jest odpowiedni komunikat i NULL.
*/
		typ* zwroc(int indeks);
		
/*!
\brief Metoda zwroc_dlugosc_listy

Metoda zwracajaca informacje o ilosci elementow znajdujacych sie na liscie
*/
		int zwroc_dlugosc_listy(){return dlugosc_listy;};
		
/*!
\brief Metoda wypisz

Metoda wypisujaca liste na stdout
*/
		void wypisz();
		
/*!
\brief Konstruktor listy

*/
		Lista<rodzaj_sortowania,typ,waga>(){lista=NULL;dlugosc_listy=0;};
};

template<sortowanie rodzaj_sortowania,class typ,class waga>
void Lista<rodzaj_sortowania,typ,waga>::dodaj(typ* element,waga wartosc){
	Element<waga,typ>* pomocnicza=NULL;
	Element<waga,typ>* ojciec;
	Element<waga,typ>* do_dodania=new Element<waga,typ>[1];
	
	do_dodania->wpisz_klucz(wartosc);
	do_dodania->wpisz_wartosc(element);				
	if(lista!=NULL){
		pomocnicza=lista;
	}
	if(pomocnicza==NULL){  
		do_dodania->wpisz_wskaznik(NULL);
		do_dodania->wpisz_ojciec(NULL);
		lista=do_dodania;
	}
	else{
		
		if(rodzaj_sortowania==posortowana){
			while(pomocnicza->zwroc_wskaznik()!=NULL && wartosc>pomocnicza->zwroc_klucz()){
				pomocnicza=pomocnicza->zwroc_wskaznik();
			}
			if(pomocnicza->zwroc_wskaznik()==NULL&&pomocnicza->zwroc_klucz()<=wartosc){  //wstawianie na koniec listy
				do_dodania->wpisz_wskaznik(NULL);
				do_dodania->wpisz_ojciec(pomocnicza); 
				pomocnicza->wpisz_wskaznik(do_dodania);
			}
			else{									//wstawianie w srodek         (pomocnicza jest "za" miejscem w które trzeba wstawic
					do_dodania->wpisz_wskaznik(pomocnicza);
					if(pomocnicza->zwroc_ojciec()!=NULL){                                             //jesli istnieje ojciec
						ojciec=pomocnicza->zwroc_ojciec();
						pomocnicza->wpisz_ojciec(do_dodania);
						ojciec->wpisz_wskaznik(do_dodania);
						do_dodania->wpisz_ojciec(ojciec);
					}
					else{																			  //jesli ojciec nie istnieje (wpisywanie na poczatek listy)
						do_dodania->wpisz_ojciec(NULL);
						pomocnicza->wpisz_ojciec(do_dodania);
						lista=do_dodania;	
					}
			}
		}
		
		else if(rodzaj_sortowania==nieposortowana){
			do_dodania->wpisz_wskaznik(pomocnicza);
			do_dodania->wpisz_ojciec(NULL);
			pomocnicza->wpisz_ojciec(do_dodania);
			lista=do_dodania;		
		}
	
	}
	dlugosc_listy++;
};

template<sortowanie rodzaj_sortowania,class typ,class waga>
typ* Lista<rodzaj_sortowania,typ,waga>::znajdz(waga wartosc){    
	Element<waga,typ>* pomocnicza=lista;
	if(rodzaj_sortowania==posortowana){
		while(pomocnicza!=NULL && pomocnicza->zwroc_wage()<wartosc){
			pomocnicza=pomocnicza->zwroc_wskaznik();
		}
		if(pomocnicza!=NULL && pomocnicza->zwroc_wage()==wartosc){	
			return pomocnicza->zwroc_wartosc();
		}
		else{
			return NULL;
		}
	}
	else if(rodzaj_sortowania==nieposortowana){
		while(pomocnicza!=NULL && pomocnicza->zwroc_wage()!=wartosc){
			
		}
		if(pomocnicza==NULL){
			return NULL;
		}
		else{
			return pomocnicza->zwroc_wartosc();
		}
	}
};

template<sortowanie rodzaj_sortowania,class typ,class waga>
Element<waga,typ>* Lista<rodzaj_sortowania,typ,waga>::znajdz_element(waga wartosc){    
	Element<waga,typ>* pomocnicza=lista;
	if(rodzaj_sortowania==posortowana){
		while(pomocnicza!=NULL && pomocnicza->zwroc_klucz()<wartosc){
			pomocnicza=pomocnicza->zwroc_wskaznik();
		}
		if(pomocnicza!=NULL && pomocnicza->zwroc_klucz()==wartosc){	
			return pomocnicza;
		}
		else{
			return NULL;
		}
	}
	else if(rodzaj_sortowania==nieposortowana){
		while(pomocnicza!=NULL && pomocnicza->zwroc_klucz()!=wartosc){
			
		}
		if(pomocnicza==NULL){
			return NULL;
		}
		else{
			return pomocnicza;
		}
	}
};

template<sortowanie rodzaj_sortowania,class typ,class waga>
bool Lista<rodzaj_sortowania,typ,waga>::usun(waga wartosc){
	Element<waga,typ>* pomocnicza=znajdz_element(wartosc);
	cout<<"usuwam z listy posortowanej"<<endl;
	if(pomocnicza!=NULL){
		if(pomocnicza->zwroc_wskaznik()!=NULL){
			pomocnicza->zwroc_wskaznik()->wpisz_ojciec(pomocnicza->zwroc_ojciec());	
		}
		if(pomocnicza->zwroc_ojciec()!=NULL){
			pomocnicza->zwroc_ojciec()->wpisz_wskaznik(pomocnicza->zwroc_wskaznik());
		}
		else if(pomocnicza->zwroc_wskaznik()!=NULL){				//usuwanie pierwszego wyrazu z listy n>1
			lista=pomocnicza->zwroc_wskaznik();
			pomocnicza->zwroc_wskaznik()->wpisz_ojciec(NULL);
		}
		else{														//usuwanie jedynego elementu
			lista=NULL;
		}
		delete pomocnicza;
		dlugosc_listy--;
		return true;
	}
	else
		return false;
	
};

template<sortowanie rodzaj_sortowania,class typ,class waga>
typ* Lista<rodzaj_sortowania,typ,waga>::zwroc(int indeks){
	int i;
	Element<waga,typ>* pomocnicza=lista;
	if(indeks<=dlugosc_listy){
		for(i=1;indeks!=i;i++){
			pomocnicza=pomocnicza->zwroc_wskaznik();
		}
		return pomocnicza->zwroc_wartosc();
	}
	else{
		cerr<<"Zly indeks w liscie."<<endl;
	}
}

template<sortowanie rodzaj_sortowania,class typ,class waga>
void Lista<rodzaj_sortowania,typ,waga>::wypisz(){
	int i;
	for(i=1;i<=dlugosc_listy;i++){
		zwroc(i)->wypisz();
	}
}

#endif

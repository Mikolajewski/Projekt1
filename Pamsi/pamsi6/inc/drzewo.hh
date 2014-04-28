/*!
\file
\brief Plik zawierajacy definicje i deklaracje klasy Drzewo.

*/

#ifndef DRZEWO
#define DRZEWO
#include <iostream>
#include <string>
#include "element.hh"
using namespace std;

/*!
\brief Klasa Drzewo

Klasa tworzaca strukture drzewa.
*/
template<class typ,class klucz,class wartosc>
class Drzewo{

/*!
\brief Zmienna korzen

Poczatek drzewa.
*/
		typ* korzen;
/*!
\brief Zmienna rozmiar

Zmienna zawierajaca informacje o ilosci elementow.
*/
		int rozmiar;
		
/*!
\brief Metoda znajdz

\param[in] haslo po ktorym odbywa sie szukanie elementu
Metoda znajdujaca element o podanym hasle.
\return Zwraca wskaznik do odpowiedniej struktury.
*/
		typ* znajdz(klucz haslo);
	public:
/*!
\brief Konstruktor Drzewa

Zeruje odpowiednie pola.
*/
		Drzewo<typ,klucz,wartosc>(){korzen=NULL;rozmiar=0;};
		
/*!
\brief Metoda dodaj

\param[in] haslo po ktorym odbywa sie szukanie elementu
\param[in] dana ktora zostaje wpisane do danego elementu
Dodaje dane na odpowiednie pole.
*/		
		void dodaj(klucz haslo,wartosc dana);
		
/*!
\brief Metoda usun

\param[in] haslo po ktorym odbywa sie szukanie elementu.
Usuwa wszystkie elementy o zadanym kluczu.
*/
		void usun(klucz haslo);

/*!
\brief Metoda pobierz 

\param[in] haslo po ktorym odbywa sie szukanie elementu.
Metoda wyswietlajaca dane o odepowienim lisci/polaczeniu drzewa. Szukanie odbywa siê po hasle.
*/		
		typ* pobierz(klucz haslo);
		
/*!
\brief Metoda is_epmty()

\return Metoda zwraca true, gdy drzewo jest puste i false, gdy w drzewie znajduje sie conajmniej jeden element.
*/
		bool is_empty();
		
/*!
\brief Metoda zlicz_elementy

Metoda podajaca ile elementow znajduje sie w drzewie.
*/
		int zlicz_elementy();
};



template<class typ,class klucz,class wartosc>
void Drzewo<typ,klucz,wartosc>::dodaj(klucz haslo,wartosc dana){
	typ* wskaznik;
	typ* obiekt;
	obiekt=new typ[1];
	obiekt->wpisz_klucz(haslo);
	obiekt->wpisz_wartosc(dana);
	
	if(korzen==NULL){
		korzen=obiekt;
	}
	else{
		wskaznik=znajdz(haslo);
		if(wskaznik->zwroc_klucz()==haslo){
			if(wskaznik->zwroc_wskaznik_prawy()!=NULL){
				obiekt->wpisz_wskaznik_prawy(wskaznik->zwroc_wskaznik_prawy());
				obiekt->zwroc_wskaznik_prawy()->wpisz_ojciec(obiekt);
				wskaznik->wpisz_wskaznik_prawy(obiekt);
				obiekt->zwroc_wskaznik_prawy()->wpisz_ojciec(wskaznik);
			}
			else{
				wskaznik->wpisz_wskaznik_prawy(obiekt);
				obiekt->wpisz_ojciec(wskaznik);
			}
		}
		if(wskaznik->zwroc_klucz()>haslo){
			wskaznik->wpisz_wskaznik_lewy(obiekt);
			wskaznik->zwroc_wskaznik_lewy()->wpisz_ojciec(wskaznik);
		}
		else{
			wskaznik->wpisz_wskaznik_prawy(obiekt);
			wskaznik->zwroc_wskaznik_prawy()->wpisz_ojciec(wskaznik);
		}
	}
	rozmiar++;
//	cout<<"Dodano element"<<endl<<"haslo: "<<obiekt->zwroc_klucz()<<"  wartosc: "<<obiekt->zwroc_wartosc()<<endl<<endl;
}


template<class typ,class klucz,class wartosc>
typ* Drzewo<typ,klucz,wartosc>::znajdz(klucz haslo){
	typ* wskaznik;
	int numer_elementu=rozmiar;
	bool znaleziono=false;
	wskaznik=korzen;
	while(1){
//		cout<<"wskaznik: "<<wskaznik<<"klucz: "<<wskaznik->zwroc_klucz()<<" lewy: "<<wskaznik->zwroc_wskaznik_lewy()<<" prawy: "<<wskaznik->zwroc_wskaznik_prawy()<<endl<<endl;	
		if(wskaznik->zwroc_klucz()>haslo){
			if(wskaznik->zwroc_wskaznik_lewy()==NULL){
				return wskaznik;
			}
			wskaznik=wskaznik->zwroc_wskaznik_lewy();
		}
		else if(wskaznik->zwroc_klucz()<haslo){
			if(wskaznik->zwroc_wskaznik_prawy()==NULL){
				return wskaznik;
			}
			wskaznik=wskaznik->zwroc_wskaznik_prawy();
		}
		else{
			return wskaznik;
		}
	}
}

template<class typ,class klucz,class wartosc>
void Drzewo<typ,klucz,wartosc>::usun(klucz haslo){
	typ* wskaznik;
	typ* wsk_pom;
	bool znaleziono=false;
	wskaznik=znajdz(haslo);
	if(wskaznik->zwroc_klucz()==haslo){
		while(wskaznik->zwroc_wskaznik_prawy()!=NULL){
			wskaznik->przepisz_dane(wskaznik->zwroc_wskaznik_prawy());
			wskaznik=wskaznik->zwroc_wskaznik_prawy();
		}
		wsk_pom=wskaznik;
		wskaznik=wskaznik->zwroc_ojciec();
		delete wsk_pom;
		rozmiar--;
		cout<<"Usunieto element."<<endl;
				
		if(wskaznik->zwroc_klucz()>haslo)
			wskaznik->wpisz_wskaznik_lewy(NULL);
		else
			wskaznik->wpisz_wskaznik_prawy(NULL);

		usun(haslo);
	}
	else{
		cout<<"Nie znaleziono wiecej elementow do usuniecia."<<endl;
	}	
}


template<class typ,class klucz,class wartosc>
typ* Drzewo<typ,klucz,wartosc>::pobierz(klucz haslo){
	typ* wskaznik;
	wskaznik=znajdz(haslo);
	
	if(wskaznik->zwroc_klucz()==haslo){
//		cout<<"Znaleziono nastepujace dane:"<<endl;
//		cout<<"Haslo: "<<wskaznik->zwroc_klucz()<<"  Dana: "<<wskaznik->zwroc_wartosc()<<endl;	
		while(wskaznik->zwroc_wskaznik_prawy()!=NULL && wskaznik->zwroc_wskaznik_prawy()->zwroc_klucz()==haslo){
//			cout<<"Haslo: "<<wskaznik->zwroc_wskaznik_prawy()->zwroc_klucz()<<"  Dana: "<<wskaznik->zwroc_wskaznik_prawy()->zwroc_wartosc()<<endl;
			wskaznik=wskaznik->zwroc_wskaznik_prawy();
		}
		return wskaznik;
	}
	else{
		cout<<"Nie znaleziono danej o zadanym kluczu. Szukano: "<<haslo<<endl;
		return NULL;	
	}
}


template<class typ,class klucz,class wartosc>
bool Drzewo<typ,klucz,wartosc>::is_empty(){
	return rozmiar==0?true:false;
}


template<class typ,class klucz,class wartosc>
int Drzewo<typ,klucz,wartosc>::zlicz_elementy(){
	return rozmiar;	
}
#endif

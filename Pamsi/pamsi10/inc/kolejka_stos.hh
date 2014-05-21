/*!
\file
\brief Plik zawierajacy deklaracje klasy Stos_lub_kolejka.

*/
#include <iostream>
#include "konfiguracja.hh"

using namespace std;


enum rodzaj_struktury {LIFO,FIFO};
/*!
\brief Klasa Stos_lub_kolejka.

Jest to klasa moga funkcjonowac jako kolejka lub stos w zaleznosci od sposobu wywolania.
*/
template <class typ, rodzaj_struktury struktura>
class Stos_lub_kolejka{
	private:
/*!
\brief Zmienna stos

Wskaznik do tablicy w ktorej przechowywane sa dane.
*/
		typ* stos;
	public:
/*!
\brief Zmienna ilosc_danych

Zmienna przechowujaca informacje o ilosci danych znajdujacych sie w tablicy
*/
		int ilosc_danych;
		
/*!
\brief Zmienna wielkosc tablicy

Zmienna okreslajaca wielkosc tablicy z danymi
*/
		int wielkosc_tablicy;
		
/*!
\brief Metoda is_empty

Metoda sprawdzajaca czy stos/kolejka jest pusty/a
*/
		bool is_empty();
/*!
\brief Metoda size

Metoda podajaca rozmiar stosu/kolejki
*/		
		int size();
/*!
\brief Metoda push

Metoda dodajaca element na stos/do kolejki
*/	
		void push(typ element);
	/*!
\brief Metoda pop

Metoda zdejmujaca element ze stosu/kolejki
*/	
		bool pop();
/*!
\brief Metoda wypisz

Metoda wypisujaca stos/kolejke
*/	
		void wypisz();

/*!
\brief Metoda front

Metoda zwracajaca element, ktory zostanie usuniety w pierwszej kolejnosci ze stosu lub kolejki.
*/		
		typ front();
/*!
\brief Konstruktor Stos_lub_kolejka

*/	
		Stos_lub_kolejka(){stos=NULL,ilosc_danych=0,wielkosc_tablicy=0;};
};

template <class typ, rodzaj_struktury struktura>
bool Stos_lub_kolejka <typ, struktura>::is_empty(){
	if(ilosc_danych>0){
//		cout<<"Stos nie jest pusty."<<endl;
		return false;
	}
	else{
//		cout<<"Stos jest pusty."<<endl;
		return true;
	}
}

template <class typ, rodzaj_struktury struktura>
int Stos_lub_kolejka <typ, struktura>::size(){
//	cout<<"Stos zawiera "<<ilosc_danych<<" danych."<<endl;
	return ilosc_danych;
}

template <class typ, rodzaj_struktury struktura>
void Stos_lub_kolejka <typ, struktura>::push(typ element){
	typ pomocnicza[ilosc_danych];
	int i;
	if(ilosc_danych==wielkosc_tablicy){
		for(i=0;i<ilosc_danych;i++){
			pomocnicza[i]=stos[i];
		}
		
//		delete stos;
		if(wielkosc_tablicy!=0)
			wielkosc_tablicy=wielkosc_tablicy*2;
		else
			wielkosc_tablicy=1;
		stos=new typ[wielkosc_tablicy];
		for(i=0;i<ilosc_danych;i++)
			stos[i]=pomocnicza[i];
	}
	ilosc_danych+=1;
	stos[ilosc_danych-1]=element;
}

template <class typ, rodzaj_struktury struktura>
bool Stos_lub_kolejka <typ, struktura>::pop(){
	typ pomocnicza[ilosc_danych-1];
	int i;
	if(is_empty()==false){
		ilosc_danych-=1;
		if(struktura==LIFO){							//implementacja dla stosu
			if(ilosc_danych<(int)wielkosc_tablicy/4){
				for(i=0;i<ilosc_danych;i++){
					pomocnicza[i]=stos[i];
				}	
//				delete stos;
				stos=new typ[ilosc_danych];
				for(i=0;i<ilosc_danych;i++){
					stos[i]=pomocnicza[i];
				}
				wielkosc_tablicy=ilosc_danych;
//				cout<<"Zmniejszono tablice stosu."<<endl;
			}
			else{
			}
			return true;
		}
		else{											//implementacja dla listy
			if(ilosc_danych<(int)wielkosc_tablicy/4){
				for(i=0;i<ilosc_danych;i++){
					pomocnicza[ilosc_danych-1-i]=stos[ilosc_danych-1-i];
				}	
				delete stos;
				stos=new typ[ilosc_danych];
				for(i=0;i<ilosc_danych;i++){
					stos[i]=pomocnicza[i];
				}
				wielkosc_tablicy=ilosc_danych;
//				cout<<"Zmniejszono kolejke."<<endl;
			}
			return true;	
		}
	}
	else{
		cerr<<"Struktura jest pusta."<<endl;
		return false;
	}
}

template <class typ, rodzaj_struktury struktura>
void Stos_lub_kolejka <typ, struktura>::wypisz(){
	int i;
	if(struktura!=LIFO){
		cout<<"Poczatek kolejki: ";
		for(i=ilosc_danych;i>0;i--){
//			cout<<stos[ilosc_danych-i]<<endl;
			stos[ilosc_danych-i]->wypisz();
		}
		cout<<"Koniec kolejki "<<endl;		
	}
	else{
		cout<<"Stos wyglada nastepujaco (od góry stosu):"<<endl;
		for(i=0;i<ilosc_danych;i++){
//			cout<<stos[ilosc_danych-1-i]<<" ";
			stos[ilosc_danych-i-1]->wypisz();
		}
		cout<<"Koniec stosu "<<endl;
	}
}


template <class typ, rodzaj_struktury struktura>
typ Stos_lub_kolejka<typ, struktura>::front(){
	if(!is_empty()){
		if(struktura==LIFO){
			return stos[ilosc_danych-1];
		}
		return stos[0];
	}
	return NULL;
}

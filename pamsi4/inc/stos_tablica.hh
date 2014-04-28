/*!
\file
\brief Plik zawierajacy deklaracje klasy Stos_lub_kolejka.

*/
#include <iostream>
#include "konfiguracja.hh"

using namespace std;

/*!
\brief Klasa Stos_lub_kolejka.

Jest to klasa mog¹ funkcjonowaæ jako kolejka lub stos w zaleznosci od sposobu wywolania.
*/
template <class typ, rodzaj_struktury struktura>
class Stos_lub_kolejka{
	private:
		typ* stos;
	public:
		int ilosc_danych;
		int wielkosc_tablicy;
		int poczatek_kolejki;
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
\brief Metoda wypisz_stos

Metoda wypisujaca stos/kolejke
*/	
		void wypisz_stos();
/*!
\brief Konstruktor Stos_lub_kolejka

*/	
		Stos_lub_kolejka(){stos=NULL,ilosc_danych=0,wielkosc_tablicy=0,poczatek_kolejki=0;};
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
	cout<<"Stos zawiera "<<ilosc_danych<<" danych."<<endl;
	return ilosc_danych;
}

template <class typ, rodzaj_struktury struktura>
void Stos_lub_kolejka <typ, struktura>::push(typ element){
	typ pomocnicza[ilosc_danych];
	int i;
#ifdef LEPSZY
	if(ilosc_danych==wielkosc_tablicy){
		for(i=0;i<ilosc_danych;i++){
			pomocnicza[i]=stos[i];
		}
	delete stos;
	if(wielkosc_tablicy!=0)
		wielkosc_tablicy=wielkosc_tablicy*2;
	else
		wielkosc_tablicy=1;
	stos=new typ[wielkosc_tablicy];
	for(i=0;i<ilosc_danych;i++)
		stos[i]=pomocnicza[i];
	}
#else	
	for(i=0;i<ilosc_danych;i++){
		pomocnicza[i]=stos[i];
	}
	delete stos;
	stos=new typ[ilosc_danych+1];
	for(i=0;i<ilosc_danych-1;i++)
		stos[i]=pomocnicza[i];
#endif
	ilosc_danych+=1;
	stos[ilosc_danych-1]=element;
}

template <class typ, rodzaj_struktury struktura>
bool Stos_lub_kolejka <typ, struktura>::pop(){
	typ pomocnicza[ilosc_danych-1];
	int i;
	if(is_empty()==false){
		ilosc_danych-=1;
		if(struktura==stosik){
#ifdef LEPSZY
			if(ilosc_danych<(int)wielkosc_tablicy/4){
				for(i=0;i<ilosc_danych;i++){
					pomocnicza[i]=stos[i];
				}	
				delete stos;
				stos=new typ[ilosc_danych];
				for(i=0;i<ilosc_danych;i++){
					stos[i]=pomocnicza[i];
				}
				wielkosc_tablicy=ilosc_danych;
//				cout<<"Zmniejszono tablice stosu."<<endl;
			}
			else{
				ilosc_danych-=1;
			}

#else
			delete stos[ilosc_danych];
#endif
			return true;
		}
		else{
			
#ifdef LEPSZY
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
#else
			for(i=1;i<ilosc_danych;i++){
				pomocnicza[i-1]=stos[i];	
			}
			delete stos;
			ilosc_danych-=1;
			stos=new typ[ilosc_danych];
			for(i=0;i<ilosc_danych;i++){
				stos[i]=pomocnicza[i];
			}
#endif
			return true;	
		}
	}
	else{
		cerr<<"Struktura jest pusta."<<endl;
		return false;
	}
}

template <class typ, rodzaj_struktury struktura>
void Stos_lub_kolejka <typ, struktura>::wypisz_stos(){
	int i;
	if(struktura==stosik){
		cout<<"Stos wyglada nastepujaco (od góry stosu):"<<endl;
	}
	else{
		cout<<"Kolejka (na gorze koniec)"<<endl;
	}
	for(i=0;i<ilosc_danych;i++){
		cout<<stos[ilosc_danych-1-i]<<endl;
	}
}


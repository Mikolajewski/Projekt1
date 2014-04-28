/*!
\file
\brief Plik zawierajacy klase Graf

*/

#ifndef GRAF
#define GRAF

#include <iostream>
#include <queue>
#include "element.hh"
#include "tab_hash.hh"

using namespace std;

/*!
\brief	Klasa Graf

Klasa zawierajaca strukture grafu. W sklad klasy wchodza metody wykonujace operacje na grafie m.in. przeszukania grafu. Graf jest oparty na tablicy z hashowaniem.
*/
template<class krawedz,class wierzcholek>
class Graf{
/*!
\brief graf

Glowna struktura klasy bedaca tablica hashujaca. To na niej wykonywane sa metody klasy graf.
*/
		Tablica_hash<krawedz,wierzcholek,int> graf;

/*!
\brief znajdz

Metoda znajdujaca zadany element w grafie. Wykorzystuje ona budowe grafu i wykonuje wyszukiwanie za pomoca wyszukiwania w tablicy hashujacej.
*/
		krawedz* znajdz(wierzcholek element);

/*!
\brief odwiedzonych

Zmienna w ktorej przechowywana jest liczba swiadczaca o ilosci odwiedzonych wierzcholkow podczas przeszukiwania.
*/
		int odwiedzonych;

/*!
\brief lista_fifo

Lista zawierajaca wierzcholki. Wykorzystywana jest do wykonywania przeszukiwania wszerz.
*/
		queue<wierzcholek> lista_fifo;



	public:

/*!
\brief czy_sasiad

Metoda sprawdzajaca czy dwa wybrane wierzcholki sa sasiadami.
*/
		bool czy_sasiad(wierzcholek pierwszy,wierzcholek drugi);
		
/*!
\brief sasiedztwo

Metoda wyswietlajaca wszystkich sasiadow zadanego wierzcholka.
*/
		krawedz* sasiedztwo(wierzcholek pole);
		
/*!
\brief dodaj_wierzcholek

Metoda dodajaca wierzcholek. Jest to metoda wymuszona przez zalozenia projektowe i malo uzyteczna w wypadku zastasowania listy krawedzi. Zakladane jest ze element graniczy sam ze soba.
*/
		void dodaj_wierzcholek(wierzcholek pole);

/*!
\brief	dodaj_krawedz

Metoda dodajaca krawedz wraz z waga. Tworzy ona polaczenia w obie strony pomiedzy elementami.
*/
		void dodaj_krawedz(wierzcholek pierwszy,wierzcholek drugi,int waga);
		
/*!
\brief usun_krawedz

Metoda usuwajaca zadana krawedz.
*/
		bool usun_krawedz(wierzcholek pierwszy,wierzcholek drugi);
		
/*!
\brief usun_wierzcholek

Metoda usuwajaca wyszystkie krawedzie "wychodzace" i "wchodzace" do wierzcholka.
*/
		bool usun_wierzcholek(wierzcholek pole);
		
/*!
\brief	depth_first_search

Metoda wykonujaca przeszukanie struktury. Wpisuje ona liczbe znalezionych elementow do pola odwiedzone co pozwala ocenic z iloma wierzcholkami jest polaczony dany element.
*/
		void depth_first_search(wierzcholek poczatek);

/*!
\brief	anty_depth_first_search

Metoda usuwajaca znaczniki powstale po wywolaniu funkcji depth_first_search. Zeruje ona rowniez pole odwiedzone w celu powtornego wykorzystania.
*/		
		void anty_depth_first_search(wierzcholek poczatek);
		
/*!
\brief breadth_first_search

Metoda wykonujaca przeszukanie wszerz. Wpisuje ona rowniez odleglosc od poczatkowego elementu do poszczegolnych pol.
*/
		void breadth_first_search(wierzcholek poczatek);
		
/*!
\brief Konstruktor grafu

Przeciazenie konstruktora wpisujace do pola odwiedzone wartosc 0.
*/
		Graf<krawedz,wierzcholek>(){odwiedzonych=0;};
		
/*!
\brief zwroc_odwiedzonych

Metoda zwracajaca ilosc odwiedzonych pol podczas przeszukiwania.
*/		
		int zwroc_odwiedzonych(){return odwiedzonych;};
		
/*!
\brief wypisz

Metoda wypisujaca strukture
*/		
		void wypisz();
	
/*!
\brief ilosc_krawedzi

Metoda wypisujaca ilosc krawedzi
*/	
		int ilosc_krawedzi();
};

template<class krawedz,class wierzcholek>
krawedz* Graf<krawedz,wierzcholek>::znajdz(wierzcholek element){
	return graf.zwroc_element(element);
}

template<class krawedz,class wierzcholek>
bool Graf<krawedz,wierzcholek>::czy_sasiad(wierzcholek pierwszy,wierzcholek drugi){
	krawedz* pomocnicza=graf.zwroc_element(pierwszy);
	if(pomocnicza==NULL){
		cout<<"Nie ma wierzcholka "<<pierwszy<<endl;
		return false;
	}	
	while(pomocnicza!=NULL){
		if(pomocnicza->zwroc_klucz2()==drugi){
			cout<<"Wierzcholki "<<pierwszy<<" i "<<drugi<<" sa sasiadami"<<endl;
			return true;
		}
		pomocnicza=graf.nastepny(pomocnicza);	
	}
	cout<<"Wierzcholki "<<pierwszy<<" i "<<drugi<<" nie sa sasiadami"<<endl;
	return false;
}

template<class krawedz,class wierzcholek>
 krawedz* Graf<krawedz,wierzcholek>::sasiedztwo(wierzcholek pole){
 	int i;
 	krawedz* pomocnicza=graf.zwroc_element(pole);
 	if(pomocnicza==NULL){
 		cout<<"Wierzcholek "<<pole<<" nie wystepuje w grafie."<<endl;
 		return NULL;
 	}
 	if(pomocnicza->zwroc_klucz2()==pole){
 		if(graf.nastepny(pomocnicza)==NULL){
	 		cout<<"Wierzcholek: "<<pole<<" nie ma sasiedztwa."<<endl;
 			return pomocnicza;
 		}
 	}
 	cout<<"Wierzcholek "<<pole<<" posiada sasiedztwo:"<<endl;
	while(pomocnicza!=NULL){
		if(pomocnicza->zwroc_klucz()!=pomocnicza->zwroc_klucz2()){
			cout<<pomocnicza->zwroc_klucz2()<<endl;
		}
		pomocnicza=graf.nastepny(pomocnicza);
	}
	return NULL;
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::dodaj_wierzcholek(wierzcholek pole){
	graf.dodaj(pole,pole);
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::dodaj_krawedz(wierzcholek pierwszy,wierzcholek drugi,int waga){
	if(graf.zwroc_element(pierwszy)!=NULL||pierwszy!=drugi){
		graf.dodaj(pierwszy,drugi,waga);
		graf.dodaj(drugi,pierwszy,waga);
	}
}

template<class krawedz,class wierzcholek>
bool Graf<krawedz,wierzcholek>::usun_krawedz(wierzcholek pierwszy,wierzcholek drugi){
	if(graf.usun_element(pierwszy,drugi)==true&&graf.usun_element(drugi,pierwszy)==true){
		return true;
	}
	else{
		cerr<<"Nie udalo sie usunac polaczenia "<<pierwszy<<"-"<<drugi<<endl;
		return false;
	}	
}

template<class krawedz,class wierzcholek>
bool Graf<krawedz,wierzcholek>::usun_wierzcholek(wierzcholek pole){
	krawedz* pomocnicza;
	pomocnicza=graf.zwroc_element(pole);
	if(pomocnicza!=NULL){
		while(pomocnicza!=NULL){
			usun_krawedz(pomocnicza->zwroc_klucz(),pomocnicza->zwroc_klucz2());
			pomocnicza=graf.nastepny(pomocnicza);
		}
		return true;
	}
	else{
		cerr<<"Wierzcholek "<<pole<<" nie istnieje."<<endl;
		return false;
	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::wypisz(){
	graf.wypisz();
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::depth_first_search(wierzcholek poczatek){
	krawedz* pomocnicza=graf.zwroc_element(poczatek);
//	krawedz* pierwszy=pomocnicza;
//	if(pomocnicza!=NULL){
		if(!pomocnicza->czy_odwiedzony()){
			pomocnicza->odwiedzony();
			odwiedzonych++;
//			cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<endl;
//			if(pomocnicza->zwroc_ojciec()!=NULL){
//				pomocnicza->wpisz_odleglosc(pierwszy->zwroc_ojciec()->zwroc_odleglosc()+1);
//				cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: "<<pomocnicza->zwroc_odleglosc()<<" ojciec: "<<pomocnicza->zwroc_ojciec()->zwroc_klucz()<<endl;
//			}
//			else{
//				cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: 0"<<endl;
//			}
			while(pomocnicza!=NULL){
				depth_first_search(pomocnicza->zwroc_klucz2());
				pomocnicza=graf.nastepny(pomocnicza);
			}
		}
//	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::anty_depth_first_search(wierzcholek poczatek){
	krawedz* pomocnicza=graf.zwroc_element(poczatek);
	if(pomocnicza!=NULL){
		if(pomocnicza->czy_odwiedzony()){
			pomocnicza->nie_odwiedzony();
			odwiedzonych--;
			cout<<"nie odwiedzam "<<pomocnicza->zwroc_klucz()<<endl;
			while(pomocnicza!=NULL){
				anty_depth_first_search(pomocnicza->zwroc_klucz2());
				pomocnicza=graf.nastepny(pomocnicza);
			}
		}
	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::breadth_first_search(wierzcholek poczatek){
	krawedz* pomocnicza=graf.zwroc_element(poczatek);
	krawedz* pierwszy=pomocnicza;
	wierzcholek nastepny;
	if(pomocnicza!=NULL){
		pomocnicza->odwiedzony();
		odwiedzonych++;
		if(pomocnicza->zwroc_ojciec()!=NULL){
			pomocnicza->wpisz_odleglosc(pierwszy->zwroc_ojciec()->zwroc_odleglosc()+1);
			cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: "<<pomocnicza->zwroc_odleglosc()<<" ojciec: "<<pomocnicza->zwroc_ojciec()->zwroc_klucz()<<endl;
		}
		else{
			cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: 0"<<endl;
		}
		if(!pomocnicza->czy_sasiedzi_odwiedzeni()){
			while(pomocnicza!=NULL){
				if(!graf.zwroc_element(pomocnicza->zwroc_klucz2())->czy_odwiedzony()){
					lista_fifo.push(pomocnicza->zwroc_klucz2());
					graf.zwroc_element(pomocnicza->zwroc_klucz2())->wpisz_ojciec(pierwszy);
				}
				pomocnicza=graf.nastepny(pomocnicza);
			}
		pierwszy->sasiedzi_odwiedzeni();
		}
		if(!lista_fifo.empty()){
			nastepny=lista_fifo.front();
			lista_fifo.pop();
			breadth_first_search(nastepny);
		}
	}
}

template<class krawedz,class wierzcholek>
int Graf<krawedz,wierzcholek>::ilosc_krawedzi(){
	return graf.zlicz_elementy();
}
#endif

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
#include "kolejka_stos.hh"
#include "lista_posortowana.hh"
#include "konfiguracja.hh"

using namespace std;

enum rodzaj_przeszukiwania{joj,best_first_search};

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
\brief Zmienna laczny_koszt_drogi

Zmienna przechowujaca informacje o koszcie jaki nalezy poniesc przemieszczajac sie pomiedzy punktami grafu.
*/
		int laczny_koszt_drogi;

/*!
\brief lista_fifo

Lista zawierajaca wierzcholki. Wykorzystywana jest do wykonywania przeszukiwania wszerz.
*/
		Stos_lub_kolejka<string,FIFO> lista_fifo;
		
/*!
\brief Struktura lista_lifo

Lista zawierajaca wierzcholki. Wykorzystywana jest do wykonywania best first search.
*/
		Stos_lub_kolejka<krawedz*,LIFO> lista_lifo;
		
/*!
\brief Lista 

Lista w ktorej zapisana jest droga.
*/
		Lista<nieposortowana,krawedz,int> droga;


		Lista<posortowana,krawedz,int> lista_priorytetowa;
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
\brief Metoda best_first_search

Metoda wykonujaca szukanie drogi pomiedzy dwoma wierzcholkami
*/
		bool best_first_search(wierzcholek poczatek, wierzcholek cel);
		bool best_first_search2(wierzcholek poczatek, wierzcholek cel);		
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
\brief Metoda wypisz_droge

Metoda wypisujaca droge pomiedzy dwoma punktami. Droga zostala wczesniej znaleziono podczas wykonywania innego algorytmu.
*/
		void wypisz_droge();
		
/*!
\brief Metoda zapisz_droge

Metoda zapisuja droge pomiedzy dwoma wierzcholkami. Metoda wykorzystywana w algorytmie best_first_search
*/		
		void zapisz_droge();
		void zapisz_droge(krawedz* koniec);		
/*!
\brief Metoda wypisz_parametry_drogi

Metoda wypisujaca laczny koszt drogi jak rowniez ilosc potrzebnych krokow. 
*/
		void wypisz_parametry_drogi();
	
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
int Graf<krawedz,wierzcholek>::ilosc_krawedzi(){
	return graf.zlicz_elementy();
}
#endif

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
//			cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: "<<pomocnicza->zwroc_odleglosc()<<" ojciec: "<<pomocnicza->zwroc_ojciec()->zwroc_klucz()<<endl;
		}
		else{
//			cout<<"odwiedzam "<<pomocnicza->zwroc_klucz()<<" odleglosc: 0"<<endl;
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
		if(!lista_fifo.is_empty()){
			nastepny=lista_fifo.front();
			lista_fifo.pop();
			breadth_first_search(nastepny);
		}
	}
}


template<class krawedz,class wierzcholek>
bool Graf<krawedz,wierzcholek>::best_first_search(wierzcholek poczatek,wierzcholek cel){
	krawedz* pomocnicza=graf.zwroc_element(poczatek);
	krawedz* wierzcholek_startowy=pomocnicza;
	wierzcholek nastepny;
	Lista<posortowana,krawedz,int> lista;
	int i;
	int waga_poprzedniej_krawedzi;
	wierzcholek nazwa_poprzedniego_wierzcholka;
	
	cout<<endl<<"Zaczynam best first search"<<endl;
	if(pomocnicza!=NULL){
		cout<<"Startuje z: ";
		pomocnicza->wypisz();
		cout<<"Szukam: "<<cel<<endl;
		if(!pomocnicza->czy_odwiedzony()){
			pomocnicza->odwiedzony();
			odwiedzonych++;
			

//------------------------wersja z uwzglednianiem wagi ostatniej sciezki---------------
#if UWZGLEDNIC_WAGE_OSTATNIEJ_SCIEZKI == Tak
			if(pomocnicza->zwroc_klucz()==cel){				//jesli element jest celem to zakoncz algorytm
				lista_lifo.push(pomocnicza);
				cout<<"Znalazlem droge do elementu: "<<cel<<endl;
				zapisz_droge();
				return true;
			}
#endif
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
			
			
			while(pomocnicza!=NULL){							//dodawania elementow do tymczasowej posortowanej listy
				lista.dodaj(pomocnicza,pomocnicza->zwroc_wage());

//------------------------wersja nie uwzgledniajaca wagi ostatniej sciezki--------------
#if UWZGLEDNIC_WAGE_OSTATNIEJ_SCIEZKI == Nie
				if(pomocnicza->zwroc_klucz2()==cel){				//jesli dodawany element jest celem to zakoncz algorytm
					lista_lifo.push(pomocnicza);
					lista_lifo.push(graf.zwroc_element(cel));
					cout<<"Znalazlem droge do elementu : "<<cel<<endl;
					zapisz_droge();
					return true;
				}
#endif 
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
				
//				graf.zwroc_element(pomocnicza->zwroc_klucz2())->wpisz_poprzedni(wierzcholek_startowy); //wpisanie do sasiada wezla-ojca
				pomocnicza=graf.nastepny(pomocnicza);
			}
			cout<<"stworzylem liste posortowana"<<endl;
			lista.wypisz();
			for(i=lista.zwroc_dlugosc_listy();i>=1;i--){			//dodawanie elementow do listy bedacej stosem metody
				lista_lifo.push(lista.zwroc(i));	
			}					
			nastepny=lista_lifo.front()->zwroc_klucz2();
			cout<<"przechodze do: "<<lista_lifo.front()->zwroc_klucz2()<<endl;
			best_first_search(nastepny,cel);
		}
		else{
			cout<<"Element byl juz odwiedzony."<<endl;
			lista_lifo.pop();
			if(lista_lifo.is_empty()){
				cout<<endl<<endl<<"Nie znaleziono drogi do elementu "<<cel<<endl;
			}
			else{
				nastepny=lista_lifo.front()->zwroc_klucz2();
				cout<<"przechodze do: "<<lista_lifo.front()->zwroc_klucz2()<<endl;
				best_first_search(nastepny,cel);
			}
		}
	}
	else{
		cerr<<"Nie ma w grafie takiego elementu."<<endl;
		return false;
	}
}



template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::zapisz_droge(){
	krawedz* pomocnicza=lista_lifo.front();
	wierzcholek poprzedni_wierzcholek;
	int i;
	int ilosc_elementow;
	
	for(i=1,ilosc_elementow=lista_lifo.size();pomocnicza!=NULL;i++){
	
		if(i!=1){
			while(pomocnicza!=NULL && poprzedni_wierzcholek==pomocnicza->zwroc_klucz()){
				lista_lifo.pop();
				pomocnicza=lista_lifo.front();
				i++;
			}
		}
		if(pomocnicza!=NULL){
			poprzedni_wierzcholek=pomocnicza->zwroc_klucz();
			droga.dodaj(pomocnicza,pomocnicza->zwroc_wage());
			pomocnicza=lista_lifo.front();
		}
		
	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::zapisz_droge(krawedz* koniec){
	krawedz* pomocnicza=koniec;
	int i;
	
	for(i=1;pomocnicza!=NULL;i++){
		droga.dodaj(pomocnicza,pomocnicza->zwroc_wage());
		pomocnicza=pomocnicza->zwroc_poprzedni();
	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::wypisz_droge(){
	krawedz* pomocnicza=droga.zwroc(1);
	int i;
	cout<<endl<<"Droga wyglada nastepujaco:"<<endl;
	for(i=2;i<=droga.zwroc_dlugosc_listy();i++){
		pomocnicza->wypisz();
		pomocnicza=droga.zwroc(i);
	}
}

template<class krawedz,class wierzcholek>
void Graf<krawedz,wierzcholek>::wypisz_parametry_drogi(){
	krawedz* pomocnicza=droga.zwroc(1);
	int i;
	int waga=0;
	for(i=1;i<droga.zwroc_dlugosc_listy();i++){
		pomocnicza=droga.zwroc(i);
		waga+=pomocnicza->zwroc_wage();
	}
	i--;
	cout<<"Koszt drogi to: "<<waga<<endl;
	cout<<"Zajmuje "<<i<<" krokow."<<endl;
}

template<class krawedz,class wierzcholek>
bool Graf<krawedz,wierzcholek>::best_first_search2(wierzcholek poczatek,wierzcholek cel){
	krawedz* pomocnicza=graf.zwroc_element(poczatek);
	krawedz* wierzcholek_startowy=pomocnicza;
	krawedz* ojciec;
	wierzcholek nastepny;
	Lista<posortowana,krawedz,int> lista;
	int i;
	int waga_krawedzi;
	bool dodano_krawedz=false;
	wierzcholek nazwa_poprzedniego_wierzcholka;
	
	cout<<endl<<"Zaczynam best first search"<<endl;
	
	if(pomocnicza!=NULL){
		cout<<"Startuje z: ";
		pomocnicza->wypisz();
		cout<<"Szukam: "<<cel<<endl;
		if(!pomocnicza->czy_odwiedzony()){
			pomocnicza->odwiedzony();
			odwiedzonych++;
			
			if(pomocnicza->zwroc_klucz()==cel){				//jesli element jest celem to zakoncz algorytm 			
				cout<<"Znalazlem droge do elementu: "<<cel<<endl;
				cout<<"Koszt drogi to: "<<pomocnicza->zwroc_odleglosc()<<endl;
				zapisz_droge(pomocnicza);
				return true;
			}
			while(pomocnicza!=NULL){															//dodawania elementow do listy priorytetowej
				pomocnicza->wpisz_odleglosc(wierzcholek_startowy->zwroc_odleglosc());				//wpisanie odleglosci do nastepnej krawedzi
				if(!graf.zwroc_element(pomocnicza->zwroc_klucz2())->czy_odwiedzony()){				//jesli punkt koncowy krawedzi nie zostal odwiedzony				
					lista_priorytetowa.dodaj(pomocnicza,pomocnicza->zwroc_wage()+pomocnicza->zwroc_odleglosc());	//to dodaj krawedz do listy
					dodano_krawedz=true;
				}
				pomocnicza=graf.nastepny(pomocnicza);												//przejdz do nastepnego sasiada
			}
			if(lista_priorytetowa.zwroc_dlugosc_listy()==0){
				cout<<"Nie znaleziono drogi pomiedzy zadanymi wierzcholkami."<<endl;
				return false;
			}
			lista_priorytetowa.wypisz();
			pomocnicza=lista_priorytetowa.zwroc(1);                    					    //pobranie krawedzi po ktorej odbedzie sie ruch
			if(pomocnicza==NULL){
				cout<<"Nie znaleziono drogi pomiedzy zadanymi wierzcholkami."<<endl;
				return false;
			}
			ojciec=pomocnicza;																	//zapisanie ojca
			waga_krawedzi=pomocnicza->zwroc_wage();												//pobranie wagi kroku ktory zostanie wykonany
			nastepny=lista_priorytetowa.zwroc(1)->zwroc_klucz2();								//  przejscie do
			pomocnicza=graf.zwroc_element(nastepny);											//  nastepnego wierzcholka
			pomocnicza->wpisz_odleglosc(ojciec->zwroc_wage()+ojciec->zwroc_odleglosc()); //aktualizowanie odleglosci od punktu startowego
			pomocnicza->wpisz_poprzedni(ojciec);												//wpisanie ojca
			cout<<"przechodze do: "<<lista_priorytetowa.zwroc(1)->zwroc_klucz2()<<endl;
//			if(dodano_krawedz==true){
				cout<<"usuwam: "<<(lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage()<<endl;
				lista_priorytetowa.usun((lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage());			//usuniecie polecenia skoku (pierwszego elementu)
//				lista_priorytetowa.wypisz();
//			}
			best_first_search2(nastepny,cel);
		}
		else{
			cout<<"Element byl juz odwiedzony."<<endl;
//			cout<<"usuwam: "<<(lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage()<<endl;
//			lista_priorytetowa.usun((lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage());			//usuniecie polecenia skoku (pierwszego elementu)
			pomocnicza=lista_priorytetowa.zwroc(1);                    					    //pobranie krawedzi po ktorej odbedzie sie ruch
			if(pomocnicza==NULL){
				cout<<"Nie znaleziono drogi pomiedzy zadanymi wierzcholkami."<<endl;
				return false;
			}
			ojciec=pomocnicza;																	//zapisanie ojca
			waga_krawedzi=pomocnicza->zwroc_wage();												//pobranie wagi kroku ktory zostanie wykonany
			nastepny=lista_priorytetowa.zwroc(1)->zwroc_klucz2();								//  przejscie do
			pomocnicza=graf.zwroc_element(nastepny);											//  nastepnego wierzcholka
			pomocnicza->wpisz_odleglosc(wierzcholek_startowy->zwroc_odleglosc()+waga_krawedzi); //aktualizowanie odleglosci od punktu startowego
			pomocnicza->wpisz_poprzedni(ojciec);												//wpisanie ojca
			cout<<"przechodze do: "<<lista_priorytetowa.zwroc(1)->zwroc_klucz2()<<endl;
			cout<<"usuwam: "<<(lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage()<<endl;
			lista_priorytetowa.usun((lista_priorytetowa.zwroc(1))->zwroc_odleglosc() + (lista_priorytetowa.zwroc(1))->zwroc_wage());			//usuniecie polecenia skoku (pierwszego elementu)
			best_first_search2(nastepny,cel);
		}
	}
	else{
		cerr<<"Nie ma w grafie takiego elementu."<<endl;
		return false;
	}
}



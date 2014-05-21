/*!
\file
\brief Plik zawierajacy definicje i deklaracje klasy Element.

*/

#ifndef ELEMENT
#define ELEMENT

/*!
\brief Klasa Element

Klasa przechowuje dane oraz klucze po ktorych odbywa sie szukanie danych. Klasa jest przystosowana do wokorzystania jako element grafu wiec zawiera wskazniki oraz metody potrzebne do polaczenia z innymi elementami.
*/
template<class klucz,class wartosc>
class Element{
/*!
\brief Zmienna _haslo

Jest to zmienna zawierajaca klucz po ktorym nalezy znalezc zmienna.
*/
		klucz _haslo;

/*!
\brief Zmienna _haslo2

Jest to zmienna zawierajaca klucz po ktorym opcjonalnie mozna znalezc zmienna. Wprzedstawianym algorytmie jest drugim kryterium wykorzystywanym w sortowaniu listy.
*/		
		klucz _haslo2;

/*!
\brief Zmienna _dana

Jest to zmienna zawierajaca wlasciwa dana
*/
		wartosc* _dana;

/*!
\brief _waga

Zmienna przechowujaca wage elementu.
*/
		int _waga;
		
/*!
\brief _odwiedzony

Zmienna przechowujaca informacji o tym czy dany element zostal odwiedzony.
*/
		bool _odwiedzony;
		
/*!
\brief _sasiedzi_odwiedzeni;

Zmienna przechowujaca informacji o tym czy sasiedzi danego elementu zostali odwiedzeni. Istotna podczas algorytmow przeszukiwan.
*/
		bool _sasiedzi_odwiedzeni;
		
/*!
\brief _odleglosc;

Dodatkowa zmienna mogaca przechowywac np.: odleglosc pomiedzy elementami.
*/
		int _odleglosc;
/*!
\brief Wskaznik ojciec

Wskazuje na strukture typu element. W grafie moze byc wykorzystany jako odnosnik do poprzedniego elementu.
*/
		Element* _ojciec;
/*!
\brief Wskaznik ojciec

Wskazuje na strukture typu element. W grafie moze byc wykorzystany jako odnosnik do nastepnego elementu.
*/
		Element* _wskaznik;

/*!
\brief Wskaznik _poprzedni
	
Wskazuje na poprzedni element z ktorego zostal wywolany omawiany element.
*/
		Element* _poprzedni;
	public:
/*!
\brief Konstruktor Element

Ustawia wskazniki na NULL.
*/
		Element <klucz,wartosc>(){_ojciec=NULL;_wskaznik=NULL;_odleglosc=0;_odwiedzony=false;_dana=NULL;};
		
/*!
\brief Metoda wpisz_wartosc

\param[in] dana 
Metoda wpisujaca wartosc do zmiennej zawierajacej dane elementu.
*/
		wartosc* wpisz_wartosc(wartosc* dana){_dana=dana;return dana;};
		
/*!
\brief Metoda wpisz_klucz

\param[in] haslo
Metoda wpisujaca klucz po ktorym mozna znalezc element.
*/
		void wpisz_klucz(klucz haslo){_haslo=haslo;};
		
/*!
\brief Metoda wpisz_klucz

\param[in] haslo2
Metoda wpisujaca klucz po ktorym mozna znalezc element.
*/
		void wpisz_klucz2(klucz haslo){_haslo2=haslo;};	

/*!
\brief wpisz_wage

Metoda wpisujaca wage do elementu.
*/	
		int wpisz_wage(int waga){_waga=waga;return _waga;};

/*!
\brief Metoda wpisz_ojciec

\param[in]wskaznik do odpowiedniej struktury.
Wpisuje wskaznik do struktury typu Element.
*/
		void wpisz_ojciec(Element<klucz,wartosc>* wskaznik){_ojciec=wskaznik;};
		
/*!
\brief wpisz_poprzedni
	
Metoda wpisujaca wskaznik na poprzedni element.
*/
		void wpisz_poprzedni(Element<klucz,wartosc>* wskaznik){_poprzedni=wskaznik;};

/*!
\brief zwroc_poprzedni
	
Metoda zwracajaca wskaznik do elementu z ktorego odwolano sie do omawianego elementu.
*/
		Element<klucz,wartosc>* zwroc_poprzedni(){return _poprzedni;};
/*!
\brief Metoda wpisz_wskaznik

\param[in]wskaznik do odpowiedniej struktury.
Wpisuje wskaznik do struktury typu Element.
*/
		void wpisz_wskaznik(Element<klucz,wartosc>* wskaznik){_wskaznik=wskaznik;};
		

/*!
\brief Metoda zwroc_wartosc

\return Metoda zwracajaca dana znajdujaca sie w strukturze Element.
*/
		wartosc* zwroc_wartosc(){return _dana;};

/*!
\brief Metoda zwroc_wage

Metoda zwracajaca wage danej krawedzi
*/
		int zwroc_wage(){return _waga;};
/*!
\brief Metoda zwroc_klucz

\return Metoda zwracajaca klucz po ktorym odbywa sie szukanie.
*/
		klucz zwroc_klucz(){return _haslo;};

/*!
\brief Metoda zwroc_klucz2

\return Metoda zwracajaca klucz2 po ktorym moze odbywac sie szukanie.
*/
		klucz zwroc_klucz2(){return _haslo2;};
		
		
/*!
\brief Metoda zwroc_wskaznik

\return Metoda zwracajaca wskaznik zawarty w strukturze Element.
*/
		Element* zwroc_wskaznik(){return _wskaznik;};		
				
/*!
\brief Metoda zwroc_ojciec

\return Metoda zwracajaca wskaznik zawarty w strukturze Element.
*/
		Element* zwroc_ojciec(){return _ojciec;};

/*!
\brief Metoda przepisz_dane

Metoda przepisujaca same dane bez zmiany wskaznikow.
*/
		void przepisz_dane(Element<klucz,wartosc>* wskaznik);
		
/*!
\brief Metoda wpisz_odleglosc
	
Metoda wpisujaca do klasy odleglosc od punktu poczatkowego.	
*/
		void wpisz_odleglosc(int odleglosc){_odleglosc=odleglosc;};
		
/*!
\brief Metoda zwroc_odleglosc

Metoda zwracajaca odleglosc od punktu poczatkowego
*/
		int zwroc_odleglosc(){return _odleglosc;};

/*!
\brief czy_odwiedzony

\return Metoda zwracajaca informacje o tym czy dany element zostal odwiedzony. (czy w polu odwiedzony znajduje sie wartosc true)
*/
		bool czy_odwiedzony(){return _odwiedzony;};
		
		
/*!
\brief odwiedzony

Metoda wpisujaca do zmiennej _odwiedzony wartosc true.
*/
		void odwiedzony(){_odwiedzony=true;};
		
		
/*!
\brief nie_odwiedzony

Metoda wpisujaca od zmiennej _odwiedzony wartosc false.
*/
		void nie_odwiedzony(){_odwiedzony=false;};
		
/*!
\brief sasiedzi_odwiedzeni

Metoda wpisujaca wartosc true do zmiennej sasiedzi_odwiedzeni.
*/		
		void sasiedzi_odwiedzeni(){_sasiedzi_odwiedzeni=true;};

/*!
\brief sasiedzi_nie_odwiedzeni

Metoda wpisujaca wartosc false do zmiennej sasiedzi_odwiedzeni.
*/	
		void sasiedzi_nie_odwiedzeni(){_sasiedzi_odwiedzeni=false;};

/*!
\brief sasiedzi_odwiedzeni

Metoda zwracajaca informacje czy sasiedzi elementu zostali odwiedzeni. (zwracana jest wartosc pola _sasiedzi_odwiedzeni)
*/
		bool czy_sasiedzi_odwiedzeni(){return _sasiedzi_odwiedzeni;};
		
/*!
\brief wypisz

Metoda wypisujaca element. Na std out zostaja wypisane klucze oraz waga.
*/
		void wypisz();
			
};


template<class klucz,class wartosc>
void Element<klucz,wartosc>::przepisz_dane(Element<klucz,wartosc>* wskaznik){
	if(wskaznik!=NULL){
		_haslo=wskaznik->zwroc_klucz();
		_haslo2=wskaznik->zwroc_klucz2();
		_dana=wskaznik->zwroc_wartosc();
	}
}

template<class klucz,class wartosc>
void Element<klucz,wartosc>::wypisz(){
	cout<<"Klucz: "<<zwroc_klucz()<<" Klucz2: "<<zwroc_klucz2()<<" Waga: "<<zwroc_wage()<<" Odleglosc: "<<_odleglosc;
//	if(zwroc_poprzedni()!=NULL){
//	cout<<" Ojciec: "<<zwroc_poprzedni()->zwroc_klucz();
//	}
	cout<<endl;
}
#endif

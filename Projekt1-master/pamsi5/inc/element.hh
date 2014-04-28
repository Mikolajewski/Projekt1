/*!
\file
\brief Plik zawierajacy definicje i deklaracje klasy Element.

*/

#ifndef ELEMENT
#define ELEMENT

/*!
\brief Klasa Element

Klasa przechowuje dane oraz klucze po ktorych odbywa sie szukanie danych. Klasa jest przystosowana do wokorzystania jako element drzewa wiec zawiera wskazniki oraz metody potrzebne do polaczenia z dwoma (trzema) innymi elementami.
*/
template<class klucz,class wartosc>
class Element{
/*!
\brief Zmienna _haslo

Jest to zmienna zawierajaca klucz po ktorym nalezy znalezc zmienna.
*/
		klucz _haslo;
/*!
\brief Zmienna _dana

Jest to zmienna zawierajaca wlasciwa dana
*/
		wartosc _dana;
		
/*!
\brief Wskaznik prawy

Wskazuje na strukture typu element. W drzewie moze byc wykorzystany jako odnosnik do nastepnej galezi.
*/
		Element* _wskaznik_prawy;
/*!
\brief Wskaznik lewy

Wskazuje na strukture typu element. W drzewie moze byc wykorzystany jako odnosnik do nastepnej galezi.
*/
		Element* _wskaznik_lewy;
/*!
\brief Wskaznik ojciec

Wskazuje na strukture typu element. W drzewie moze byc wykorzystany jako odnosnik do poprzedniej galezi.
*/
		Element* _ojciec;
	public:
/*!
\brief Konstruktor Element

Ustawia wskazniki na NULL.
*/
		Element <klucz,wartosc>(){_wskaznik_prawy=NULL;_wskaznik_lewy=NULL;_ojciec=NULL;};
		
/*!
\brief Destruktor Element

Wywoluje usuniecie obiektow na ktore wskazuja dwa ze wskaznikow.
*/
		~Element <klucz,wartosc>(){delete _wskaznik_lewy;_wskaznik_prawy;};
		
/*!
\brief Metoda wpisz_wartosc

\param[in] dana 
Metoda wpisujaca wartosc do zmiennej zawierajacej dane elementu.
*/
		wartosc wpisz_wartosc(wartosc dana);
		
/*!
\brief Metoda wpisz_klucz

\param[in] haslo
Metoda wpisujaca klucz po ktorym mozna znalezc element.
*/
		klucz wpisz_klucz(klucz haslo);

/*!
\brief Metoda wpisz_wskaznik_prawy

\param[in]wskaznik do odpowiedniej struktury.
Wpisuje wskaznik do struktury typu Element.
*/
		Element* wpisz_wskaznik_prawy(Element<klucz,wartosc>* wskaznik);

/*!
\brief Metoda wpisz_wskaznik_lewy

\param[in]wskaznik do odpowiedniej struktury.
Wpisuje wskaznik do struktury typu Element.
*/
		Element* wpisz_wskaznik_lewy(Element<klucz,wartosc>* wskaznik);

/*!
\brief Metoda wpisz_ojciec

\param[in]wskaznik do odpowiedniej struktury.
Wpisuje wskaznik do struktury typu Element.
*/
		Element* wpisz_ojciec(Element<klucz,wartosc>* wskaznik);

/*!
\brief Metoda zwroc_wartosc

\return Metoda zwracajaca dana znajdujaca sie w strukturze Element.
*/
		wartosc zwroc_wartosc(){return _dana;};
		
/*!
\brief Metoda zwroc_klucz

\return Metoda zwracajaca klucz po ktorym odbywa sie szukanie.
*/
		klucz zwroc_klucz(){return _haslo;};
		
/*!
\brief Metoda zwroc_wskaznik_prawy

\return Metoda zwracajaca wskaznik zawarty w strukturze Element.
*/
		Element* zwroc_wskaznik_prawy(){return _wskaznik_prawy;};
		
/*!
\brief Metoda zwroc_wskaznik_lewy

\return Metoda zwracajaca wskaznik zawarty w strukturze Element.
*/
		Element* zwroc_wskaznik_lewy(){return _wskaznik_lewy;};
		
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
};

template<class klucz,class wartosc>
wartosc Element<klucz,wartosc>::wpisz_wartosc(wartosc dana){
	_dana=dana;
	return dana;                  
}

template<class klucz,class wartosc>
klucz Element<klucz,wartosc>::wpisz_klucz(klucz haslo){
	cout<<"dodaje haslo"<<endl;
	_haslo=haslo;
	return haslo;
}

template<class klucz,class wartosc>
Element<klucz,wartosc>* Element<klucz,wartosc>::wpisz_wskaznik_prawy(Element<klucz,wartosc>* wskaznik){
	_wskaznik_prawy=wskaznik;
	return wskaznik;
}

template<class klucz,class wartosc>
Element<klucz,wartosc>* Element<klucz,wartosc>::wpisz_wskaznik_lewy(Element<klucz,wartosc>* wskaznik){
	_wskaznik_lewy=wskaznik;
	return wskaznik;
}

template<class klucz,class wartosc>
void Element<klucz,wartosc>::przepisz_dane(Element<klucz,wartosc>* wskaznik){
	if(wskaznik!=NULL){
		_haslo=wskaznik->zwroc_klucz();
		_dana=wskaznik->zwroc_wartosc();
	}
}

template<class klucz,class wartosc>
Element<klucz,wartosc>* Element<klucz,wartosc>::wpisz_ojciec(Element<klucz,wartosc>* wskaznik){
	_ojciec=wskaznik;
	return wskaznik;
}
#endif

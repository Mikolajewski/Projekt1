/*
 * pole.hh
 *
 *  Created on: May 25, 2014
 *      Author: Tomek
 */

	/*!
	\file
	\brief Plik zawierajacy klase Pole.

	*/

#ifndef POLE
#define POLE
#include <cmath>
#include <iostream>
#include "konfiguracja.hh"
#include "statek.hh"
using namespace std;

	/*!
	\brief Klasa Pole

	Klasa bedaca elementem klasy plansza. Zawiera ona metody przystosowane do obslugi przez klase nadrzedna.
	*/
class Pole{
	/*!
	\brief Zmienna _x

	Zmienna zawierajaca wspolrzedna x pola.
	*/
		int _x;

	/*!
	\brief Zmienna _y

	Zmienna zawierajaca wspolrzedna y pola.
	*/
		int _y;

		rodzaj_pola _rodzaj_terenu;
	/*!
	\brief Zmienna _odleglosc_od_poczatku

	Zmienna zawierajaca informacje o koszcie jaki nalezy poniesc przemieszczajac sie od punktu poczatkowego do pola
	*/
		int _odleglosc_od_poczatku;

	/*!
	\brief Zmienna _prognozowany_koszt

	Zmienna zawierajaca prognozowany koszt calej drogi
	*/
		int _prognozowany_koszt;

	/*!
	\brief Zmienna _poprzednie_pole

	Wskaznik na pole z ktorego odwolano sie do obecnego pola podczas wyszukiwania.
	*/
		Pole* _poprzednie_pole;

	/*!
	\brief Zmienna _dostepnosc

	Zmienna zawierajca informacje czy dane pole jest polem normalnym i mozna z niego korzystac, czy pole z ograniczonym dostepem.
	*/
		bool _dostepnosc;
		int _ile_razy_zablokowany;

		Statek* _jednostka;

	public:

	/*!
	\brief Konstruktor Pole()

	*/
		Pole(){_dostepnosc=true;_odleglosc_od_poczatku=0;_prognozowany_koszt=0;_poprzednie_pole=NULL;_x=0;_y=0;_rodzaj_terenu=nic;_jednostka=NULL;_ile_razy_zablokowany=0;};
		void oznacz_pole_jako_morze(){_rodzaj_terenu=nic;};
		void oznacz_pole_jako_lad(){_rodzaj_terenu=ziemia;};
//		void oznacz_pole_jako_statek(){_rodzaj_terenu=jednostka;};

		void oznacz_pole_jako_maszynownia_czarnego(){_rodzaj_terenu=maszynownia_zielonego;};
		void oznacz_pole_jako_maszynownia_czerwonego(){_rodzaj_terenu=maszynownia_fioletowego;};
		void oznacz_pole_jako_budynek(){_rodzaj_terenu=budynek;};
		void oznacz_pole_jako_statek_czarnego(){_rodzaj_terenu=jednostka_zielonego;};
		void oznacz_pole_jako_statek_czerwonego(){_rodzaj_terenu=jednostka_fioletowego;};
		rodzaj_pola zwroc_rodzaj_terenu(){return _rodzaj_terenu;};
		void wpisz_statek(Statek* jednostka){_jednostka=jednostka;};
		Statek* zwroc_statek(){return _jednostka;};
	/*!
	\brief Metoda wpisz_wspolrzedne

	Metoda wpisujaca wspolrzedne do pola.
	*/
		void wpisz_wspolrzedne(int x,int y){_x=x;_y=y;};

	/*!
	\brief Metoda zwroc_x

	Metoda zwracajaca wspolrzedna x.
	*/
		int zwroc_x(){return _x;};

	/*!
	\brief Metoda zwroc_y

	Metoda zwracajaca wspolrzedna y.
	*/
		int zwroc_y(){return _y;};

	/*!
	\brief Metoda wpisz_odleglosc_od_poczatku

	Metoda wpisujaca koszt jaki nalezy poniesc poruszajac sie od punktu startowego do omawianego pola
	*/
		void wpisz_odleglosc_od_poczatku(int odleglosc){_odleglosc_od_poczatku=odleglosc;};

	/*!
	\brief Metoda wpisz_prognozowany_koszt

	Metoda wpisujaca prognozowany koszt dotarcia do elementu koncowego.
	*/
		void wpisz_prognozowany_koszt(int odleglosc){_prognozowany_koszt=odleglosc;};

	/*!
	\brief Metoda zwroc_prognozowany_koszt

	Metoda zwracajaca koszt jaki nalezy najprawdopodobniej poniesc przemieszczajac sie od punktu startu do punktu docelowego przez omawiany punkt
	*/
		int zwroc_prognozowany_koszt(){return _prognozowany_koszt;};

	/*!
	\brief Metoda zwroc_odleglosc_od_poczatku

	Metoda zwracajaca koszt jaki nalezy poniesc przemieszczajac sie od punktu startowego do omawianego pola.
	*/
		int zwroc_odleglosc_od_poczatku(){return _odleglosc_od_poczatku;};
	/*!
	\brief Metoda zwroc_prognozowana_odleglosc_od

	Metoda zwracajaca przyblizona odleglosc pomiedzy polem, a celem.
	*/
		int zwroc_prognozowana_odleglosc_od(Pole* cel);

	/*!
	\brief Metoda wpisz_poprzednie_pole

	Metoda wpisujaca wskaznik do pola z ktorego nastepuje odwolanie do omawianego pola
	*/
		void wpisz_poprzednie_pole(Pole *komorka){_poprzednie_pole=komorka;};

	/*!
	\brief Metoda zwroc_poprzednie_pole

	Metoda zwracajaca wskaznik do pola z ktorego nastapilo odwolania do omawianego pola
	*/
		Pole* zwroc_poprzednie_pole(){return _poprzednie_pole;};

	/*!
	\brief Metoda udostepnij_pole

	Metoda zmieniajaca stan pola na dostepny.
	*/
		void udostepnij_pole(){_dostepnosc=true;};

	/*!
	\brief Metoda zablokuj_pole

	Metoda zmieniajaca stan pola na niedostepne.
	*/
		void zablokuj_pole(){_dostepnosc=false;_ile_razy_zablokowany++; _prognozowany_koszt=-1;};
		void odblokuj_pole(){_ile_razy_zablokowany==0?_ile_razy_zablokowany=0:_ile_razy_zablokowany--;_ile_razy_zablokowany>0?_dostepnosc=false: _dostepnosc=true;};
		int zwroc_ile_razy_zablokowany(){return _ile_razy_zablokowany;};
	/*!
	\brief Metoda zwroc_dostepnosc_pola

	Metoda zwracajaca informacje o stani pola.
	*/
		bool zwroc_dostepnosc_pola(){return _dostepnosc;};
	/*!
	\brief Metoda wyswietl

	Metoda wyswietlajaca wspolrzedne pola
	*/
		void wyswietl();
};


int Pole::zwroc_prognozowana_odleglosc_od(Pole* cel){
	int odleglosc;
	int x=cel->zwroc_x();
	int y=cel->zwroc_y();
	odleglosc=(abs(abs(x-_x)-abs(y-_y)))*KOSZT_RUCHU_O_POLE+fmin(abs(x-_x),abs(y-_y))*KOSZT_RUCHU_PO_SKOSIE;
	return odleglosc;
}

void Pole::wyswietl(){
	cout<<"x="<<_x<<" y="<<_y;
}
#endif

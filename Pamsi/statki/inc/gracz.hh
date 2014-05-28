/*
 * gracz.hh
 *
 *  Created on: May 25, 2014
 *      Author: Tomek
 */

#ifndef GRACZ
#define GRACZ
#include <iostream>
#include <cstdlib>
#include "konfiguracja.hh"
#include "pole.hh"
#include "lista_posortowana.hh"
#include "statek.hh"
using namespace std;

class Gracz{
		Lista<posortowana,Statek,string> lista_statkow;
		Pole** _plansza;
		void aktualizuj_widok_gracza(int x,int y);
		zawodnik _flaga;
	public:
		Pole** widok_gracza;
		void wpisz_gracza(zawodnik flaga){_flaga=flaga;};
		zawodnik zwroc_gracza(){return _flaga;};
		Pole** zwroc_widok_gracza(int x,int y);
		void przypisz_plansze_gracza(Pole** plansza){_plansza=plansza;};
		void dodaj_statek(Statek jednostka,int x,int y);
		Gracz(){_plansza=NULL;widok_gracza=NULL,_flaga=czerwony;;};
		void wprowadz_statek_na_plansze(rodzaj_statku rodzaj);
		bool wstaw_statek_na_zadana_pozycje(Statek*  jednostka,int x,int y);
};

bool Gracz::wstaw_statek_na_zadana_pozycje(Statek* jednostka,int x,int y){
	int kierunek_poludnie=1;
	int kierunek_wschod=1;
	switch(jednostka->zwroc_kierunek()){
		case zachod:
			kierunek_wschod=-1;
			kierunek_poludnie=0;
			break;
		case wschod:
				kierunek_wschod=1;
				kierunek_poludnie=0;
				break;
		case polnoc:
				kierunek_wschod=0;
				kierunek_poludnie=-1;
				break;
		case poludnie:
				kierunek_wschod=0;
				kierunek_poludnie=1;
				break;
	}
	for(int i=0;  i<jednostka->zwroc_ilosc_pol();i++){
		if(_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].zwroc_dostepnosc_pola()==false){
			return false;
		}
	}
	jednostka->wpisz_wspolrzedne(x,y);

	cout<<"wpisalem wspolrzedne"<<endl;
	lista_statkow.dodaj(jednostka,jednostka->zwroc_nazwe());
	_plansza[x][y].oznacz_pole_jako_maszynownia();
	for(int i=1;jednostka->zwroc_ilosc_pol()>i;i++){
		_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].oznacz_pole_jako_statek();
	}
	for(int i=0;jednostka->zwroc_ilosc_pol()>i;i++){
		_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].zablokuj_pole();
		if(x+i*kierunek_wschod!=0){
			_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie].zablokuj_pole();
			if(y+i*kierunek_poludnie!=0){
				_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie-1].zablokuj_pole();
			}
			if(y+i*kierunek_poludnie+1!=ROZMIAR_Y){
				_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie+1].zablokuj_pole();
			}
		}
		if(x+i*kierunek_wschod+1!=ROZMIAR_X){
			_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie].zablokuj_pole();
			if(y+i*kierunek_poludnie!=0){
				_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie-1].zablokuj_pole();
			}
			if(y+i*kierunek_poludnie+1!=ROZMIAR_Y){
				_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie+1].zablokuj_pole();
			}
		}
		if(y+i*kierunek_poludnie!=0){
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie-1].zablokuj_pole();
		}
		if(y+i*kierunek_poludnie+1!=ROZMIAR_Y){
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie+1].zablokuj_pole();
		}
	}
	cout<<"po wpisaniu statku"<<endl;
	return true;
}

//bool Gracz::przeszukaj_pola_w_odleglosci(int odleglosc,Pole* poczatek,cel_poszukiwan cel){
//	if(x)!=0){
//		_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie].zablokuj_pole();
//		if(y!=0){
//			_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie-1].zablokuj_pole();
//		}
//		if(y+1!=ROZMIAR_Y){
//			_plansza[x+i*kierunek_wschod-1][y+i*kierunek_poludnie+1].zablokuj_pole();
//		}
//	}
//	if(x+1!=ROZMIAR_X){
//		_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie].zablokuj_pole();
//		if(y!=0){
//			_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie-1].zablokuj_pole();
//		}
//		if(y+1!=ROZMIAR_Y){
//			_plansza[x+i*kierunek_wschod+1][y+i*kierunek_poludnie+1].zablokuj_pole();
//		}
//	}
//	if(y+i*kierunek_poludnie!=0){
//		_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie-1].zablokuj_pole();
//	}
//	if(y+i*kierunek_poludnie+1!=ROZMIAR_Y){
//		_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie+1].zablokuj_pole();
//	}
//}

void Gracz::wprowadz_statek_na_plansze(rodzaj_statku rodzaj){
	Statek*  jednostka=new Statek;
	int x=0,y=0;
	bool wstawiony=false;
	bool blad;
	cout<<"zaczynam"<<endl;
	jednostka->inicjalizuj_statek(_flaga,rodzaj,x,y);
	jednostka->wypisz_parametry_statku();
	cout<<"po inicjalizacji"<<endl;
	if(lista_statkow.zwroc_dlugosc_listy()==0){  //<--------------------
	cout<<"zaczynam wstawianie"<<endl;
		while(!wstawiony){
		cout<<"probuje"<<endl;
			x=rand()%(ROZMIAR_X/5);
			y=rand()%ROZMIAR_Y;
			blad=false;
			if(_flaga==czarny){
				x+=(ROZMIAR_X/5*4);
				for(int i=0; blad==false && i<jednostka->zwroc_ilosc_pol();i++){
					cout<<x-i<<" "<<y<<endl;
					if(_plansza[x-i][y].zwroc_dostepnosc_pola()==false){
						blad=true;
					}
				}
			}
			else{
				for(int i=0; blad==false && i<jednostka->zwroc_ilosc_pol();i++){
					cout<<x+i<<" "<<y<<endl;
					if(_plansza[x+i][y].zwroc_dostepnosc_pola()==false){
						blad=true;
					}
				}
			}
			if(blad==false){
				wstawiony=true;
			}
		}
		jednostka->wpisz_wspolrzedne(x,y);
		cout<<"wpisalem wspolrzedne"<<endl;
		lista_statkow.dodaj(jednostka,jednostka->zwroc_nazwe());
		_plansza[x][y].oznacz_pole_jako_maszynownia();
		for(int p=1;jednostka->zwroc_ilosc_pol()>p;p++){
			if(_flaga==czarny){
				_plansza[x-p][y].oznacz_pole_jako_statek();
			}
			else{
				_plansza[x+p][y].oznacz_pole_jako_statek();
			}
		}
		for(int i=-1;jednostka->zwroc_ilosc_pol()>=i;i++){
			if(x+i>=0 && x+i<ROZMIAR_X){
				_plansza[x+i][y].zablokuj_pole();
				if( y+1<ROZMIAR_Y){
					_plansza[x+i][y+1].zablokuj_pole();
				}
				if(y-1>=0){
					_plansza[x+i][y-1].zablokuj_pole();
				}
			}
		}
	}
	else{
		for(int i=2,znaleziono=false;znaleziono!=true;i++){
			for(int j=-1;znaleziono!=true && j<4;j++){
				cout<<"wstawiam drugi  wzgledem"<<endl;
				x=lista_statkow.zwroc(1)->zwroc_wspolrzedna_x();
				if(	lista_statkow.zwroc(1)->zwroc_wspolrzedna_y()+i<ROZMIAR_Y){
					y=	lista_statkow.zwroc(1)->zwroc_wspolrzedna_y()+i;
				}
				else{
					y=lista_statkow.zwroc(1)->zwroc_wspolrzedna_y()-i;
				}
				lista_statkow.zwroc(1)->wypisz_parametry_statku();
				if(j==-1){
					jednostka->wpisz_kierunek(lista_statkow.zwroc(1)->zwroc_kierunek());
				}
				else{
					jednostka->wpisz_kierunek((kierunek)j);
				}
				cout<<"wstawiany"<<endl;
				jednostka->wypisz_parametry_statku();
				znaleziono=wstaw_statek_na_zadana_pozycje(jednostka,x,y);
			}
		}
	}
	cout<<"po wpisaniu statku"<<endl;
}

Pole** Gracz::zwroc_widok_gracza(int x, int y){
	aktualizuj_widok_gracza(x,y);
	return widok_gracza; //<----koniecznosc_podania wspolrzednych w planszy (wszystkie 4 wierzcholki musza byc w planszy)
}

void Gracz::aktualizuj_widok_gracza(int x,int y){
	if(widok_gracza!=NULL){
		for (int i=0; i<ROZMIAR_EKRANU_X/SZEROKOSC_POLA; i++){
		   delete [] widok_gracza[i];
		}
	}
	widok_gracza=new Pole*[ROZMIAR_EKRANU_X/SZEROKOSC_POLA];
	for(int it=0; it<ROZMIAR_EKRANU_X/SZEROKOSC_POLA; it++){
	   widok_gracza[it] = new Pole[ROZMIAR_EKRANU_Y/SZEROKOSC_POLA];
	}
	for(int ix=0;ix<ROZMIAR_EKRANU_X/SZEROKOSC_POLA;ix++){
		for(int j=0;j<ROZMIAR_EKRANU_Y/SZEROKOSC_POLA;j++){
			widok_gracza[ix][j]=_plansza[ix+x][j+y];	//<--do zmiany przy mgle
		}
	}
}

#endif /* GRACZ_HH_ */

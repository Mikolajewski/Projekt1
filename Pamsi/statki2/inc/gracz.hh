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
#include "statek.hh"
#include "pole.hh"
#include "lista_posortowana.hh"
#include "plansza.hh"
using namespace std;

extern int wys_x,wys_y;
extern int klikniecie_x,klikniecie_y;
extern Plansza morze;
extern zdarzenie obsluga_zdarzen();

class Gracz{
		Lista<posortowana,Statek,string> lista_statkow;
		Lista<posortowana,Statek,string> statki_przeciwnika;
		Pole** _plansza;
		zawodnik _flaga;
		typ_gracza _typ;

		void aktualizuj_widok_gracza(int x,int y);
		void znajdz_przeciwnikow();
		int odleglosc_miedzy_statkami(Statek* pierwszy,Statek* drugi);

public:
		Pole** widok_gracza;
		void wpisz_kolor_gracza(zawodnik flaga){_flaga=flaga;};
		zawodnik zwroc_gracza(){return _flaga;};
		Pole** zwroc_widok_gracza(int x,int y);
		void przypisz_plansze_gracza(Pole** plansza){_plansza=plansza;};
		void dodaj_statek(Statek jednostka,int x,int y);
		Gracz(){_plansza=NULL;widok_gracza=NULL;_flaga=fioletowy;_typ=czlowiek;};
		void wprowadz_statek_na_plansze(rodzaj_statku rodzaj);
		bool wstaw_statek_na_zadana_pozycje(Statek*  jednostka,int x,int y);
		bool przesun_statek_na_zadana_pozycje(Statek*jednostka,int x,int y,kierunek zwrot);
		bool sprawdz_czy_mozna_wstawic(Statek* jednostka,int x,int y);
		bool sprawdz_czy_mozna_wstawic_w_jakiejs_pozycji(Statek* jednostka,int x,int y);
		void odblokuj_pola_morza(Statek* jednostka);
		void zablokuj_pola_morza(Statek* jednostka);
		void wpisz_rodzaj_gracza(typ_gracza rodzaj){_typ=rodzaj;};
		typ_gracza zwroc_rodzaj_gracza(){return _typ;};
		void wykonaj_ruch_statkow();
		void znajdz_swoich();
		void przygotuj_statki_do_ruchu();
		void zaznacz_pole_statku(int x, int y);
		bool sprawdz_czy_zaznaczone(int x,int y);
		bool strzel(Statek* jednostka, int x,int y);
		void odznacz_statki();
		bool sprobuj_usunac_statek(Statek* jednostka);
		bool sprawdz_czy_wygrales();
};


extern void wyswietl_gre(Gracz* zawodnik);

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

//	cout<<"wpisalem wspolrzedne"<<endl;
	if(lista_statkow.znajdz(jednostka->zwroc_nazwe())==NULL){
		lista_statkow.dodaj(jednostka,jednostka->zwroc_nazwe());
	}
	if(_flaga==zielony){
		_plansza[x][y].oznacz_pole_jako_maszynownia_czarnego();
	}
	else{
		_plansza[x][y].oznacz_pole_jako_maszynownia_czerwonego();
	}
	_plansza[x][y].wpisz_statek(jednostka);
	for(int i=1;jednostka->zwroc_ilosc_pol()>i;i++){
		_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].wpisz_statek(jednostka);
		if(_flaga==zielony){
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].oznacz_pole_jako_statek_czarnego();
		}
		else{
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].oznacz_pole_jako_statek_czerwonego();
		}
	}
	zablokuj_pola_morza(jednostka);
//	cout<<"po wpisaniu statku"<<endl;
	return true;
}


void Gracz::wprowadz_statek_na_plansze(rodzaj_statku rodzaj){
	Statek*  jednostka=new Statek;
	int x=0,y=0;
	bool wstawiony=false;
//	bool blad;
//	cout<<"zaczynam"<<endl;
	jednostka->inicjalizuj_statek(_flaga,rodzaj,x,y);
	jednostka->wyswietl();
//	cout<<"po inicjalizacji"<<endl;
	if(lista_statkow.zwroc_dlugosc_listy()==0){  //<--------------------
//		cout<<"zaczynam wstawianie"<<endl;
		while(!wstawiony){
//			cout<<"probuje"<<endl;
			x=rand()%(ROZMIAR_X/5);
			y=rand()%ROZMIAR_Y;
//			blad=false;
			if(_flaga==zielony){//<----------------------------------------
				x+=(ROZMIAR_X/5*4);
				jednostka->wpisz_kierunek(zachod);
				wstawiony=wstaw_statek_na_zadana_pozycje(jednostka,x,y);
			}
			else{
				jednostka->wpisz_kierunek(wschod);
				wstawiony=wstaw_statek_na_zadana_pozycje(jednostka,x,y);
			}
		}
	}
	else{
		y=	lista_statkow.zwroc(1)->zwroc_wspolrzedna_y();
		x=lista_statkow.zwroc(1)->zwroc_wspolrzedna_x();
		for(bool znaleziono=false;znaleziono!=true;){
//			for(int j=-1;znaleziono!=true && j<4;j++){
			for(int i=0;x>=ROZMIAR_X || x<0 || i==0;i++){
				if((i)%2==1){
					x+=-1+rand()%(int)(3);
				}
				else{
					x+=1-rand()%(int)(3);
				}
			}
			for(int i=0;y>=ROZMIAR_Y || y<0 || i==0;i++){
				if((i)%2==1){
					y+=-1+rand()%(int)(3);
				}
				else{
					y+=1-rand()%(int)(3);
				}
			}
			for(int j=-1;!znaleziono && j<4;j++){
				if(j==-1){
					jednostka->wpisz_kierunek(lista_statkow.zwroc(1)->zwroc_kierunek());
				}
				else{
					jednostka->wpisz_kierunek((kierunek)j);
				}
				if(sprawdz_czy_mozna_wstawic(jednostka,x,y)){
					znaleziono=wstaw_statek_na_zadana_pozycje(jednostka,x,y);
				}
			}
		}
	}
}

Pole** Gracz::zwroc_widok_gracza(int x, int y){
	aktualizuj_widok_gracza(x,y);
	return widok_gracza; //<----koniecznosc_podania wspolrzednych w planszy (wszystkie 4 wierzcholki musza byc w planszy)
}

void Gracz::aktualizuj_widok_gracza(int x,int y){
	if(widok_gracza==NULL){
//		cout<<"tworze tablice gracza"<<endl;
		widok_gracza=new Pole*[ROZMIAR_EKRANU_X/SZEROKOSC_POLA];
		for(int it=0; it<ROZMIAR_EKRANU_X/SZEROKOSC_POLA; it++){
		   widok_gracza[it] = new Pole[ROZMIAR_EKRANU_Y/SZEROKOSC_POLA];
		}
	}
	for(int ix=0;ix<ROZMIAR_EKRANU_X/SZEROKOSC_POLA;ix++){
		for(int j=0;j<ROZMIAR_EKRANU_Y/SZEROKOSC_POLA;j++){
			widok_gracza[ix][j]=_plansza[ix+x][j+y];	//<--do zmiany przy mgle
		}
	}
}

bool Gracz::przesun_statek_na_zadana_pozycje(Statek* jednostka,int nowy_x,int nowy_y,kierunek zwrot){
	int x,y;
	kierunek poczatkowy_kierunek=jednostka->zwroc_kierunek();
	bool wstawiony=false;
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

	odblokuj_pola_morza(jednostka);


	for(int i=-1;wstawiony==false && i<4;i++ ){
		if(!wstawiony && i!=-1){
			jednostka->wpisz_kierunek((kierunek)i);
		}
		else{
			jednostka->wpisz_kierunek(zwrot);
		}
		wstawiony=sprawdz_czy_mozna_wstawic(jednostka,nowy_x,nowy_y);
	}
	if(!wstawiony){
		jednostka->wpisz_kierunek(poczatkowy_kierunek);
		zablokuj_pola_morza(jednostka);
		return false;
	}
	x=jednostka->zwroc_wspolrzedna_x();
	y=jednostka->zwroc_wspolrzedna_y();

	//usuwanie statku
		for(int i=0;jednostka->zwroc_ilosc_pol()>i;i++){
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].odblokuj_pole();
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].oznacz_pole_jako_morze();
			_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].wpisz_statek(NULL);
	}
	wstaw_statek_na_zadana_pozycje(jednostka,nowy_x,nowy_y);
	jednostka->wpisz_wspolrzedne(nowy_x,nowy_y);
	return true;
}


//dodaje wszystkie statki
void Gracz::znajdz_przeciwnikow(){
	if(statki_przeciwnika.zwroc_dlugosc_listy()!=0){
		statki_przeciwnika.usun_wszystko();
	}
	for(int x=0;x<ROZMIAR_X;x++){
		for(int y=0;y<ROZMIAR_Y;y++){
			if(_plansza[x][y].zwroc_statek()!=NULL){
//				cout<<"msm cos"<<endl;
				if(_flaga==zielony){
					if(statki_przeciwnika.znajdz(_plansza[x][y].zwroc_statek()->zwroc_nazwe())==NULL  &&  _plansza[x][y].zwroc_rodzaj_terenu()==maszynownia_fioletowego){ //<------------
//						cout<<"znalazlem"<<x<<" "<<y<<endl;
						statki_przeciwnika.dodaj(_plansza[x][y].zwroc_statek(),_plansza[x][y].zwroc_statek()->zwroc_nazwe());
					}
				}
				else{
					if(statki_przeciwnika.znajdz(_plansza[x][y].zwroc_statek()->zwroc_nazwe())==NULL  &&  _plansza[x][y].zwroc_rodzaj_terenu()==maszynownia_zielonego){ //<------------
//						cout<<"znalazlem"<<x<<" "<<y<<endl;
						statki_przeciwnika.dodaj(_plansza[x][y].zwroc_statek(),_plansza[x][y].zwroc_statek()->zwroc_nazwe());
					}
				}
			}
		}
	}
}

//dodaje wszystkie statki
void Gracz::znajdz_swoich(){
	if(lista_statkow.zwroc_dlugosc_listy()!=0){
		lista_statkow.usun_wszystko();
	}
	for(int x=0;x<ROZMIAR_X;x++){
		for(int y=0;y<ROZMIAR_Y;y++){
			if(_plansza[x][y].zwroc_statek()!=NULL){
//				cout<<"msm cos"<<endl;
				if(_flaga==zielony){
					if(lista_statkow.znajdz(_plansza[x][y].zwroc_statek()->zwroc_nazwe())==NULL  &&  _plansza[x][y].zwroc_rodzaj_terenu()==maszynownia_zielonego){ //<------------
//						cout<<"znalazlem"<<x<<" "<<y<<endl;
						lista_statkow.dodaj(_plansza[x][y].zwroc_statek(),_plansza[x][y].zwroc_statek()->zwroc_nazwe());
					}
				}
				else{
					if(lista_statkow.znajdz(_plansza[x][y].zwroc_statek()->zwroc_nazwe())==NULL  &&  _plansza[x][y].zwroc_rodzaj_terenu()==maszynownia_fioletowego){ //<------------
//						cout<<"znalazlem"<<x<<" "<<y<<endl;
						lista_statkow.dodaj(_plansza[x][y].zwroc_statek(),_plansza[x][y].zwroc_statek()->zwroc_nazwe());
					}
				}
			}
		}
	}
}

void Gracz::odblokuj_pola_morza(Statek* jednostka){
	int kierunek_poludnie=1;
	int kierunek_wschod=1;
	int x=jednostka->zwroc_wspolrzedna_x();
	int y=jednostka->zwroc_wspolrzedna_y();
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
	for(int i=-1;jednostka->zwroc_ilosc_pol()>=i;i++){
		if(kierunek_wschod!=0){																				//jezeli statek ma kierunek zgodny z osia x
			if(x+i*kierunek_wschod>=0 && x+i*kierunek_wschod<ROZMIAR_X){	//zmieniamy wzdluz po x
				for(int j=-1;j<2;j++){
					if(y+j>=0 && y+j<ROZMIAR_Y){														//wszerz po y
						if(_plansza[x+i*kierunek_wschod][y+j].zwroc_rodzaj_terenu()!=ziemia){
							_plansza[x+i*kierunek_wschod][y+j].odblokuj_pole();
						}
					}
				}
			}
		}
		else{																											//zmieniamy wzdluz po y
			if(y+i*kierunek_poludnie>=0 && y+i*kierunek_poludnie<ROZMIAR_Y){
				for(int j=-1;j<2;j++){
					if(x+j>=0 && x+j<ROZMIAR_X){
						if(_plansza[x+j][y+i*kierunek_poludnie].zwroc_rodzaj_terenu()!=ziemia){
							_plansza[x+j][y+i*kierunek_poludnie].odblokuj_pole();
						}
					}
				}
			}
		}
	}
}
void Gracz::przygotuj_statki_do_ruchu(){
	znajdz_swoich();
	for(int i=1;i<=lista_statkow.zwroc_dlugosc_listy();i++){
		lista_statkow.zwroc(i)->wpisz_koszt_wykonanego_ruchu(0);
	}
}


void Gracz::zablokuj_pola_morza(Statek* jednostka){
	int kierunek_poludnie=1;
	int kierunek_wschod=1;
	int x=jednostka->zwroc_wspolrzedna_x();
	int y=jednostka->zwroc_wspolrzedna_y();
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
	for(int i=-1;jednostka->zwroc_ilosc_pol()>=i;i++){
			if(kierunek_wschod!=0){																				//jezeli statek ma kierunek zgodny z osia x
				if(x+i*kierunek_wschod>=0 && x+i*kierunek_wschod<ROZMIAR_X){	//zmieniamy wzdluz po x
					for(int j=-1;j<2;j++){
						if(y+j>=0 && y+j<ROZMIAR_Y){														//wszerz po y
							if(_plansza[x+i*kierunek_wschod][y+j].zwroc_rodzaj_terenu()!=ziemia){
								_plansza[x+i*kierunek_wschod][y+j].zablokuj_pole();
							}
						}
					}
				}
			}
			else{																											//zmieniamy wzdluz po y
				if(y+i*kierunek_poludnie>=0 && y+i*kierunek_poludnie<ROZMIAR_Y){
					for(int j=-1;j<2;j++){
						if(x+j>=0 && x+j<ROZMIAR_X){
							if(_plansza[x+j][y+i*kierunek_poludnie].zwroc_rodzaj_terenu()!=ziemia){
								_plansza[x+j][y+i*kierunek_poludnie].zablokuj_pole();
							}
						}
					}
				}
			}
	}
}

bool Gracz::sprawdz_czy_mozna_wstawic_w_jakiejs_pozycji(Statek* jednostka,int x,int y){
	kierunek poczatkowy_kierunek=jednostka->zwroc_kierunek();
	for(int i=0;i<4;i++){
		jednostka->wpisz_kierunek((kierunek)i);
		if(sprawdz_czy_mozna_wstawic(jednostka,x,y)){
			jednostka->wpisz_kierunek(poczatkowy_kierunek);
			return true;
		}
	}
	jednostka->wpisz_kierunek(poczatkowy_kierunek);
	return false;
}
bool Gracz::sprawdz_czy_mozna_wstawic(Statek* jednostka,int x,int y){
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
			if((x+i*kierunek_wschod<0 || x+i*kierunek_wschod>=ROZMIAR_X)  ||  (y+i*kierunek_poludnie<0 || y+i*kierunek_poludnie>=ROZMIAR_Y)){
				return false;
			}
			if(_plansza[x+i*kierunek_wschod][y+i*kierunek_poludnie].zwroc_dostepnosc_pola()==false){
				return false;
			}
		}
		return true;
}

void Gracz::wykonaj_ruch_statkow(){
	Statek* najblizszy_przeciwnik=NULL;
	Statek* okret=NULL;
	kierunek zwrot=poludnie;
	int x,y;

//	int tab[lista_statkow.zwroc_dlugosc_listy()];
	znajdz_przeciwnikow();
//	cout<<"Znaleziono przeciwnikow: <----------------------------------------------------------------------"<<endl;
//	statki_przeciwnika.wypisz();
//	znajdz_swoich();
//	cout<<"Znaleziono swoje: <----------------------------------------------------------------------"<<endl;
//		lista_statkow.wypisz();
//	cout<<"ilosc przeciwnikow "<<statki_przeciwnika.zwroc_dlugosc_listy();
//	cout<<"ilosc "<<lista_statkow.zwroc_dlugosc_listy();
for(int powtorzen=0;powtorzen<5;powtorzen++){
	for(int numer=1;numer<=lista_statkow.zwroc_dlugosc_listy();numer++){
//		cout<<"moje statki"<<endl;
//		lista_statkow.wypisz();
		okret=lista_statkow.zwroc(numer);
		while(okret->zwroc_koszt_wykonanego_ruchu()!=0  &&  numer<=lista_statkow.zwroc_dlugosc_listy()){
			okret=lista_statkow.zwroc(numer);
			numer++;
		}
		for(int p=1;p<=statki_przeciwnika.zwroc_dlugosc_listy();p++){
			if(najblizszy_przeciwnik==NULL){
				najblizszy_przeciwnik=statki_przeciwnika.zwroc(1);
			}
			else{
				if(odleglosc_miedzy_statkami(okret,statki_przeciwnika.zwroc(p))  <  odleglosc_miedzy_statkami(okret,najblizszy_przeciwnik)){
					najblizszy_przeciwnik=statki_przeciwnika.zwroc(p);
				}
			}
		}
		x=najblizszy_przeciwnik->zwroc_wspolrzedna_x();
		y=najblizszy_przeciwnik->zwroc_wspolrzedna_y();


		wyswietl_gre(this);
		obsluga_zdarzen();

		//szukaj pola kolo przeciwnika
		for(bool znaleziono=false;znaleziono!=true;){
//			for(int j=-1;znaleziono!=true && j<4;j++){
			for(int i=0;x>=ROZMIAR_X || x<0 || i==0;i++){
				if((i)%2==1){
					x+=-1+rand()%(int)(3);
				}
				else{
					x+=1-rand()%(int)(3);
				}
			}
			for(int i=0;y>=ROZMIAR_Y || y<0 || i==0;i++){
				if((i)%2==1){
					y+=-1+rand()%(int)(3);
				}
				else{
					y+=1-rand()%(int)(3);
				}
			}
			if(morze.zwroc_pole(x,y)->zwroc_rodzaj_terenu()==ziemia){
				x=najblizszy_przeciwnik->zwroc_wspolrzedna_x();
				y=najblizszy_przeciwnik->zwroc_wspolrzedna_y();
			}
			else if(sprawdz_czy_mozna_wstawic_w_jakiejs_pozycji(okret,x,y)){
				znaleziono=true;
			}
		}


		odblokuj_pola_morza(okret);
		if(morze.znajdz_droge(morze.zwroc_pole(okret->zwroc_wspolrzedna_x(),okret->zwroc_wspolrzedna_y()) , morze.zwroc_pole(x,y))){
			zablokuj_pola_morza(okret);
				for (int i = 1, pom=0,koniec=0;    koniec==0  &&    morze.droga.zwroc_dlugosc_listy() >= i;      i++, pom=0) {
				okret->odznacz_statek();
//				odblokuj_pola_morza(okret);
				Sleep(OPOZNIENIE_W_RUCHU);
				if(i>1){
					if(morze.droga.zwroc(i)->zwroc_y()  >  morze.droga.zwroc(i-1)->zwroc_y()){
						zwrot=poludnie;
						pom++;
					}
					else if(morze.droga.zwroc(i)->zwroc_y()  <  morze.droga.zwroc(i-1)->zwroc_y()){
						zwrot=polnoc;
						pom++;
					}
					if(morze.droga.zwroc(i)->zwroc_x()  >  morze.droga.zwroc(i-1)->zwroc_x()){
						zwrot=wschod;
						pom++;
					}
					else if(morze.droga.zwroc(i)->zwroc_x()  <  morze.droga.zwroc(i-1)->zwroc_x()){
						zwrot=zachod;
						pom++;
					}
				}
				if(pom==1){
					if(KOSZT_RUCHU_O_POLE< okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
						przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);
						okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+KOSZT_RUCHU_O_POLE);
					}
					else{
						koniec=1;
					}
				}
				else if(pom==2){
					if(KOSZT_RUCHU_PO_SKOSIE < okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
						przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);
						okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+KOSZT_RUCHU_PO_SKOSIE);
					}
						else{
							koniec=1;
						}
				}
				else{
					if(KOSZT_RUCHU_PO_SKOSIE < okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
						przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);\
						okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+ KOSZT_RUCHU_PO_SKOSIE);
					}
						else{
							koniec=1;
					}
				}
				wyswietl_gre(this);
				obsluga_zdarzen();
			}
		}
		else{
			zablokuj_pola_morza(okret);
		}
	}
	}
}

int Gracz::odleglosc_miedzy_statkami(Statek* pierwszy,Statek* drugi){
	return _plansza[pierwszy->zwroc_wspolrzedna_x()][pierwszy->zwroc_wspolrzedna_y()].zwroc_prognozowana_odleglosc_od(&_plansza[drugi->zwroc_wspolrzedna_x()][drugi->zwroc_wspolrzedna_y()]);
}


void Gracz::zaznacz_pole_statku(int x, int y){
	int wspolrzedna_statku_x=morze.zwroc_pole(x,y)->zwroc_statek()->zwroc_wspolrzedna_x();
	int wspolrzedna_statku_y=morze.zwroc_pole(x,y)->zwroc_statek()->zwroc_wspolrzedna_y();
	int pole_statku=abs(wspolrzedna_statku_x-x)+abs(wspolrzedna_statku_y-y);
	morze.zwroc_pole(x,y)->zwroc_statek()->zaznacz_pole(pole_statku);
}

bool Gracz::sprawdz_czy_zaznaczone(int x, int y){
	int wspolrzedna_statku_x=morze.zwroc_pole(x,y)->zwroc_statek()->zwroc_wspolrzedna_x();
	int wspolrzedna_statku_y=morze.zwroc_pole(x,y)->zwroc_statek()->zwroc_wspolrzedna_y();
	int pole_statku=abs(wspolrzedna_statku_x-x)+abs(wspolrzedna_statku_y-y);
	return morze.zwroc_pole(x,y)->zwroc_statek()->czy_pole_zaznaczone(pole_statku);
}

bool Gracz::strzel(Statek* jednostka, int x,int y){
	if(odleglosc_miedzy_statkami(jednostka,morze.zwroc_pole(x,y)->zwroc_statek())>jednostka->zwroc_zasieg()){
		return false;
	}
	cout<<"strzelam"<<endl;
	jednostka->strzel();
	cout<<"zaznaczam trafienie"<<endl;
	return morze.zwroc_pole(x,y)->zwroc_statek()->trafiony(x,y);
}

void Gracz::odznacz_statki(){
	for(int i=1; lista_statkow.zwroc_dlugosc_listy()>=i;i++){
		lista_statkow.zwroc(i)->usun_strzaly();
	}
}

bool Gracz::sprobuj_usunac_statek(Statek* jednostka){
	int kierunek_poludnie=1;
	int kierunek_wschod=1;
	int x,y;
	cout<<"probuje sciagac okret"<<endl;
		 jednostka->wyswietl();
		if(jednostka->zwroc_ilosc_pol()==jednostka->zwroc_ilosc_trafionych_pol()){
			cout<<"wszystkie pola zaznaczone"<<endl;
			jednostka->odznacz_pola();
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
			x=jednostka->zwroc_wspolrzedna_x();
			y=jednostka->zwroc_wspolrzedna_y();
			cout<<"sciagam statek "<<x<<" "<<y<<endl;
			for(int k=0;  k<jednostka->zwroc_ilosc_pol();k++){
				_plansza[x+k*kierunek_wschod][y+k*kierunek_poludnie].oznacz_pole_jako_morze();
			}
			jednostka->usun_statek();
			odblokuj_pola_morza(jednostka);
			morze.wyswietl();
			return true;
		}
		return false;
}

bool Gracz::sprawdz_czy_wygrales(){
		znajdz_przeciwnikow();
		cout<<"przeciwnikow: "<<statki_przeciwnika.zwroc_dlugosc_listy()<<endl;
			statki_przeciwnika.wypisz();
			if(statki_przeciwnika.zwroc_dlugosc_listy()==0){
				cout<<"wygralem"<<endl;
				return true;
			}
			else{
				return false;
			}
//	else{
//		znajdz_swoich();
//		cout<<"przeciwnikow0: "<<lista_statkow.zwroc_dlugosc_listy()<<endl;
//		lista_statkow.wypisz();
//			if(lista_statkow.zwroc_dlugosc_listy()==0){
//				cout<<"wygralem"<<endl;
//				return true;
//			}
//			else{
//				return false;
//			}
//	}
}

#endif /* GRACZ_HH_ */

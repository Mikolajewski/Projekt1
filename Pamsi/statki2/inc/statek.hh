/*
 * statek.hh
 *
 *  Created on: May 26, 2014
 *      Author: Tomek
 */

#ifndef STATEK_HH
#define STATEK_HH
#include <sstream>
#include <string>
#include <iostream>
#include "konfiguracja.hh"
#include "pole.hh"//<------------------------------- nie dodaje sie
#include "lista_posortowana.hh"
#include "plansza.hh"


using namespace std;



class Statek{
	sprawnosc_pola_jednostki*  tab;
	bool* zaznaczone;
	int ilosc_pol;
	int ilosc_sprawnych_dzial;
	kierunek obrocony;
	int _x,_y;
	string nazwa;
	rodzaj_statku _rodzaj_jednostki;
	int predkosc;
	int koszt_wykonanego_ruchu;
	bool zaznaczony;
	int dlugosc_drogi;
	int zasieg_strzalu;
	int ilosc_trafionych_pol;

	static int ilosc_kutrow[2];
	static int ilosc_krazownikow[2];
	static int ilosc_liniowych[2];
	static int ilosc_pancernikow[2];
public:
//	int** kroki;
	void inicjalizuj_statek(zawodnik flaga,rodzaj_statku rodzaj_jednostki,int x,int y);
	void wpisz_wspolrzedne(int x,int y){_x=x,_y=y;};
	rodzaj_statku zwroc_rodzaj_statku(){return _rodzaj_jednostki;};
	int zwroc_ilosc_pol(){return  ilosc_pol;};
	int zwroc_wspolrzedna_x(){return _x;};
	int zwroc_wspolrzedna_y(){return _y;};
	string zwroc_nazwe(){return nazwa;};
	void wpisz_kierunek(kierunek zwrot){obrocony=zwrot;};
	kierunek zwroc_kierunek(){return obrocony;};
	int zwroc_ilosc_sprawnych_dzial(){return ilosc_sprawnych_dzial;};
	bool sprawdz_sprawnosc_pola_statku(int x){return tab[x]==sprawne?true:false;};
	void wyswietl();
	void zaznacz_statek();
	void odznacz_statek(){odznacz_pola();zaznaczony=false;};
	void odznacz_pola();
	void zaznacz_pole(int i);
	bool czy_pole_zaznaczone(int i){return zaznaczone[i];};
	bool czy_zaznaczony(){return zaznaczony;};
	void wpisz_dlugosc_drogi(int dlugosc){dlugosc_drogi=dlugosc;};
	int zwroc_dlugosc_drogi(){return dlugosc_drogi;};
	void wpisz_predkosc(int _predkosc){predkosc=_predkosc;};
	int zwroc_predkosc(){return predkosc;};
	void wpisz_koszt_wykonanego_ruchu(int koszt){koszt_wykonanego_ruchu=koszt;};
	int zwroc_koszt_wykonanego_ruchu(){return koszt_wykonanego_ruchu;};
	int zwroc_ilosc_trafionych_pol(){return ilosc_trafionych_pol;};
	void usun_statek();

	void strzel();
	bool trafiony(int x,int y);
	sprawnosc_pola_jednostki zwroc_sprawnosc_pola(int x, int y);
	int zwroc_zasieg(){return zasieg_strzalu;};
	void usun_strzaly();

	Statek(){tab=NULL;ilosc_sprawnych_dzial=0;ilosc_pol=0;obrocony=wschod;_x=0;_y=0;_rodzaj_jednostki=kuter;predkosc=0;zaznaczony=false;dlugosc_drogi=0;koszt_wykonanego_ruchu=0;zaznaczone=NULL;zasieg_strzalu=0;ilosc_trafionych_pol=0;};
};

int Statek:: ilosc_kutrow[2]={0,0};
int Statek::ilosc_krazownikow[2]={0,0};
int Statek::ilosc_liniowych[2]={0,0};
int Statek::ilosc_pancernikow[2]={0,0};

void Statek::inicjalizuj_statek(zawodnik flaga,rodzaj_statku rodzaj_jednostki,int x,int y){
	string liczba;
	ostringstream pom;

	cout<<"inicjalizuje statek"<<endl;
	_rodzaj_jednostki=rodzaj_jednostki;
	_x=x;
	_y=y;
	zaznaczony=false;
	zasieg_strzalu=ZASIEG;
	ilosc_trafionych_pol=0;
	if(flaga==fioletowy){
		obrocony=wschod;
	}else{
		obrocony=zachod;
	}
	switch(rodzaj_jednostki){
		case kuter:
			ilosc_pol=1;
			ilosc_sprawnych_dzial=0;
			ilosc_kutrow[flaga]++;
			pom << ilosc_kutrow[flaga];
			liczba = pom.str();
			nazwa="kuter";
			nazwa+=liczba;
			predkosc=PREDKOSC_KUTRA;
			break;
		case krazownik:
			ilosc_pol=2;
			ilosc_sprawnych_dzial=1;
			ilosc_krazownikow[flaga]++;
			pom << ilosc_krazownikow[flaga];
			liczba = pom.str();
			nazwa="krazownik";
			nazwa+=liczba;
			predkosc=PREDKOSC_KRAZOWNIKA;
			break;
		case liniowiec:
			ilosc_pol=3;
			ilosc_sprawnych_dzial=2;
			ilosc_liniowych[flaga]++;
			pom << ilosc_liniowych[flaga];
			liczba = pom.str();
			nazwa="liniowiec";
			nazwa+=liczba;
			predkosc=PREDKOSC_LINIOWCA;
			break;
		case pancernik:
			ilosc_pol=4;
			tab=new sprawnosc_pola_jednostki[4];
			ilosc_sprawnych_dzial=3;
			cout<<"przed zwiekszeniem statycznej"<<endl;
			ilosc_pancernikow[flaga]++;
			cout<<"po zwiekszeniu statycznej"<<endl;
			pom << ilosc_pancernikow[flaga];
			liczba = pom.str();
			cout<<liczba<<endl;
			nazwa="pancernik";
			nazwa+=liczba;
			predkosc=PREDKOSC_PANCERNIKA;
			break;
	}
	tab=new sprawnosc_pola_jednostki[ilosc_pol];
	zaznaczone=new bool[ilosc_pol];
	for(int i=0;i<ilosc_pol;i++){
		tab[i]=sprawne;
		zaznaczone[i]=false;
	}
}

void Statek::odznacz_pola(){
	for(int i=0;i<ilosc_pol;i++){
		zaznaczone[i]=false;
	}
	zaznaczony=false;
}

void Statek::zaznacz_pole(int i){
	zaznaczone[i]=true;
	cout<<"zaznaczam "<<i<<endl;
	zaznaczony=true;
}

void Statek::zaznacz_statek(){
	cout<<"zaczynam zaznaczac"<<endl;
	for(int i=0;i<ilosc_pol;i++){
		zaznaczone[i]=true;
		cout<<"zaznaczam "<<i<<endl;
	}
	zaznaczony=true;
}

void Statek::wyswietl(){
	cout<<"Parametry jednostki o nazwie "<<nazwa<<":"<<endl;
	cout<<"   typ jednostki: ";
	switch(zwroc_rodzaj_statku()){
			case kuter:
				cout<<"kuter"<<endl;
				break;
			case krazownik:
				cout<<"krazownik"<<endl;
				break;
			case liniowiec:
				cout<<"liniowiec"<<endl;
				break;
			case pancernik:
				cout<<"pancernik"<<endl;
				break;
	}
	cout<<"   ilosc pol: "<<ilosc_pol<<endl;
	cout<<"   Iiosc_sprawnych_dzial: "<<ilosc_sprawnych_dzial<<endl;
	cout<<"   kierunek: ";
	switch(obrocony){
		case zachod:
			cout<<"zachod"<<endl;
			break;
		case wschod:
			cout<<"wschod"<<endl;
			break;
		case poludnie:
			cout<<"poludnie"<<endl;
			break;
		case polnoc:
			cout<<"polnoc"<<endl;
			break;
	}
	cout<<"   polozenie: x="<<_x<<" y="<<_y<<endl;
	cout<<"   predkosc: "<<predkosc<<endl;
}





sprawnosc_pola_jednostki Statek::zwroc_sprawnosc_pola(int x, int y){
	int zaznaczone_x=zwroc_wspolrzedna_x();
	int zaznaczone_y=zwroc_wspolrzedna_y();
	int i=0;
	for(i=0;zaznaczone_x!=x || zaznaczone_y!=y ;i++){
		switch(obrocony){
			case zachod:
				zaznaczone_x--;
				break;
			case wschod:
				zaznaczone_x++;
				break;
			case poludnie:
				zaznaczone_y++;
				break;
			case polnoc:
				zaznaczone_y--;
				break;
		}
	}
	return tab[i];
}

void Statek::strzel(){
	int i;
	for(i=0;zaznaczone[i]==false ;i++){	}
	tab[i]=wystrzelono;
}

bool Statek::trafiony(int x, int y){
	int zaznaczone_x=zwroc_wspolrzedna_x();
	int zaznaczone_y=zwroc_wspolrzedna_y();
	int i=0;

	for(i=0;zaznaczone_x!=x || zaznaczone_y!=y ;i++){
		switch(obrocony){
			case zachod:
				zaznaczone_x--;
				break;
			case wschod:
				zaznaczone_x++;
				break;
			case poludnie:
				zaznaczone_y++;
				break;
			case polnoc:
				zaznaczone_y--;
				break;
		}
	}
	if(tab[i]==sprawne || tab[i]==wystrzelono){
		tab[i]=niesprawne;
		ilosc_trafionych_pol++;
		cout<<"Trafiono juz "<<ilosc_trafionych_pol<<" pol"<<endl;
		if(i!=0){
			ilosc_sprawnych_dzial--;
		}
		wyswietl();
		return true;
	}
	else{
		return false;
	}
}

void Statek::usun_strzaly(){
	for(int i=0;i<ilosc_pol;i++){
		if(tab[i]==wystrzelono){
			tab[i]=sprawne;
		}
	}
}

void Statek::usun_statek(){
	delete[] tab;
	delete[] zaznaczone;
}

#endif /* STATEK_HH_ */

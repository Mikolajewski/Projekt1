/*
 * statek.hh
 *
 *  Created on: May 26, 2014
 *      Author: Tomek
 */

#ifndef STATEK_HH_
#define STATEK_HH_
#include "konfiguracja.hh"
#include <string>
#include <sstream>

class Statek{
	sprawnosc_pola_jednostki*  tab;
	int ilosc_pol;
	int ilosc_sprawnych_dzial;
	kierunek obrocony;
	int _x,_y;
	string nazwa;
	rodzaj_statku _rodzaj_jednostki;
	int predkosc;
	static int ilosc_kutrow[2];
	static int ilosc_krazownikow[2];
	static int ilosc_liniowych[2];
	static int ilosc_pancernikow[2];
public:
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
	void strzel_w_pole_statku(int x){tab[x]=niesprawne;};
	bool sprawdz_sprawnosc_pola_statku(int x){return tab[x]==sprawne?true:false;};
	void wypisz_parametry_statku();
	//Statek(){tab=NULL;ilosc_sprawnych_pol=0;};
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
	if(flaga==czerwony){
		obrocony=wschod;
	}else{
		obrocony=zachod;
	}
	switch(rodzaj_jednostki){
		case kuter:
			ilosc_pol=1;
			tab=new sprawnosc_pola_jednostki[1];
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
			tab=new sprawnosc_pola_jednostki[2];
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
			tab=new sprawnosc_pola_jednostki[3];
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
	for(int i=0;i<ilosc_pol;i++){
		tab[i]=sprawne;
	}
}

void Statek::wypisz_parametry_statku(){
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




#endif /* STATEK_HH_ */

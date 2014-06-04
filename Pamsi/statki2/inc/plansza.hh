	/*!
	\file
	\brief Plik zawierajacy klase Plansza.

	*/

#ifndef PLANSZA
#define PLANSZA
#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "pole.hh"
#include "statek.hh"
#include "konfiguracja.hh"
#include "lista_posortowana.hh"
using namespace std;

	/*!
	\brief Klasa Plansza

	Klasa odpowiedzialna za tworzenie struktury polaczonych ze soba pol. W strukturze tej mozna szukac najkrotszej sciezki pomiedzy polami.
	*/
class Plansza{


	/*!
	\brief _wielkosc_x

	Zmienna zawierajaca informacje o rozmiarze x planszy.
	*/
		int _wielkosc_x;


	/*!
	\brief _wielkosc_y

	Zmienna zawierajaca informacje o rozmiarze y planszy.
	*/
		int _wielkosc_y;


	/*!
	\brief kolejka_priorytetowa

	Lista na ktorej sa gromadzone pola do ktorych nalezy sie udac wykonujac poszukiwanie optymalnej drogi. Pola te sa posortowane wzgledem prognozowanego kosztu przejscia przez dane pole.
	*/
		Lista<posortowana,Pole,int> kolejka_priorytetowa;


	/*!
	\brief lista_odwiedzonych

	Lista na ktorej sa gromadzone pola do ktorych juz sie odwolano podczas poszukiwania optymalnej drogi.
	*/
		Lista<posortowana,Pole,int> lista_odwiedzonych;




	/*!
	\brief dodaj_mozliwe_kierunki_ruchu

	Metoda dodajaca do kolejki priorytetowej wszystkie mozliwe sciezki wychodzace z pola pomocnicza.
	*/
		void dodaj_mozliwe_kierunki_ruchu(Pole* pomocnicza);


	/*!
	\brief dodaj_kierunek_ruchu

	Metoda dodajaca sciezke z pola do_dodania do pola pomocnicza o koszcie koszt_ruchu. Dane te sa dodawane do kolejki priorytetowej.
	*/
		bool dodaj_kierunek_ruchu(Pole* do_dodania,Pole* pomocnicza,int koszt_ruchu);


	/*!
	\brief kodowanie_pola

	Metoda zwracajaca kod pola pomocnicza. Po tym kodzie wykonywane jest szukanie pola w liscie odwiedzonych.
	*/
		int kodowanie_pola(Pole* pomocnicza);


	/*!
	\brief zapisz_droge

	Metoda zapisujaca droge z pola pomocnicza do pola z ktorego rozpoczelo sie poszukiwanie.
	*/
		void zapisz_droge(Pole* koniec);
		void stworz_wyspy();

		Pole** plansza_dla_A;
		void aktualizuj_plansze_dla_A();

	public:
	/*!
	\brief tab

	Wskaznik na tablice zawierajaca zmienne Pole i bedacej podstawowa struktura klasy Plansza
	*/
		Pole** tab;

	/*!
	\brief cel

	Zmienna w ktorej przechowywany jest wskaznik do pola bedacego celem wyszukiwania sciezki.
	*/
		Pole* cel;


		/*!
		\brief droga

		Lista na ktorej gromadzone sa pola po ktorych nalezy sie poruszac, aby przejsc pomiedzy zadanymi punktami.
		*/
			Lista<nieposortowana,Pole,int> droga;

	/*!
	\brief Konstruktor Planszy

	*/
		Plansza(){tab=NULL;plansza_dla_A=NULL;cel=NULL;_wielkosc_x=0;_wielkosc_y=0;};


//		Plansza operator =(Plansza pierwsza,Plansza druga);
	/*!
	\brief stworz_plansze

	Metoda tworzaca plansze o wymiarze x na y
	*/
		bool stworz_plansze(int x,int y);


	/*!
	\brief zwroc_pole

	Metoda zwracajaca wskaznik do pola o wspolrzednych x i y.
	*/
		Pole* zwroc_pole(int wspolrzedna_x, int wspolrzedna_y);

	/*!
	\brief znajdz_droge

	Metoda znajdujaca droge z pola poczatek do pola koniec. Metoda zapisuje otrzymana sciezke w liscie droga. Wyszukiwanie odbywa sie za pomoca algorytmu A*.
	*/
		bool znajdz_droge(Pole* poczatek,Pole* koniec);

//		void przepisz_droge(Statek* jednostka);
	/*!
	\brief wyswietl_droge

	Metoda wyswietlajaca droge zawarta w liscie droga.
	*/
		void wyswietl_droge();

	/*!
	\brief wyswietl_parametry_drogi

	Metoda wyswietlajaca ilosc krokow, ktore sa potrzebne do pokonania sciezki zawartej w liscie droga oraz wyswietlajaca laczny koszt jaki jest potrzebny do jej pokonania.
	*/
		void wyswietl_parametry_drogi();

	/*!
	\brief wyswietl

	Metoda wyswietlajaca cala plansze na stdout.
	*/
		void wyswietl();
};


//						Czesc Publicza					//

bool Plansza::stworz_plansze(int x, int y){
	if(tab==NULL){
		tab = new Pole*[x];
		for (int i = 0; i < x; ++i) {
    		tab[i] = new Pole[y];
		}
		for(int i_x=0; i_x<x; i_x++){
			for(int i_y=0; i_y<y; i_y++){
				tab[i_x][i_y].wpisz_wspolrzedne(i_x,i_y);
				tab[i_x][i_y].oznacz_pole_jako_morze();
			}
		}
		stworz_wyspy();
		_wielkosc_x=x;
		_wielkosc_y=y;

		plansza_dla_A = new Pole*[x];
		for (int i = 0; i < x; ++i) {
    		plansza_dla_A[i] = new Pole[y];
		}
		return true;
	}
	else{
		cout<<"Plansza nie moze byc utworzona powtornie."<<endl;
	}
	return false;
}

//Plansza Plansza::operator =(Plansza)

Pole* Plansza::zwroc_pole(int wspolrzedna_x,int wspolrzedna_y){
	return &tab[wspolrzedna_x][wspolrzedna_y];
}


bool Plansza::znajdz_droge(Pole* poczatek,Pole* koniec){
	Pole* pomocnicza=NULL;
	aktualizuj_plansze_dla_A();
	cel=&plansza_dla_A[koniec->zwroc_x()][koniec->zwroc_y()];
	pomocnicza=&plansza_dla_A[poczatek->zwroc_x()][poczatek->zwroc_y()];

	if(!koniec->zwroc_dostepnosc_pola()){
//		cout<<"Pole docelowe nie jest dostepne."<<endl;
		return false;
	}

	kolejka_priorytetowa.usun_wszystko();
	lista_odwiedzonych.usun_wszystko();
	droga.usun_wszystko();

//	Sleep(100);
//	cout<<"Zaczynam szukanie drogi z."<<endl;
//	poczatek->wyswietl();
//	cout<<" do ";
//	koniec->wyswietl();
//	cout<<endl;
	kolejka_priorytetowa.dodaj(pomocnicza,0);
	pomocnicza->wpisz_prognozowany_koszt(pomocnicza->zwroc_prognozowana_odleglosc_od(cel));
//	cout<<"przed while"<<endl;
	while(kolejka_priorytetowa.zwroc_dlugosc_listy()!=0){
		pomocnicza=kolejka_priorytetowa.zwroc(1);
//		cout<<"pole: ";
//		pomocnicza->wyswietl();
//		cout<<"kodowanie pola: "<<kodowanie_pola(pomocnicza)<<endl;
		if(lista_odwiedzonych.znajdz(kodowanie_pola(pomocnicza))==NULL){
			lista_odwiedzonych.dodaj(pomocnicza,kodowanie_pola(pomocnicza));
//			cout<<"nie znalazlem"<<endl;
		}
		if(pomocnicza==cel){
//			wyswietl();
//			cout<<"Znaleziono droge do pola ";
//			pomocnicza->wyswietl();
//			cout<<endl;
//			droga.usun_wszystko();
			zapisz_droge(pomocnicza);
//			cout<<"zapisalem do planszy"<<endl;
			return true;
		}
//		cout<<"przed pop"<<endl;
		kolejka_priorytetowa.pop();
//		cout<<"po pop"<<endl;
		dodaj_mozliwe_kierunki_ruchu(pomocnicza);
//		cout<<"kolejka priorytetowa rozmiar: "<<kolejka_priorytetowa.zwroc_dlugosc_listy();
//		cout<<"      lista odwiedzonych: "<<lista_odwiedzonych.zwroc_dlugosc_listy()<<endl;
	}
//	cout<<"Nie mozna przejsc z ";
//	poczatek->wyswietl();
//	cout<<" do ";
//	koniec->wyswietl();
//	cout<<endl;
	return false;
}

//void Plansza::przepisz_droge(Statek* jednostka){
//cout<<"przepisuje"<<endl;
//		if(jednostka->kroki!=NULL){
//			cout<<"nie bylo null"<<endl;
//			for(int i=0;i<jednostka->zwroc_dlugosc_drogi();i++){
//				delete jednostka->kroki[i];
//			}
//			delete jednostka->kroki;
//		}
//		cout<<"tworze dlugosc listy"<<droga.zwroc_dlugosc_listy()<<endl;
//		jednostka->wpisz_dlugosc_drogi(droga.zwroc_dlugosc_listy());
//		cout<<"jednostka "<<jednostka->zwroc_dlugosc_drogi();
//		jednostka->kroki = new int*[jednostka->zwroc_dlugosc_drogi()];
//		for (int i = 0; i < jednostka->zwroc_dlugosc_drogi(); i++) {
//			jednostka->kroki[i] = new int[2];
//		}
//		cout<<"stworzylem ";
//		for (int k =1; k <= jednostka->zwroc_dlugosc_drogi(); k++) {
//			cout<<"wpksuje ";
//			jednostka->kroki[k][0]=droga.zwroc(k)->zwroc_x();
//			jednostka->kroki[k][1]=droga.zwroc(k)->zwroc_y();
//		}
//		cout<<"skonczylem przepisywanie"<<endl;
//}

void Plansza::wyswietl_parametry_drogi(){
	cout<<"Droga zawiera "<<droga.zwroc_element(1)->zwroc_klucz()<<" krokow."<<endl;
	cout<<"Koszt drogi to: "<<droga.zwroc(droga.zwroc_dlugosc_listy())->zwroc_prognozowany_koszt()<<endl;
}

void Plansza::wyswietl_droge(){
	droga.wypisz();
	cout<<endl;
}

void Plansza::wyswietl(){
	cout<<"    ";
	for(int i=0;i<_wielkosc_x;i++){
		cout.width(4);
		cout<<i;
	}
	cout<<endl;
	for(int j=0;j<_wielkosc_y;j++){
		cout.width(4);
		cout<<j<<"|";
		for(int i=0;i<_wielkosc_x;i++){
			cout.width(4);
//			tab[i][j].wyswietl()
//			cout<<tab[i][j].zwroc_odleglosc_od_poczatku();
//			cout<<tab[i][j].zwroc_prognozowany_koszt();
			cout<<tab[i][j].zwroc_rodzaj_terenu();
//			cout<<tab[i][j].zwroc_ile_razy_zablokowany();
		}
		cout<<endl;
	}
}

////////////////////////////////////					Czesc Prywatna					/////////////////////////////////////////////////////

void Plansza::aktualizuj_plansze_dla_A(){
	for(int x=0;x<ROZMIAR_X;x++){
		for(int y=0;y<ROZMIAR_Y;y++){
			plansza_dla_A[x][y]=tab[x][y];
		}
	}
}

bool Plansza::dodaj_kierunek_ruchu(Pole* do_dodania,Pole* pomocnicza,int koszt_ruchu){
	int koszt_drogi;
//	cout<<"dodaje kierunek ruch"<<endl;
	koszt_drogi=pomocnicza->zwroc_odleglosc_od_poczatku()+koszt_ruchu;
	if(do_dodania->zwroc_dostepnosc_pola()==true && lista_odwiedzonych.znajdz(kodowanie_pola(do_dodania))==NULL){
//	cout<<"przed czy sprawdzany"<<endl;
		if(do_dodania->zwroc_odleglosc_od_poczatku()==0){
//			cout<<"nie bylem"<<endl;
			do_dodania->wpisz_poprzednie_pole(pomocnicza);
			do_dodania->wpisz_odleglosc_od_poczatku(koszt_drogi);
			do_dodania->wpisz_prognozowany_koszt(do_dodania->zwroc_prognozowana_odleglosc_od(cel)+koszt_drogi);
			kolejka_priorytetowa.dodaj(do_dodania,do_dodania->zwroc_prognozowana_odleglosc_od(cel)+koszt_drogi);
			return true;
		}
		else if(do_dodania->zwroc_odleglosc_od_poczatku()>koszt_drogi){
//			cout<<"lepsza"<<endl;
//			do_dodania->wyswietl();
//			kolejka_priorytetowa.usun_konkretny_element(do_dodania->zwroc_odleglosc_od_poczatku() + do_dodania->zwroc_prognozowana_odleglosc_od(cel),do_dodania);
			do_dodania->wpisz_poprzednie_pole(pomocnicza);
			do_dodania->wpisz_odleglosc_od_poczatku(koszt_drogi);
			do_dodania->wpisz_prognozowany_koszt(do_dodania->zwroc_prognozowana_odleglosc_od(cel)+koszt_drogi);
//			cout<<"dodaje"<<endl;
			kolejka_priorytetowa.dodaj(do_dodania,do_dodania->zwroc_prognozowana_odleglosc_od(cel)+koszt_drogi);
//			cout<<"dodalem"<<endl;
			return false;
		}
	}
//	cout<<"zakonczylem dodawnie kierunku ruchu"<<endl;
	return false;
}

void Plansza::dodaj_mozliwe_kierunki_ruchu(Pole* pomocnicza){
	int x_0,y_0;
	Pole* do_dodania;
	x_0=pomocnicza->zwroc_x();
	y_0=pomocnicza->zwroc_y();
	if(x_0!=0){
		do_dodania=&plansza_dla_A[x_0-1][y_0];
		dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_O_POLE);
		if(y_0!=0){
			if(plansza_dla_A[x_0-1][y_0].zwroc_dostepnosc_pola() && plansza_dla_A[x_0][y_0-1].zwroc_dostepnosc_pola()){
				do_dodania=&plansza_dla_A[x_0-1][y_0-1];
				dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_PO_SKOSIE);
			}
		}
		if(y_0+1!=_wielkosc_y){
			if(plansza_dla_A[x_0-1][y_0].zwroc_dostepnosc_pola() && plansza_dla_A[x_0][y_0+1].zwroc_dostepnosc_pola()){
				do_dodania=&plansza_dla_A[x_0-1][y_0+1];
				dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_PO_SKOSIE);
			}
		}
	}
	if(x_0+1!=_wielkosc_x){
		do_dodania=&plansza_dla_A[x_0+1][y_0];
		dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_O_POLE);
		if(y_0!=0){
			if(plansza_dla_A[x_0+1][y_0].zwroc_dostepnosc_pola() && plansza_dla_A[x_0][y_0-1].zwroc_dostepnosc_pola()){
				do_dodania=&plansza_dla_A[x_0+1][y_0-1];
				dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_PO_SKOSIE);
			}
		}
		if(y_0+1!=_wielkosc_y){
			if(plansza_dla_A[x_0+1][y_0].zwroc_dostepnosc_pola() && plansza_dla_A[x_0][y_0+1].zwroc_dostepnosc_pola()){
				do_dodania=&plansza_dla_A[x_0+1][y_0+1];
				dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_PO_SKOSIE);
			}
		}
	}
	if(y_0!=0){
		do_dodania=&plansza_dla_A[x_0][y_0-1];
		dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_O_POLE);
	}
	if(y_0+1!=_wielkosc_y){
		do_dodania=&plansza_dla_A[x_0][y_0+1];
		dodaj_kierunek_ruchu(do_dodania,pomocnicza,KOSZT_RUCHU_O_POLE);
	}
}


void Plansza::zapisz_droge(Pole* koniec){
	Pole* pomocnicza=koniec;
	droga.dodaj(pomocnicza,1);
	for(int i=0;pomocnicza->zwroc_poprzednie_pole()!=NULL;){
		i++;
		pomocnicza=pomocnicza->zwroc_poprzednie_pole();
		droga.dodaj(pomocnicza,i);
	}
}

int Plansza::kodowanie_pola(Pole* pomocnicza){
	return pomocnicza->zwroc_x()+pomocnicza->zwroc_y()*_wielkosc_y+1;
}

void Plansza::stworz_wyspy(){
	int wielkosc_ladu=(int)(ROZMIAR_X*ROZMIAR_Y*PROCENTOWO_WYSP_MIN/100)+(rand()%(int)(ROZMIAR_X*ROZMIAR_Y*(PROCENTOWO_WYSP_MAX-PROCENTOWO_WYSP_MIN)/100));
	int ilosc_wysp=1+(rand()%(int)(MAX_ILOSC_WYSP));
	bool dodano_lad;
	bool zmiana;
	int x,y;
	Pole** wyspy;
	Pole* pomocnicza;
	wyspy=new Pole*[ilosc_wysp];

	//dodawanie wysp
	for(int i=0;i<ilosc_wysp;i++){
		wyspy[i]=&tab[rand()%(int)(ROZMIAR_X)][rand()%(int)(ROZMIAR_Y)];
	}

	//dodawanie elementow wysp
	for(int ilosc_dodanych=0;ilosc_dodanych<wielkosc_ladu;ilosc_dodanych++){
		dodano_lad=false;
		pomocnicza=wyspy[rand()%(int)(ilosc_wysp)];
		while(dodano_lad==false){
			if(pomocnicza->zwroc_rodzaj_terenu()==nic){
				pomocnicza->oznacz_pole_jako_lad();
				pomocnicza->zablokuj_pole();
				dodano_lad=true;
			}
			else{
				zmiana=false;
				for(int i=0;x>=ROZMIAR_X || x<0 || zmiana==false;i++){
					if((i+ilosc_dodanych)%2==1){
						x=pomocnicza->zwroc_x()-1+rand()%(int)(3);
					}
					else{
						x=pomocnicza->zwroc_x()+1-rand()%(int)(3);
					}
					zmiana=true;
				}
				zmiana=false;
				for(int i=0;y>=ROZMIAR_Y || y<0 || zmiana==false;i++){
					if((i+ilosc_dodanych)%2==1){
						y=pomocnicza->zwroc_y()-1+rand()%(int)(3);
					}
					else{
						y=pomocnicza->zwroc_y()+1-rand()%(int)(3);
					}
					zmiana=true;
				}
				pomocnicza=&tab[x][y];
			}
		}
	}
}
#endif

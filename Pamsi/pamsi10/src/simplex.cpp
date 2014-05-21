/*!
\file
\brief Plik zawierajacy Klase Simplex

*/
#include <iostream>
#include "simplex.h"
#include "komunikacja.hh"
#include "lista_posortowana.hh"
using namespace std;

void Simplex::stworz_tabele_simplex(){
	Komunikacja dialog;
	bool dobra_ilosc_rownan=false;
	
	//Tworzenie macierzy//
	cout<<"Wpisz ilosc zmiennych."<<endl;
	ilosc_zmiennych=dialog.pobierz_int();
	cout<<"Wpisz ilosc rownan."<<endl;
	do{
		ilosc_rownan=dialog.pobierz_int();
		if(ilosc_rownan>=ilosc_zmiennych+1){
			dobra_ilosc_rownan=true;
		}
		else{
			cout<<"Za malo rownan."<<endl;
			cout<<"Wpisz ilosc rownan."<<endl;
		}
	}while(!dobra_ilosc_rownan);
	ilosc_kolumn=ilosc_rownan+ilosc_zmiennych;
	macierz_wspolczynnikow=new float*[ilosc_kolumn];
	for(int k=0;k<ilosc_kolumn;k++){
		macierz_wspolczynnikow[k]=new float[ilosc_rownan];
		for(int w=0;w<ilosc_rownan;w++){
			macierz_wspolczynnikow[k][w]=0;
		}
	}
	wektor_b=new float[ilosc_rownan];
	wektor_funkcji_kosztu=new float[ilosc_zmiennych];
	
	//Wprowadzanie wspolczynnikow//
	cout<<endl<<"Wprowadzanie wspolczynnikow."<<endl;
	for(int w=0;w<ilosc_rownan;w++){
		cout<<"Wprowadzasz zmienne do rownania "<<w<<endl;
		for(int k=0;k<ilosc_zmiennych;k++){
			cout<<" Podaj wspolczynnik przy x"<<k<<": ";
			macierz_wspolczynnikow[k][w]=dialog.pobierz_int();
			cout<<endl;
		}
		macierz_wspolczynnikow[ilosc_zmiennych+w][w]=1;
		cout<<" Podaj b"<<w<<": ";
		wektor_b[w]=dialog.pobierz_int();
		cout<<endl;
		
	}
//	cout<<"Czy chcesz szukac maksimum?"<<endl;
//	if(dialog.pytanie_tak_nie()==true){
		rodzaj_szukania=1;	//szukania maksimum
//	}
//	else{
//		rodzaj_szukania=-1;	//szukanie minimum
//	}
	cout<<"Wprowadzanie funkcji kosztu."<<endl;
	for(int k=0;k<ilosc_zmiennych;k++){
		cout<<" Podaj wspolczynnik przy x"<<k<<": ";
		wektor_funkcji_kosztu[k]=rodzaj_szukania*dialog.pobierz_int();
		cout<<endl;
	}	
	for(int k=ilosc_zmiennych;k<ilosc_kolumn;k++){
		wektor_funkcji_kosztu[k]=0;	
	}
	obliczony_koszt=0;
	cout<<"koniec wpisywania"<<endl;
}

int Simplex::znajdz_max_x(){
	float max=0;
	int kolumna;
	for(int k=0;k<ilosc_kolumn;k++){
		if(wektor_funkcji_kosztu[k]*rodzaj_szukania>max){
			kolumna=k;
			max=wektor_funkcji_kosztu[k];
		}
	}
	return kolumna;
}

bool Simplex::koniec(){
	for(int k=0;k<ilosc_kolumn;k++){
		if(wektor_funkcji_kosztu[k]*rodzaj_szukania>0){
			return false;
		}
	}
	return true;
}

int Simplex::znajdz_min_iloraz(int kolumna){
	float min=0;
	float pomocnicza;
	int wiersz=-1;
	for(int w=0;w<ilosc_rownan;w++){
		if(macierz_wspolczynnikow[kolumna][w]!=0){
			pomocnicza=wektor_b[w]/macierz_wspolczynnikow[kolumna][w];
			if(pomocnicza>0){
				if(wiersz==-1||pomocnicza<min){
					min=pomocnicza;
					wiersz=w;
				}
			}
		}
	}
	return wiersz;
}

void Simplex::zamien(int kolumna,int wiersz){
	bool koniec=false;
	float A,B,C;
	if(wektor_funkcji_kosztu[kolumna]!=0){
		B=wektor_funkcji_kosztu[kolumna]/macierz_wspolczynnikow[kolumna][wiersz];
		for(int k=0;k<ilosc_kolumn;k++){
			wektor_funkcji_kosztu[k]-=B*macierz_wspolczynnikow[k][wiersz];
		}
		obliczony_koszt-=B*wektor_b[wiersz];		
	}
	for(int w=0;w<ilosc_rownan;w++){
		if(w!=wiersz){
			A=macierz_wspolczynnikow[kolumna][w]/macierz_wspolczynnikow[kolumna][wiersz];
			for(int k=0;k<ilosc_kolumn;k++){
				macierz_wspolczynnikow[k][w]-=A*macierz_wspolczynnikow[k][wiersz];
			}
			wektor_b[w]-=A*wektor_b[wiersz];
		}
	}
	
	//dzielenie aby otrzymac 1
	if(macierz_wspolczynnikow[kolumna][wiersz]!=1){
		C=macierz_wspolczynnikow[kolumna][wiersz];
		for(int k=0;k<ilosc_kolumn;k++){
			macierz_wspolczynnikow[k][wiersz]=macierz_wspolczynnikow[k][wiersz]/C;
		}		
		wektor_b[wiersz]=wektor_b[wiersz]/C;
	}
}

bool Simplex::znajdz_optimum(){
	int* iloraz;
	int kolumna,wiersz;
	iloraz=new int[ilosc_rownan];
	while(!koniec()){
//		wyswietl_tabele_simplex();
		kolumna=znajdz_max_x();
		wiersz=znajdz_min_iloraz(kolumna);
		if(wiersz==-1){
			cout<<"Funkcja nie jest ograniczona z dolu."<<endl;
			return false;
		}
		zamien(kolumna,wiersz);
	}
		cout<<"Znaleziono."<<endl;
		return true;
}

void Simplex::wypisz_rozwiazanie(){
	int liczba_wystapila;
	int wiersz;
	cout<<"Znalezione rozwiazanie to: ";
	for(int k=0;k<ilosc_zmiennych;k++){
		liczba_wystapila=0;
		wiersz=-1;
		for(int w=0;w<ilosc_rownan&&liczba_wystapila<2;w++){
			if(macierz_wspolczynnikow[k][w]==1){
				liczba_wystapila++;
				wiersz=w;
			}
			else if(macierz_wspolczynnikow[k][w]!=0){
				liczba_wystapila=liczba_wystapila+2;
			}
		}
		if(liczba_wystapila==1){
			cout<<"x"<<k<<"="<<wektor_b[wiersz]<<" ";
		}
		else{
			cout<<"x"<<k<<"="<<0<<" ";
		}
	}
	cout<<endl<<"Koszt dla otrzymanego punktu wynosi: "<<-obliczony_koszt<<endl;
}

void Simplex::wyswietl_tabele_simplex(){
	cout.width(11);
	for(int k=0;k<ilosc_rownan+ilosc_zmiennych;k++){		
		cout<<"x"<<k;
		cout.width(5);
	}
	cout<<"b";
	cout<<endl;
	cout.width(12);
	for(int k=0;k<=6*(ilosc_rownan+ilosc_zmiennych);k++){
		cout<<"-";	
	}
	cout<<endl;
	for(int w=0;w<ilosc_rownan;w++){
		cout.width(6);
		cout<<"";
		for(int k=0;k<ilosc_zmiennych+ilosc_rownan;k++){
			cout.width(6);
			cout<<macierz_wspolczynnikow[k][w];
		}	
		cout.width(6);
		cout<<wektor_b[w]<<endl;
	}
	cout<<"Koszt ";
	for(int k=0;k<ilosc_zmiennych+ilosc_rownan;k++){
		cout.width(6);
		cout<<wektor_funkcji_kosztu[k];
	}	
	cout.width(6);
	cout<<obliczony_koszt<<endl<<endl;
}

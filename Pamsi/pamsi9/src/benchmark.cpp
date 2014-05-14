/*!
\file
\brief Plik zawierajacy definicje metod klasy benchmark.

*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
#include "przykladowy_program.hh"	
#include "benchmark.hh"
#include "komunikacja.hh"
#include "konfiguracja.hh"
#include "tab_hash.hh"
#include "element.hh"
using namespace std;


/*!
\brief Metoda wykonaj_sprawdzenie_algorytmu

\param[in] Ilosc wykonan algorytmu.
*/
bool benchmark::wykonaj_sprawdzenie_algorytmu(int ile_razy){
	clock_t czas_trwania_programu;
	Przykladowy_program program;
	Komunikacja dialog;
	string nazwa;
	dlugosc_tablicy_czasow=0;
	int plik_ze_sciezkami=0;
 	int i,j,k;
 	ostringstream ss;
 //	char * plik_sprawdzajacy=(char *)"sprawdzenie.txt";
	char * plik_wyjsciowy=(char *)"wyjscie.txt";
 	char * plik_wynikowy=(char *)"wynik.txt";
 	char * plik_latex=(char*)"graf.tex";
 	string podstawa_nazwy_pliku_z_danymi= "dane";
 	dlugosc_tablicy_czasow=ile_razy;
 	tablica_czasow=new double[ile_razy];
// 	cout<<endl<<"Czy chcesz tworzyc nowe pliki .txt? (tak/nie)"<<endl;
// 	if(dialog.pytanie_tak_nie()){
//		plik_ze_sciezkami=2;	
//	}
//	else{
//	 	cout<<endl<<"Czy chcesz otworzyc plik ze sciezkami do plikow .txt? (tak/nie)"<<endl;
// 		if(dialog.pytanie_tak_nie()){												//jesli nalezy otworzyc plik ze sciezkami do innych plikow z danymi
// 			do{
// 				cout<<"Wprowadz nazwe pliku:"<<endl;
// 				cin>>nazwa;
//	 		}while(dialog.wczytaj_stringi_do_tablicy(dane,nazwa)==false);
// 			if(dane.dlugosc_tablicy<ile_razy){
//	 			cerr<<"Ilosc znajdujacych sie w pliku sciezek jest mniejsza od ilosci powtorzen."<<endl;	
// 			}
//	 		plik_ze_sciezkami=1;
// 		}
// 	}
 	for(i=0,j=0;j<ile_razy;i++,j++){													//wykonanie algortmu odpowiednia ilosc razy
// 		do{																			//wczytaj dane z pliku o nazwie																	
//	 		if(!plik_ze_sciezkami){														//podanej recznie
// 				cout<<"Wprowadz nazwe pliku z danymi:"<<endl;
// 				cin.clear();
// 				cin>>nazwa;
//			}
//			else if(plik_ze_sciezkami==1){																	//lub wczesniej wpisanej
//				if(i<dane.dlugosc_tablicy){
//					nazwa=dane.napisy[i];
//				}
//				else{
//					cerr<<endl<<"Skonczyly sie nazwy podane w pliku"<<endl<<endl;
//					i=0;
//				}
//			}
//			else{
//				if(nazwa!=podstawa_nazwy_pliku_z_danymi){
//					nazwa=podstawa_nazwy_pliku_z_danymi;
//					ss << j;													//tutaj poprawic zeby nazwy byly prawidlowe
//					nazwa+=ss.str();
//					nazwa+=".txt";
//					cout<<"Stworzylem nazwe: "<<nazwa<<endl;
//					program.stworz_plik_testowy(ILOSC_DANYCH,(char*)nazwa.c_str());
//				}
//			}
//	 	}while(dialog.wczytaj_klucze_i_dane(program.dane,nazwa)==false);
	 	program.zacznij_pomiar_czasu();
	 	for(k=0;k<ILE_RAZY_POWTORZYC;k++){
 			program.wykonaj_program(program.dane);
 		}
		czas_trwania_programu=program.zakoncz_pomiar_czasu();
 	  	tablica_czasow[j]=(double)czas_trwania_programu/CLOCKS_PER_SEC/ILE_RAZY_POWTORZYC;
  	 	cout<<"Wykonanie programu zajelo "<<(float)czas_trwania_programu/CLOCKS_PER_SEC<<" sekundy"<<endl<<endl;
   }
   wypisz_tablice_czasow();
   zapisz_czasy_do_pliku(plik_wynikowy);
   zapisz_graf_do_pliku_latex(plik_latex,program.dane);
   return true;
};

/*!
\brief Metoda oblicz_sredni_czas_wykonywania_algorytmu

\return Zwraca wartosc srednia potrzebna na wykonanie algorytmu w sekundach (liczba double).
*/
double benchmark::oblicz_sredni_czas_wykonywania_algorytmu(){
	double zmienna=0;
	srednia=0;
	int i;
	for(i=0;i<dlugosc_tablicy_czasow;i++){
		zmienna+=tablica_czasow[i];
	}
	srednia=(double)zmienna/dlugosc_tablicy_czasow;
	cout<<"Sredni czas wykonywania algorytmu to "<<srednia<<" sekundy"<<endl;
	return srednia;
};

void benchmark::wypisz_tablice_czasow(){
	int i;
	for(i=0;i<dlugosc_tablicy_czasow;i++){
		cout<<tablica_czasow[i]<<endl;
	}
}

bool benchmark::zapisz_czasy_do_pliku(char *nazwa){
	fstream plik_wyjsciowy,plik_konfiguracji;
	int i;
	string napis;
	Komunikacja dialog;
//	cout<<"Czy zapisac wynik obliczen? (t/n)"<<endl;
	if(1){//dialog.pytanie_tak_nie()){	
		plik_wyjsciowy.open(nazwa,ios::out);
		if(plik_wyjsciowy.good()==false){
			cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
			return false;
		}
		for(i=0;i<dlugosc_tablicy_czasow;i++)
			plik_wyjsciowy<<tablica_czasow[i]<<endl;
		
		#ifdef KONFIGURACJA
		plik_konfiguracji.open((char*)"inc/konfiguracja.hh",ios::in);
		plik_wyjsciowy<<endl<<endl;
		while(plik_konfiguracji.eof()!=true){
			getline (plik_konfiguracji,napis);
			plik_wyjsciowy<<napis<<endl;
		}
		#endif
		
		plik_wyjsciowy.close();
		cout<<"Dane zostaly poprawnie zapisane do pliku"<<endl;
	}	
	return true;
};

bool benchmark::zapisz_graf_do_pliku_latex(char *plik_latex,Tablica& dane){
	fstream plik_wyjsciowy,plik_wstepu,plik_zakonczenia;
	int i,j;
	string napis;
	string wezel="  \\Vertex[x=";
	string krawedz="  \\Edge[label=$";
	string pomiedzy="  \\tikzstyle{LabelStyle}=[fill=white,sloped]";
	Komunikacja dialog;
	Tablica_hash <Element<string,int>,string,int> struktura;

	srand( time( NULL ));
//	cout<<"Czy zapisac wynik obliczen? (t/n)"<<endl;
	if(1){//dialog.pytanie_tak_nie()){	
		plik_wyjsciowy.open(plik_latex,ios::out);
		if(plik_wyjsciowy.good()==false){
			cerr<<"Nie udalo sie zapisac danych do pliku"<<endl;
			return false;
		}
		plik_wstepu.open((char*)"wstep_latex.txt",ios::in);
		while(plik_wstepu.eof()!=true){
			getline (plik_wstepu,napis);
			plik_wyjsciowy<<napis<<endl;
		}
		plik_wstepu.close();
		for(j=0,i=0;dane.dlugosc_tablicy!=i;i++){ 
			if(struktura.znajdz1(dane.klucze[i])==false){
				j++;
				struktura.dodaj(dane.klucze[i],dane.klucze2[i],dane.tablica[i]);
				plik_wyjsciowy<<wezel<<j<<",y="<<(rand()%(int)MAKSYMALNA_ILOSC_DANYCH_BEZ_POWTORZEN);   		
				plik_wyjsciowy<<"]{"<<dane.klucze[i]<<"}"<<endl; 
			}
			if(struktura.znajdz1(dane.klucze2[i])==false){
				j++;
				struktura.dodaj(dane.klucze2[i],dane.klucze[i],dane.tablica[i]);
				plik_wyjsciowy<<wezel<<j<<",y="<<(rand()%(int)MAKSYMALNA_ILOSC_DANYCH_BEZ_POWTORZEN);   		
				plik_wyjsciowy<<"]{"<<dane.klucze2[i]<<"}"<<endl; 
			}
      	}
      	plik_wyjsciowy<<pomiedzy<<endl;
		for(i=0;dane.dlugosc_tablicy!=i;i++){ 
			if(dane.klucze[i]!=dane.klucze2[i]){
				plik_wyjsciowy<<krawedz<<dane.tablica[i]<<"$]("<<dane.klucze[i]<<")("<<dane.klucze2[i]<<")"<<endl; 	
			}  		
      	}		
		
//		plik_zakonczenia.open((char*)"zakonczenie_latex.txt",ios::in);
//		plik_wyjsciowy<<endl<<endl;
//		while(plik_zakonczenia.eof()!=true){
//			getline (plik_zakonczenia,napis);
//			plik_wyjsciowy<<napis<<endl;
//		}		
		plik_wyjsciowy<<"\\end{tikzpicture}"<<endl<<"}"<<"\\end{figure}"<<endl<<"\\end{document}"<<endl;
		plik_wyjsciowy.close();
		cout<<"Dane zostaly poprawnie zapisane w postaci grafu."<<endl;
	}	
	return true;
};
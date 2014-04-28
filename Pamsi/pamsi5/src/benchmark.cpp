/*!
\file
\brief Plik zawierajacy definicje metod klasy benchmark.

*/

#include <iostream>
#include <ctime>
#include <string>
#include "przykladowy_program.hh"	
#include "benchmark.hh"
#include "komunikacja.hh"
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
 	int i;
 //	char * plik_sprawdzajacy=(char *)"sprawdzenie.txt";
	 char * plik_wyjsciowy=(char *)"wyjscie.txt";
 	char * plik_wynikowy=(char *)"wynik.txt";
 	dlugosc_tablicy_czasow=ile_razy;
 	tablica_czasow=new double[ile_razy];
 	cout<<endl<<"Czy chcesz otworzyc plik ze sciezkami do plikow .txt? (tak/nie)"<<endl;
 	if(dialog.pytanie_tak_nie()){												//jesli nalezy otworzyc plik ze sciezkami do innych plikow z danymi
 		do{
 			cout<<"Wprowadz nazwe pliku:"<<endl;
 			cin>>nazwa;
 		}while(dialog.wczytaj_stringi_do_tablicy(dane,nazwa)==false);
 		if(dane.dlugosc_tablicy<ile_razy){
	 		cerr<<"Ilosc znajdujacych sie w pliku sciezek jest mniejsza od ilosci powtorzen."<<endl;
 			return false;	
 		}
	 	plik_ze_sciezkami=1;
 	}
 	for(i=0;i<ile_razy;){													//wykonanie algortmu odpowiednia ilosc razy
 		do{																			//wczytaj dane z pliku o nazwie																	
	 		if(!plik_ze_sciezkami){														//podanej recznie
 				cout<<"Wprowadz nazwe pliku z danymi:"<<endl;
 				cin.clear();
 				cin>>nazwa;
			}
			else{																	//lub wczesniej wpisanej
				if(i<dane.dlugosc_tablicy)
					nazwa=dane.napisy[i];
				else{
					cerr<<"Skonczyly sie nazwy podane w pliku"<<endl;
					return false;
				}
			}
			i++;
	 	}while(dialog.wczytaj_klucze_i_dane(program.dane,nazwa)==false);
 		program.zacznij_pomiar_czasu();
 		program.wykonaj_program(program.dane);
 		czas_trwania_programu=program.zakoncz_pomiar_czasu();
// 		program.zapisz_dane_posortowane(plik_wyjsciowy);
// 		program.zapisz_dane(plik_wyjsciowy);
//   		program.porownaj_dane(plik_sprawdzajacy);
//		program.wypisz_dane();
   		tablica_czasow[i-1]=(double)czas_trwania_programu/CLOCKS_PER_SEC;
   		cout<<"Wykonanie programu zajelo "<<(float)czas_trwania_programu/CLOCKS_PER_SEC<<" sekundy"<<endl<<endl;	
   }
   wypisz_tablice_czasow();
   zapisz_czasy_do_pliku(plik_wynikowy);
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
	fstream plik_wyjsciowy;
	int i;
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
		plik_wyjsciowy.close();
		cout<<"Dane zostaly poprawnie zapisane do pliku"<<endl;
	}	
	return true;
};

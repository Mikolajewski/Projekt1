/*!
\file
\brief Plik zawierajacy definicje metod klasy Przykladowy_program

*/

#include <iostream>
#include "operacje.hh"
#include "tablica.hh"
#include "komunikacja.hh"
#include "program.hh"
#include "przykladowy_program.hh"
using namespace std;

/*!
\brief Metoda wykonaj_program

Wykonuje czynnosci zgodne z zadanym algorytme.
*/
bool Przykladowy_program::wykonaj_program(){
	int a,mnoznik,i,j;
	int zadanie;
	int koniec=0;
	Operacje operacje;
	Tablica pomocnicza;
	Komunikacja dialog;
	pomocnicza=dane;

	while(!koniec){
		koniec=0;
		cout<<endl<<"Jakie zadanie wykonac? (wprowadz liczbe)"<<endl<<"1      mnozenie"<<endl<<"2      zamien_liczby"<<endl<<"3      dodaj_tablice"<<endl<<"4      dodaj_element"<<endl<<"5      odwrot_tablice"<<endl<<"6      porownaj_tablice"<<endl<<"7      wypisz_dane"<<endl<<"8      koniec"<<endl<<endl;
		cin.clear();
		zadanie=dialog.pobierz_int();
		switch(zadanie){
			case 1:
				cout<<"Ile razy pomnozyc liczby?"<<endl;
				cin.clear();
				cin>>mnoznik;
				operacje.mnozenie(dane,mnoznik);
				break;
			case 2:
				cout<<"Pierwszy element do zamiany."<<endl;
				cin>>i;
				cout<<"Drugi element do zamiany"<<endl;
				cin>>j;
				operacje.zamien_elementy(dane,i,j);
				break;
			case 3:
				cout<<"Dodaje ta sama tablice na koniec."<<endl;
				operacje.dodaj_tablice(dane,pomocnicza);
				break;
			case 4:
				cout<<"Jaki element wpisac."<<endl;
				cin>>a;
				operacje.dodaj_element(dane,a);
				break;
			case 5:
				operacje.odwroc_tablice(dane);
				break;
			case 6:
				cout<<"Porownuje tablice z pamieci z ta ktora znajduje sie w pliku."<<endl;
				cout<<"Aby tego dokonac potrzebne bylo przeciazenie operatora = i ==."<<endl;
				if(pomocnicza==dane)
					cout<<"Dane zgodne."<<endl;
				else
					cout<<"Dane niezgodne."<<endl;
				break;
			case 7:
				wypisz_dane();
				break;
			case 8:
				koniec=1;
				break;
			default:
				cerr<<"Nie znaleziono komendy "<<zadanie<<endl;
				break;
		}
	}
return true;
};

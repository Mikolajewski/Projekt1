/*!
\file
\brief Plik zawierajacy deklaracje i definicje klasy Sortowanie.

*/

#ifndef SORTOWANIE
#define SORTOWANIE

/*!
\brief Klasa Sortowanie

Klasa  zawierajaca metody konieczne do sortowania liczb.
*/
template <class typ>
class Sortowanie{
	private:
/*!
\brief Metoda zamien

\param[in] j,i wskazniki do zamienianych liczb .
*/		
		void zamien(typ* j,typ* i);


/*!
\brief Metoda wypisz

Metoda wypisujaca tablice od wskaznika do wskaznika
\param[in] poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void wypisz(typ* poczatek,typ* koniec);
		
/*!
\brief Metoda buduj_kopiec

Tworzy strukture wykorzystywana podczas algorytmu kopcowania
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void buduj_kopiec(typ* poczatek,typ* koniec);

/*!
\brief Metoda stworz_kopczyk

Tworzy strukture wykorzystywana podczas algorytmu kopcowania
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void stworz_kopczyk(typ* poczatek,typ* koniec,int i);
		
/*!
\brief Metoda scalanie

Laczy ze soba elementy po wykonaniu sortowanie przez scalanie
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/		
		void scalanie(typ* poczatek,typ* srodek,typ *koniec);
		
/*!
\brief Metoda quicksort_optymalizacja

Metoda wykorzystywana do przyspieszenia algorytmu
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void quicksort_optymalizacja(typ* poczatek,typ* koniec);		
	public:
		
/*!
\brief Metoda quicksort

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void quicksort(typ* poczatek,typ* koniec);

/*!
\brief Metoda merge

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
		void merge(typ* poczatek,typ* koniec);

/*!
\brief Metoda kopcowanie

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/

		void kopcowanie(typ* poczatek,typ* koniec);

};


/*!
\brief Metoda zamien

\param[in] j,i wskazniki do zamienianych liczb .
*/	
template <class typ>
void Sortowanie <typ>::zamien(typ* j,typ* i){
	typ element;
	element=*j;
	*j=*i;
	*i=element;
}

/*!
\brief Metoda wypisz

Metoda wypisujaca tablice od wskaznika do wskaznika
\param[in] poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::wypisz(typ* poczatek, typ* koniec){
	typ* p=poczatek;
	typ* k=koniec;
	while(p<=k){
		cout<<*p<<" ";//<<p<<endl;
		p++;
	}
	cout<<endl;
}
		
/*!
\brief Metoda quicksort_optymalizacja

Metoda wykorzystywana do przyspieszenia algorytmu
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::quicksort_optymalizacja(typ* poczatek,typ* koniec){
	int pomocnicza=0;
	typ* srodek;
	srodek=poczatek+(koniec-poczatek)/2;
	if(*poczatek<*koniec)
		pomocnicza+=1;
	else
		pomocnicza+=2;
	if(*poczatek<*srodek)
		pomocnicza+=10;
	else
		pomocnicza+=20;
	if(*srodek<*koniec)
		pomocnicza+=100;
	else
		srodek+=200;
	if(pomocnicza==121||pomocnicza==212){
		zamien(poczatek,koniec);
	}
	if(pomocnicza==111||pomocnicza==222){
		zamien(srodek,koniec);	
	}
}

/*!
\brief Metoda quicksort

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::quicksort(typ* poczatek,typ* koniec){
	typ* wsk_mniej=poczatek;
	typ* wsk_wieksz;
	typ* odniesienie=koniec;
	int zmiana;
//	if(koniec-poczatek>4){
//		quicksort_optymalizacja(poczatek,koniec);
//	}
	if(koniec-poczatek>0){
		wsk_wieksz=koniec-1;
		while(wsk_mniej<wsk_wieksz){
			zmiana=0;
			if(*wsk_mniej<*odniesienie){
				wsk_mniej++;
				zmiana++;
			}
			if(*wsk_wieksz>*odniesienie&&wsk_wieksz<koniec){
				wsk_wieksz--;
				zmiana++;
			}
			if(zmiana==0){
				zamien(wsk_mniej,wsk_wieksz);
				wsk_mniej++;
				wsk_wieksz--;
			}
	//	cout<<"petla"<<endl;
		}
		if(*wsk_wieksz>*odniesienie){
			zamien(wsk_wieksz,odniesienie);
		}
		else{
			zamien(wsk_wieksz+1,odniesienie);
		}
		if(wsk_wieksz!=poczatek){
			quicksort(poczatek,wsk_wieksz);
		}
		if(wsk_mniej!=koniec){
			quicksort(wsk_wieksz+1,koniec);
		}
	}
//	cout<<"quicksort"<<endl;
}

/*!
\brief Metoda merge

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::merge(typ* poczatek,typ* koniec){
	typ* srodek;
	if(poczatek!=koniec){
		srodek=poczatek+(koniec-poczatek)/2;
		merge(poczatek,srodek);
		merge(srodek+1,koniec);
		scalanie(poczatek,srodek,koniec);
	}
}

/*!
\brief Metoda scalanie

Laczy ze soba elementy po wykonaniu sortowanie przez scalanie
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/	
template <class typ>
void Sortowanie <typ>::scalanie(typ* poczatek,typ* srodek,typ *koniec){
	typ* pomocnicza;
	typ* wpisz,* wskaznik,* wsk_pom,* koniec_pom;
	int k=0,i;
	if(koniec-srodek==srodek-poczatek)        //jesli jest nieparzysta ilosc liczb
		k=1;						
	pomocnicza=new typ[koniec-srodek+k];			//odpowiednio powieksz tablice pomocnicza		
	koniec_pom=pomocnicza+(koniec-srodek+k-1);		//wyznacz koniec tablicy pomocniczej
	for(i=0;i<koniec-srodek+k;i++){        	      	//wpisz liczbe srodkowa do tablicy pomocniczej
		pomocnicza[i]=poczatek[i];
	}
	wpisz=poczatek;
	wskaznik=srodek+1;
	wsk_pom=pomocnicza;
	while(wsk_pom<=koniec_pom&&wskaznik<=koniec){
		if(*wsk_pom<*wskaznik){
			*wpisz=*wsk_pom;
			wsk_pom++;
		}
		else{
			*wpisz=*wskaznik;
			wskaznik++;
		}
		wpisz++;
	}
	while(wsk_pom<=koniec_pom){
		*wpisz=*wsk_pom;
		wsk_pom++;
		wpisz++;
	}
	while(wskaznik<=koniec){
		*wpisz=*wskaznik;
		wskaznik++;
		wpisz++;
	}
}

/*!
\brief Metoda buduj_kopiec

Tworzy strukture wykorzystywana podczas algorytmu kopcowania
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::buduj_kopiec(typ* poczatek,typ* koniec){
	int i;
	for(i=(koniec-poczatek+1)/2;i>0;i--)
		stworz_kopczyk(poczatek,koniec,i-1);
}

/*!
\brief Metoda stworz_kopczyk

Tworzy strukture wykorzystywana podczas algorytmu kopcowania
\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::stworz_kopczyk(typ* poczatek,typ* koniec,int i){
	int zmienna,wielkosc;
	wielkosc=koniec-poczatek+1;
	do{
		zmienna=i;
		if(zmienna*2<wielkosc&&poczatek[2*zmienna]>poczatek[i]){
			i=zmienna*2;
		}	
		if(zmienna*2+1<wielkosc&&poczatek[2*zmienna+1]>poczatek[i]){
			i=zmienna*2+1;
		}	
		zamien(poczatek+zmienna,poczatek+i);
	}while(i!=zmienna);
}

/*!
\brief Metoda kopcowanie

\param[in]  poczatek, koniec wskazniki odpowiednich stron tabeli
*/
template <class typ>
void Sortowanie <typ>::kopcowanie(typ* poczatek,typ* koniec){
	buduj_kopiec(poczatek,koniec);
	for(int i=koniec-poczatek+1;i>1;i--){
		zamien(poczatek,poczatek+i-1);
		stworz_kopczyk((double*)poczatek,koniec-(koniec-poczatek+2-i),0);
	}
}
#endif

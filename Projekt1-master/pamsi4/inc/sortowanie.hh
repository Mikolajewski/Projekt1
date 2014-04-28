#ifndef SORTOWANIE
#define SORTOWANIE

template <class typ>
class Sortowanie{
	private:
		void zamien(typ* j,typ* i);
		void wypisz(typ* poczatek,typ* koniec);
		void buduj_kopiec(typ* poczatek,typ* koniec);
		void stworz_kopczyk(typ* poczatek,typ* koniec,int i);
		void scalanie(typ* poczatek,typ* srodek,typ *koniec);
		typ podziel(int tablica[], int p, int r) ;		
	public:
		void quicksort(int tablica[], int p, int r);
		void quicksort2(typ* poczatek,typ* koniec);
		void merge(typ* poczatek,typ* koniec);
		void kopcowanie(typ* poczatek,typ* koniec);

};

template <class typ>
void Sortowanie <typ>::zamien(typ* j,typ* i){
	typ element;
	element=*j;
	*j=*i;
	*i=element;
}

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
template <class typ>
typ Sortowanie <typ>::podziel(int tablica[], int p, int r) 
{
	int x = tablica[p]; 
	int i = p, j = r, w; 
	while (true)
	{
		while (tablica[j] > x)
			j--;
		while (tablica[i] < x) 
			i++;
		if (i < j) 
		{
			w = tablica[i];
			tablica[i] = tablica[j];
			tablica[j] = w;
			i++;
			j--;
		}
		else 
			return j;
	}
}
template <class typ>
void Sortowanie <typ>::quicksort(int tablica[], int p, int r) 
{
	int q;
	if (p < r) 
	{	
		q = podziel(tablica,p,r); 
		quicksort(tablica, p, q); 
		quicksort(tablica, q+1, r); 
	}
}



template <class typ>
void Sortowanie <typ>::quicksort2(typ* poczatek,typ* koniec){
	typ* i;
	typ* j;
	typ piwot;
	i=poczatek+(koniec-poczatek)/2;
	piwot=*i;
	*i=*koniec;
	j=poczatek;
	i=poczatek;
	while(i<koniec){
		if(*i<piwot){
			zamien(i,j);
			j++;
		}
		i++;
	}
	*poczatek=*j;
	*j=piwot;
	if(poczatek<j-1){
		quicksort2(poczatek,j-1);
	}
	if(j+1<koniec){
		quicksort2(j+1,koniec);
	}
}

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


template <class typ>
void Sortowanie <typ>::buduj_kopiec(typ* poczatek,typ* koniec){
	int i;
	for(i=(koniec-poczatek+1)/2;i>0;i--)
		stworz_kopczyk(poczatek,koniec,i-1);
}

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

template <class typ>
void Sortowanie <typ>::kopcowanie(typ* poczatek,typ* koniec){
	buduj_kopiec(poczatek,koniec);
	for(int i=koniec-poczatek+1;i>1;i--){
		zamien(poczatek,poczatek+i-1);
		stworz_kopczyk((int*)poczatek,koniec-(koniec-poczatek+2-i),0);
	}
}
#endif

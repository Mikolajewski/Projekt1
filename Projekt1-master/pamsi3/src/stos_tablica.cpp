#include <iostream>

using namespace std;


template <class typ>
class Stos_tablica{
	public:
		typ* stos;
		int ilosc_danych;
		bool is_empty();
		int size();
		void push(typ element);
		bool pop();
		Stos_tablica(){ilosc_danych=0;};
};

template <class typ>
bool Stos_tablica::is_empty(){
	return (ilosc_danych)>0?false:true;	
}

template <class typ>
int Stos_tablica::size(){
	return ilosc_danych;
}

template <class typ>
void Stos_tablica::push(typ element){
	typ pomocnicza[ilosc_danych];
	int i;
	for(i=0;i<ilosc_danych;i++){
		pomocnicza[i]=stos[ilosc_danych-i-1];
	}
	delate stos;
	ilosc_danych+=1;
	stos=new typ[ilosc_danych];
	for(i=0;i<ilosc_danych-1;i++)
		stos[i]=pomocnicza[ilosc_danych-i-1];
	stos[ilosc_danych-1]=element;
}

template <class typ>
bool Stos_tablica::pop(){
	if(is_empty()==false){
		delate stos[ilosc_danych-1];
		ilosc_danych-=1;
		return true;
	}
	else{
		cerr<<"Stos jest pusty."<<endl;
		return false;
	}
}


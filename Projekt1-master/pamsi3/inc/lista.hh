#include <iostream>
using namespace std;


template <class typ,class rodzaj_zmiennej>
class Lista{
	public:
		typ lista<rodzaj_zmiennej>;
		bool isEmpty();
		int size();
		void push(rodzaj_zmiennej zmienna);
		bool pop();
};

template <class typ,class rodzaj_zmiennej>
bool Lista<typ,rodzaj_zmiennej>::isEmpty(){
	cout<<"Metoda isEmpty() klasy Lista nie zosta³a nadpisana"<<endl;
	return false;
}

template <class typ,class rodzaj_zmiennej >
int Lista <typ,rodzaj_zmiennej>::size(){
	cout<<"Metoda size() klasy Lista nie zosta³a nadpisana"<<endl;
	return 1;
}

template <class typ,class rodzaj_zmiennej>
void Lista <typ,rodzaj_zmiennej>::push(rodzaj_zmiennej zmienna){
	cout<<"Metoda push() klasy Lista nie zosta³a nadpisana"<<endl;
}

template <class typ,class rodzaj_zmiennej>
bool Lista <typ,rodzaj_zmiennej>::pop(){
	cout<<"Metoda pop() klasy Lista nie zosta³a nadpisana"<<endl;
	return false;
}


#ifndef KONFIGURACJA
#define KONFIGURACJA

//              Opcje algorytmu
#define UWZGLEDNIC_WAGE_OSTATNIEJ_SCIEZKI  Nie //  Tak //  

//				Opcje benchmarku
#define ILOSC_DANYCH 40
#define ILE_RAZY_POWTORZYC 1

//				Opcje programu
#define TYP Graf //Tablica_hash //Drzewo //
#define PIERWSZY_ZNAK 'a'
#define ILOSC_MOZLIWYCH_ZNAKOW  ('z'-'a'+1)
#define ILOSC_SPRAWDZANYCH_ZNAKOW 1
#define POCZATKOWY_ROZMIAR_TABLICY (pow(ILOSC_MOZLIWYCH_ZNAKOW,ILOSC_SPRAWDZANYCH_ZNAKOW))
#define MAKSYMALNA_DLUGOSC_SLOWA 1
#define MAKSYMALNA_ILOSC_DANYCH_BEZ_POWTORZEN (pow(ILOSC_MOZLIWYCH_ZNAKOW,MAKSYMALNA_DLUGOSC_SLOWA))
#define MINIMALNA_WARTOSC 0
#define MAKSYMALNA_WARTOSC 100

//				Opcje gry
#define KOSZT_RUCHU_O_POLE	10
#define KOSZT_RUCHU_PO_SKOSIE	14

#endif
/*
 * konfiguracja.hh
 *
 *  Created on: May 25, 2014
 *      Author: Tomek
 */

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
#define ROZMIAR_X 100
#define ROZMIAR_Y 100
#define KOSZT_RUCHU_O_POLE	10
#define KOSZT_RUCHU_PO_SKOSIE	14
#define SZEROKOSC_POLA 27
#define PROCENTOWO_WYSP_MAX 25
#define PROCENTOWO_WYSP_MIN 15
#define MAX_ILOSC_WYSP 10
#define ROZMIAR_EKRANU_X 1350
#define ROZMIAR_EKRANU_Y 650
#define PREDKOSC_KUTRA 100
#define PREDKOSC_KRAZOWNIKA 80
#define PREDKOSC_LINIOWCA 60
#define PREDKOSC_PANCERNIKA 40

#define POCZATKOWA_ILOSC_PANCERNIKOW 2
#define POCZATKOWA_ILOSC_LINIOWCOW 2
#define POCZATKOWA_ILOSC_KRAZOWNIKOW 4
#define POCZATKOWA_ILOSC_KUTROW 1

enum rodzaj_pola{nic,ziemia,jednostka,budynek,maszynownia};
enum sprawnosc_pola_jednostki{sprawne,niesprawne};
enum kierunek{wschod,zachod,polnoc,poludnie};
enum rodzaj_statku{kuter,krazownik,liniowiec,pancernik};
enum zawodnik{czerwony,czarny};



#endif

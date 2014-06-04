/*
 * konfiguracja.hh
 *
 *  Created on: May 25, 2014
 *      Author: Tomek
 */

#ifndef KONFIGURACJA
#define KONFIGURACJA


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
#define GRACZ_ZIELONY czlowiek
#define GRACZ_FIOLETOWY czlowiek

#define ROZMIAR_X 100
#define ROZMIAR_Y 100
#define KOSZT_RUCHU_O_POLE	10
#define KOSZT_RUCHU_PO_SKOSIE	14
#define SZEROKOSC_POLA 27
#define PROCENTOWO_WYSP_MAX 25
#define PROCENTOWO_WYSP_MIN 15
#define MAX_ILOSC_WYSP 40
#define ROZMIAR_EKRANU_X 1350
#define ROZMIAR_EKRANU_Y 678


#define POCZATKOWA_ILOSC_PANCERNIKOW 1
#define POCZATKOWA_ILOSC_LINIOWCOW 0
#define POCZATKOWA_ILOSC_KRAZOWNIKOW 0
#define POCZATKOWA_ILOSC_KUTROW 0
#define PREDKOSC_KUTRA 180
#define PREDKOSC_KRAZOWNIKA 3000
#define PREDKOSC_LINIOWCA 2400
#define PREDKOSC_PANCERNIKA 1800
#define ZASIEG 100

#define OPOZNIENIE_W_RUCHU 0

enum typ_gracza{czlowiek,komputer};
enum rodzaj_pola{nic,ziemia,budynek,maszynownia_zielonego,maszynownia_fioletowego,jednostka_zielonego,jednostka_fioletowego};  //tutaj byla jednostka
enum sprawnosc_pola_jednostki{sprawne,wystrzelono,niesprawne};
enum kierunek{wschod,zachod,polnoc,poludnie};
enum rodzaj_statku{kuter,krazownik,liniowiec,pancernik};
enum zawodnik{fioletowy,zielony};
enum zdarzenie{brak,klikniecie,kolejnosc_fioletowego,kolejnosc_zielonego,strzela_fioletowy,strzela_zielony,nastepna_faza,potwierdzenie,koniec};


#endif

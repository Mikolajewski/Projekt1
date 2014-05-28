/*
 * main.cpp
 *
 *  Created on: May 25, 2014
 *      Author: Tomek
 */

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include "pole.hh"
#include "plansza.hh"
#include "konfiguracja.hh"
#include "gracz.hh"

using namespace std;

int main(){
	int i,j;
	int wys_x,wys_y;
	Plansza morze;
//	Pole** do_wyswietlenia;
	Gracz gracz_czarny;
	Gracz gracz_czerwony;
	gracz_czarny.wpisz_gracza(czarny);
	gracz_czerwony.wpisz_gracza(czerwony);


	srand( time( NULL ));
	sf::RenderWindow oknoAplikacji( sf::VideoMode(ROZMIAR_EKRANU_X,ROZMIAR_EKRANU_Y, 32 ), "Bitwa Morska");//, sf::Style::Fullscreen );
    sf::Event zdarzenie;

    sf::Texture _lad;
    _lad.loadFromFile( "obrazki/lad.png" );
    sf::Sprite lad;
    lad.setTexture(_lad);

    sf::Texture _statek;
    _statek.loadFromFile( "obrazki/statek.png" );
    sf::Sprite statek;
    statek.setTexture(_statek);

    sf::Texture _silnik;
    _silnik.loadFromFile( "obrazki/silnik.png" );
    sf::Sprite silnik;
    silnik.setTexture(_silnik);

    sf::Texture _woda;
    _woda.loadFromFile( "obrazki/morze.png" );
    sf::Sprite woda;
    woda.setTexture(_woda);
    oknoAplikacji.clear( sf::Color( 0,0,255 ) );
    wys_x=0;
    wys_y=0;    //<---------------zmienic dla bazy (widok poczatkowy)

	morze.stworz_plansze(ROZMIAR_X,ROZMIAR_Y);
	gracz_czarny.przypisz_plansze_gracza(morze.tab);
	gracz_czerwony.przypisz_plansze_gracza(morze.tab);

	for(int i=0;i<POCZATKOWA_ILOSC_PANCERNIKOW;i++){
		gracz_czarny.wprowadz_statek_na_plansze(pancernik);
		gracz_czerwony.wprowadz_statek_na_plansze(pancernik);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_LINIOWCOW;i++){
		gracz_czarny.wprowadz_statek_na_plansze(liniowiec);
		gracz_czerwony.wprowadz_statek_na_plansze(liniowiec);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_KRAZOWNIKOW;i++){
		gracz_czarny.wprowadz_statek_na_plansze(krazownik);
		gracz_czerwony.wprowadz_statek_na_plansze(krazownik);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_KUTROW;i++){
		gracz_czarny.wprowadz_statek_na_plansze(kuter);
		gracz_czerwony.wprowadz_statek_na_plansze(kuter);
	}
	morze.wyswietl();

    while( oknoAplikacji.isOpen() ){
        while( oknoAplikacji.pollEvent( zdarzenie ) ){
        	if( zdarzenie.type == sf::Event::MouseButtonPressed ){
        		//oknoAplikacji.clear( sf::Color( 0,0,255 ) );
        	}
        	if( zdarzenie.type == sf::Event::Closed )
        	{
        	    //tu np. zapisanie stanu gry
       	    oknoAplikacji.close();
        	}
        		if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.x<SZEROKOSC_POLA) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 71)){
        			if(wys_x>0){
        				wys_x--;
        				cout<<"przesuwam w lewo"<<endl;
        			}
        		}
        		else if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.x>ROZMIAR_EKRANU_X-SZEROKOSC_POLA && zdarzenie.mouseMove.x<ROZMIAR_EKRANU_X) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 72)){
        			if(wys_x<ROZMIAR_X-ROZMIAR_EKRANU_X/SZEROKOSC_POLA){
        				wys_x++;
        				cout<<"przesuwam w prawo"<<endl;
        			}
        		}
        		if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.y<SZEROKOSC_POLA) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 73)){
        			if(zdarzenie.mouseMove.y<SZEROKOSC_POLA){
        				cout<<"myszka"<<endl;
        			}

        			if(wys_y>0){
        				wys_y--;
        				cout<<"przesuwam w gore"<<endl;
        			}
        		}
        		else if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.y>ROZMIAR_EKRANU_Y-SZEROKOSC_POLA && zdarzenie.mouseMove.y<ROZMIAR_EKRANU_Y) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 74)){
        			if(wys_y<ROZMIAR_Y-ROZMIAR_EKRANU_Y/SZEROKOSC_POLA){
        				wys_y++;
        				cout<<"przesuwam w dol"<<endl;
        			}
        		}

//       		cout<<zdarzenie.key.code<<endl;
        	if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape )
        	{
        	    //obsługa zajścia zdarzenia wciśnięcia klawisza ESC
        	    oknoAplikacji.close(); //np. zamknięcie aplikacji
        	}
        }
//    	for(i=0;i*SZEROKOSC_POLA<ROZMIAR_EKRANU_X && i<ROZMIAR_X;i++){
//    		for(j=0;j*SZEROKOSC_POLA<ROZMIAR_EKRANU_Y && j<ROZMIAR_Y;j++){
//    			if(morze.zwroc_pole(i,j)->zwroc_rodzaj_terenu()==nic){
//    				woda.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
//    				oknoAplikacji.draw(woda);
//    			}
//    			else if(morze.zwroc_pole(i,j)->zwroc_rodzaj_terenu()==ziemia){
//    				lad.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
//    				oknoAplikacji.draw(lad);
//    			}
//            }
//        }
//    	do_wyswietlenia=gracz_czarny.zwroc_widok_gracza(wys_x,wys_y);

        for(i=0;i*SZEROKOSC_POLA<ROZMIAR_EKRANU_X && i<ROZMIAR_X;i++){
    		for(j=0;j*SZEROKOSC_POLA<ROZMIAR_EKRANU_Y && j<ROZMIAR_Y;j++){
    			if(gracz_czarny.zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==nic){
    				woda.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
    				oknoAplikacji.draw(woda);
    			}
    			else if(gracz_czarny.zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==ziemia){
    				lad.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
    				oknoAplikacji.draw(lad);
    			}
    			else if(gracz_czarny.zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==jednostka){
//    				cout<<"statek<-------------------------------"<<endl;
    				statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
    				oknoAplikacji.draw(statek);
    			}
    			else if(gracz_czarny.zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==maszynownia){
    				silnik.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
    				oknoAplikacji.draw(silnik);
    			}
            }
        }
    	oknoAplikacji.display();
        oknoAplikacji.clear( sf::Color( 0,0,255 ) );
    }
    return 0;
}



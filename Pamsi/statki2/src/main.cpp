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
#include <windows.h>
#include "konfiguracja.hh"
#include "plansza.hh"
#include "gracz.hh"
#include "statek.hh"
#include "pole.hh"

using namespace std;

static sf::RenderWindow oknoAplikacji( sf::VideoMode(ROZMIAR_EKRANU_X,ROZMIAR_EKRANU_Y, 32 ), "Bitwa Morska");//, sf::Style::Fullscreen );
 int wys_x=0,wys_y=0;
Plansza morze;
int klikniecie_x,klikniecie_y;

zdarzenie obsluga_zdarzen(){
	 sf::Event zdarzenie;
//	 cout<<"zaczynam obsluge zdarzen"<<endl;
   while( oknoAplikacji.pollEvent( zdarzenie ) ){
    	if( zdarzenie.type == sf::Event::Closed ){
   	    oknoAplikacji.close();
    	}
		else if((zdarzenie.type == sf::Event::MouseButtonPressed)){
			klikniecie_x= sf::Mouse::getPosition( oknoAplikacji ).x/SZEROKOSC_POLA;
			klikniecie_y= sf::Mouse::getPosition( oknoAplikacji ).y/SZEROKOSC_POLA;
//			cout<<"Kliknieto: "<<klikniecie_x<<" "<<klikniecie_y<<endl;
//			cout<<"Pozycja: "<<klikniecie_x+wys_x<<" "<<klikniecie_y+wys_y<<endl;
			return klikniecie;
		}
   		if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.x<SZEROKOSC_POLA) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 71)){
   			if(wys_x>0){
   				wys_x--;
   			}
   		}
   		else if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.x>ROZMIAR_EKRANU_X-SZEROKOSC_POLA && zdarzenie.mouseMove.x<ROZMIAR_EKRANU_X) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 72)){
   			if(wys_x<ROZMIAR_X-ROZMIAR_EKRANU_X/SZEROKOSC_POLA){
   				wys_x++;
   			}
   		}
   		if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.y<SZEROKOSC_POLA) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 73)){
   			if(zdarzenie.mouseMove.y<SZEROKOSC_POLA){
//   				cout<<"myszka"<<endl;
   			}
    			if(wys_y>0){
   				wys_y--;
   			}
   		}
   		else if((zdarzenie.type == sf::Event::MouseMoved && zdarzenie.mouseMove.y>ROZMIAR_EKRANU_Y-SZEROKOSC_POLA && zdarzenie.mouseMove.y<ROZMIAR_EKRANU_Y) || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == 74)){
   			if(wys_y<ROZMIAR_Y-ROZMIAR_EKRANU_Y/SZEROKOSC_POLA){
   				wys_y++;
   			}
   		}

//       		cout<<zdarzenie.key.code<<endl;
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape ){
   			oknoAplikacji.close(); //np. zamknięcie aplikacji
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num1 ){
   			return kolejnosc_fioletowego;
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num2){
   			return kolejnosc_zielonego;
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num4){
   			return strzela_zielony;
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Num3){
   			return strzela_fioletowy;
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space){
   			return nastepna_faza;
    	}
   		if( zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Tab){
   			return potwierdzenie;
    	}
}
//    cout<<"koncze obsluge zdarzen"<<endl;
    return brak;
}


void wyswietl_gre(Gracz* zawodnik){
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

	    sf::Texture _czarny;
	    _czarny.loadFromFile( "obrazki/czarny.png" );
	    sf::Sprite czarny;
	    czarny.setTexture(_czarny);

	    sf::Texture _czerwony;
	    _czerwony.loadFromFile( "obrazki/czerwony.png" );
	    sf::Sprite czerwony;
	    czerwony.setTexture(_czerwony);

	    sf::Texture _woda;
	    _woda.loadFromFile( "obrazki/morze.png" );
	    sf::Sprite woda;
	    woda.setTexture(_woda);

	    sf::Texture _uszkodzony;
	    _uszkodzony.loadFromFile( "obrazki/trafiony.png" );
	    sf::Sprite uszkodzony;
	    uszkodzony.setTexture(_uszkodzony);
	    oknoAplikacji.clear( sf::Color( 0,0,255 ) );

	    sf::Texture _wystrzelono;
	    _wystrzelono.loadFromFile( "obrazki/wystrzelono.png" );
	    sf::Sprite strzelono;
	    strzelono.setTexture(_wystrzelono);
	    oknoAplikacji.clear( sf::Color( 0,0,255 ) );

        sf::CircleShape kolo;
        kolo.setOrigin( sf::Vector2f( SZEROKOSC_POLA/3, SZEROKOSC_POLA/3) );
        kolo.setRadius(SZEROKOSC_POLA/3);
        kolo.setFillColor( sf::Color::Red );

	    ///////////////////////////////////////wyswietlanie///////////////////////////////////////
	            for(int i=0;i*SZEROKOSC_POLA<ROZMIAR_EKRANU_X && i<ROZMIAR_X;i++){
	        		for(int j=0;j*SZEROKOSC_POLA<ROZMIAR_EKRANU_Y && j<ROZMIAR_Y;j++){
	        			if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==nic){
	    //    				cout<<"woda"<<endl;
	        				woda.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(woda);
	        			}
	        			else if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==ziemia){
	        				lad.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(lad);
	        			}
	    //    			else if(zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==jednostka){
	    //    				statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	    //    				oknoAplikacji.draw(statek);
	    //    			}
	        			else if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==maszynownia_fioletowego){
	        				silnik.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(silnik);
	        				if(zawodnik->sprawdz_czy_zaznaczone(wys_x+i,wys_y+j)==true){
	        					statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        					oknoAplikacji.draw(statek);
	        				}
	        				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==niesprawne){
	        					uszkodzony.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        			        kolo.setPosition(i*SZEROKOSC_POLA+SZEROKOSC_POLA/2, j*SZEROKOSC_POLA+SZEROKOSC_POLA/2 );
	            				oknoAplikacji.draw(kolo);
	        				}
	        			}
	        			else if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==maszynownia_zielonego){
	        				silnik.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(silnik);
	        				if(zawodnik->sprawdz_czy_zaznaczone(wys_x+i,wys_y+j)==true){
	        					statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        					oknoAplikacji.draw(statek);
	        				}
	        				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==niesprawne){
	        					uszkodzony.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        			        kolo.setPosition(i*SZEROKOSC_POLA+SZEROKOSC_POLA/2, j*SZEROKOSC_POLA+SZEROKOSC_POLA/2 );
	            				oknoAplikacji.draw(kolo);
	        				}
	        			}
	        			else if( zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==jednostka_fioletowego){
	    //    				cout<<"czerwony"<<endl;
	        				czerwony.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(czerwony);
	        				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->czy_zaznaczony()==true){
	    //    					cout<<"zmieniam na zaznaczony"<<endl;
	        					if(zawodnik->sprawdz_czy_zaznaczone(wys_x+i,wys_y+j)==true){
	        						statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        						oknoAplikacji.draw(statek);
	        					}
	        				}
	        				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==niesprawne){
	        					uszkodzony.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        			        kolo.setPosition(i*SZEROKOSC_POLA+SZEROKOSC_POLA/2, j*SZEROKOSC_POLA+SZEROKOSC_POLA/2 );
	            				oknoAplikacji.draw(kolo);
	        				}
	        				else if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==wystrzelono){
	        					strzelono.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	            				oknoAplikacji.draw(strzelono);
	        				}
	        			}
	        			else if( zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_rodzaj_terenu()==jednostka_zielonego){
	        				czarny.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	        				oknoAplikacji.draw(czarny);
	           				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->czy_zaznaczony()==true){
		        				if(zawodnik->sprawdz_czy_zaznaczone(wys_x+i,wys_y+j)==true){
		        					statek.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
		            				oknoAplikacji.draw(statek);
		        				}
	            			}
	        				if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==niesprawne){

	        			        kolo.setPosition(i*SZEROKOSC_POLA+SZEROKOSC_POLA/2, j*SZEROKOSC_POLA+SZEROKOSC_POLA/2 );
	        					uszkodzony.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	            				oknoAplikacji.draw(kolo);
	        				}
	        				else if(zawodnik->zwroc_widok_gracza(wys_x,wys_y)[i][j].zwroc_statek()->zwroc_sprawnosc_pola(wys_x+i,wys_y+j)==wystrzelono){
	        					strzelono.setPosition(i*SZEROKOSC_POLA,j*SZEROKOSC_POLA);
	            				oknoAplikacji.draw(strzelono);
	        				}
	        			}
	                }
	            }
	    //        cout<<"skonczylem wyswietlac"<<endl;
	        	oknoAplikacji.display();
	            oknoAplikacji.clear( sf::Color( 0,0,255 ) );
}

int main(){
//	int i,j;
//	Pole** do_wyswietlenia;
	Gracz gracz_zielony;
	Gracz gracz_fioletowy;
	Gracz* zawodnik;
	gracz_zielony.wpisz_kolor_gracza(zielony);
	gracz_zielony.wpisz_rodzaj_gracza(GRACZ_ZIELONY);

	gracz_fioletowy.wpisz_kolor_gracza(fioletowy);
	gracz_fioletowy.wpisz_rodzaj_gracza(GRACZ_FIOLETOWY);

	zdarzenie ostatnia_akcja=kolejnosc_fioletowego;
	bool zaznaczono_okret=false;
	Statek* okret=NULL;
	bool ruch_zielonego=false;
	bool faza_ruchu=true;
	bool atak_fioletowego=true;
	bool wykonano_ruch=false;
	rodzaj_pola teren=nic;
	kierunek zwrot=zachod;
	bool zielony_zakonczyl_faze_ataku=false;
	bool fioletowy_zakonczyl_faze_ataku=false;

	srand( time( NULL ));


	zawodnik=&gracz_fioletowy;
    wys_x=0;
    wys_y=0;    //<---------------zmienic dla bazy (widok poczatkowy)

	morze.stworz_plansze(ROZMIAR_X,ROZMIAR_Y);
	gracz_zielony.przypisz_plansze_gracza(morze.tab);
	gracz_fioletowy.przypisz_plansze_gracza(morze.tab);

	for(int i=0;i<POCZATKOWA_ILOSC_PANCERNIKOW;i++){
		gracz_zielony.wprowadz_statek_na_plansze(pancernik);
		gracz_fioletowy.wprowadz_statek_na_plansze(pancernik);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_LINIOWCOW;i++){
		gracz_zielony.wprowadz_statek_na_plansze(liniowiec);
		gracz_fioletowy.wprowadz_statek_na_plansze(liniowiec);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_KRAZOWNIKOW;i++){
		gracz_zielony.wprowadz_statek_na_plansze(krazownik);
		gracz_fioletowy.wprowadz_statek_na_plansze(krazownik);
	}
	for(int i=0;i<POCZATKOWA_ILOSC_KUTROW;i++){
		gracz_zielony.wprowadz_statek_na_plansze(kuter);
		gracz_fioletowy.wprowadz_statek_na_plansze(kuter);
	}
	morze.wyswietl();

    while( oknoAplikacji.isOpen() && ostatnia_akcja!=koniec ){

///////////////KOMPUTER///////////////////
		if(faza_ruchu==true && wykonano_ruch==false && zawodnik->zwroc_rodzaj_gracza()==komputer){
				cout<<"komputer"<<endl;
				zawodnik->wykonaj_ruch_statkow();
//				wykonano_ruch=true;
				ruch_zielonego=!ruch_zielonego;
				if(ruch_zielonego==true){
					zawodnik=&gracz_zielony;
		    		zawodnik->przygotuj_statki_do_ruchu();
				}
				else{
					zawodnik=&gracz_fioletowy;
		    		zawodnik->przygotuj_statki_do_ruchu();
				}
	    		if(okret!=NULL){
	    			okret->odznacz_statek();
	    		}
    			zaznaczono_okret=false;
	    		cout<<"zakonczylem akcje komputera"<<endl;
		}



///////////////CZLOWIEK//////////////////
    	if(faza_ruchu==true && ostatnia_akcja==klikniecie){
    		cout<<"bylo klikniecie"<<endl;
    		teren=morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y)->zwroc_rodzaj_terenu();
    		if(ruch_zielonego == true &&( teren==jednostka_zielonego ||   teren==maszynownia_zielonego)){
    			cout<<"zaznaczam statek"<<endl;
    			if(okret!=NULL){
    				okret->odznacz_statek();
    			}
    			okret=morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y)->zwroc_statek();
    			okret->zaznacz_statek();
    			zaznaczono_okret=true;
    			cout<<"skonczylem zaznaczac"<<endl;
    		}
    		else if(ruch_zielonego==false && (teren==jednostka_fioletowego ||  teren==maszynownia_fioletowego)){
    			cout<<"zaznaczam statek"<<endl;
    			if(okret!=NULL){
    				okret->odznacz_statek();
    			}
    			okret=morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y)->zwroc_statek();
    			okret->zaznacz_statek();
    			zaznaczono_okret=true;
    		}
    		else if(faza_ruchu==true){
				if(zaznaczono_okret==true){
	    			cout<<"przesuwam"<<endl;
    				if(1){
    						zawodnik->odblokuj_pola_morza(okret);
    						if(zawodnik->sprawdz_czy_mozna_wstawic_w_jakiejs_pozycji(okret,klikniecie_x+wys_x,klikniecie_y+wys_y)){
    							if(morze.znajdz_droge(morze.zwroc_pole(okret->zwroc_wspolrzedna_x(),okret->zwroc_wspolrzedna_y()),morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y))){
    								zawodnik->zablokuj_pola_morza(okret);
    								for (int i = 1, pom=0,koniec=0;    koniec==0  &&    morze.droga.zwroc_dlugosc_listy() >= i;      i++, pom=0) {
    									okret->odznacz_statek();
    									Sleep(OPOZNIENIE_W_RUCHU);

    									///////////////ustawianie preferowanego kierunku///////////////
    									if (i > 1) {
    										if (morze.droga.zwroc(i)->zwroc_y() > morze.droga.zwroc(i - 1)->zwroc_y()) {
    											zwrot = poludnie;
    											pom++;
    										}
    										else if (morze.droga.zwroc(i)->zwroc_y() < morze.droga.zwroc(i - 1)->zwroc_y()) {
    											zwrot = polnoc;
    											pom++;
    										}
    										if (morze.droga.zwroc(i)->zwroc_x()	> morze.droga.zwroc(i - 1)->zwroc_x()) {
    											zwrot = wschod;
    											pom++;
    										}
    										else if (morze.droga.zwroc(i)->zwroc_x()	< morze.droga.zwroc(i - 1)->zwroc_x()) {
    											zwrot = zachod;
    											pom++;
    										}
    									}
    									if(pom==1){
        									if(KOSZT_RUCHU_O_POLE< okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
        										zawodnik->przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);
        										okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+KOSZT_RUCHU_O_POLE);
        									}
        									else{
        										koniec=1;
        									}
    									}
    									else if(pom==2){
        									if(KOSZT_RUCHU_PO_SKOSIE < okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
        										zawodnik->przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);
        										okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+KOSZT_RUCHU_PO_SKOSIE);
        									}
         									else{
            										koniec=1;
            									}
    									}
    									else{
    										if(KOSZT_RUCHU_PO_SKOSIE < okret->zwroc_predkosc() - okret->zwroc_koszt_wykonanego_ruchu()){
    											zawodnik->przesun_statek_na_zadana_pozycje(okret, morze.droga.zwroc(i)->zwroc_x(),morze.droga.zwroc(i)->zwroc_y(), zwrot);\
    											okret->wpisz_koszt_wykonanego_ruchu(okret->zwroc_koszt_wykonanego_ruchu()+ KOSZT_RUCHU_PO_SKOSIE);
    										}
         									else{
            										koniec=1;
            								}
    									}

    									wyswietl_gre(zawodnik);
//    									morze.wyswietl();
    								}
    							}
    							else{
        							zawodnik->zablokuj_pola_morza(okret);
//    								morze.wyswietl();
        						}
    						}
    						else{
    							zawodnik->zablokuj_pola_morza(okret);
//								morze.wyswietl();
    						}
    					}

    				}
//					morze.wyswietl();
					if(okret!=NULL){
						okret->odznacz_statek();
						okret=NULL;
						zaznaczono_okret=false;
					}
    		}
    	}

    	////////////// jesli jest to faza ataku ////////////////////
    	else if(faza_ruchu==false && ostatnia_akcja==klikniecie){
    		if(atak_fioletowego==true){
    			if(morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==jednostka_fioletowego    &&   morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_statek()->zwroc_sprawnosc_pola(wys_x+klikniecie_x, wys_y+klikniecie_y)==sprawne){
    			cout<<"atak fioletowego"<<endl;
    				if(okret!=NULL){
    					okret->odznacz_pola();
    				}
    				okret=morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y)->zwroc_statek();
    				zawodnik->zaznacz_pole_statku(klikniecie_x+wys_x,klikniecie_y+wys_y);
    				zaznaczono_okret=true;
    			}
    			else if(zaznaczono_okret==true && (morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==jednostka_zielonego  ||  morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==maszynownia_zielonego)){
    				if(zawodnik->strzel(okret,wys_x+klikniecie_x, wys_y+klikniecie_y)==true){ //jesli strzelono
    					okret->odznacz_pola();
    					zaznaczono_okret=false;
       					if(zawodnik->sprobuj_usunac_statek(morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_statek())){
    						if(zawodnik->sprawdz_czy_wygrales()==true){
    							ostatnia_akcja=koniec;
    						}
    					}
    					if(ostatnia_akcja!=koniec){
    						ostatnia_akcja=nastepna_faza;
    					}
    				}
    			}
    		}
    		else{									//atak zielonego
    			if(morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==jednostka_zielonego    &&   morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_statek()->zwroc_sprawnosc_pola(wys_x+klikniecie_x, wys_y+klikniecie_y)==sprawne){
    				cout<<"atak zielonego"<<endl;
    				if(okret!=NULL){
    					okret->odznacz_pola();
    				}
    				okret=morze.zwroc_pole(klikniecie_x+wys_x,klikniecie_y+wys_y)->zwroc_statek();
    				zawodnik->zaznacz_pole_statku(klikniecie_x+wys_x,klikniecie_y+wys_y);
    				zaznaczono_okret=true;
    			}
    			else if(zaznaczono_okret==true && (morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==jednostka_fioletowego || morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_rodzaj_terenu()==maszynownia_fioletowego)){
    				if(zawodnik->strzel(okret,wys_x+klikniecie_x, wys_y+klikniecie_y)==true){ //jesli strzelono
    					okret->odznacz_pola();
    					zaznaczono_okret=false;
    					if(zawodnik->sprobuj_usunac_statek(morze.zwroc_pole(wys_x+klikniecie_x, wys_y+klikniecie_y)->zwroc_statek())){
    						if(zawodnik->sprawdz_czy_wygrales()==true){
    							ostatnia_akcja=koniec;
    						}
    					}
    					if(ostatnia_akcja!=koniec){
    						ostatnia_akcja=nastepna_faza;
    					}
    				}
    			}
    		}
    	}
    	else if(faza_ruchu==false && ostatnia_akcja==potwierdzenie){
    		if(atak_fioletowego==true){
    			fioletowy_zakonczyl_faze_ataku=true;
    		}
    		else{
    			zielony_zakonczyl_faze_ataku=true;
    		}
    		ostatnia_akcja=nastepna_faza;
    	}
    	else if(faza_ruchu==true && ostatnia_akcja==potwierdzenie){
    		zawodnik=&gracz_fioletowy;
    		zawodnik->odznacz_statki();
    		zawodnik=&gracz_zielony;
    		zawodnik->odznacz_statki();
    		faza_ruchu=false;
    		ostatnia_akcja=nastepna_faza;
    	}



////////Przydzielenie nastepnej fazy ruchu///////
    	 if(ostatnia_akcja==nastepna_faza){
    		if(faza_ruchu==false){
    			if(fioletowy_zakonczyl_faze_ataku==true && zielony_zakonczyl_faze_ataku==false){
    				ostatnia_akcja=strzela_zielony;
    			}
    			else if(fioletowy_zakonczyl_faze_ataku==false && zielony_zakonczyl_faze_ataku==true){
    				ostatnia_akcja=strzela_fioletowy;
    			}
    			else if(rand()%2){
    				ostatnia_akcja=strzela_fioletowy;
    			}
    			else{
    				ostatnia_akcja=strzela_zielony;
    			}
    			if(fioletowy_zakonczyl_faze_ataku==true && zielony_zakonczyl_faze_ataku==true){
    				faza_ruchu=true;
    				cout<<"ustawiam zakonczenia na false"<<endl;
    				fioletowy_zakonczyl_faze_ataku=false;
    				zielony_zakonczyl_faze_ataku=false;
    			}
//        		zawodnik->odznacz_statki();
    		}
    		if(faza_ruchu==true){
    			if(ruch_zielonego==true){
    				ostatnia_akcja=kolejnosc_fioletowego;
    			}
    			else{
    				ostatnia_akcja=kolejnosc_zielonego;
    			}
    		}
    	}

    	if(ostatnia_akcja==kolejnosc_zielonego){
    		ruch_zielonego=true;
    		wykonano_ruch=false;
    		sf::Texture _mapa_zielony;
    		_mapa_zielony.loadFromFile( "obrazki/mapa_zielony.jpg" );
    		sf::Sprite mapa_zielony;
    		mapa_zielony.setTexture(_mapa_zielony);
    		mapa_zielony.setPosition(400,170);
    		oknoAplikacji.clear(sf::Color(255,255,255));
    		oknoAplikacji.draw(mapa_zielony);
    		oknoAplikacji.display();
    		Sleep(2000);
    		zawodnik=&gracz_fioletowy;
    		zawodnik->odznacz_statki();
    		zawodnik=&gracz_zielony;
    		zawodnik->odznacz_statki();
    		zawodnik->przygotuj_statki_do_ruchu();
    		if(okret!=NULL){
    			okret->odznacz_statek();
    			zaznaczono_okret=false;
    		}
    	}
    	else if(ostatnia_akcja==kolejnosc_fioletowego){
    		wykonano_ruch=false;
    		ruch_zielonego=false;
    		sf::Texture _mapa_fioletowy;
    		_mapa_fioletowy.loadFromFile( "obrazki/mapa_fioletowy.png" );
    		sf::Sprite mapa_fioletowy;
    		mapa_fioletowy.setTexture(_mapa_fioletowy);
    		mapa_fioletowy.setPosition(400,170);
    		oknoAplikacji.clear(sf::Color(255,255,255));
    		oknoAplikacji.draw(mapa_fioletowy);
    		oknoAplikacji.display();
    		Sleep(2000);
    		zawodnik=&gracz_zielony;
    		zawodnik->odznacz_statki();
    		zawodnik=&gracz_fioletowy;
    		zawodnik->odznacz_statki();
    		zawodnik->przygotuj_statki_do_ruchu();
    		if(okret!=NULL){
    			okret->odznacz_statek();
    			zaznaczono_okret=false;
    		}
    	}
    	else if(ostatnia_akcja==strzela_fioletowy){
    		atak_fioletowego=true;
    		faza_ruchu=false;
    		wykonano_ruch=false;
    		sf::Texture _strzela_fioletowy;
    		_strzela_fioletowy.loadFromFile( "obrazki/strzela_fioletowy.png" );
    		sf::Sprite strzela_fioletowy;
    		strzela_fioletowy.setTexture(_strzela_fioletowy);
    		strzela_fioletowy.setPosition(400,200);
    		oknoAplikacji.clear(sf::Color(255,255,255));
    		oknoAplikacji.draw(strzela_fioletowy);
    		oknoAplikacji.display();
    		Sleep(2000);
//    		ruch_zielonego=false;
//    		zawodnik->odznacz_statki();
//    		zawodnik->sciagnij_zatopione_statki();
    		zawodnik=&gracz_fioletowy;
    		zawodnik->przygotuj_statki_do_ruchu();
    		if(okret!=NULL){
    			okret->odznacz_statek();
    			zaznaczono_okret=false;
    		}
    	}
    	else if(ostatnia_akcja==strzela_zielony){
    		atak_fioletowego=false;
    		faza_ruchu=false;
    		wykonano_ruch=false;
    		sf::Texture _strzela_zielony;
    		_strzela_zielony.loadFromFile( "obrazki/strzela_zielony.png" );
    		sf::Sprite strzela_zielony;
    		strzela_zielony.setTexture(_strzela_zielony);
    		strzela_zielony.setPosition(400,200);
    		oknoAplikacji.clear(sf::Color(255,255,255));
    		oknoAplikacji.draw(strzela_zielony);
    		oknoAplikacji.display();
    		Sleep(2000);
//    		ruch_zielonego=true;
//    		zawodnik->odznacz_statki();
//    		zawodnik->sciagnij_zatopione_statki();
    		zawodnik=&gracz_zielony;
    		zawodnik->przygotuj_statki_do_ruchu();
    		if(okret!=NULL){
    			okret->odznacz_statek();
    			zaznaczono_okret=false;
    		}
    	}


//    	cout<<"zaczynam wyswietlac"<<endl;
    	wyswietl_gre(zawodnik);
    	if(ostatnia_akcja!=koniec){
    		ostatnia_akcja=obsluga_zdarzen();
    	}
    	else{
    	    	if( zawodnik->zwroc_gracza()==fioletowy){
    	    		sf::Texture _fioletowy;
    	    		_fioletowy.loadFromFile( "obrazki/fioletowy.jpg" );
    	    		sf::Sprite fioletowy;
    	    		fioletowy.setTexture(_fioletowy);
    	    		fioletowy.setPosition(400,200);
    	    		oknoAplikacji.clear(sf::Color(255,255,255));
    	    		oknoAplikacji.draw(fioletowy);
    	    		oknoAplikacji.display();
    	    	}
    	    	else{
    	    		sf::Texture _zielony;
    	    		_zielony.loadFromFile( "obrazki/zielony.jpg" );
    	    		sf::Sprite zielony;
    	    		zielony.setTexture(_zielony);
    	    		zielony.setPosition(550,170);
    	    		oknoAplikacji.clear(sf::Color(255,255,255));
    	    		oknoAplikacji.draw(zielony);
    	    		oknoAplikacji.display();
    	    	}
    	    	while(nastepna_faza!=obsluga_zdarzen());
    	}
    }
    cout<<"poza petla"<<endl;

    ////////koniec gry//////////

   return 0;
}



/*!
\file
\brief Plik zawierajacy deklaracje klasy Lista_kolejka

*/
#include <iostream>
#include "element.hh"
#include <queue>

using namespace std;

/*!
\brief Klasa Lista_kolejka

Klasa zawierajaca strukture queue.
*/
template <class typ>
class Lista_kolejka{
	public:
	queue <typ> elementy;
};


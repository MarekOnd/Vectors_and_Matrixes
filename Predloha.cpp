#include "Predloha.h"

Predloha::Predloha()
{

}

Predloha::Predloha(string j)
{
	jmeno = j;
}

Predloha::~Predloha()
{

}

void Predloha::pojmenuj()
{
	cout << "Zadej jmeno pro " << typ << ": ";
	cin >> jmeno;
}


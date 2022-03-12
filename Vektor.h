#pragma once
#include "Predloha.h"


struct souradnice
{
	float cislo;
	souradnice* dalsiS;
};

class Vektor : public Predloha
{
private:
	souradnice* prvni;
	souradnice* posledni;
	int velikost;
public:
	Vektor();
	Vektor(int n, string s = "", int predlohaNastaveni = -1);

	Vektor(const Vektor&);//konstruktor na dìlání kopií
	~Vektor();

	//pøidávání
	void pridejNaZacatek(souradnice* p);
	void pridejNaZacatek(float cislo);
	void pridejNaKonec(souradnice* p);
	void pridejNaKonec(float cislo);
	void pridejNkrat(int n);


	//odstraòování
	void odstranPrvniPrvek();
	void odstranPosledniPrvek();
	void vyprazdniSeznam();


	//ziskávání informací
	souradnice* prvniPrvek();
	souradnice* posledniPrvek();
	souradnice souradniceNaPozici(int a);
	souradnice* najdiPrvek(float data);
	int pocetPrvku();//manuálnì spoèítá kolik prvkù je v seznamu, NAHRAZENO velikosti
	int ziskejVelikost() { return velikost; };
	
	//úpravy
	void nastavVektor(Vektor vektor);

	//vypisování
	void vypis();
	void info();

	//operátory
	float operator*(Vektor vektor);//testovací funkce, skalární souèin vektorù
	void operator=(Vektor* vektor);
	void operator*=(float a);//násobení èíslem
	void operator+=(Vektor vektor);
	void operator-=(Vektor vektor);
	Vektor* operator*(float a);
	Vektor* operator+(Vektor vektor);
	Vektor* operator-(Vektor vektor);
	souradnice operator[](int index);//ZN
	

};


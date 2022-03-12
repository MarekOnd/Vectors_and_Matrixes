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

	Vektor(const Vektor&);//konstruktor na d�l�n� kopi�
	~Vektor();

	//p�id�v�n�
	void pridejNaZacatek(souradnice* p);
	void pridejNaZacatek(float cislo);
	void pridejNaKonec(souradnice* p);
	void pridejNaKonec(float cislo);
	void pridejNkrat(int n);


	//odstra�ov�n�
	void odstranPrvniPrvek();
	void odstranPosledniPrvek();
	void vyprazdniSeznam();


	//zisk�v�n� informac�
	souradnice* prvniPrvek();
	souradnice* posledniPrvek();
	souradnice souradniceNaPozici(int a);
	souradnice* najdiPrvek(float data);
	int pocetPrvku();//manu�ln� spo��t� kolik prvk� je v seznamu, NAHRAZENO velikosti
	int ziskejVelikost() { return velikost; };
	
	//�pravy
	void nastavVektor(Vektor vektor);

	//vypisov�n�
	void vypis();
	void info();

	//oper�tory
	float operator*(Vektor vektor);//testovac� funkce, skal�rn� sou�in vektor�
	void operator=(Vektor* vektor);
	void operator*=(float a);//n�soben� ��slem
	void operator+=(Vektor vektor);
	void operator-=(Vektor vektor);
	Vektor* operator*(float a);
	Vektor* operator+(Vektor vektor);
	Vektor* operator-(Vektor vektor);
	souradnice operator[](int index);//ZN
	

};


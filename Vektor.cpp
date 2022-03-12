#include "Vektor.h"

Vektor::Vektor()
{
	pojmenuj();
	prvni = nullptr;
	posledni = nullptr;
	velikost = 0;
	typ = "vektor";
}
Vektor::Vektor(int n, string s, int predlohaNastaveni)
{
	prvni = nullptr;
	posledni = nullptr;
	velikost = 0;
	typ = "vektor";

	//pojmenov�n�
	if (s == "")//pokud nepojmenov�no, tak pojmenuje u�ivatel
	{
		pojmenuj();
	}
	else
	{
		pojmenuj(s);
	}
	//zad�n� prvk�
	if (predlohaNastaveni == -1 || predlohaNastaveni > n)//pokud uzivatel nzadal p�edlohu
	{
		pridejNkrat(n);
	}
	else//pokud chce ud�lat p�edlohu (0 ud�l� nulov� vektor, ��sla 1 a� n ud�laj� vektor standardn� b�ze
	{
		for (int i = 1; i <= n;i++)
		{
			if (predlohaNastaveni == i)
			{
				pridejNaKonec(1);
			}
			else
			{
				pridejNaKonec((float)0);
			}
		}
	}
	
}
Vektor::Vektor(const Vektor& v)
{
	souradnice* pomocne = v.prvni;
	
	prvni = nullptr;
	posledni = nullptr;
	velikost = 0;
	typ = "vektor";
	pojmenuj(v.jmeno);
	if (pomocne == nullptr)
	{
		return;
	}
	while (pomocne != v.posledni)
	{
		pridejNaKonec(pomocne->cislo);
		pomocne = pomocne->dalsiS;
	}
	pridejNaKonec(pomocne->cislo);
}
Vektor::~Vektor()
{
	vyprazdniSeznam();
}

//p�id�v�n�
void Vektor::pridejNaZacatek(souradnice* p)
{
	velikost++;
	if (prvni == nullptr)//seznam pr�zdn�
	{
		prvni = p;
		posledni = p;
		p->dalsiS = nullptr;
	}
	else//nepr�zdn�
	{
		p->dalsiS = prvni;
		prvni = p;
	}
}
void Vektor::pridejNaZacatek(float cislo)
{
	pridejNaZacatek(new souradnice{ cislo,nullptr });
}
void Vektor::pridejNaKonec(souradnice* p)
{
	velikost++;
	if (prvni == nullptr)//seznam pr�zdn�
	{
		prvni = p;
		posledni = p;
		p->dalsiS = nullptr;
	}
	else//nepr�zdn�
	{
		posledni->dalsiS = p;
		posledni = p;
	}
}
void Vektor::pridejNaKonec(float cislo)
{
	pridejNaKonec(new souradnice{ cislo, nullptr });
}
void Vektor::pridejNkrat(int n)
{
	float cislo;
	while ((n > 0))
	{
		cout << "Zadej cislo na pozici " << velikost + 1 << " pro " << typ << " " << jmeno << ": ";
		cin >> cislo;
		if (cin.fail() != true)
		{
			pridejNaKonec(cislo);
			n--;
		}
		else
		{
			cout << "Vstup ve spatnem formatu" << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
}
void Vektor::nastavVektor(Vektor vektor)//vypr�zn� a nastav� hodnoty na vstupn�
{
	vyprazdniSeznam();
	souradnice* pomocna = vektor.prvniPrvek();
	for (int i = 0; i < vektor.ziskejVelikost(); i++)
	{
		pridejNaKonec(pomocna->cislo);
		pomocna = pomocna->dalsiS;
	}
}


//odstra�ov�n�
void Vektor::odstranPrvniPrvek()
{
	if (velikost < 1)//pr�zdn� seznam
	{
		return;
	}
	
	if (velikost == 1)//pokud je v seznamu jen jeden prvek
	{
		prvni = nullptr;
		posledni = nullptr;
	}
	else
	{
		souradnice* pomocny = prvni->dalsiS;
		delete prvni;
		prvni = pomocny;
	}
	velikost--;
}
void Vektor::odstranPosledniPrvek()
{
	if (prvni == nullptr)
	{
		return;
	}
	velikost--;
	if (prvni == posledni)
	{
		delete posledni;
		prvni = nullptr;
		posledni = nullptr;
	}
	souradnice* pomocny = prvni;
	while (pomocny != nullptr && pomocny->dalsiS != posledni)//nejd��v pot�eba kontrolovat, �e ukazatel nen� nullptr (jinak nem��u z�sk�vat co je v n�m)
	{
		pomocny = pomocny->dalsiS;
	}

	pomocny->dalsiS = nullptr;
	delete posledni;
	posledni = pomocny;
}
void Vektor::vyprazdniSeznam()
{
	while (velikost != 0)
	{
		odstranPrvniPrvek();
	}

}


//zisk�v�n� informac�
souradnice* Vektor::prvniPrvek()//docasne mozna neni bezpecne
{
	return prvni;
}
souradnice* Vektor::posledniPrvek()//docasne mozna neni bezpecne
{
	return posledni;
}
souradnice Vektor::souradniceNaPozici(int a)
{
	if (a < 1 || a > velikost)
	{
		cout << "Index hledane souradnice je mimo seznam" << endl;
		throw exception();
	}
	souradnice* pomocna = prvni;
	for (int i = 1;i < a;i++)
	{
		pomocna = pomocna->dalsiS;
	}
	return *pomocna;
}
souradnice* Vektor::najdiPrvek(float data)
{
	souradnice* pomocny = prvni;
	while (pomocny != nullptr && pomocny->cislo != data)
	{
		pomocny = pomocny->dalsiS;
	}
	if (pomocny != nullptr)
	{
		cout << "prvek nalezen" << endl;
		return pomocny;
	}
	cout << "prvek nenalezen" << endl;
	return nullptr;
}
int Vektor::pocetPrvku()
{
	int pocet = 0;
	souradnice* pomocny = prvni;
	while (pomocny != nullptr)
	{
		pocet++;
		pomocny = pomocny->dalsiS;

	}
	return pocet;
}


//vypisov�n�
void Vektor::vypis()//vyp�e sou�adnice
{
	souradnice* pomocny = prvni;
	while (pomocny != nullptr)
	{
		cout << pomocny->cislo << endl;
		pomocny = pomocny->dalsiS;

	}
}
void Vektor::info()
{
	cout << "Jmeno: " << ziskejJmeno() << endl;
	cout << "Typ: " <<	ziskejTyp() << endl;
	cout << "Obsahuje: " << endl;
	vypis();
}


//oper�tory
void Vektor::operator=(Vektor* vektor)
{
	nastavVektor(*vektor);
}
float Vektor::operator*(Vektor vektor)//skal�rn� sou�in vektor�
{
	if (vektor.velikost != velikost)
	{
		cout << "Vektory nemaji stejnou dimenzi" << endl;
		throw exception();
	}
	souradnice* x = prvni;
	souradnice* y = vektor.prvniPrvek();
	float vysledek = 0;
	while (x->dalsiS != nullptr)
	{
		vysledek += x->cislo * y->cislo;
		x = x->dalsiS;
		y = y->dalsiS;
	}
	vysledek += x->cislo * y->cislo;//posledn� iterace
	return vysledek;

}
void Vektor::operator*=(float a)
{
	souradnice* x = prvni;
	for (int i = 0; i < velikost; i++)
	{
		x->cislo *= a;
		x = x->dalsiS;
	}
}
void Vektor::operator+=(Vektor vektor)
{
	if (vektor.ziskejVelikost() != velikost)
	{
		cout << "Vektory nemaji stejnou dimenzi" << endl;
		return;
	}
	souradnice* x = prvni;
	souradnice* y = vektor.prvniPrvek();
	for (int i = 0; i <	velikost; i++)
	{
		x->cislo += y->cislo;
		x = x->dalsiS;
		y = y->dalsiS;
	}
}
void Vektor::operator-=(Vektor vektor)
{
	if (vektor.ziskejVelikost() != velikost)
	{
		cout << "vektory nemaji stejnou velikost" << endl;
		return;
	}
	souradnice* x = prvni;
	souradnice* y = vektor.prvniPrvek();
	for (int i = 0; i < velikost; i++)
	{
		x->cislo -= y->cislo;
		x = x->dalsiS;
		y = y->dalsiS;
	}
}
Vektor* Vektor::operator*(float a)
{
	Vektor* vysledek = new Vektor(0, "docasneJmeno");
	vysledek->nastavVektor(*this);
	*vysledek *= a;
	return vysledek;
}
Vektor* Vektor::operator+(Vektor vektor)
{
	Vektor* vysledek = new Vektor(0, "docasneJmeno");
	vysledek->nastavVektor(*this);
	*vysledek += vektor;
	return vysledek;
}
Vektor* Vektor::operator-(Vektor vektor)
{
	Vektor* vysledek = new Vektor(0, "docasneJmeno");
	vysledek->nastavVektor(*this);
	*vysledek -= vektor;
	return vysledek;
}
souradnice Vektor::operator[](int index)
{
	return souradniceNaPozici(index);
}




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

	//pojmenování
	if (s == "")//pokud nepojmenováno, tak pojmenuje uživatel
	{
		pojmenuj();
	}
	else
	{
		pojmenuj(s);
	}
	//zadání prvkù
	if (predlohaNastaveni == -1 || predlohaNastaveni > n)//pokud uzivatel nzadal pøedlohu
	{
		pridejNkrat(n);
	}
	else//pokud chce udìlat pøedlohu (0 udìlá nulový vektor, èísla 1 až n udìlají vektor standardní báze
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

//pøidávání
void Vektor::pridejNaZacatek(souradnice* p)
{
	velikost++;
	if (prvni == nullptr)//seznam prázdný
	{
		prvni = p;
		posledni = p;
		p->dalsiS = nullptr;
	}
	else//neprázdný
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
	if (prvni == nullptr)//seznam prázdný
	{
		prvni = p;
		posledni = p;
		p->dalsiS = nullptr;
	}
	else//neprázdný
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
void Vektor::nastavVektor(Vektor vektor)//vyprázní a nastaví hodnoty na vstupní
{
	vyprazdniSeznam();
	souradnice* pomocna = vektor.prvniPrvek();
	for (int i = 0; i < vektor.ziskejVelikost(); i++)
	{
		pridejNaKonec(pomocna->cislo);
		pomocna = pomocna->dalsiS;
	}
}


//odstraòování
void Vektor::odstranPrvniPrvek()
{
	if (velikost < 1)//prázdný seznam
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
	while (pomocny != nullptr && pomocny->dalsiS != posledni)//nejdøív potøeba kontrolovat, že ukazatel není nullptr (jinak nemùžu získávat co je v nìm)
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


//ziskávání informací
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


//vypisování
void Vektor::vypis()//vypíše souøadnice
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


//operátory
void Vektor::operator=(Vektor* vektor)
{
	nastavVektor(*vektor);
}
float Vektor::operator*(Vektor vektor)//skalární souèin vektorù
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
	vysledek += x->cislo * y->cislo;//poslední iterace
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




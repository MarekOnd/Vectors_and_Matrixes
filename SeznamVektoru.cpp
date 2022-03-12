#include "SeznamVektoru.h"
#include <fstream>
#include <math.h>


SeznamVektoru::SeznamVektoru(int dim)
{
	prvni = nullptr;
	posledni = nullptr;
	dimenze = dim;
	pocetSloupcu = 0;
	typ = "seznam vektoru";
}
SeznamVektoru::~SeznamVektoru()
{
	vyprazdniSeznam();
}


//p�id�v�n�
void SeznamVektoru::pridejNaPozici(int a, sloupec* s)
{
	if (s->vektor.ziskejVelikost() != dimenze)//kontrola dimenze
	{
		cout << "!!! - Vektor m� jinou dimenzi nez ostatni" << endl;
		return;
	}
	if (a < 1 || a  > pocetSloupcu + 1)//kontrola um�st�n�
	{
		cout << "Pozice je mimo seznam" << endl;
		return;
	}

	if (s->vektor.ziskejJmeno() != "docasneJmeno" && s->vektor.ziskejJmeno() != "")//u t�chto jmen se nekontroluje, jestli jsou v seznamu stejnojmenn� vektory (slou�� k pr�ci s pomocn�mi seznamy)
	{
		if (najdiPodleJmena(s->vektor.ziskejJmeno()) != nullptr)//kontrola neopakov�n� jmena//nedokon�eno
		{
			cout << "Vektor se jmenem " << s->vektor.ziskejJmeno() <<" je jiz v seznamu" << endl;
			system("pause");
			return;
		}
	}
	

	sloupec* pomocny;
	s->dalsiS = nullptr;//pro jistotu odstran�m pointer na dal�� prvky
	if (pocetSloupcu == 0)//seznam je prazdn�
	{
		prvni = s;
		posledni = s;
	}
	else if (a == 1)//p�id�n� na prvn� pozici
	{
		s->dalsiS = prvni;
		prvni = s;
	}
	else if (a == pocetSloupcu + 1)//p�id�n� na posledni pozici
	{
		posledni->dalsiS = s;
		posledni = s;
	}
	else//p�id�n� na ostatn� pozice
	{
		pomocny = sloupecNaPozici(a - 1);
		s->dalsiS = pomocny->dalsiS;
		pomocny->dalsiS = s;
	}
	pocetSloupcu++;
}
void SeznamVektoru::pridejNaPozici(int a, Vektor vektor)
{
	pridejNaPozici(a, new sloupec{ vektor, nullptr });
}
void SeznamVektoru::pridejNaZacatek(sloupec* s)
{
	pridejNaPozici(1, s);
}
void SeznamVektoru::pridejNaZacatek(Vektor vektor)
{
	sloupec* kPridani = new sloupec{ vektor, nullptr };
	pridejNaZacatek(kPridani);
}
void SeznamVektoru::pridejNaKonec(sloupec* s)
{
	pridejNaPozici(pocetSloupcu + 1, s);
}
void SeznamVektoru::pridejNaKonec(Vektor vektor)
{
	sloupec* kPridani = new sloupec{ vektor, nullptr };
	pridejNaKonec(kPridani);
}
void SeznamVektoru::zadejSloupec()
{
	pridejNaKonec(*(new Vektor(dimenze)));
}
void SeznamVektoru::zadejSloupecNaPozici(int a)
{
	Vektor* v = new Vektor(dimenze);
	pridejNaPozici(a, *v);
	delete v;
}


//odstra�ov�n�
sloupec* SeznamVektoru::odpojNaPozici(int a)//metoda m��e b�t vol�na pouze pokud jsou v poli prvky
{
	if (a < 1 || a > pocetSloupcu)
	{
		return nullptr;
	}
	sloupec* odpojeny;
	if (pocetSloupcu == 1)
	{
		odpojeny = prvni;
		prvni = nullptr;
		posledni = nullptr;
	}
	else if (a == 1)//prvn�
	{
		odpojeny = prvni;
		prvni = prvni->dalsiS;
		if (prvni == nullptr)//pro p��pad dvou prvk�
		{
			posledni = nullptr;
		}
	}
	else if (a == pocetSloupcu)//posledn�
	{
		odpojeny = posledni;
		posledni = sloupecNaPozici(pocetSloupcu - 1);
		posledni->dalsiS = nullptr;
	}
	else//ostatn�
	{
		odpojeny = sloupecNaPozici(a);
		sloupecNaPozici(a - 1)->dalsiS = odpojeny->dalsiS;
	}

	pocetSloupcu--;
	odpojeny->dalsiS = nullptr;
	return odpojeny;
}
void SeznamVektoru::odstranNaPozici(int a)
{
	delete odpojNaPozici(a);
}
void SeznamVektoru::odstranPrvni()
{
	delete odpojNaPozici(1);
}
void SeznamVektoru::odstranPosledni()
{
	delete odpojNaPozici(pocetSloupcu);
}
void SeznamVektoru::vyprazdniSeznam()
{
	while (prvni != nullptr && pocetSloupcu != 0)
	{
		odstranPrvni();
	}
}


//vypisov�n�
void SeznamVektoru::vypisInfo()
{
	cout << "Informace o seznamu___" << endl;
	cout << "dimenze seznamu: " << dimenze << endl;
	cout << "pocet sloupcu: " << pocetSloupcu << endl;
	if (ziskejJmeno() != "")
	{
		cout << "soubor k ukladani: " << ziskejJmeno() << ".txt" << endl;
	}
	else
	{
		cout << "soubor k ukladani: neni zvolen" << endl;
	}
	if (vypisovatMaticiPriUpravach)
	{
		cout << "Postup bude vypisovan" << endl;
	}
	else
	{
		cout << "Postup nebude vypisovan" << endl;
	}
}
void SeznamVektoru::vypisSloupec(int a)
{
	if (a < 1 && a > pocetSloupcu)//a mus� b�t ze seznamu
	{
		return;
	}
	sloupecNaPozici(a)->vektor.vypis();

}
void SeznamVektoru::vypisSloupecInfo(int a)
{
	if (a < 1 && a > pocetSloupcu)//a mus� b�t ze seznamu
	{
		return;
	}
	sloupecNaPozici(a)->vektor.info();

}
void SeznamVektoru::vypisSeznam()
{
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		vypisSloupec(i);
	}
}
void SeznamVektoru::vypisRadek(int a)
{
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		cout << round(pow(10,2)*sloupecNaPozici(i)->vektor[a].cislo)/ pow(10, 2) << "\t";//nen� optim�ln�
	}
}
void SeznamVektoru::vypisMatici(bool vypisSeJmeny)
{
	vypisInfo();
	cout << "vektory v matici:" << endl;
	if (vypisSeJmeny)
	{
		for (int i = 1; i <= pocetSloupcu; i++)
		{
			cout << sloupecNaPozici(i)->vektor.ziskejJmeno() << "\t";
		}
		cout << endl;
	}
	for (int i = 1; i <= dimenze; i++)
	{
		vypisRadek(i);
		cout << endl;
	}
	cout << endl;
}


//z�sk�v�n� informac�
sloupec* SeznamVektoru::sloupecNaPozici(int a)
{
	if (a<1 || a>pocetSloupcu)
	{
		throw exception();
		
	}
	sloupec* pomocny = prvni;
	for(int i = 1;i < a;i++)
	{
		pomocny = pomocny->dalsiS;
	}
	
	return pomocny;
}
sloupec* SeznamVektoru::najdiPodleJmena(string jmeno)
{
	int pozice = najdiCisloSloupcePodleJmena(jmeno);
	if (pozice == 0)
	{
		return nullptr;
	}
	else
	{
		return sloupecNaPozici(pozice);
	}

}
int SeznamVektoru::najdiCisloSloupcePodleJmena(string jmeno)
{
	if (pocetSloupcu == 0)//pr�zdn� seznam
	{
		return 0;
	}
	sloupec* pomocny = prvni;
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		if (pomocny->vektor.ziskejJmeno().compare(jmeno) == 0)
		{
			return i;
		}
		pomocny = pomocny->dalsiS;
	}
	return 0;//0 znamen�, �e funkce nena�la vektor s t�mto jm�nem
}
Vektor SeznamVektoru::radekNaVektor(int a)
{
	Vektor* v = new Vektor(0, "docasneJmeno");//jm�na se nezachov�vaj�
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		v->pridejNaKonec(sloupecNaPozici(i)->vektor[a].cislo);
	}
	Vektor vysledek = *v;
	delete v;
	return vysledek;
}

Vektor SeznamVektoru::vektorNaPozici(int a)
{
	return sloupecNaPozici(a)->vektor;
}

bool SeznamVektoru::hledaniPoziceVektoruPodleJmena(string popisek, int* pozice)
{
	string jmeno = "Docasne jmeno";
	*pozice = 0;
	while (*pozice == 0)//nech� u�ivatele hledat vektor dokud ho nenajde, nebo dokud nenapise nulu
	{
		cout << popisek << " (zadanim 0 se prerusi hledani jmena): ";
		cin >> jmeno;
		if (jmeno == "0")
		{
			break;
		}
		*pozice = najdiCisloSloupcePodleJmena(jmeno);

	}
	if (*pozice != 0)//byl nalezen vektor, pozice je ulozena
	{
		return true;
	}
	else//uzivatel ukoncil hledani
	{
		return false;
	}
}


//�pravy seznamu
void SeznamVektoru::vymenSloupce(int a, int b)
{
	if (a<1 || a>pocetSloupcu || b<1 || b>pocetSloupcu || b == a)
	{
		return;
	}
	if (a > b)//abych mohl p�edpokl�dat, �e a < b; se zaru�en�m p�edpokladem, �e a!=b, pak sta�� okraje diskutovat jen pro jeden prvek
	{
		vymenSloupce(b, a);
		return;
	}
	//v�m�na
	sloupec* A = odpojNaPozici(a);
	sloupec* B = odpojNaPozici(b - 1);//vyu��v�m toho, �e A je p�ed B
	pridejNaPozici(a, B);
	pridejNaPozici(b, A);
}
void SeznamVektoru::prevratPodleDiagonaly()
{
	int docasnyPocetSloupcu = pocetSloupcu;//----
	int docasnaDimenze = dimenze;

	//vytvo�� nov� seznam vektor�
	SeznamVektoru* sv = new SeznamVektoru(pocetSloupcu);
	for (int i = 1; i <= dimenze; i++)
	{
		sv->pridejNaKonec(radekNaVektor(i));
	}

	//vyprazdn� aktu�ln� seznam a vlo�� tam vektory z sv
	vyprazdniSeznam();
	dimenze = docasnyPocetSloupcu;//----
	pocetSloupcu = 0;
	for (int i = 1; i <= docasnaDimenze; i++)
	{

		pridejNaKonec(sv->sloupecNaPozici(i)->vektor);
	}
	delete sv;
}
void SeznamVektoru::horniTrojuhelnikovyTvar(float* det)
{
	//��� zachov�v�n� jmen vektoru
	string* jmena = new string[pocetSloupcu];
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		jmena[i-1] = sloupecNaPozici(i)->vektor.ziskejJmeno();
	}
	//���

	prevratPodleDiagonaly();//---p�evr�t�m podle diagon�ly, abych mohl vyu��vat oper�tory vektor� 
	sloupec* pomocny;
	for (int i = 1; i <= dimenze; i++)
	{

		

		pomocny = nullptr;
		//najdu sloupec s nenulov�m prvek a posunu ho na pozici i
		for (int y = i; y <= pocetSloupcu; y++)
		{
			if (sloupecNaPozici(y)->vektor[i].cislo != 0)
			{
				pomocny = sloupecNaPozici(y);
				vymenSloupce(i, y);
				//DETERMINANT - m�n� znam�nko
				if (y != i && det)
				{
					*det *= -1;
				}
				if (i!=y && vypisovatMaticiPriUpravach)
				{
					vypisMatici();
					system("pause");
				}
				break;
			}

			//DETERMINANT - pokud jsem ��dn� nenulov� prvek nena�el, tak m� matice nulov� ��dek -> determinant je nulov�
			if (det && y == pocetSloupcu)
			{
				*det = 0;
			}
		}
		//
		if (pomocny != nullptr)//pokud jsem na�el takov� sloupec
		{
			
			for (int y = i +1; y <= pocetSloupcu; y++)//od v�ech n�sleduj�c�ch sloupc� nasobek pomocn�ho sloupce tak, aby v i-t�m ��dku byly po i-t� pozici jen nuly
			{
				if (sloupecNaPozici(y)->vektor.souradniceNaPozici(i).cislo != 0 && sloupecNaPozici(y) != pomocny)
				{
					float nasobek = sloupecNaPozici(y)->vektor[i].cislo / pomocny->vektor[i].cislo;
					pomocny->vektor = pomocny->vektor * nasobek;
					sloupecNaPozici(y)->vektor -= pomocny->vektor;
					pomocny->vektor = pomocny->vektor *(1/nasobek);
					if (vypisovatMaticiPriUpravach)
					{
						vypisMatici();
						system("pause");
					}
				}
			}
		
			
		}
		
		
	}
	prevratPodleDiagonaly();//---
	//���
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		 sloupecNaPozici(i)->vektor.pojmenuj(jmena[i - 1]);
	}
	delete[] jmena;
	//���
}
void SeznamVektoru::dolniTrojuhelnikovyTvar()
{
	//��� zachov�v�n� jmen vektoru
	string* jmena = new string[pocetSloupcu];
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		jmena[i - 1] = sloupecNaPozici(i)->vektor.ziskejJmeno();
	}
	//���

	prevratPodleDiagonaly();//---p�evr�t�m podle diagon�ly, abych mohl vyu��vat oper�tory vektor� 
	sloupec* pomocny;
	for (int i = pocetSloupcu; i > 0; i--)
	{

		

		pomocny = nullptr;
		//najdu sloupec s nenulov�m prvek a posunu ho na pozici i
		for (int y = i; y > 0; y--)
		{
			if (sloupecNaPozici(y)->vektor[i].cislo != 0)
			{
				pomocny = sloupecNaPozici(y);
				vymenSloupce(i, y);
				if (i!= y && vypisovatMaticiPriUpravach)
				{
					vypisMatici();
					system("pause");
				}
				break;
			}
		}
		//
		if (pomocny != nullptr)//pokud jsem na�el takov� sloupec
		{

			for (int y = i - 1; y > 0; y--)//od v�ech n�sleduj�c�ch sloupc� nasobek pomocn�ho sloupce tak, aby v i-t�m ��dku byly po i-t� pozici jen nuly
			{
				if (sloupecNaPozici(y)->vektor.souradniceNaPozici(i).cislo != 0 && sloupecNaPozici(y) != pomocny)
				{
					float nasobek = sloupecNaPozici(y)->vektor[i].cislo / pomocny->vektor[i].cislo;
					pomocny->vektor = pomocny->vektor * nasobek;
					sloupecNaPozici(y)->vektor -= pomocny->vektor;
					pomocny->vektor = pomocny->vektor * (1 / nasobek);
					if (vypisovatMaticiPriUpravach)
					{
						vypisMatici();
						system("pause");
					}
				}
			}
			pomocny->vektor *= (1 / pomocny->vektor[i].cislo);//vyd�l�m cel� ��dek tak, aby na hlavn� diagon�le byla jedni�ka
			if (vypisovatMaticiPriUpravach)
			{
				vypisMatici();
				system("pause");
			}
		}
		vypisMatici();

	}
	prevratPodleDiagonaly();//---
	//���
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		sloupecNaPozici(i)->vektor.pojmenuj(jmena[i - 1]);
	}
	delete[] jmena;
	//���
}
void SeznamVektoru::zmenDimenzi(int d)
{
	if (dimenze == d || d <= 0)
	{
		return;
	}
	vyprazdniSeznam();
	dimenze = d;
}

//inverzn� matice Gaussovou eliminac�
void SeznamVektoru::pridejJednotkovouMatici()
{
	for (int i = 1; i <= dimenze;i++)
	{
		Vektor v = Vektor(dimenze, "docasneJmeno", i);
		pridejNaKonec(v);
	}
}

void SeznamVektoru::urciInverzniMatici()
{
	//podm�nky pro v�po�et
	if (!regularniOperator())
	{
		cout << "K matici neexistuje inverzni." << endl;
		system("pause");
		return;
	}

	//Gaussova eliminace
	pridejJednotkovouMatici();
	horniTrojuhelnikovyTvar();
	dolniTrojuhelnikovyTvar();

	//odstran� nepot�ebnou matici A
	for (int i = 0; i < dimenze; i++)
	{
		sloupecNaPozici(dimenze + 1)->vektor.pojmenuj(sloupecNaPozici(1)->vektor.ziskejJmeno());//p�ed� jm�no vektoru v lev� matici do A-1
		odstranPrvni();
	}
}

float SeznamVektoru::determinant()
{
	
	//zkontroluje podm�nky
	if (dimenze != pocetSloupcu)
	{
		cout << "Matice neni ctvercova!" << endl;
		system("pause");
		return NULL;
	}


	//vytvo�� kopii seznamu
	SeznamVektoru* docasny = new SeznamVektoru(dimenze);
	for (int i = 1;i <= pocetSloupcu;i++)
	{
		docasny->pridejNaKonec(vektorNaPozici(i));
	}
	//uprav� ho na diagonalni tvar, a vlo�� referenci na determinant
	float d = 1;
	docasny->horniTrojuhelnikovyTvar(&d);
	for (int i = 1;i <= pocetSloupcu;i++)
	{
		d *= docasny->sloupecNaPozici(i)->vektor[i].cislo;
	}
	delete docasny;
	return d;
}

bool SeznamVektoru::regularniOperator()
{
	if (determinant() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//pr�ce se soubory
void SeznamVektoru::uloz(string adresar)//ulo�� do souboru 'adresarjmeno.txt', pokud m� seznam ji� jm�no
{
	if (ziskejJmeno()=="")
	{
		cout << "Seznam vektoru nejde ulozit, protoze neni pojmenovany." << endl;
	}
	ofstream soubor(adresar + ziskejJmeno() + ".txt");
	if (soubor.is_open())
	{
		soubor << dimenze << endl;
		soubor << pocetSloupcu << endl;
		for (int i = 1; i <= pocetSloupcu; i++)
		{
			Vektor vektor = sloupecNaPozici(i)->vektor;
			soubor << vektor.ziskejJmeno() << endl;
			for (int y = 1;y <= dimenze;y++)
			{
				soubor << vektor.souradniceNaPozici(y).cislo << endl;
			}
		}
		soubor << "konec" << endl;
		soubor.close();
	}
	
}
void SeznamVektoru::ulozitJako(string adresar)//nastav� seznamu jm�no a ulo�� ho
{
	pojmenuj();
	uloz(adresar);
}
void SeznamVektoru::nactiZeSouboru(string nazevSouboru, string adresar)//na�te seznam, pokud ho najde
{
	vyprazdniSeznam();
	ifstream soubor(adresar + nazevSouboru + ".txt");

	pojmenuj(nazevSouboru);
	if (!soubor.is_open())//p�i nenalezen� souboru
	{
		cout << "Soubor " << adresar << nazevSouboru << ".txt" << " se nepodarilo otevrit. Pokracujte stisknutim libovolne klavesy" << endl;
		system("pause");
		return;
	}

	soubor >> dimenze;
	int sloupce;
	soubor >> sloupce;
	for (int i = 1; i <= sloupce; i++)//pridavani sloupcu
	{
		string s;
		soubor >> s;
		Vektor* vektor = new Vektor(0, s);
		for(int y = 1; y <= dimenze; y++)//pridavani souradnic
		{
			float souradnice;
			soubor >> souradnice;
			vektor->pridejNaKonec(souradnice);
		}
		pridejNaKonec(*vektor);
		delete vektor;
	}
	string s;
	soubor >> s;
	
	if (s != "konec")//p�i �patn�m form�tu souboru
	{
		cout << "Soubor byl ve spatnem formatu. Pokracujte stisknutim libovolne klavesy" << endl;
		system("pause");
		vyprazdniSeznam();
		return;
	}
	soubor.close();
}
//form�t .txt souboru
//dimenze
//pocetvektoru
//jmeno prvniho
//prvni souradnice prvniho
//...
//posledni souradnice posledniho
//konec




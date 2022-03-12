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


//pøidávání
void SeznamVektoru::pridejNaPozici(int a, sloupec* s)
{
	if (s->vektor.ziskejVelikost() != dimenze)//kontrola dimenze
	{
		cout << "!!! - Vektor má jinou dimenzi nez ostatni" << endl;
		return;
	}
	if (a < 1 || a  > pocetSloupcu + 1)//kontrola umístìní
	{
		cout << "Pozice je mimo seznam" << endl;
		return;
	}

	if (s->vektor.ziskejJmeno() != "docasneJmeno" && s->vektor.ziskejJmeno() != "")//u tìchto jmen se nekontroluje, jestli jsou v seznamu stejnojmenné vektory (slouží k práci s pomocnými seznamy)
	{
		if (najdiPodleJmena(s->vektor.ziskejJmeno()) != nullptr)//kontrola neopakování jmena//nedokonèeno
		{
			cout << "Vektor se jmenem " << s->vektor.ziskejJmeno() <<" je jiz v seznamu" << endl;
			system("pause");
			return;
		}
	}
	

	sloupec* pomocny;
	s->dalsiS = nullptr;//pro jistotu odstraním pointer na další prvky
	if (pocetSloupcu == 0)//seznam je prazdný
	{
		prvni = s;
		posledni = s;
	}
	else if (a == 1)//pøidání na první pozici
	{
		s->dalsiS = prvni;
		prvni = s;
	}
	else if (a == pocetSloupcu + 1)//pøidání na posledni pozici
	{
		posledni->dalsiS = s;
		posledni = s;
	}
	else//pøidání na ostatní pozice
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


//odstraòování
sloupec* SeznamVektoru::odpojNaPozici(int a)//metoda mùže být volána pouze pokud jsou v poli prvky
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
	else if (a == 1)//první
	{
		odpojeny = prvni;
		prvni = prvni->dalsiS;
		if (prvni == nullptr)//pro pøípad dvou prvkù
		{
			posledni = nullptr;
		}
	}
	else if (a == pocetSloupcu)//poslední
	{
		odpojeny = posledni;
		posledni = sloupecNaPozici(pocetSloupcu - 1);
		posledni->dalsiS = nullptr;
	}
	else//ostatní
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


//vypisování
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
	if (a < 1 && a > pocetSloupcu)//a musí být ze seznamu
	{
		return;
	}
	sloupecNaPozici(a)->vektor.vypis();

}
void SeznamVektoru::vypisSloupecInfo(int a)
{
	if (a < 1 && a > pocetSloupcu)//a musí být ze seznamu
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
		cout << round(pow(10,2)*sloupecNaPozici(i)->vektor[a].cislo)/ pow(10, 2) << "\t";//není optimální
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


//získávání informací
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
	if (pocetSloupcu == 0)//prázdný seznam
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
	return 0;//0 znamená, že funkce nenašla vektor s tímto jménem
}
Vektor SeznamVektoru::radekNaVektor(int a)
{
	Vektor* v = new Vektor(0, "docasneJmeno");//jména se nezachovávají
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
	while (*pozice == 0)//nechá uživatele hledat vektor dokud ho nenajde, nebo dokud nenapise nulu
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


//úpravy seznamu
void SeznamVektoru::vymenSloupce(int a, int b)
{
	if (a<1 || a>pocetSloupcu || b<1 || b>pocetSloupcu || b == a)
	{
		return;
	}
	if (a > b)//abych mohl pøedpokládat, že a < b; se zaruèeným pøedpokladem, že a!=b, pak staèí okraje diskutovat jen pro jeden prvek
	{
		vymenSloupce(b, a);
		return;
	}
	//výmìna
	sloupec* A = odpojNaPozici(a);
	sloupec* B = odpojNaPozici(b - 1);//využívám toho, že A je pøed B
	pridejNaPozici(a, B);
	pridejNaPozici(b, A);
}
void SeznamVektoru::prevratPodleDiagonaly()
{
	int docasnyPocetSloupcu = pocetSloupcu;//----
	int docasnaDimenze = dimenze;

	//vytvoøí nový seznam vektorù
	SeznamVektoru* sv = new SeznamVektoru(pocetSloupcu);
	for (int i = 1; i <= dimenze; i++)
	{
		sv->pridejNaKonec(radekNaVektor(i));
	}

	//vyprazdní aktuální seznam a vloží tam vektory z sv
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
	//¤¤¤ zachovávání jmen vektoru
	string* jmena = new string[pocetSloupcu];
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		jmena[i-1] = sloupecNaPozici(i)->vektor.ziskejJmeno();
	}
	//¤¤¤

	prevratPodleDiagonaly();//---pøevrátím podle diagonály, abych mohl využívat operátory vektorù 
	sloupec* pomocny;
	for (int i = 1; i <= dimenze; i++)
	{

		

		pomocny = nullptr;
		//najdu sloupec s nenulovým prvek a posunu ho na pozici i
		for (int y = i; y <= pocetSloupcu; y++)
		{
			if (sloupecNaPozici(y)->vektor[i].cislo != 0)
			{
				pomocny = sloupecNaPozici(y);
				vymenSloupce(i, y);
				//DETERMINANT - mìní znaménko
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

			//DETERMINANT - pokud jsem žádný nenulový prvek nenašel, tak má matice nulový øádek -> determinant je nulový
			if (det && y == pocetSloupcu)
			{
				*det = 0;
			}
		}
		//
		if (pomocny != nullptr)//pokud jsem našel takový sloupec
		{
			
			for (int y = i +1; y <= pocetSloupcu; y++)//od všech následujících sloupcù nasobek pomocného sloupce tak, aby v i-tém øádku byly po i-té pozici jen nuly
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
	//¤¤¤
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		 sloupecNaPozici(i)->vektor.pojmenuj(jmena[i - 1]);
	}
	delete[] jmena;
	//¤¤¤
}
void SeznamVektoru::dolniTrojuhelnikovyTvar()
{
	//¤¤¤ zachovávání jmen vektoru
	string* jmena = new string[pocetSloupcu];
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		jmena[i - 1] = sloupecNaPozici(i)->vektor.ziskejJmeno();
	}
	//¤¤¤

	prevratPodleDiagonaly();//---pøevrátím podle diagonály, abych mohl využívat operátory vektorù 
	sloupec* pomocny;
	for (int i = pocetSloupcu; i > 0; i--)
	{

		

		pomocny = nullptr;
		//najdu sloupec s nenulovým prvek a posunu ho na pozici i
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
		if (pomocny != nullptr)//pokud jsem našel takový sloupec
		{

			for (int y = i - 1; y > 0; y--)//od všech následujících sloupcù nasobek pomocného sloupce tak, aby v i-tém øádku byly po i-té pozici jen nuly
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
			pomocny->vektor *= (1 / pomocny->vektor[i].cislo);//vydìlím celý øádek tak, aby na hlavní diagonále byla jednièka
			if (vypisovatMaticiPriUpravach)
			{
				vypisMatici();
				system("pause");
			}
		}
		vypisMatici();

	}
	prevratPodleDiagonaly();//---
	//¤¤¤
	for (int i = 1; i <= pocetSloupcu; i++)
	{
		sloupecNaPozici(i)->vektor.pojmenuj(jmena[i - 1]);
	}
	delete[] jmena;
	//¤¤¤
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

//inverzní matice Gaussovou eliminací
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
	//podmínky pro výpoèet
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

	//odstraní nepotøebnou matici A
	for (int i = 0; i < dimenze; i++)
	{
		sloupecNaPozici(dimenze + 1)->vektor.pojmenuj(sloupecNaPozici(1)->vektor.ziskejJmeno());//pøedá jméno vektoru v levé matici do A-1
		odstranPrvni();
	}
}

float SeznamVektoru::determinant()
{
	
	//zkontroluje podmínky
	if (dimenze != pocetSloupcu)
	{
		cout << "Matice neni ctvercova!" << endl;
		system("pause");
		return NULL;
	}


	//vytvoøí kopii seznamu
	SeznamVektoru* docasny = new SeznamVektoru(dimenze);
	for (int i = 1;i <= pocetSloupcu;i++)
	{
		docasny->pridejNaKonec(vektorNaPozici(i));
	}
	//upraví ho na diagonalni tvar, a vloží referenci na determinant
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

//práce se soubory
void SeznamVektoru::uloz(string adresar)//uloží do souboru 'adresarjmeno.txt', pokud má seznam již jméno
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
void SeznamVektoru::ulozitJako(string adresar)//nastaví seznamu jméno a uloží ho
{
	pojmenuj();
	uloz(adresar);
}
void SeznamVektoru::nactiZeSouboru(string nazevSouboru, string adresar)//naète seznam, pokud ho najde
{
	vyprazdniSeznam();
	ifstream soubor(adresar + nazevSouboru + ".txt");

	pojmenuj(nazevSouboru);
	if (!soubor.is_open())//pøi nenalezení souboru
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
	
	if (s != "konec")//pøi špatném formátu souboru
	{
		cout << "Soubor byl ve spatnem formatu. Pokracujte stisknutim libovolne klavesy" << endl;
		system("pause");
		vyprazdniSeznam();
		return;
	}
	soubor.close();
}
//formát .txt souboru
//dimenze
//pocetvektoru
//jmeno prvniho
//prvni souradnice prvniho
//...
//posledni souradnice posledniho
//konec




﻿// ZP_Vektory.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//

#include <iostream>
#include <fstream>
using namespace std;

//pro výpis souborů ve složce
#include <filesystem>


//#include "Predloha.h";
#include "Vektor.h"
#include "SeznamVektoru.h"

void vypisTextovySoubor(string jmeno);
int vstupCisla(int dolniHranice, int horniHranice);
float vstupCisla();


int main()
{
	
	SeznamVektoru* seznam = new SeznamVektoru(3);
	int vyber;
	bool naposledyUlozeno;
	string adresar = "Data\\";
	do
	{
		cout << "_____________________Program pro praci s vektory_____________________\n\n";

		seznam->vypisMatici(true);

		vypisTextovySoubor("PomocneSoubory\\ZPMoznosti.txt");
		cout << "Zadej cislo volby: ";
		vyber = vstupCisla(0, 15);

		naposledyUlozeno = false;
		//hlavni switch
		switch (vyber)
		{
		case 1://pridavani na pozici
		{
			cout << "V seznamu je " << seznam->pocetSloupcuSeznamu() << " vektoru. Zadejte pozici 1-" << seznam->pocetSloupcuSeznamu() + 1 << ", na jakou budete chtit umistit vektor(zadejte 0 pro vraceni do hlavni nabidky): ";
			int pozice = vstupCisla(0, seznam->pocetSloupcuSeznamu() + 1);
			if (pozice != 0)
			{
				seznam->zadejSloupecNaPozici(pozice);
			}
			break;
		}
		case 2://odstranovani
		{
			cout << "1 - odstranit vektor na pozici" << endl;
			cout << "2 - odstranit vektor podle jmena" << endl;
			cout << "0 - zpet do hlavni nabidky" << endl;
			cout << "Zadejte cislo volby: ";
			int rozhodnuti = vstupCisla(0, 2);
			if (rozhodnuti == 1)//odstranit na pozici
			{
				cout << "V seznamu je " << seznam->pocetSloupcuSeznamu() << " vektoru. Zadejte pozici vektoru 1-" << seznam->pocetSloupcuSeznamu() << ", ktery chcete vymazat(zadejte 0 pro vraceni do hlavni nabidky): ";
				int pozice = vstupCisla(0, seznam->pocetSloupcuSeznamu());
				seznam->odstranNaPozici(pozice);
			}
			else if (rozhodnuti == 2)//odstranit podle jmena
			{
				cout << "Zadej jmeno sloupce k odstraneni: ";
				string jmeno;
				cin >> jmeno;
				int pozice = seznam->najdiCisloSloupcePodleJmena(jmeno);
				if (pozice == 0)
				{
					cout << "Vektor s timto jmenem nebyl nalezen. Pokracujte stisknutim libovolne klavesy" << endl;
					system("pause");
				}
				else
				{
					seznam->odstranNaPozici(pozice);
				}
			}
			break;
		}
		case 3://operace
		{
			cout << "Operace s vektory" << endl;
			cout << "1 - scitani" << endl;
			cout << "2 - odcitani" << endl;
			cout << "3 - nasobeni cislem" << endl;
			cout << "0 - zpet do hlavni nabidky" << endl;
			int rozhodnuti = vstupCisla(0, 3);

			int poziceVysledku, pozicePrvnihoClenu, poziceDruhehoClenu;

			if (rozhodnuti == 1 || rozhodnuti == 2)//sčítání a odčítání
			{
				if (seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno vektoru, do ktereho pujde vysledek", &poziceVysledku)
					&& seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno prvniho vektoru", &pozicePrvnihoClenu)
					&& seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno druheho vektoru", &poziceDruhehoClenu))
				{
					if (rozhodnuti == 1)
					{
						seznam->sloupecNaPozici(poziceVysledku)->vektor = seznam->sloupecNaPozici(pozicePrvnihoClenu)->vektor + seznam->sloupecNaPozici(poziceDruhehoClenu)->vektor;
					}
					else//rozhodnuti == 2
					{
						seznam->sloupecNaPozici(poziceVysledku)->vektor = seznam->sloupecNaPozici(pozicePrvnihoClenu)->vektor - seznam->sloupecNaPozici(poziceDruhehoClenu)->vektor;
					}

				}
			}
			else if (rozhodnuti == 3)//nasobení
			{
				if (seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno vektoru, do ktereho pujde vysledek", &poziceVysledku)
					&& seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno vektoru, ktery bude nasoben", &pozicePrvnihoClenu))
				{
					cout << "Zadejte cislo, kterym chcete vektor nasobit: ";
					float cislo = vstupCisla();
					seznam->sloupecNaPozici(poziceVysledku)->vektor = seznam->sloupecNaPozici(pozicePrvnihoClenu)->vektor * cislo;
				}
			}
			break;
		}
		case 4://vymenit vektory
		{
			int indexA, indexB;
			if (seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno prvniho vektoru k vymene: ", &indexA)
				&& seznam->hledaniPoziceVektoruPodleJmena("Zadejte jmeno druheho vektoru k vymene: ", &indexB))
			{
				seznam->vymenSloupce(indexA, indexB);
			}
			break;
		}
		case 5:
			seznam->horniTrojuhelnikovyTvar();
			break;
		case 6://pojmenovani
			seznam->pojmenuj();
			break;
		case 7://zmena dimenze
		{
			cout << "Dimenze seznamu je " << seznam->dimenzeSeznamu() << ". Zadejte cislo 1-100, na jaké chcete dimenzi zmenit (zadejte 0 pro vraceni do hlavni nabidky): ";
			int dim = vstupCisla(0, 100);
			if (dim != 0)
			{
				seznam->zmenDimenzi(dim);
			}
			break;
		}
		case 8://ulozit
			seznam->uloz(adresar);
			naposledyUlozeno = true;
			break;
		case 9://ulozit jako
			seznam->ulozitJako(adresar);
			naposledyUlozeno = true;
			break;
		case 10://nacist soubor
		{
			cout << "Zadejte jmeno souboru, ktery chcete otevrit, bez typu souboru (napr. pro otevreni souboru 'mojeJmeno.txt' je potreba zadat 'mojeJmeno'): ";
			string jmenoSouboru;
			cin >> jmenoSouboru;
			seznam->nactiZeSouboru(jmenoSouboru, adresar);
			break;
		}
		case 11://navod
			vypisTextovySoubor("PomocneSoubory\\Navod.txt");
			system("pause");
			break;
		case 12:
			cout << seznam->determinant() << endl;
			system("pause");
			break;
		case 13:
			seznam->urciInverzniMatici();
			break;
		case 14:
			seznam->pridejJednotkovouMatici();
			break;
		case 15:
			seznam->prepnoutVypisovani();
			break;
		case 0://pred ukoncenim
			if (!naposledyUlozeno)
			{
				cout << "Posledni upravy jeste nebyly ulozeny. Opravdu chcete ukoncit program?" << endl;
				cout << "1 - presto ukoncit" << endl;
				cout << "2 - ulozit a ukoncit" << endl;
				cout << "0 - zpet do hlavni nabidky" << endl;
				int rozhodnuti = vstupCisla(0, 2);
				if (rozhodnuti == 0)
				{
					vyber = -1;
				}
				else if (rozhodnuti == 1)
				{
					break;
				}
				else//rozhodnuti == 2
				{
					seznam->uloz(adresar);
					break;
				}
			}
			break;
		default:
			break;
		}
		system("cls");
	} while (vyber != 0);

	delete seznam;
}


void vypisTextovySoubor(string jmeno)
{
	ifstream soubor = ifstream(jmeno);
	if (!soubor.is_open())
	{
		cout << "!!! Soubor " << jmeno << " nebyl nalezen nebo se ho nepodarilo otevrit" << endl;
		return;
	}
	string pomocny;
	while (soubor.peek() != EOF)//vypisuje znaky dokud nedojde na konec souboru
	{
		pomocny = soubor.get();
		cout << pomocny;
	}
	cout << endl;
}

int vstupCisla(int dolniHranice, int horniHranice)//využívána pro výběr z očíslovaných možností
{
	int cislo;
	cin >> cislo;
	while (cin.fail() == true || cislo < dolniHranice || cislo > horniHranice)
	{
		cout << "Vstup byl ve spatnem formatu" << endl;
		cin.clear();
		cin.ignore(256,'\n');
		cout << "Zadej svou volbu znovu: ";
		cin >> cislo;
	}
	return cislo;
}

float vstupCisla()
{
	float cislo;
	cin >> cislo;
	while (cin.fail() == true)
	{
		cout << "Vstup byl ve spatnem formatu" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Zadej svou volbu znovu: ";
		cin >> cislo;
	}
	return cislo;
}



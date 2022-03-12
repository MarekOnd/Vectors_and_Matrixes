#pragma once
#include "Predloha.h";
#include "Vektor.h";


struct sloupec {
	Vektor vektor;
	sloupec* dalsiS;
};
class SeznamVektoru : public Predloha
{
private:
	sloupec* prvni;
	sloupec* posledni;
	int pocetSloupcu;
	int dimenze;

	//detaily
	int pocetDesetinnychMist = 2;//m�n� se manu�ln� zde
	bool vypisovatMaticiPriUpravach = false;
public:
	SeznamVektoru(int dim);
	~SeznamVektoru();

	//nastaveni
	void prepnoutVypisovani() { vypisovatMaticiPriUpravach = !vypisovatMaticiPriUpravach; }

	//p�id�v�n�
	void pridejNaPozici(int a, sloupec* s);
	void pridejNaPozici(int a, Vektor vektor);
	void pridejNaZacatek(sloupec* s);
	void pridejNaZacatek(Vektor vektor);
	void pridejNaKonec(sloupec* s);
	void pridejNaKonec(Vektor vektor);
	void zadejSloupec();
	void zadejSloupecNaPozici(int a);

	//odstra�ov�n�
	sloupec* odpojNaPozici(int a);
	void odstranNaPozici(int a);
	void odstranPrvni();
	void odstranPosledni();
	void vyprazdniSeznam();


	//vypisov�n�
	void vypisInfo();//dimenze, pocet sloupcu, soubor k ukladani
	void vypisSloupec(int a);
	void vypisSloupecInfo(int a);
	void vypisSeznam();
	void vypisRadek(int a);
	void vypisMatici(bool vypisSeJmeny = false);

	//zisk�v�n� informac�
	int pocetSloupcuSeznamu() { return pocetSloupcu; };
	int dimenzeSeznamu() { return dimenze; };
	sloupec* sloupecNaPozici(int a);
	sloupec* najdiPodleJmena(string jmeno);
	int najdiCisloSloupcePodleJmena(string jmeno);
	Vektor radekNaVektor(int a);
	Vektor vektorNaPozici(int a);

	bool hledaniPoziceVektoruPodleJmena(string popisek, int* pozice);//u�ivatel zad�v� jm�no vektoru, kter� chce naj�t, dokud ho program nenajde v seznamu (0 funguje jako ukonceni procesu)

	//�pravy seznamu
	void vymenSloupce(int a, int b);
	void prevratPodleDiagonaly();
	void horniTrojuhelnikovyTvar(float* det = nullptr);//funkce uprav� matici bez E�� n�soben� ��dku nenulov�m ��slem, aby 1) matice byla v p�ehledn�m tvaru 2) absolutn� hodnota determinantu se nezm�nila
	void dolniTrojuhelnikovyTvar();//uprav� s t�m, �e na diagon�le ud�l� jedni�ky
	void zmenDimenzi(int d);

	//LAL2
	//inverzn� matice Gaussovou eliminac�
	void pridejJednotkovouMatici();
	void urciInverzniMatici();
	float determinant();
	bool regularniOperator();

	//pr�ce se soubory
	void uloz(string adresar = "");
	void ulozitJako(string adresar = "");
	void nactiZeSouboru(string nazevSouboru, string adresar = "");
};


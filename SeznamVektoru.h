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
	int pocetDesetinnychMist = 2;//mìní se manuálnì zde
	bool vypisovatMaticiPriUpravach = false;
public:
	SeznamVektoru(int dim);
	~SeznamVektoru();

	//nastaveni
	void prepnoutVypisovani() { vypisovatMaticiPriUpravach = !vypisovatMaticiPriUpravach; }

	//pøidávání
	void pridejNaPozici(int a, sloupec* s);
	void pridejNaPozici(int a, Vektor vektor);
	void pridejNaZacatek(sloupec* s);
	void pridejNaZacatek(Vektor vektor);
	void pridejNaKonec(sloupec* s);
	void pridejNaKonec(Vektor vektor);
	void zadejSloupec();
	void zadejSloupecNaPozici(int a);

	//odstraòování
	sloupec* odpojNaPozici(int a);
	void odstranNaPozici(int a);
	void odstranPrvni();
	void odstranPosledni();
	void vyprazdniSeznam();


	//vypisování
	void vypisInfo();//dimenze, pocet sloupcu, soubor k ukladani
	void vypisSloupec(int a);
	void vypisSloupecInfo(int a);
	void vypisSeznam();
	void vypisRadek(int a);
	void vypisMatici(bool vypisSeJmeny = false);

	//ziskávání informací
	int pocetSloupcuSeznamu() { return pocetSloupcu; };
	int dimenzeSeznamu() { return dimenze; };
	sloupec* sloupecNaPozici(int a);
	sloupec* najdiPodleJmena(string jmeno);
	int najdiCisloSloupcePodleJmena(string jmeno);
	Vektor radekNaVektor(int a);
	Vektor vektorNaPozici(int a);

	bool hledaniPoziceVektoruPodleJmena(string popisek, int* pozice);//uživatel zadává jméno vektoru, který chce najít, dokud ho program nenajde v seznamu (0 funguje jako ukonceni procesu)

	//úpravy seznamu
	void vymenSloupce(int a, int b);
	void prevratPodleDiagonaly();
	void horniTrojuhelnikovyTvar(float* det = nullptr);//funkce upraví matici bez EØÚ násobení øádku nenulovým èíslem, aby 1) matice byla v pøehledném tvaru 2) absolutní hodnota determinantu se nezmìnila
	void dolniTrojuhelnikovyTvar();//upraví s tím, že na diagonále udìlá jednièky
	void zmenDimenzi(int d);

	//LAL2
	//inverzní matice Gaussovou eliminací
	void pridejJednotkovouMatici();
	void urciInverzniMatici();
	float determinant();
	bool regularniOperator();

	//práce se soubory
	void uloz(string adresar = "");
	void ulozitJako(string adresar = "");
	void nactiZeSouboru(string nazevSouboru, string adresar = "");
};


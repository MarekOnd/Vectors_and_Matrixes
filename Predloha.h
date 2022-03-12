#pragma once

#include <iostream>
#include <string.h>

using namespace std;

class Predloha
{
protected:
	string jmeno;
	string typ;
public:
	Predloha(string j);
	Predloha();
	~Predloha();
	string ziskejJmeno() { return jmeno; };
	string ziskejTyp() { return typ; };
	void pojmenuj(string nove) { jmeno = nove; };
	void pojmenuj();
};


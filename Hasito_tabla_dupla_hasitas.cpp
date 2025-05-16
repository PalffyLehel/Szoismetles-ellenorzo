#include <iostream>
#include <fstream>

#include "Hasito_tabla_dupla_hasitas.h"

Hasito_tabla::Hasito_tabla(int meret)
{
	this->meret = meret;
	hossz = 0;
	elemek = new Elem[meret];
	for (int i = 0; i < meret; i++)
	{
		elemek[i].ertek = 0;
		elemek[i].kulcs = new char[1];
		elemek[i].kulcs[0] = ']';
	}

	std::ifstream pr("primek.txt");
	int h2szam;
	pr >> h2szam;
	while (h2szam * 2 < meret)
	{
		pr >> h2szam;
	}
	pr.close();

	hash2szam = h2szam;
}

Hasito_tabla::~Hasito_tabla()
{
	delete elemek;
}

void Hasito_tabla::berak(Elem elem)
{
	int hely = hash1(elem.kulcs);
	int eltolas = hash2(elem.kulcs);
	while (elemek[hely].ertek != 0)
	{
		hely = (hely + eltolas) % meret;
	}
	elemek[hely] = elem;

	hossz++;
	if (hossz / (double)meret >= 0.75)
	{
		rehash();
	}
}

void Hasito_tabla::kivesz(Elem elem)
{
	int hely = hash1(elem.kulcs);
	int eltolas = hash2(elem.kulcs);
	while (strcmp(elemek[hely].kulcs, elem.kulcs))
	{
		if (elemek[hely].ertek == 0)
		{
			return;
		}

		hely = (hely + eltolas) % meret;
	}
	elemek[hely].ertek = 0;
	hossz--;
}

Hasito_tabla::Elem Hasito_tabla::keres(char* kulcs)
{
	int hely = hash1(kulcs);
	int eltolas = hash2(kulcs);
	while (strcmp(elemek[hely].kulcs, kulcs))
	{
		if (elemek[hely].ertek == 0)
		{
			Elem seged;
			seged.ertek = -1;
			return seged;
		}

		hely = (hely + eltolas) % meret;
	}
	return elemek[hely];
}

/*
void Hasito_tabla::kiir()
{
	for (int i = 0; i < meret; i++)
	{
		if (elemek[i].ertek != 0)
		{
			std::cout << elemek[i].kulcs << " " << elemek[i].ertek << std::endl;
		}
	}
}
*/

int Hasito_tabla::hash1(char* kulcs)
{
	int m = strlen(kulcs);
	return (kulcs[0] * kulcs[m - 1] * kulcs[m / 2]) % meret;
}

int Hasito_tabla::hash2(char* kulcs)
{
	return hash2szam % meret;
}

void Hasito_tabla::rehash()
{
	std::ifstream pr("primek.txt");
	int ujmeret;
	pr >> ujmeret;
	while (ujmeret < meret * 2)
	{
		pr >> ujmeret;
	}
	pr.close();

	Hasito_tabla ujtabla(ujmeret);

	for (int i = 0; i < meret; i++)
	{
		if (elemek[i].ertek != 0)
		{
			ujtabla.berak(elemek[i]);
		}
	}

	meret = ujmeret;
	delete[] elemek;
	elemek = new Elem[meret];
	std::copy(ujtabla.elemek, ujtabla.elemek + meret, elemek);
	hash2szam = ujtabla.hash2szam;
}

int Hasito_tabla::get_meret()
{
	return meret;
}
#pragma once
#include <iostream>

class Hasito_tabla
{
private:
	struct Elem;
	Elem* elemek;

	int hossz;
	int meret;

	int hash2szam;
	
	void rehash();
	
	int hash1(char*);
	int hash2(char*);

public:
	struct Elem
	{
		char* kulcs;
		int ertek;
	};
	
	Hasito_tabla(int);
	~Hasito_tabla();
	
	void berak(Elem);
	void kivesz(Elem);
	
	Elem keres(char*);
	
	//void kiir();
	
	int get_meret();
};


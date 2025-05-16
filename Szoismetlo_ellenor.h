#pragma once

#include <string>
#include <vector>

#include "Hasito_tabla_dupla_hasitas.h"

class Szoismetlo_ellenor
{
private:
	Hasito_tabla* szoveg;
	const char* szoveg_allomany;
	int mondatszam;
	
	Hasito_tabla* szinonimak;
	const char* szinonima_allomany;
	std::vector < std::pair<std::string, std::vector<std::string > > > szinonima_seged;
	int szinonimak_szama;
	Hasito_tabla* kijavitando;

	bool betu_v_szam(char);
	void hibas_kivesz(std::string&);

	void szinonimak_firssites();
	
	void szoveg_beolvas_tombbe(const char*);
	void szotar_beolvas_tombbe(const char*);

public:
	Szoismetlo_ellenor(int);
	Szoismetlo_ellenor(int, const char*);

	void szoveg_beolvas(const char*, bool);
	void szoveg_beolvas(bool);
	
	void szotar_beolvas(const char*, bool);
	void szotar_letrehoz();
	
	void szoveg_kijavit(int, bool, bool);
};
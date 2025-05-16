#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>

#include <ctime>
#include <iomanip>

#include <cmath>

#include "Szoismetlo_ellenor.h"

Szoismetlo_ellenor::Szoismetlo_ellenor(int meret)
{
	szoveg = new Hasito_tabla(meret);
	szinonimak = new Hasito_tabla(meret);
	szinonima_seged.resize(meret);
	kijavitando = new Hasito_tabla(meret);

	mondatszam = 0;
	szinonimak_szama = 1;
}

Szoismetlo_ellenor::Szoismetlo_ellenor(int meret, const char* allomany)
{
	szoveg = new Hasito_tabla(meret);
	szinonimak = new Hasito_tabla(meret);
	szinonima_seged.resize(meret);
	kijavitando = new Hasito_tabla(meret);
	
	szoveg_allomany = allomany;

	mondatszam = 0;
	szinonimak_szama = 1;
}

bool Szoismetlo_ellenor::betu_v_szam(char karakter)
{
	return ('a' <= karakter && karakter <= 'z') || 
		   ('A' <= karakter && karakter <= 'Z') || 
		   ('0' <= karakter && karakter <= '9');
}

void Szoismetlo_ellenor::hibas_kivesz(std::string& szo)
{
	int i = 0;
	while (i < szo.size())
	{
		if (!betu_v_szam(szo[i]))
		{
			szo = szo.substr(0, i) + szo.substr(i + 1);
		}

		else
		{
			i++;
		}
	}
}

void Szoismetlo_ellenor::szoveg_beolvas(const char* allomany, bool statisztika)
{
	std::cout << allomany << " feldolgozasa.\n";

	Hasito_tabla::Elem elem;
	std::ifstream in(allomany);
	std::string sor;

	clock_t ido = clock();
	while (getline(in, sor))
	{
		mondatszam++;

		if (sor == "")
		{
			continue;
		}

		std::stringstream seged(sor);
		std::string szo;
		while (getline(seged, szo, ' '))
		{
			hibas_kivesz(szo);

			if (szo == "")
			{
				continue;
			}

			elem.kulcs = new char[szo.size() + 1];
			strcpy(elem.kulcs, szo.c_str());
			elem.ertek = szoveg->keres(elem.kulcs).ertek;
			if (elem.ertek == -1)
			{
				elem.ertek = 1;
				szoveg->berak(elem);
			}

			else
			{
				szoveg->kivesz(elem);
				elem.ertek++;
				szoveg->berak(elem);
			}
		}
	}

	if (statisztika)
	{
		std::cout << std::fixed << std::setprecision(2) << (double)(clock() - ido) / CLOCKS_PER_SEC << " masodperc hasito tablaval" << std::endl;
		szoveg_beolvas_tombbe(allomany);
	}
}

void Szoismetlo_ellenor::szoveg_beolvas(bool statisztika)
{
	szoveg_beolvas(szoveg_allomany, statisztika);
}

void Szoismetlo_ellenor::szotar_beolvas(const char* allomany, bool statisztika)
{
	std::cout << allomany << " szotarra alakitasa.\n";
	szinonima_allomany = allomany;

	Hasito_tabla::Elem elem;
	std::ifstream in(allomany);
	std::string sor;

	clock_t ido = clock();
	while (getline(in, sor))
	{
		if (sor == "")
		{
			continue;
		}

		std::stringstream seged(sor);
		std::string szinonima;
		getline(seged, szinonima, ' ');
		std::string szo = szinonima;
		
		elem.kulcs = new char[szo.size() + 1];
		strcpy(elem.kulcs, szo.c_str());
		elem.ertek = szinonimak->keres(elem.kulcs).ertek;
		if (elem.ertek == -1)
		{
			elem.ertek = szinonimak_szama;
			szinonimak->berak(elem);
			szinonimak_szama++;
		}

		while (getline(seged, szinonima, ' '))
		{
			if (szinonima == "")
			{
				continue;
			}

			for (int i = 0; i < szinonima.size(); i++)
			{
				if (szinonima[i] == '_')
				{
					szinonima[i] = ' ';
				}
			}

			if (elem.ertek == szinonima_seged.size())
			{
				szinonima_seged.resize(szinonimak->get_meret());
			}

			szinonima_seged[elem.ertek].first = szo;
			szinonima_seged[elem.ertek].second.push_back(szinonima);
		}
	}

	if (statisztika)
	{
		std::cout << std::fixed << std::setprecision(2) << (double)(clock() - ido) / CLOCKS_PER_SEC << " masodperc hasito tablaval" << std::endl;
		szotar_beolvas_tombbe(allomany);
	}
}

void Szoismetlo_ellenor::szotar_letrehoz()
{
	szinonima_allomany = "uj_szotar.txt";
	std::cout << std::endl;
	std::cout << "Adja meg a szavakat. Ha mar nem akar tobbet irni irjon be egy 0-t.\n";
	std::string szo;
	do
	{
		std::cout << "Adjon meg egy szot: ";
		std::cin >> szo;

		if (szo == "0")
		{
			continue;
		}

		std::pair <std::string, std::vector<std::string> > seged;
		seged.first = szo;

		std::string szinonima;
		std::cout << "Adjon meg szinonimakat:\n";
		do
		{
			std::cout << "Szinonima: ";
			std::cin >> szinonima;

			if (szinonima != "0")
			{
				seged.second.push_back(szinonima);
			}
		} while (szinonima != "0");

		Hasito_tabla::Elem elem;
		elem.ertek = szinonimak_szama;
		elem.kulcs = new char[szo.size() + 1];
		strcpy(elem.kulcs, szo.c_str());
		szinonimak->berak(elem);
		szinonima_seged[szinonimak_szama++] = seged;

		if (szinonimak_szama == szinonima_seged.size())
		{
			szinonima_seged.resize(szinonimak->get_meret());
		}

	} while (szo != "0");

	std::cout << "Szeretne elmenteni az uj szotarat?\n";
	std::cout << "1 Igen\n2 Nem\n";
	int valasz;
	std::cin >> valasz;
	std::cin.get();

	if (valasz == 1)
	{
		std::ofstream ki("uj_szotar.txt");
		for (int i = 1; i < szinonimak_szama; i++)
		{
			ki << szinonima_seged[i].first << " ";
			for (int j = 0; j < szinonima_seged[i].second.size(); j++)
			{
				ki << szinonima_seged[i].second[j] << " ";
			}
			ki << std::endl;
		}
		ki.close();

		std::cout << "A szotar el lett mentve uj_szotar.txt neven.\n";
	}
}

void Szoismetlo_ellenor::szinonimak_firssites()
{
	std::ofstream ki(szinonima_allomany);

	for (int i = 0; i < szinonimak_szama; i++)
	{
		ki << szinonima_seged[i].first << " ";
		for (int j = 0; j < szinonima_seged[i].second.size(); j++)
		{
			ki << szinonima_seged[i].second[j] << " ";
		}
		ki << std::endl;
	}

	ki.close();
}

void Szoismetlo_ellenor::szoveg_kijavit(int gyakorisag, bool manualis, bool statisztika)
{
	std::cout << szoveg_allomany << " kijavitasa" << std::endl;

	Hasito_tabla::Elem elem;
	std::ifstream in(szoveg_allomany);
	std::string sor;

	int mentes = szinonimak_szama;

	std::ofstream er("eredmeny.txt");

	clock_t ido = clock();
	while (getline(in, sor))
	{
		if (sor == "")
		{
			continue;
		}

		std::stringstream seged(sor);
		std::string szo;
		std::string feldolgozott;
		while (getline(seged, szo, ' '))
		{
			hibas_kivesz(szo);

			if (szo == "")
			{
				continue;
			}
		
			elem.kulcs = new char[szo.size() + 1];
			strcpy(elem.kulcs, szo.c_str());
			elem.ertek = szoveg->keres(elem.kulcs).ertek;
			if (elem.ertek == -1)
			{
				std::cout << "nincs benne\n";
				exit(1);
			}
			
			if (manualis)
			{
				std::cout << szo << " ";
			}

			if ((double)elem.ertek / mondatszam * gyakorisag > 1)
			{
				int szin;
				szin = szinonimak->keres(elem.kulcs).ertek;
			
				if (szin == -1)
				{
					if (kijavitando->keres(elem.kulcs).ertek == 0)
					{
						if (manualis)
						{
							feldolgozott += elem.kulcs;
							feldolgozott += " ";
						}

						else
						{
							er << elem.kulcs << " ";

						}
						continue;
					}

					std::cout << "\nNincs szinonima erre a szora: <" << elem.kulcs << ">. " << "Akar megadni szinonimat? \n";
					std::cout << "1 Igen\n2 Nem\n";
					int valasz;
					std::cin >> valasz;
					std::cin.get();
					if (valasz == 1)
					{
						std::string seged;
						std::cin >> seged;

						if (manualis)
						{
							feldolgozott += seged + " ";
							std::cout << feldolgozott;
						}

						else
						{
							er << seged << " ";
						}

						elem.ertek = szinonimak_szama;
						szinonima_seged[szinonimak_szama].first = elem.kulcs;
						szinonima_seged[szinonimak_szama].second.push_back(seged);
						szinonimak->berak(elem);

						szinonimak_szama++;
						
						if (!manualis)
						{
							Hasito_tabla::Elem valt = szoveg->keres(elem.kulcs);
							szoveg->kivesz(valt);
							valt.ertek--;
							if (valt.ertek != 0)
							{
								szoveg->berak(valt);
							}

							char* p = new char[seged.size() + 1];
							strcpy(p, seged.c_str());
							valt = szoveg->keres(p);
							if (valt.ertek == -1)
							{
								valt.ertek = 1;
								valt.kulcs = new char[seged.size() + 1];
								strcpy(valt.kulcs, p);
								szoveg->berak(valt);
							}

							else
							{
								szoveg->kivesz(valt);
								valt.ertek++;
								szoveg->berak(valt);
							}
						}
					}
					else
					{
						Hasito_tabla::Elem seged;
						seged.ertek = 0;
						seged.kulcs = new char[szo.size() + 1];
						strcpy(seged.kulcs, elem.kulcs);
						kijavitando->berak(seged);
						if (manualis)
						{
							feldolgozott += szo + " ";
							std::cout << feldolgozott;
						}

						else
						{
							er << elem.kulcs << " ";
						}
					}
				}

				else
				{
					if (manualis)
					{
						std::cout << "\nA <" << szo << "> tul sokszor fordul elo.\n";
						std::cout << "1 Specifikus helyettesites\n2 Rrandom helyettesites\n3 Bekenhagy\n";
						int valasz;
						std::cin >> valasz;
						std::cin.get();

						switch (valasz)
						{
						case 1:
							for (int i = 0; i < szinonima_seged[szin].second.size(); i++)
							{
								std::cout << i + 1 << " " << szinonima_seged[szin].second[i] << std::endl;
							}

							int valasz2;
							std::cin >> valasz2;
							std::cin.get();
							feldolgozott += szinonima_seged[szin].second[valasz2 - 1] + " ";
							std::cout << feldolgozott;

							break;
						case 2:
							feldolgozott += szinonima_seged[szin].second[rand() % szinonima_seged[szin].second.size()] + " ";
							std::cout << feldolgozott;
							break;

						case 3:
							feldolgozott += szo + " ";
							std::cout << feldolgozott;
							break;

						default:
							feldolgozott += szo + " ";
							std::cout << feldolgozott;
							break;
						}
					}

					else
					{
						er << szinonima_seged[szin].second[rand() % szinonima_seged[szin].second.size()] << " ";
					}
				}
			}

			else
			{
				if (manualis)
				{
 					feldolgozott += szo + " ";
				}

				else
				{
					er << szo << " ";
				}
			}
		}

		if (manualis)
		{
			std::cout << std::endl;
		}

		else
		{
			er << std::endl;
		}

		if (manualis)
		{
			er << feldolgozott << std::endl;
		}
	}

	er.close();

	if (szinonimak_szama != mentes)
	{
		std::cout << "El szeretne menteni az uj szinonimakat?\n";
		std::cout << "1 igen\n2 nem\n";
		int valasz;
		std::cin >> valasz;
		std::cin.get();

		if (valasz == 1)
		{
			szinonimak_firssites();
			std::cout << "Szotar frissitve.\n";
		}
	}

	if (statisztika)
	{
		std::cout << std::fixed << std::setprecision(2) << (double)(clock() - ido) / CLOCKS_PER_SEC << " masodperc" << std::endl;
	}
}

void Szoismetlo_ellenor::szoveg_beolvas_tombbe(const char* allomany)
{
	std::ifstream in(allomany);
	std::vector < std::pair < std::string, int > > elofordulasok;
	std::string sor;

	int i;
	bool kapott;

	clock_t ido = clock();
	while (getline(in, sor))
	{
		if (sor == "")
		{
			continue;
		}

		std::stringstream seged(sor);
		std::string szo;
		while (getline(seged, szo, ' '))
		{
			hibas_kivesz(szo);

			if (szo == "")
			{
				continue;
			}

			i = 0;
			kapott = false;
			while (i < elofordulasok.size() && !kapott)
			{
				if (elofordulasok[i].first == szo)
				{
					elofordulasok[i].second++;
					kapott = true;
				}

				else
				{
					i++;
				}
			}

			if (i == elofordulasok.size())
			{
				elofordulasok.push_back(std::make_pair(szo, 1));
			}
		}
	}

	std::cout << std::fixed << std::setprecision(2) << (double)(clock() - ido) / CLOCKS_PER_SEC << " masodperc tombbel" << std::endl;
}

void Szoismetlo_ellenor::szotar_beolvas_tombbe(const char* allomany)
{
	std::ifstream in(allomany);
	std::vector < std::pair < std::string, std::vector<std::string> > > elofordulasok;
	std::string sor;

	int i, index;
	bool kapott;

	clock_t ido = clock();
	while (getline(in, sor))
	{
		if (sor == "")
		{
			continue;
		}

		std::stringstream seged(sor);
		std::string szo;
		getline(seged, szo, ' ');

		index = -1;
		i = 0;
		kapott = false;
		while (i < elofordulasok.size() && !kapott)
		{
			if (elofordulasok[i].first == szo)
			{
				kapott = true;
			}

			else
			{
				i++;
			}
		}
		index = i;
		if (index == elofordulasok.size())
		{
			std::vector<std::string> aux;
			elofordulasok.push_back(std::make_pair(szo, aux));
		}

		while (getline(seged, szo, ' '))
		{
			hibas_kivesz(szo);

			if (szo == "")
			{
				continue;
			}

			elofordulasok[index].second.push_back(szo);
		}
	}

	std::cout << std::fixed << std::setprecision(2) << (double)(clock() - ido) / CLOCKS_PER_SEC << " masodperc tombbel" << std::endl;
}

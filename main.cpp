#include <iostream>
#include <string>

#include "Szoismetlo_ellenor.h"

int main()
{
	int valasz = 1;
	std::string allomany;
	std::string szotar;
	bool statisztika, manualis;
	int gyakorisag;

	while (valasz != 2)
	{
		std::cout << "\n_____________________________________	Szoismetles ellenorzo	_____________________________________\n\n";
		std::cout << "Irja be az allomany nevet amit ellenorizni szeretne: ";
		std::cin >> allomany;
		Szoismetlo_ellenor ellenorzo(7, allomany.c_str());

		std::cout << "\nSzeretne megmerni, hogy mennyi ido alatt dolgozza fel a program az allomanyt?\n";
		std::cout << "1 Igen\n2 Nem\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get();
		statisztika = valasz == 1;
		ellenorzo.szoveg_beolvas(statisztika);

		std::cout << "\nAdjon meg egy szinonima szotarat!\n";
		std::cout << "1 Letezo szotar\n2 Uj szotar letrehozasa\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get();

		if (valasz == 1)
		{
			std::cout << "Adja meg a szotarat: ";
			std::cin >> szotar;

			std::cout << "\nSzeretne megmerni, hogy mennyi ido alatt dolgozza fel a program a szotarat?\n";
			std::cout << "1 Igen\n2 Nem\n";
			std::cout << "Valasz: ";
			std::cin >> valasz;
			std::cin.get();
			statisztika = valasz == 1;
			ellenorzo.szotar_beolvas(szotar.c_str(), statisztika);
		}

		else
		{
			ellenorzo.szotar_letrehoz();
		}

		std::cout << "\nManualisan vagy automatikusan szeretne kijavitani a szoveget?\n";
		std::cout << "1 Manualisan\n2 Automatikusan\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get(); 
		manualis = valasz == 1;

		std::cout << "\nEgy 1-10-es skalan mennyire gyakran fordulhatnak elo szavak?\n(1 - viszonylag gyakran, 10 - nagyon ritkan)\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get();
		gyakorisag = valasz;

		std::cout << "\nSzeretne megmerni, hogy mennyi ido alatt javitja ki a program a szoveget?\n";
		std::cout << "1 Igen\n2 Nem\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get();
		statisztika = valasz == 1;
		ellenorzo.szoveg_kijavit(gyakorisag, manualis, statisztika);

		std::cout << "\nSzeretne ujabb allomanyt feldolgozni?\n";
		std::cout << "1 Igen\n2 Nem\n";
		std::cout << "Valasz: ";
		std::cin >> valasz;
		std::cin.get();

		system("cls");
	}
	
	return 0;
}
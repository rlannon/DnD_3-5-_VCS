#include "RaceCreationUtility.h"

void createRace() {
	std::string name;
	int bonuses[6];
	std::string langs;
	int c;

	std::cout << "Name: ";
	std::getline(std::cin, name);

	std::cout << "Languages: ";
	std::getline(std::cin, langs);

	std::cout << "Bonuses (str, dex, con, int, wis, cha):" << std::endl;
	std::cin >> bonuses[0];
	std::cin >> bonuses[1];
	std::cin >> bonuses[2];
	std::cin >> bonuses[3];
	std::cin >> bonuses[4];
	std::cin >> bonuses[5];

	Race race(name, bonuses[0], bonuses[1], bonuses[2], bonuses[3], bonuses[4], bonuses[5], langs);

	std::ofstream savefile;
	savefile.open(name + ".rvr", std::ios::out | std::ios::binary);
	if (savefile.is_open()) {
		saveToRVR(savefile, race);
		savefile.close();
	}
	else {
		std::cerr << "error writing to " << name + ".rvr" << std::endl;
	}
}
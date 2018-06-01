#include "Utility.h"

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
	savefile.open("data/" + name + ".rvr", std::ios::out | std::ios::binary);
	if (savefile.is_open()) {
		saveToRVR(savefile, race);
		savefile.close();
	}
	else {
		std::cerr << "error writing to " << name + ".rvr" << std::endl;
	}
}

void createClass(Skill skill_structure[num_skills]) {
	std::string name;
	int c;

	bool save = true; // if we get an error, don't save

	ClassData new_class;
	std::ofstream classfile;

	const unsigned short good_bab[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	const unsigned short avg_bab[20] = { 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15 };
	const unsigned short poor_bab[20] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10 };

	const unsigned short good_save[20] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
	const unsigned short poor_save[20] = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6 };

	std::cout << "Class Name: " << std::endl;
	std::getline(std::cin, name);

	new_class.name = name;

	std::cout << "[1] Good, [2] Average, or [3] Poor BAB?";
	std::cin >> c;
	if (c == 1) {
		for (int i = 0; i < 20; i++) {
			new_class.base_attack_bonus[i] = good_bab[i];
		}
	}
	else if (c == 2) {
		for (int i = 0; i < 20; i++) {
			new_class.base_attack_bonus[i] = avg_bab[i];
		}
	}
	else if (c == 3) {
		for (int i = 0; i < 20; i++) {
			new_class.base_attack_bonus[i] = poor_bab[i];
		}
	}
	else {
		std::cout << "invalid value!" << std::endl;
		save = false;
	}

	std::cout << "[1] Good or [2] Poor Fortitude?";
	std::cin >> c;
	if (c == 1) {
		for (int i = 0; i < 20; i++) {
			new_class.fortitude[i] = good_save[i];
		}
	}
	else if (c == 2) {
		for (int i = 0; i < 20; i++) {
			new_class.fortitude[i] = poor_save[i];
		}
	}
	else {
		std::cout << "invalid value!" << std::endl;
		save = false;
	}

	std::cout << "[1] Good or [2] Poor Reflex?";
	std::cin >> c;
	if (c == 1) {
		for (int i = 0; i < 20; i++) {
			new_class.reflex[i] = good_save[i];
		}
	}
	else if (c == 2) {
		for (int i = 0; i < 20; i++) {
			new_class.reflex[i] = poor_save[i];
		}
	}
	else {
		std::cout << "invalid value!" << std::endl;
		save = false;
	}

	std::cout << "[1] Good or [2] Poor Will?";
	std::cin >> c;
	if (c == 1) {
		for (int i = 0; i < 20; i++) {
			new_class.will[i] = good_save[i];
		}
	}
	else if (c == 2) {
		for (int i = 0; i < 20; i++) {
			new_class.will[i] = poor_save[i];
		}
	}
	else {
		std::cout << "invalid value!" << std::endl;
		save = false;
	}

	std::cout << "Hit Die Type? ";
	std::cin >> c;
	new_class.hit_die = c;

	std::cout << "Skill Coefficient? ";
	std::cin >> c;
	new_class.skill_coefficient = c;

	std::cout << "\t\tClass Skills:" << std::endl;

	for (int i = 0; i < num_skills; i++) {
		std::cout << skill_structure[i].getSkillName() << "?";
		std::cin >> c;
		if (c == 0) {
			new_class.classSkillFlag[i] = false;
		}
		else {
			new_class.classSkillFlag[i] = true;
		}
	}

	if (save) {
		classfile.open("data/" + name + ".rvc", std::ios::out | std::ios::binary);
		if (classfile.is_open()) {
			saveToRVC(classfile, new_class);
		}
		else {
			std::cout << "error opening file in \"createClass()\"!" << std::endl;
		}
	}
	else if (!save) {
		std::cout << "there was one (or more!) errors in inputting values; data was not saved" << std::endl;
	}
}

void createSkill() {
	Skill skill_structure[num_skills];
	for (int i = 0; i < num_skills; i++) {
		std::string name;
		bool untrained;
		std::string ability;
		std::string c;

		std::cout << "Skill Name: ";
		std::getline(std::cin, name);
		std::cout << "Key Ability: ";
		std::getline(std::cin, ability);
		std::cout << "Untrained? ";
		std::getline(std::cin, c);
		if (c == "yes") {
			untrained = true;
		}
		else if (c == "no") {
			untrained = false;
		}
		else {
			std::cout << "invalid selection. defaulting to yes" << std::endl;
			untrained = true;
		}
		skill_structure[i].name = name;
		skill_structure[i].ability = ability;
		skill_structure[i].untrained = untrained;

		std::cout << std::endl;
	}
	std::ofstream skillfile;
	skillfile.open("data/skills.skills", std::ios::out | std::ios::binary);
	if (skillfile.is_open()) {
		saveSkillStructure(skillfile, skill_structure);
	}
}

void modClass() {
	ClassData temp;
	std::ifstream classfile;
	std::string classname;

	int i = 1;
	int c;

	std::cout << "Which class would you like to modify?" << std::endl;
	std::getline(std::cin, classname);

	classfile.open("data/" + classname + ".rvc", std::ios::in | std::ios::binary);
	if (classfile.is_open()) {
		loadClassData_RVC(classfile, &temp);
		classfile.close();
	}
	else {
		std::cout << "error reading classfile in loadClassData_RVC" << std::endl;
	}

	std::ofstream rvcsave;
	rvcsave.open("data/" + classname + ".rvc", std::ios::out | std::ios::binary);

	while (i > 0) {
		std::cout << "What do you want to modify?" << std::endl
			<< "[1] Name" << std::endl
			<< "[2] BAB" << std::endl
			<< "[3] Saving Throws" << std::endl
			<< "[4] Skill Flags" << std::endl
			<< "[5] Hit Die" << std::endl
			<< "[6] Skill Coefficient" << std::endl
			<< std::endl << "[7] Nevermind " << std::endl;
		std::cin >> c;
		switch (c) {
		case 1:
			std::getline(std::cin, classname);
			std::cout << "New name: ";
			std::getline(std::cin, classname);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			i--;
			break;
		}
	}
	
	if(rvcsave.is_open()) {
		saveToRVC(rvcsave, temp);
		rvcsave.close();
	}
	else {
		std::cout << "cout not open \"rvcsave\" for writing in modClass() !" << std::endl;
	}
}

void utility() {
	std::string err;

	Skill skill_structure[num_skills];
	Skill* skill_ptr = &skill_structure[0];
	
	int i = 1;
	short ch;

	while (i > 0) {
		std::cout << "\t\tUTILITY" << std::endl;
		std::cout << "What would you like to do?" << std::endl
			<< "[1] Create Race File" << std::endl
			<< "[2] Create Class File" << std::endl
			<< "[3] Create Skill File" << std::endl
			<< "[4] Modify Class File" << std::endl
			<< "[5] Quit" << std::endl;

		std::cin >> ch;

		if (ch == 1) {
			// create race
			std::getline(std::cin, err); // to prevent an err
			createRace();
		}
		else if (ch == 2) {
			// create class
			std::getline(std::cin, err); // to prevent an err
			std::ifstream skillfile;
			skillfile.open("data/skills.skills", std::ios::in, std::ios::binary);
			if (skillfile.is_open()) {
				loadSkillStructure(skillfile, skill_ptr, &err);
				skillfile.close();
			}
			createClass(skill_structure);
		}
		else if (ch == 3) {
			// create skill
			std::getline(std::cin, err); // to prevent an err
			createSkill();
		}
		else if (ch == 4) {
			std::getline(std::cin, err);
			modClass();
		}
		else if (ch == 5) {
			i--;
		}
		else {
			std::cout << "invalid selection!" << std::endl;
		}
	}
}
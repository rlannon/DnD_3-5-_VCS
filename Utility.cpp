#include "Utility.h"

void createRace() {
	std::string name;
	int bonuses[6];
	std::string langs;

	std::cout << "Name: ";
	std::cin.ignore();
	std::getline(std::cin, name);

	std::cout << "Languages: ";
	std::cin.ignore();
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

	Spell new_spell("Blindness/Deafness", "Bard, Cleric, Sorcerer/Wizard", 2, "V", "1 standard action", "Medium (100 ft + 10 ft/level)", "One living creature", "Permanent (D)", "Fortitude negates", true);

	const unsigned short good_bab[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	const unsigned short avg_bab[20] = { 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15 };
	const unsigned short poor_bab[20] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10 };

	const unsigned short good_save[20] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
	const unsigned short poor_save[20] = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6 };

	std::cout << "Class Name: " << std::endl;
	std::cin.ignore();
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
	
	std::cout << "Caster? (1/0) ";
	std::cin >> c;
	new_class.is_caster = (bool)c;

	std::cout << "\t\tClass Skills:" << std::endl;

	for (int i = 0; i < num_skills; i++) {
		std::cout << skill_structure[i].getSkillName() << "? ";
		std::cin >> c;
		if ((bool)c) {
			new_class.class_skill_vector.push_back(skill_structure[i]);
		}
		else {
			continue;
		}
	}

	for (int i = 0; i < 20; i++) {
		new_class.spells_known_by_level[i] = i;
		new_class.spells_per_day_by_level[i] = i+1;
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
		std::cin.ignore();
		std::getline(std::cin, name);

		std::cout << "Key Ability: ";
		std::cin.ignore();
		std::getline(std::cin, ability);

		std::cout << "Untrained? ";
		std::cin.ignore();
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

void modClass(Skill skill_structure[num_skills]) {
	ClassData temp;
	std::ifstream classfile;
	std::string classname;

	std::string skillname;

	Spell temp_spell;
	std::string data;
	int spell_num_data;

	int n = 1;
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

	if (rvcsave.is_open()) {
		while (n > 0) {
			int s_c;
			short good_save[20] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
			short poor_save[20] = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6 };

			std::cout << "What do you want to modify?" << std::endl
				<< "[1] Name" << std::endl
				<< "[2] BAB" << std::endl
				<< "[3] Saving Throws" << std::endl
				<< "[4] Class Skills" << std::endl
				<< "[5] Hit Die" << std::endl
				<< "[6] Skill Coefficient" << std::endl << std::endl
				<< "[7] is_caster" << std::endl
				<< "[8] Add Spells to Class" << std::endl
				<< "[9] Remove Spells from Class" << std::endl
				<< std::endl << "[10] Nothing, I'm done" << std::endl;
			std::cin >> c;
			switch (c) {
			case 1:
				std::cout << "New name: ";
				std::cin.ignore();
				std::getline(std::cin, classname);
				temp.name = classname;
				break;
			case 2:
				std::cout << "New BAB?" << std::endl
					<< "[1] Good" << std::endl
					<< "[2] Average" << std::endl
					<< "[3] Poor" << std::endl;
				std::cin >> s_c;
				if (s_c == 1) {
					short good_bab[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
					for (int i = 0; i < 20; i++) {
						temp.base_attack_bonus[i] = good_bab[i];
					}
				}
				else if (s_c == 2) {
					short avg_bab[20] = { 0, 1, 2, 3, 3, 4, 5, 6, 6, 7, 8, 9, 9, 10, 11, 12, 12, 13, 14, 15 };
					for (int i = 0; i < 20; i++) {
						temp.base_attack_bonus[i] = avg_bab[i];
					}
				}
				else if (s_c == 3) {
					short poor_bab[20] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10 };
					for (int i = 0; i < 20; i++) {
						temp.base_attack_bonus[i] = poor_bab[i];
					}
				}
				else {
					std::cout << "invalid selection!" << std::endl;
				}
				break;
			case 3:
				std::cout << "New Fortitude: " << std::endl
					<< "\t[1] Good" << std::endl
					<< "\t[2] Poor" << std::endl;
				std::cin >> s_c;
				if (s_c == 1) {
					for (int i = 0; i < 20; i++) {
						temp.fortitude[i] = good_save[i];
					}
				}
				else if (s_c == 2) {
					for (int i = 0; i < 20; i++) {
						temp.fortitude[i] = poor_save[i];
					}
				}
				else {
					std::cout << "invalid selection!" << std::endl;
					break;
				}

				std::cout << "New Reflex: " << std::endl
					<< "\t[1] Good" << std::endl
					<< "\t[2] Poor" << std::endl;
				std::cin >> s_c;
				if (s_c == 1) {
					for (int i = 0; i < 20; i++) {
						temp.reflex[i] = good_save[i];
					}
				}
				else if (s_c == 2) {
					for (int i = 0; i < 20; i++) {
						temp.reflex[i] = poor_save[i];
					}
				}
				else {
					std::cout << "invalid selection!" << std::endl;
					break;
				}

				std::cout << "New Will: " << std::endl
					<< "\t[1] Good" << std::endl
					<< "\t[2] Poor" << std::endl;
				std::cin >> s_c;
				if (s_c == 1) {
					for (int i = 0; i < 20; i++) {
						temp.will[i] = good_save[i];
					}
				}
				else if (s_c == 2) {
					for (int i = 0; i < 20; i++) {
						temp.will[i] = poor_save[i];
					}
				}
				else {
					std::cout << "invalid selection!" << std::endl;
					break;
				}

				break;
			case 4: // mod skills
				std::cout << "Add or remove a skill from the class? ";
				std::cin.ignore();
				std::getline(std::cin, data);
				if (data == "add") {
					std::cout << "Skill name? ";
					std::getline(std::cin, data);

					for (int i = 0; i < num_skills; i++) {
						bool add = true;
						// check to see if the skill is in our skill file
						if (skill_structure[i].getSkillName() == data) {
							// if it is, check to see if we already have the skill
							for (std::vector<Skill>::iterator it = temp.class_skill_vector.begin(); it != temp.class_skill_vector.end(); it++) {
								if (skill_structure[i].getSkillName() == it->getSkillName()) {
									add = false; // set this to false if the skill is in our vector already
								}
							}
							// now check to see if we should add it
							if (add) {
								temp.class_skill_vector.push_back(skill_structure[i]);
							}
							else if (!add) {
								std::cout << "skill already in vector" << std::endl;
							}
						}
					}
				}
				else if (data == "remove") {
					std::cout << "Skills in class file: " << std::endl;
					for (int i = 0; i < temp.class_skill_vector.size(); i++) {
						std::cout << "\t" << temp.class_skill_vector[i].getSkillName() << std::endl;
					}
					std::cout << "\nSkill name? (type q to quit) ";
					std::getline(std::cin, data);
					if (data == "q") {
						break;
					}
					else {
						int pos;
						for (int i = 0; i < temp.class_skill_vector.size(); i++) {
							if (temp.class_skill_vector[i].getSkillName() == data) {
								pos = i;
							}
						}
						std::cout << "removing \"" << temp.class_skill_vector[pos].getSkillName() << "\" ..." << std::endl;
						temp.class_skill_vector.erase(temp.class_skill_vector.begin() + pos);
					}
				}
				else {
					std::cout << "invalid input" << std::endl;
				}
				break;
			case 5:
				std::cout << "New Hit Die: d";
				std::cin >> s_c;
				temp.hit_die = s_c;
				break;
			case 6:
				std::cout << "New Skill Coefficient: ";
				std::cin >> s_c;
				temp.skill_coefficient = s_c;
				break;
			case 7:
				std::cout << "Is caster? (1/0): ";
				std::cin >> s_c;
				temp.is_caster = (bool)s_c;
				break;
			case 8:
				if (temp.isCaster()) {
					std::cout << "Select: " << std::endl
						<< "[1] Add Spell" << std::endl
						<< "[2] Done" << std::endl;
					std::cin >> s_c;

					if (s_c == 1) {
						std::cout << "Spell name: ";
						std::cin.ignore();
						std::getline(std::cin, data);

						temp_spell.name = data;

						temp_spell.associated_class = temp.name;

						std::cout << "Spell Level: ";
						std::cin >> spell_num_data;
						temp_spell.spell_level = spell_num_data;

						std::cout << "Spell Resistance? (1/0) ";
						std::cin >> spell_num_data;
						temp_spell.spell_resistance = (bool)spell_num_data;

						std::cout << "Components: ";
						std::cin.ignore();
						std::getline(std::cin, data);
						temp_spell.components = data;

						std::cout << "Cast Time: ";
						std::getline(std::cin, data);
						temp_spell.casting_time = data;

						std::cout << "Range: ";
						std::getline(std::cin, data);
						temp_spell.range = data;

						std::cout << "Target: ";
						std::getline(std::cin, data);
						temp_spell.target = data;

						std::cout << "Duration: ";
						std::getline(std::cin, data);
						temp_spell.duration = data;

						std::cout << "Saving Throw: ";
						std::getline(std::cin, data);
						temp_spell.saving_throw = data;

						std::cout << "Description: ";
						std::getline(std::cin, data);
						temp_spell.saving_throw = data;

						temp.class_spells.push_back(temp_spell);
					}
					else if (s_c == 2) {
						break;
					}
					else {
						std::cout << "invalid choice" << std::endl;
						break;
					}
				}
				else {
					std::cout << "Selected class is not a casting class; modify this to add spells" << std::endl;
				}
				break;
			case 9:
				std::cout << "Class Spells: " << std::endl;
				for (int i = 0; i < temp.class_spells.size(); i++) { // list spells in vector
					std::cout << "\t" << temp.class_spells[i].name << std::endl;
				}
				std::cout << "Type a spell name to remove it (or type q to cancel) ... ";
				std::cin.ignore();
				std::getline(std::cin, data);

				if (data == "q") {
					break;
				}
				else {
					int pos;
					for (int i = 0; i < temp.class_spells.size(); i++) {
						if (temp.class_spells[i].name == data) {
							pos = i;
							break;
						}
					}

					std::cout << "are you sure you want to remove \"" << temp.class_spells[pos].name << "\" ? (yes/no) ";
					std::getline(std::cin, data);

					if (data == "yes") {
						temp.class_spells.erase(temp.class_spells.begin() + pos);
					}
					else if (data == "no") {
						break;
					}
					else {
						std::cout << "invalid input. exiting..." << std::endl;
						break;
					}
				}
				break;
			case 10:
				n--;
				break;
			}
		}

	saveToRVC(rvcsave, temp);
	rvcsave.close();

	} else {
		std::cout << "cout not open \"rvcsave\" for writing in modClass() !" << std::endl;
	}
}

void utility() {
	std::string err;

	Skill skill_structure[num_skills];
	Skill* skill_ptr = &skill_structure[0];

	std::ifstream skillfile;

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
			createRace();
		}
		else if (ch == 2) {
			// create class			
			skillfile.open("data/skills.skills", std::ios::in, std::ios::binary);
			if (skillfile.is_open()) {
				loadSkillStructure(skillfile, skill_ptr);
				skillfile.close();
			}
			createClass(skill_structure);
		}
		else if (ch == 3) {
			// create skill
			createSkill();
		}
		else if (ch == 4) {
			skillfile.open("data/skills.skills", std::ios::in, std::ios::binary);
			if (skillfile.is_open()) {
				loadSkillStructure(skillfile, skill_ptr);
				skillfile.close();
			}
			std::getline(std::cin, err);
			modClass(skill_structure);
		}
		else if (ch == 5) {
			i--;
		}
		else {
			std::cout << "invalid selection!" << std::endl;
		}
	}
}
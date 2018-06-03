#pragma once
#include "stdafx.h"

#include "Race.h"
#include "ClassData.h"
#include "Skill.h"

#include "RVR.h"
#include "RVC.h"
#include "SkillsFormat.h"

void createRace();
void createClass(Skill skill_structure[num_skills]);
void createSkill();

void modClass(Skill skill_structure[num_skills]);

void utility();
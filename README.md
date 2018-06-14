# D&D v3.5 VCS

A Virtual Character Sheet Management program for D&D v3.5. The goal of this code is to establish the class structures and relationships for use in other VCS programs. This is *not* meant to be run as a command-line tool, though that is what the case is now. This will eventually have its own GUI, but at the moment, the code simply establishes all of our structures.

## Getting Started

This project uses the C++ Standard Libraries and is not platform-dependent; therefore, it can be compiled using any UNIX or DOS compiler. `main.cpp` is the main file, and each class and file format has its own `.h` and `.cpp` file.

## Classes

All game data is stored in a series of related classes; these mimic the way the information is handled in the D&D Books and Character Sheets. We have individual classes for Race, Class, Skills, Spells, Weapons, Armor, and Items, all used in the central Character class. This Characted class contains copies of data from the other classes, similar to how a Character Sheet in D&D contains information which was copied from the books. Some of these classes, namely as Skills, Spells, Weapons, Armor, and Items, are all stored in vectors. For example, our Spells are stored in `Character::vector<Spell> char_spells`. Our Race and Class data are simply pointers to our Race and Class objects that we establish alongside our Character object. See the documentation for more information on how this operates in the code.

## Utility Program

Currently, the program contains a utility program to add and edit our resource files.

## Binary File Formats

This VCS uses a few different file formats so that game data is not hard-coded in the program and so the user can save their progress. The main formats are VCS, RVO, RVC, RVR, SKILLS.

Our two central formats are VCS and RVO; they are the only variable types, the other file types will remain static within a given system (i.e., the VCS and RVO files are what will be written to, while RVC, RVR, and SKILLS are all read-only within a VCS program, unless new races and classes are to be added).

### VCS

The Virtual Character Sheet format (.vcs) is used for storing all data about the player character.

### RVO

The RKS Virtual Object format (.rvo) is used for storing information about in-game objects within the RKS program. Player inventory and object lists from the Player's Handbook are among the things that are stored in RVO files.

#### INVENTORY RVO

An RKS Inventory Object file (.intentory.rvo) is a file type that contains the inventory of a player; it is linked to a player's VCS file. One can store multiple object types inside a single Inventory RVO file.

### RVC

The RKS Virtual Class format (.rvc) is the file type used for storing data about character classes. It contains data regarding base attack bonus, saving throws, hit die, skill point coefficients, and an array to link class skills with the class and character. The format is laid out in RVC.h and RVC.cpp.

### SKILLS

The Skills format (.skills) is simply used to store our array of Skills objects.

## Built With

*[Microsoft Visual Studio 2017]() - Editor and Compiler

## Authors

*_Riley Lannon_ - Program author and debugger

## Acknowledgments

* Wizards of the Coast -- the system used, D&D v3.5, was published by WotC
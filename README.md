# D&D v3.5 VCS

A Virtual Character Sheet Management program for D&D v3.5. The goal of this code is to establish the class structures and relationships for use in other VCS programs. This is *not* meant to be run as a command-line tool, though that is what the case is now. This will eventually have its own GUI, but at the moment, the code simply establishes all of our structures.

## Classes

All game data is stored in a series of related classes; these mimic the way the information is handled in the D&D Books and Character Sheets. We have individual classes for Race, Class, and Skills, all used in the central Character class. This Characted class contains copies of data from the other classes, similar to how a Character Sheet in D&D contains information which was copied from the books.

## Utility Program

Currently, the program contains a utility program to add and edit our resource files.

## Binary File Formats

This VCS uses a few different file formats so that game data is not hard-coded in the program and so the user can save their progress. The main formats are VCS, RVC, RVR, SKILLS.

### VCS

The Virtual Character Sheet format (.vcs) is used for storing all data about the player character.

### RVC

The RKS Virtual Class format (.rvc) is the file type used for storing data about character classes. It contains data regarding base attack bonus, saving throws, hit die, skill point coefficients, and an array to link class skills with the class and character. The format is laid out in RVC.h and RVC.cpp.

### SKILLS

The Skills format (.skills) is simply used to store our array of Skills objects.
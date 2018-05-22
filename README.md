# D&D v3.5 VCS

A Virtual Character Sheet Management program for D&D v3.5. The goal of this code is to establish the class structures and relationships for use in other VCS programs. This is *not* meant to be run as a command-line tool, though that is what the case is now. This will eventually have its own GUI, but at the moment, the code simply establishes all of our structures.

## Binary File Formats

### RVC

The RKS Virtual Class format (.rvc) is the file type used for storing data about character classes. It contains data regarding base attack bonus, saving throws, hit die, skill point coefficients, and an array to link class skills with the class and character. The format is laid out in RVC.h and RVC.cpp.

### VCS

The Virtual Character Sheet format (.vcs) is used for storing all data about the player character.

### SKILLS

The Skills format (.skills) is simply used to store our array of Skills objects so it isn't hard-coded into the program.

## Note for future

Replace all instances of `readU8()` with `file.read()` and all instances of `writeU8` with `file.write()`, because we don't really need a function to do this for us.
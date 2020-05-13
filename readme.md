Creator: Timothy Rolich
Date: 5/12/20
Version 1.0

Project Desciption: This is a small text based game that allows the player to move from enemy to enemy by attacking, defending, or running. When an enemy is defeated a new random weapon or armor is added to the player. When the player is defeated they lose either the last armor or the last weapon they received. The main purpose of this game is to securely store and obfuscate the parameters of the game to avoid undue manipulation.

Installation: A .cpp and .exe are included. The exe was compiled on Windows 10 64 bit. The Obfuscator.cpp contains all of the methods required to run itself and can be compiled on most operating systems.

Usage: To use, simply run the exe file created by compilation. In the same directory a file called outputfile.txt should appear after using the quit command during gameplay. This is the file that contains the parameters of the game and they should be mostly immune from tampering. When tampering is detected default values are restored to the game.
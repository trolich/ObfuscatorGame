// Obfuscator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using std::string;

string* armors = new string[6]{"chestplate", "boots", "chainmail", "greaves", "gloves", "helmet"};
string* weapons = new string[8]{"sword", "spear", "crossbow", "bow", "axe", "hammer", "fireball", "dagger"};

unsigned int BUFF_SIZE = 64;
string playerName = "Quincy";

float maxHealth = 100;
float currentHealth = 100;

float attackPower = 1.0f;
float defense = .9f;

int numWeapons = 1;
int numArmor = 1;

string* armorNames = new string[numWeapons]{"helmet"};
float* armorValues = new float[numWeapons] {1.0f};

string* weaponNames = new string[numArmor]{"dagger"};
float* weaponValues = new float[numArmor] {1.0f};

char* encode(int); // should convert the int to a char array, pad with 0's and swivel the numbers
char* encode(float); // should convert the float to a char array, pad with 0's and swivel the numbers
char* encode(string); // should convert the string to a char array, pad with 0's and swivel the numbers

char* swivel(char[]);
char* unswivel(char[]);

int decodeInt(char[]);
float decodeFloat(char[]);
string decodeString(char[]);

char getRedundancy(char[]);
bool readInt(std::ifstream&, int&);
bool readString(std::ifstream&, string&);
bool readFloat(std::ifstream&, float&);

void writeInt(std::ofstream&, int);
void writeString(std::ofstream&, string);
void writeFloat(std::ofstream&, float);

void readFile();
void recieveInput();
void writeFile();

void printPlayerInfo();

int main()
{
	// read values of the file, if any of the redundancy checks don't pass, leave default values
	readFile();
	printPlayerInfo();
	// todo allow user to manipulate the player attributes
	recieveInput();
	printPlayerInfo();
	// write values to the file
	writeFile();
}

void readFile()
{
	std::ifstream inFile;
	inFile.open("outputfile.txt");
	string tempPlayerName;
	if (!readString(inFile, tempPlayerName))
	{
		inFile.close();
		return;
	}

	float tempMaxHealth;
	if (!readFloat(inFile, tempMaxHealth))
	{
		inFile.close();
		return;
	}

	float tempCurrentHealth;
	if(!readFloat(inFile, tempCurrentHealth))
	{
		inFile.close();
		return;
	}

	float tempAttackPower;
	if (!readFloat(inFile, tempAttackPower))
	{
		inFile.close();
		return;
	}

	float tempDefense;
	if (!readFloat(inFile, tempDefense))
	{
		inFile.close();
		return;
	}

	int tempNumWeapons;
	if (!readInt(inFile, tempNumWeapons))
	{
		inFile.close();
		return;
	}

	int tempNumArmor;
	if (!readInt(inFile, tempNumArmor))
	{
		inFile.close();
		return;
	}

	string* tempWeaponNames = new string[tempNumWeapons];
	float* tempWeaponValues = new float[tempNumWeapons];
	for (int i = 0; i < tempNumWeapons; i++)
	{
		string tempString;
		float tempFloat;
		if (!readString(inFile, tempString) || !readFloat(inFile, tempFloat))
		{
			inFile.close();
			return;
		}
		tempWeaponNames[i] = tempString;
		tempWeaponValues[i] = tempFloat;
	}

	string* tempArmorNames = new string[tempNumArmor];
	float* tempArmorValues = new float[tempNumArmor];
	for (int i = 0; i < tempNumArmor; i++)
	{
		string tempString;
		float tempFloat;
		if (!readString(inFile, tempString) || !readFloat(inFile, tempFloat))
		{
			inFile.close();
			return;
		}
		tempArmorNames[i] = tempString;
		tempArmorValues[i] = tempFloat;
	}

	playerName = tempPlayerName;
	maxHealth = tempMaxHealth;
	currentHealth = tempCurrentHealth;
	attackPower = tempAttackPower;
	numWeapons = tempNumWeapons;
	numArmor = tempNumArmor;
	weaponNames = tempWeaponNames;
	weaponValues = tempWeaponValues;
	armorNames = tempArmorNames;
	armorValues = tempArmorValues;

	inFile.close();
}

bool readString(std::ifstream& file, string& str)
{
	char redunCheck = file.get();
	char* arr = new char[BUFF_SIZE] {0};
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		arr[i] = file.get();
	}

	if (redunCheck != getRedundancy(arr))
		return false;
	else
	{
		str = decodeString(arr);
		return true;
	}
}

bool readInt(std::ifstream& file, int& num)
{
	char redunCheck = file.get();
	char* arr = new char[BUFF_SIZE] {0};
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		arr[i] = file.get();
	}

	if (redunCheck != getRedundancy(arr))
		return false;
	else
	{
		num = decodeInt(arr);
		return true;
	}
}

bool readFloat(std::ifstream& file, float& num)
{
	char redunCheck = file.get();
	char* arr = new char[BUFF_SIZE] {0};
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		arr[i] = file.get();
	}

	if (redunCheck != getRedundancy(arr))
		return false;
	else
	{
		num = decodeFloat(arr);
		return true;
	}
}

void writeFile()
{
	std::ofstream outFile;
	outFile.open("outputfile.txt", std::ofstream::trunc);
	writeString(outFile, playerName);

	writeFloat(outFile, maxHealth);
	writeFloat(outFile, currentHealth);
	
	writeFloat(outFile, attackPower);
	writeFloat(outFile, defense);
	
	writeInt(outFile, numWeapons);
	writeInt(outFile, numArmor);

	for (int i = 0; i < numWeapons; i++)
	{
		writeString(outFile, weaponNames[i]);
		writeFloat(outFile, weaponValues[i]);
	}

	for (int i = 0; i < numArmor; i++)
	{
		writeString(outFile, armorNames[i]);
		writeFloat(outFile, armorValues[i]);
	}
	
	outFile.close();
}

void writeInt(std::ofstream& file, int num)
{
	char* arr = encode(num);
	file.put(getRedundancy(arr));
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		file.put(arr[i]);
	}
}

void writeString(std::ofstream& file, string wrd)
{
	char* arr = encode(wrd);
	file.put(getRedundancy(arr));
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		file.put(arr[i]);
	}
}

void writeFloat(std::ofstream& file, float num)
{
	char* arr = encode(num);
	file.put(getRedundancy(arr));
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		file.put(arr[i]);
	}
}

char* encode(int number)
{
	char* word = new char[BUFF_SIZE]{ 0 };
	unsigned int index = 0;
	while (number > 0)
	{
		word[index] = '0' + (number % 10);
		number /= 10;
		index++;
	}
	// todo swizel word
	return swivel(word);
}

char* encode(float number)
{
	char* word = new char[BUFF_SIZE]{ 0 };
	
	int wholePart = (int)number;
	float decPart = number - wholePart;
	unsigned int index = 0;

	while (wholePart > 0)
	{
		word[index] = '0' + (wholePart % 10);
		wholePart /= 10;
		index++;
	}

	word[index] = '.';
	index++;

	while (decPart > 0.000001)
	{
		decPart *= 10;
		word[index] = '0' + (int)decPart;
		decPart = decPart - (int)decPart;
		index++;
	}
	return swivel(word);
}

char* encode(string wrd)
{
	if (wrd.length() <= BUFF_SIZE + 1)
	{
		char* word = new char[BUFF_SIZE]{ 0 };
		for (unsigned int i = 0; i < wrd.length(); i++)
		{
			word[i] = wrd[i];
		}

		for (unsigned int i = 0; i < BUFF_SIZE; i++)
		{
			if (word[i] == '\0')
			{
				word[i] = 0;
			}
		}

		return swivel(word);
	}
	else
	{
		unsigned int size = 0;
		size = (wrd.length() / BUFF_SIZE + 1) * BUFF_SIZE;
		char* returnWord = new char[size];
		for (unsigned int i = 0; i <= wrd.length() / BUFF_SIZE; i++)
		{
			char* encoded = encode(wrd.substr(i * BUFF_SIZE, BUFF_SIZE));
			for (unsigned int j = 0; j < BUFF_SIZE; j++)
			{
				returnWord[i*BUFF_SIZE + j] = encoded[j];
			}
		}
		return returnWord;
	}
}

// Gotta pass an array of buff size
char* swivel(char arr[])
{
	// swivel individual characters
	for (unsigned int i = 0; i < BUFF_SIZE / 4; i++)
	{
		char tempChar = arr[4*i];
		arr[4 * i] = arr[4 * i + 2]; // first = third
		arr[4 * i + 2] = arr[4 * i + 3]; // third = fourth
		arr[4 * i + 3] = arr[4 * i + 1]; // fourth = second
		arr[4 * i + 1] = tempChar; // second = first
	}
	
	// swivel groups of 4
	for (unsigned int i = 0; i < BUFF_SIZE / 16; i++)
	{
		char* tempCharArr = new char[4] { arr[16 * i], arr[16 * i + 1], arr[16 * i + 2], arr[16 * i + 3] };

		// first 4 = third 4
		arr[16 * i] = arr[16 * i + 8];
		arr[16 * i + 1] = arr[16 * i + 9];
		arr[16 * i + 2] = arr[16 * i + 10];
		arr[16 * i + 3] = arr[16 * i + 11];

		// third 4 = fourth 4
		arr[16 * i + 8] = arr[16 * i + 12];
		arr[16 * i + 9] = arr[16 * i + 13];
		arr[16 * i + 10] = arr[16 * i + 14];
		arr[16 * i + 11] = arr[16 * i + 15];

		// fourth 4 = second 4
		arr[16 * i + 12] = arr[16 * i + 4];
		arr[16 * i + 13] = arr[16 * i + 5];
		arr[16 * i + 14] = arr[16 * i + 6];
		arr[16 * i + 15] = arr[16 * i + 7];

		//second 4 = first 4
		arr[16 * i + 4] = tempCharArr[0];
		arr[16 * i + 5] = tempCharArr[1];
		arr[16 * i + 6] = tempCharArr[2];
		arr[16 * i + 7] = tempCharArr[3];
	}

	return arr;
}

char* unswivel(char wrd[])
{
	char* arr = new char[BUFF_SIZE] { 0 };
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		arr[i] = wrd[i];
	}

	// unswivel individual characters
	for (unsigned int i = 0; i < BUFF_SIZE / 4; i++)
	{
		char tempChar = arr[4 * i]; // first
		arr[4 * i] = arr[4 * i + 1]; // first = second
		arr[4 * i + 1] = arr[4 * i + 3]; //second = fourth
		arr[4 * i + 3] = arr[4 * i + 2]; // fourth = third
		arr[4 * i + 2] = tempChar; // third = first
	}

	// unswivel groups of 4
	
	for (unsigned int i = 0; i < BUFF_SIZE / 16; i++)
	{
		char* tempCharArr = new char[4]{ arr[16 * i], arr[16 * i + 1], arr[16 * i + 2], arr[16 * i + 3] };

		// first 4 = second 4
		arr[16 * i] = arr[16 * i + 4];
		arr[16 * i + 1] = arr[16 * i + 5];
		arr[16 * i + 2] = arr[16 * i + 6];
		arr[16 * i + 3] = arr[16 * i + 7];

		// second 4 = fourth 4
		arr[16 * i + 4] = arr[16 * i + 12];
		arr[16 * i + 5] = arr[16 * i + 13];
		arr[16 * i + 6] = arr[16 * i + 14];
		arr[16 * i + 7] = arr[16 * i + 15];

		// fourth 4 = third 4
		arr[16 * i + 12] = arr[16 * i + 8];
		arr[16 * i + 13] = arr[16 * i + 9];
		arr[16 * i + 14] = arr[16 * i + 10];
		arr[16 * i + 15] = arr[16 * i + 11];

		//third 4 = first 4
		arr[16 * i + 8] = tempCharArr[0];
		arr[16 * i + 9] = tempCharArr[1];
		arr[16 * i + 10] = tempCharArr[2];
		arr[16 * i + 11] = tempCharArr[3];
	}

	return arr;
}

// decodes a 64 char array into a string
string decodeString(char encoded[])
{
	char* word = new char[BUFF_SIZE] {0};

	word = unswivel(encoded);
	string str = string(word);
	str.shrink_to_fit();
	return str;
}

// decodes a 64 char array into an int
int decodeInt(char encoded[])
{
	char* word = new char[BUFF_SIZE] {0};

	word = unswivel(encoded);
	int num = 0;
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		std::cout << "num: " << num << std::endl;
		int digit = (int)(word[i] - '0');
		if (digit < 0 || digit > 9)
			break;
		num += digit*pow(10, i);
	}
	return num;
}

float decodeFloat(char encoded[])
{
	char* word = new char[BUFF_SIZE] {0};

	word = unswivel(encoded);
	bool whole = true;
	float num = 0;

	for (int i = 0, dec = -1; i < BUFF_SIZE; i++)
	{
		if (whole)
		{
			if (word[i] == '.')
			{
				whole = false;
				continue;
			}

			int digit = (int)(word[i] - '0');
			if (digit < 0 || digit > 9)
				break;
			num += digit * pow(10, i);
		}
		else
		{
			int digit = (int)(word[i] - '0');
			if (digit < 0 || digit > 9)
				break;
			num += digit * pow(10, dec);
			dec--;
		}		
	}

	return num;
}

void calculateAttack()
{
	attackPower = 0;
	for (int i = 0; i < numWeapons; i++)
	{
		attackPower += weaponValues[i];
	}
}

void calculateDefense()
{
	defense = 0;
	for (int i = 0; i < numArmor; i++)
	{
		defense += armorValues[i];
	}

	defense /= ((float)numArmor * 10); // armor values should be between 1 and 10, average out and make a percentage
	defense = 1 - defense; // swap high and low
}

void addWeaponOrArmor()
{
	int num = rand();
	if (num < RAND_MAX / 2) // add armor
	{
		numArmor++;
		string* names = new string[numArmor];
		float* values = new float[numArmor];
		for (int i = 0; i < numArmor - 1; i++)
		{
			names[i] = armorNames[i];
			values[i] = armorValues[i];
		}

		num = rand() % 6;
		names[numArmor - 1] = armors[num];
		values[numArmor - 1] = ((float)rand() / (float)RAND_MAX) * 9.0f + 1.0f;

		armorNames = names;
		armorValues = values;
		calculateDefense();
	}
	else // add weapon
	{
		numWeapons++;
		string* names = new string[numWeapons];
		float* values = new float[numWeapons];
		for (int i = 0; i < numWeapons - 1; i++)
		{
			names[i] = weaponNames[i];
			values[i] = weaponValues[i];
		}

		num = rand() % 8;
		names[numWeapons - 1] = weapons[num];
		values[numWeapons - 1] = ((float)rand() / (float)RAND_MAX) * 9.0f + 1.0f;

		weaponNames = names;
		weaponValues = values;
		calculateAttack();
	}
}

void removeWeaponOrArmor()
{
	int num = rand();
	if (num < RAND_MAX / 2) // remove armor
	{
		numArmor--;
		string* names = new string[numArmor];
		float* values = new float[numArmor];
		for (int i = 0; i < numArmor; i++)
		{
			names[i] = armorNames[i];
			values[i] = armorValues[i];
		}

		armorNames = names;
		armorValues = values;
		calculateDefense();
	}
	else // remove weapon
	{
		numWeapons--;
		string* names = new string[numWeapons];
		float* values = new float[numWeapons];
		for (int i = 0; i < numWeapons; i++)
		{
			names[i] = weaponNames[i];
			values[i] = weaponValues[i];
		}

		weaponNames = names;
		weaponValues = values;
		calculateAttack();
	}
}

void recieveInput()
{
	string input;

	std::cout << "Change player name, " << playerName << "? (y/n)" << std::endl;
	std::cin >> input;
	if (input == "y" || input == "yes" || input == "Y" || input == "Yes")
	{
		std::cout << "Please enter a new name: " << std::endl;
		std::cin >> playerName;
	}

	bool fight = true;
	srand((unsigned int)time(0));

	while (fight)
	{
		std::cout << "A new enemy approaches!" << std::endl;
		float enemyHealth = ((float)rand() / (float)RAND_MAX) * (attackPower * 3) + 1.0f;
		float enemyAttack = ((float)rand() / (float)RAND_MAX) * (maxHealth / 2) + 1.0f;
		bool alive = true;
		while (alive)
		{
			std::cout << "The enemy has health of: " << enemyHealth << " and a power of: " << enemyAttack << std::endl;
			std::cout << "You have a health of: " << currentHealth << " and a power of: " << attackPower << std::endl;
			std::cout << "Do you... (attack/defend/run/quit)?" << std::endl;
			std::cin >> input;

			if (input == "attack")
			{
				std::cout << "You attack!" << std::endl;
				enemyHealth -= attackPower;
				if (enemyHealth <= 0)
				{
					std::cout << "Enemy died!" << std::endl;
					// add random weapon or armor
					addWeaponOrArmor();

					alive = false;
					continue;
				}

				currentHealth -= enemyAttack * defense; // multiply by defense
				if (currentHealth <= 0)
				{
					std::cout << "You died..." << std::endl;
					// remove most recent weapon or armor
					removeWeaponOrArmor();

					alive = false;
					currentHealth = maxHealth;
					continue;
				}
			}
			else if (input == "defend")
			{
				continue;
			}
			else if (input == "run")
			{
				alive = false;
				continue;
			}
			else if (input == "quit")
			{
				fight = false;
				alive = false;
			}
		}
	}
}

char getRedundancy(char arr[])
{
	char value = 0;
	for (int i = 0; i < BUFF_SIZE; i++)
	{
		value += arr[i];
	}

	return value % 29;
}

void printPlayerInfo()
{
	std::cout << "Player Info" << std::endl;
	std::cout << "Max health: " << maxHealth << std::endl;
	std::cout << "Current health: " << currentHealth << std::endl;
	std::cout << "Attack power: " << attackPower << std::endl;
	std::cout << "Weapons" << std::endl;
	for (int i = 0; i < numWeapons; i++)
	{
		std::cout << weaponNames[i] << " " << weaponValues[i] << std::endl;
	}
	std::cout << "Armor" << std::endl;
	for (int i = 0; i < numArmor; i++)
	{
		std::cout << armorNames[i] << " " << armorValues[i] << std::endl;
	}
}
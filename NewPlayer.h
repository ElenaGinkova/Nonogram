#pragma once
#include <iostream>
#include <fstream>
#include "StrFunctions.h"

void newPlayer(char* playersName)
{
	const int FILENAME = 100;
	std::ofstream outFile;
	outFile.open("Names.txt", std::ios_base::app);
	outFile << playersName << " 1\n";
	std::cout << "Player " << playersName << " was added successfully!\n";
	outFile.close();
	
	char fileName[FILENAME]{};
	char txt[] = ".txt\0";
	myStrcat(fileName, playersName);
	myStrcat(fileName, txt);

	std::ofstream player(fileName);//creating a file to store information, but no information for now because there hasnt been saved game
	player.close();
}

#pragma once
#include <iostream>
#include <fstream>
void newPlayer(char* playersName)
{
	std::ofstream outFile;
	outFile.open("Names.txt", std::ios_base::app);
	outFile << playersName << " 1\n";
	std::cout << "Player " << playersName << " was added successfully!\n";
	outFile.close();
}

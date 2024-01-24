/**
*
* Solution to course project #9
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Elena Ginkova
* @idnumber 1MI0600289* @compiler VC
*
* <file with helper functions>
*
*/

#include <iostream>
#include <fstream>
#include <random>
#include "Found.h"
#include "NewPlayer.h"
#include "StrFunctions.h"

const int EMPTY = -1;
const int FILLED = 1;
const int QUIT = -1;
const int HINTSCOUNT = 2;
const unsigned LEVELS = 5;
const size_t CELLS = 6;
const size_t MAXSIZELEVEL = 11;
const int MAXINPUT = 300;

void start(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL],  int size);
void create(char* name, int matrix[][MAXSIZELEVEL], int size, int toOpen);
void play(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL], int size, int lives, int levelVersion);
int searchForPlayerLevel(char* playersName)//returns the level of the player
{
	char name[MAXINPUT];
	int level = 0;
	std::ifstream inputFile;
	inputFile.open("Names.txt");
	if (inputFile.is_open())
	{
		while (inputFile >> name)
		{
			if (found(playersName, name))
			{
				inputFile >> level;
				inputFile.close();
				return level;
			}
		}
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	inputFile.close();
	return 0;
	
}
int readProgress(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL], int size)//returns the remaining lives
{
	int levelVersion = 1;
	int lives = 1;
	char filename[MAXINPUT]{};
	std::ifstream inFile;
	inFile.open(name);

	
	if (inFile.is_open())
	{
		inFile >> levelVersion;
		inFile >> lives;

		for (int i = 0; i < MAXSIZELEVEL; i++)
		{
			for (int j = 0; j < MAXSIZELEVEL; j++)
			{
				inFile >> matrix[i][j];
			}
		}
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	inFile.close();

	create(name, answer, size, levelVersion * 10);//the matrix filled with the right answers
	return lives;
}
void saveProgress(int lives, char* name, int matrix[][MAXSIZELEVEL], int size, int levelVersion)//saves the progress of the last quit
{

	std::ofstream outFile;
	outFile.open(name);

	outFile << levelVersion << " " << lives << std::endl;
	for (int i = 0; i < MAXSIZELEVEL; i++)
	{
		for (int j = 0; j < MAXSIZELEVEL - 1; j++)
		{
			outFile << matrix[i][j] << " ";
		}
		outFile << matrix[i][MAXSIZELEVEL - 1] << std::endl;
	}
	
	outFile.close();
}
void print(int matrix[][MAXSIZELEVEL],  int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == EMPTY || matrix[i][j] == -2)
			{
				std::cout << " ";
			}
			else
			{
				std::cout << matrix[i][j];
			}
			if (j == 1 && i > 1)
			{
				std::cout << '|';
			}
			else
			{
				std::cout<< ' ';
			}
		}
		if (i == 1)
		{
			switch (size)
			{
			case 7:std::cout << "\n---------------"; break;//lv1
			case 8:std::cout << "\n-----------------"; break;//lv2
			case 9:std::cout << "\n-------------------"; break;//lv3
			case 10:std::cout << "\n---------------------"; break;//lv4
			case 11:std::cout << "\n-----------------------"; break;//lv5
			}
			
		}
		std::cout << "\n";
	}
}
void create(char* name, int matrix[][MAXSIZELEVEL],  int size, int toOpen)//creating matrixes for each level when level is entered
{
	std::ifstream inputFile;

		switch (toOpen)
		{
		//level 1
		 case 10://version 1
			 inputFile.open("TemplateLv1.1.txt"); break;
		 case 100://version 1 answers
			 inputFile.open("AnswerLv1.1.txt"); break;

		 case 11://version 2
			 inputFile.open("TemplateLv1.2.txt"); break;
		 case 110://version 2 answers
			 inputFile.open("AnswerLv1.2.txt"); break;

		//level 2
		 case 20://version 1
			 inputFile.open("TemplateLv2.1.txt"); break;
		 case 200://version 1 answers
			 inputFile.open("AnswerLv2.1.txt"); break;

		 case 21://version 2
			 inputFile.open("TemplateLv2.2.txt"); break;
		 case 210://version 2 answers
			 inputFile.open("AnswerLv2.2.txt"); break;

		//level 3	
		 case 30://version 1
			 inputFile.open("TemplateLv3.1.txt"); break;
		 case 300://version 1 answers
			 inputFile.open("AnswerLv3.1.txt"); break;

		 case 31://version 2
			 inputFile.open("TemplateLv3.2.txt"); break;
		 case 310://version 2 answers
			 inputFile.open("AnswerLv3.2.txt"); break;

		//level 4
		 case 40://version 1
			 inputFile.open("TemplateLv4.1.txt"); break;
		 case 400://version 1 answers
			 inputFile.open("AnswerLv4.1.txt"); break;

		 case 41://version 2
			 inputFile.open("TemplateLv4.2.txt"); break;
		 case 410://version 2 answers
			 inputFile.open("AnswerLv4.2.txt"); break;

		//level 5
		 case 50://version 1
			 inputFile.open("TemplateLv5.1.txt"); break;
		 case 500://version 1 answers
			 inputFile.open("AnswerLv5.1.txt"); break;

		 case 51://version 2
			 inputFile.open("TemplateLv5.2.txt"); break;
		 case 510://version 2 answers
			 inputFile.open("AnswerLv5.2.txt"); break;
	    }

	if (inputFile.is_open())
	{
		int num = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				inputFile >> matrix[i][j];
			}
		}
		for (int i = 0; i < MAXSIZELEVEL; i++)
		{
			for (int j = size; j < MAXSIZELEVEL; j++)
			{
				if(matrix[i][j] == 0)
				matrix[i][j] = EMPTY;
			}
		}
		for (int i = size; i < MAXSIZELEVEL; i++)
		{
			for (int j = 0; j < MAXSIZELEVEL; j++)
			{
				if (matrix[i][j] == 0)
					matrix[i][j] = EMPTY;
			}
		}
		
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	
	inputFile.close();
}
bool isValidIndex(const int i, const int j,  int size)
{
	return (i > 1 && j > 1 && i < size && j < size);
}
bool isFilled(int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL],  int size)//if the cell has already been assigned with a value
{
	for (int i = 0; i < size - HINTSCOUNT; i++)
	{
		for (int j = 0; j < size - HINTSCOUNT; j++)
		{
			if (matrix[i + HINTSCOUNT][j + HINTSCOUNT] != answer[i + HINTSCOUNT][j + HINTSCOUNT])
				return false;
		}
	}
	return true;
}
bool isValidLevel(int a)//there are only 5 levels
{
	return (a > 0 && a < LEVELS + 1);
}
void checkForFullRow(int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL],  int size, int rowIndx)//if all filleed cells have been found then filling the empty ones in this row
{
	bool filledRow = true;
	for (int j = 0; j < size - HINTSCOUNT; j++)
	{
		if (answer[rowIndx][j + HINTSCOUNT] == FILLED && matrix[rowIndx][j + HINTSCOUNT] != FILLED)
		{
			filledRow = false;
			break;
		}
	}

	if (filledRow == true)
	{
		for (int j = 0; j < size - HINTSCOUNT; j++)
		{
			if (matrix[rowIndx][j + HINTSCOUNT] == EMPTY)
			{
				matrix[rowIndx][j + HINTSCOUNT] = 0;
			}
		}
	}
}
void checkForFullColumn(int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL],  int size, int colIndx)//if all filleed cells have been found then filling the empty ones in this column
{
	bool filledCol = true;
	for (int i = 0; i < size - HINTSCOUNT; i++)
	{
		if (answer[i + HINTSCOUNT][colIndx] == FILLED && matrix[i + HINTSCOUNT][colIndx] != FILLED)
		{
			filledCol = false;
			break;
		}
	}

	if (filledCol == true)
	{
		for (int i = 0; i < size - HINTSCOUNT; i++)
		{
			if (matrix[i + HINTSCOUNT][colIndx] == EMPTY)
			{
				matrix[i + HINTSCOUNT][colIndx] = 0;
			}
		}
	}
}

int playAgain(char answer)
{
	if (answer == 'Y' || answer == 'y') return 1;
	else if (answer == 'N' || answer == 'n') return 0;
	else return -1;
}
void finishedLevel(char* namePlayer)// when a player completes successfully a level the function increases his level to the next one
{
	const int FILESIZE = 600;
	std::ifstream inputFile;
	std::ofstream outputFile;

	inputFile.open("Names.txt");
	
	char name[MAXINPUT];
	char file[FILESIZE]{};
	char level[4];

	if (inputFile.is_open())
	{
		while (inputFile >> name)
		{
			myStrcat(file, name);
			level[0] = ' ';
			inputFile >> level[1];

			if (found(namePlayer, name))
			{
				level[1]++;
			}
			level[2] = '\n';
			level[3] = '\0';
			myStrcat(file, level);
		}
		inputFile.close();
		outputFile.open("Names.txt");
		outputFile << file;
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	outputFile.close();
}

void quit(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL], int size, int lives, int levelVersion)
{
	char choice[MAXINPUT];
	std::cout << "Do you really want to exit the level? [Y/N]\n";
	std::cin >> choice;
	if ((!myStrcmp(choice, "Y")) || (!myStrcmp(choice, "y")))
	{

		saveProgress(lives, name, matrix, size, levelVersion);
		std::cout << "Level exited\n";
		std::cin.ignore(MAXINPUT, '\n');
		start(name, matrix, answer, size);
	}
	else if ((!myStrcmp(choice, "N")) || (!myStrcmp(choice, "n")))
	{
		std::cout << "Continue playing\n";
		std::cin.ignore(MAXINPUT, '\n');
		play(name, matrix, answer, size, lives, levelVersion);
	}
	else
	{
		std::cout << "Incorrect input";
		std::cin.ignore(MAXINPUT, '\n');
		quit(name, matrix, answer, size, lives, levelVersion);
	}
}
void play(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL],  int size, int lives, int levelVersion)//the function is used while gameplay in a certain level 
{
	
	if (lives <= 0)//lost all lives
	{
		char choice;
		std::cout << "No more lives! Do you want to play more? Y/N\n";
		std::cin >> choice;

		switch (playAgain(choice))
		{
		case 1:start(name, matrix, answer, size); break;
		case 0:std::cout << "You chose to end the game!"; return; break;
		case -1:std::cout << "Incorrect input!"; play(name, matrix, answer, size, lives, levelVersion); break;
		}

	}

	if (isFilled(matrix, answer, size))//filled the whole nonogram
	{
		std::cout << "Done! Congratulations you completed the level\n";
		char choice;
		int reachedLevel = searchForPlayerLevel(name) + 1;

		if (reachedLevel != LEVELS + 1)//there are only 5 levels checking if the player have went trough all of them and if not then increasinf the level
		{
			finishedLevel(name);
		}
		
		print(matrix, size);
		std::cout << "Do you want to play more? Y/N\n";
		std::cin >> choice;

		switch (playAgain(choice))
		{
		case 1: start(name, matrix, answer, size); break;
		case 0: std::cout << "You chose to end the game!"; return; break;
		case -1: std::cout << "Incorrect input!"; play(name, matrix, answer, size, lives, levelVersion); break;
		}
		
		print(matrix, size);
		start(name, matrix, answer, size);
		std::cout << std::endl;
		return;
	}
	//the coordinates of the cell the player want to fill in
	int i = 0;
	int j = 0;

	print(matrix, size);
	std::cin >> i;

	if (i == QUIT)//player decides to quit the level
	{
		quit(name, matrix, answer, size, lives, levelVersion);
	}
		
	std::cin >> j;

	if (j == QUIT)
	{
		quit(name, matrix, answer, size, lives, levelVersion);
	}

	if (!isValidIndex(i + HINTSCOUNT, j + HINTSCOUNT, size))
	{
		std::cout << "Invalid Input! Try again: \n";
	}
	else if (matrix[i + HINTSCOUNT][j + HINTSCOUNT] != EMPTY)
	{
		std::cout << "Cell is already filled! Try again: \n";
	}
	else 
	{
		
		if (answer[i + HINTSCOUNT][j + HINTSCOUNT] == FILLED)
		{
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = FILLED;
			std::cout << "Correct guess! Cell filled!\n";

			checkForFullRow(matrix, answer, size, i + HINTSCOUNT);
			checkForFullColumn(matrix, answer, size, j + HINTSCOUNT);
		}
		else
		{
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = 0; 
			std::cout << "Incorrect! The cell is empty. Lives left: " << --lives << std::endl;
		}
	}

	play(name, matrix, answer, size, lives, levelVersion);
}

bool emptyFile(char* name)//if the player hasnt saved any game yet
{
	std::ifstream inFile;
	inFile.open(name);
	int num = 0;
	if (inFile.is_open())
	{
		inFile >> num;
	}
	inFile.close();
	return (num == 0);
}
void start(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL], int size)//the function is used every time the player wants to start a level
{
	int level = 1;
	char lv;
	int lives = 3;
	int maxLevel = searchForPlayerLevel(name);
	char choice = 'n';

	if (!emptyFile(name))
	{
		std::cout << "Do you want to continue[C] your last saved level or start a new one[N]? \n[C/N]\n";
		std::cin >> choice;
	}
		
	

	if (choice == 'C' || choice == 'c')
	{
		 lives  = readProgress(name, matrix, answer, size);
	}
	else if (choice == 'N' || choice == 'n')
	{
		std::cout << "Which level?\n";

		
		std::cin >> level;

		if (!isValidLevel(level))
		{
			std::cout << "There is no such level!\n";
			std::cin.ignore(MAXINPUT, '\n');
			start(name, matrix, answer, size);
		}
		else if (level > maxLevel)
		{
			std::cout << "Your level: " << maxLevel << "\nTrying to reach level: " << level << "\nYou cant reach that level!\n";
			start(name, matrix, answer, size);
		}

		size = CELLS + level;

		srand(time(nullptr));//changing the seed if rand with time to get different numbers
		int version = rand() % 2;//gennerating 0 or 1

		level = level * 10 + version;

		create(name, matrix, size, level);//the matrix that the player is going to use
		create(name, answer, size, level * 10);//the matrix filled with the right answers
	}
	else
	{
		std::cin.clear();
		std::cin.ignore(MAXINPUT, '\n');
		std::cout << "Incorrect input!\n";
		start(name, matrix, answer, size);
	}
	
	play(name, matrix, answer, size, lives, level);
}

int main()
{
	
	char playersName[MAXINPUT] = "";
	int matrix[MAXSIZELEVEL][MAXSIZELEVEL] = {};
	int answer[MAXSIZELEVEL][MAXSIZELEVEL] = {};

	std::cout << "Welcome to Nonogram!\nIf you would like to exit a level please type -1\nEnter the name of a player: ";
	std::cin >> playersName;
	int level = 1;
	
	if (level = searchForPlayerLevel(playersName))//if the function returns a level then the int variable will take the the value and the if will be performed
	{
		std::cout << "Player " << playersName << " was found!\n" << "Your level is " << level << ":\n";
	}
	else
	{
		newPlayer(playersName);
	}

	start(playersName, matrix, answer, MAXSIZELEVEL);
	return 0;
}

#include <iostream>
#include <fstream>

const size_t LEVELFIRST = 7;
const int HINTSCOUNT = 2;
const int EMPTY = -1;
const int FILLED = 1;
void start(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size);
bool found(const char* playersName, const char* name)
{
	while (*name != '\0' && *playersName != '\0')
	{
		if (*name != *playersName)
		{
			return false;
		}
		name++;
		playersName++;
	}
	return (*playersName == '\0' && *name == '\0');
}
int searchForPlayer(char* playersName)
{
	char name[256];
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
void newPlayer(char* playersName)
{
	std::ofstream outFile;
	outFile.open("Names.txt", std::ios_base::app);
	outFile << playersName << " 1\n";
	std::cout << "Player " << playersName << " was added successfully!\n";
	outFile.close();
}
void print(int matrix[][LEVELFIRST], const int size)//napravi da e s size of lv 5//tuk e specialno za lv1
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
			if (j == 1 && i > 1)//za vs lvl razl
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
			std::cout << "\n---------------------";//da se opravi za vs level
		}
		std::cout << "\n";
	}
}
unsigned myStrlen(char* str)
{
	if (!str)
		return 0;

	unsigned result = 0;
	while (*str)
	{
		result++;
		str++;
	}
	return result;
}
void myStrcpy(char* source, char* dest)
{
	if (!source || !dest)
		return;
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}
void myStrcat(char* first, char* second)
{
	if (!first || !second)
		return;

	size_t firstLen = myStrlen(first);
	first += firstLen;
	myStrcpy(second, first);
}
void create(int matrix[][LEVELFIRST], const int size, int toOpen)//napravi da e s size of lv 5
{
	std::ifstream inputFile;
	switch (toOpen)//switch za levela
	{
	 case 1:
		 inputFile.open("Template.txt"); break;
	 case 10:
		 inputFile.open("Answer.txt"); break;
	}
	
	
	if (inputFile.is_open())
	{
		int num = 0;
		for (int i = 0; i < size; i++)//spcialno za lv1 e
		{
			for (int j = 0; j < size; j++)
			{
				inputFile >> matrix[i][j];
			}
		}
	}
	else
	{
		std::cout << "Coudn't open the file.\n";
	}
	
	inputFile.close();
}
bool isValidIndex(const int i, const int j, const int size)
{
	return (i > 0 && j > 0 && i < size && j < size);
}
bool isFilled(int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size)
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
bool isValidNum(char a)
{
	return (a > '0' && a < '9');
}
void checkForFullRow(int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size, int rowIndx)
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
				print(matrix, size);
			}
		}
	}
}
void checkForFullColumn(int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size, int colIndx)
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
void getInput(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size, int& lives);
int playAgain(char answer)
{
	if (answer == 'Y' || answer == 'y') return 1;
	else if (answer == 'N' || answer == 'n') return 0;
	else return -1;
}
void finishedLevel(char* namePlayer)
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
int myStrcmp(const char* first, const char* second)
{
	if (!first || !second)
		return 0; 
	while ((*first) && (*second) && ((*first) == (*second))) 
	{
		first++;
		second++;
	}

	return (*first - *second);

}
void quit(char* name, int matrix[][MAXSIZELEVEL], int answer[][MAXSIZELEVEL], int size, int lives)
{
	char answ[MAXINPUT];
	std::cout << "Do you really want to exit the level? [Y/N]\n";
	std::cin >> answ;
	if ((!myStrcmp(answ, "Y")) || (!myStrcmp(answ, "y")))
	{
		std::cout << "Level exited\n";
		std::cin.ignore(MAXINPUT, '\n');
		start(name, matrix, answer, size);
	}
	else if ((!myStrcmp(answ, "N")) || (!myStrcmp(answ, "n")))
	{
		std::cout << "Continue playing\n";
		std::cin.ignore(MAXINPUT, '\n');
		getInput(name, matrix, answer, size, lives);
	}
	else
	{
		std::cout << "Incorrect input";
		std::cin.ignore(MAXINPUT, '\n');
		quit(name, matrix, answer, size, lives);
	}
}

void getInput(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size, int& lives)//size->rows,cols ako ne e kvadratna
{
	
	if (lives <= 0)//lost all lives
	{
		char answ;
		std::cout << "No more lives! Do you want to play more? Y/N\n";
		std::cin >> answ;

		switch (playAgain(answ))
		{
		case 1:start(name, matrix, answer, size); break;
		case 0:std::cout << "You chose to end the game!"; return; break;
		case -1:std::cout << "Incorrect input!"; getInput(name, matrix, answer, size, lives); break;
		}

	}

	if (isFilled(matrix, answer, size))//filled the whole nonogram
	{
		std::cout << "Done! Congratulations you completed the level\n";
		char answ;
		std::cout << "No more lives! Do you want to play more? Y/N\n";
		std::cin >> answ;

		switch (playAgain(answ))
		{
		case 1:start(name, matrix, answer, size); break;
		case 0:std::cout << "You chose to end the game!"; return; break;
		case -1:std::cout << "Incorrect input!"; getInput(name, matrix, answer, size, lives); break;
		}
		
		print(matrix, size);
		start(name, matrix, answer, size);
		std::cout << std::endl;
		return;
	}

	
	int i = 0;
	int j = 0;

	print(matrix, size);
	std::cin >> i >> j;

	//validation!!!!

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
		//matrix[i + HINTSCOUNT][j + HINTSCOUNT] = num;
		if (answer[i + HINTSCOUNT][j + HINTSCOUNT] == FILLED)
		{
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = FILLED;//const
			std::cout << "Correct guess! Cell filled!\n";

			checkForFullRow(matrix, answer, size, i + HINTSCOUNT);
			checkForFullColumn(matrix, answer, size, j + HINTSCOUNT);
		}
		else
		{
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = 0; // const
			std::cout << "Incorrect! The cell is empty. Lives left: " << --lives << std::endl;
		}
	}

	getInput(name, matrix, answer, size, lives);
}
int playerlives(char* playersname)
{
	char buff[MAXINPUT];
	int lives = 0;
	std::ifstream inputfile;
	inputfile.open("Names.txt");
	if (inputfile.is_open())
	{
		while (inputfile >> buff)
		{
			if (found(playersname, buff))
			{
				inputfile >> buff;
				inputfile >> lives;
				inputfile.close();
				return lives;
			}
		}
	}
	else
	{
		std::cout << "coudn't open the file.\n";
	}
	inputfile.close();
	return 0;
}
int playerLevelContinue(char* playersName)
{
	char buff[MAXINPUT];
	int level = 0;
	std::ifstream inputFile;
	inputFile.open("Names.txt");
	if (inputFile.is_open())
	{
		while (inputFile >> buff)
		{
			if (found(playersName, buff))
			{
				inputFile >> buff;
				inputFile >> buff;
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


void start(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size)
{
	int lives = 3;
	std::cout << "Which level?\n";
	char input;
	int level = 1;
	int maxLevel = searchForPlayer(name);
	std::cin >> input;//validaciq na vhoda pomisli samo da e vutre
	level = input - '0';

	if (!isValidNum(input))
	{
		std::cout << "Incorrect input!\n";
		start(name, matrix, answer, size);
	}

	else if (level > maxLevel)
	{
		std::cout << "You cant reach that level!\n";
		start(name, matrix, answer, size);
	}

	create(matrix, size, level);
	create(answer, size, level * 10);

	getInput(name, matrix, answer, LEVELFIRST, lives);
}

int main()
{
	const size_t SIZE = 256;
	char playersName[SIZE] = "";

	int matrix[LEVELFIRST][LEVELFIRST] = {};//za 1 lv//trqbva da se suobrazi razmera s levela
	int answer[LEVELFIRST][LEVELFIRST] = {};//za 1 lv//trqbva da se suobrazi razmera s levela

	std::cout << "Welcome to Nonogram!\n" << "Enter the name of the player: ";
	std::cin >> playersName;

	char name[SIZE];
	int level = 1;

	
	if (level = searchForPlayer(playersName))//izbirane na lv
	{
		std::cout << "Player " << playersName << " was found!\n" << "Your level is " << level << ":\n";
	}
	else
	{
		newPlayer(playersName);
	}

	start(playersName, matrix, answer, LEVELFIRST);//napravi da stava i za drgite niva//nz za size
}

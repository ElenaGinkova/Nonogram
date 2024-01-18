#include <iostream>
#include <fstream>

const size_t LEVELFIRST = 7;
const int HINTSCOUNT = 2;
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
			if (matrix[i][j] == -1)
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
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] != answer[i][j])
				return false;
		}
	}
	return true;
}
bool isValidNum(char a)
{
	return (a > '0' && a < '9');
}
void getInput(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size, int& lives)//size->rows,cols ako ne e kvadratna
{
	
	if (lives <= 0)//krai
	{
		char answ;
		std::cout << "No more lives! Do you want to play more? Y/N\n";
		std::cin >> answ;
		if (answ == 'Y' || answ == 'y')
		{
			start(name, matrix, answer, size);
		}
		else if (answ == 'N' || answ == 'n')
		{
			return;
		}
		else
		{
			std::cout << "Incorrect input!";
			getInput(name, matrix, answer, size, lives);
		}

	}
	if (isFilled(matrix, answer, size))//kato trqbva da se dobavi zapulvaneto avtomatichno s nuli
	{
		std::cout << "Done! Congratulations you completed the level\n";//i kakvo stava
		return;
	}

	/*char inputI = 0;
	char inputJ = 0;*/
	int i = 0;
	int j = 0;
	print(matrix, size);
	std::cin >> i >> j;
	//validation!!!!
	/*if (!isValidNum(inputI) || !isValidNum(inputJ))
	{
		i = inputI - '0';
		j = inputJ - '0';
	}*/

	if (!isValidIndex(i + HINTSCOUNT, j + HINTSCOUNT, size))
	{
		std::cout << "Invalid Input! Try again: \n";
	}
	else if (matrix[i + HINTSCOUNT][j + HINTSCOUNT] != -1)//hintsCount opravi
	{
		std::cout << "Cell is already filled! Try again: \n";
	}
	else
	{
		//matrix[i + HINTSCOUNT][j + HINTSCOUNT] = num;
		if (answer[i + HINTSCOUNT][j + HINTSCOUNT] == 1)
		{            //ako e zapulnen reda
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = 1;//const
			std::cout << "Correct guess! Cell filled!\n";
		}
		else
		{
			matrix[i + HINTSCOUNT][j + HINTSCOUNT] = 0; // const
			std::cout << "Incorrect! The cell is empty. Lives left: " << --lives << std::endl;
		}
	}
	getInput(name, matrix, answer, size, lives);

}


void start(char* name, int matrix[][LEVELFIRST], int answer[][LEVELFIRST], const int size)
{
	int lives = 3;
	std::cout << "Which level?\n";
	char input;
	int level = 1;
	int maxLevel = searchForPlayer(name);
	std::cin >> input;//validaciq na vhoda pomisli 
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

/**
*
* Solution to course project # 1
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Desislava Lyubomirova
* @idnumber 7MI0600144 @compiler VC
*
* Main source file
*
*/

#include <iostream>
#include <fstream>>
#include <string>
#include <cstring>
#include <cmath>
#pragma warning( disable : 4996)

using namespace std;

const unsigned int MAX_MISTAKES = 3;
const char symbol_emty_cell = '-';
const char symbol_full_cell = '*';
const char MIN_LEVEL = 1;
const char MAX_LEVEL = 5;
const unsigned int MAX_COUNT_OF_NUMBERS = 50;

void createAccount(string username, string password)
{
	std::ofstream out(username + ".txt");
	out << password << endl;
	out.close();
}

int existingAccounts(string username, string password)
{
	std::ifstream in;
	in.open((username + ".txt"));
	string players_passoword;
	getline(in, players_passoword);
	if (!in.is_open() || players_passoword != password) {
		return 0;
	}
	cout << "You entered succesfully in your account! ";
	return 1;
}

char** createMatrix(int n)
{
	char** matrix;
	matrix = new char* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new char[n];
	return matrix;
}

void freeMatrix(char** matrix, int n)
{
	for (int i = 0; i < n; i++)
		delete[] matrix[i];
	delete[] matrix;
}

unsigned int** createMatrix(int n, int m)
{
	unsigned int** matrix;
	matrix = new unsigned int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new unsigned int[m];
	return matrix;
}

void printSourceCode(unsigned int level, string& matrix, unsigned int size)
{
	ifstream myfile;
	srand(time(NULL));
	int n = rand() % 1 + 0;
	if (level == 1)
	{
		if (n == 0)
			myfile.open("level1_1.txt");
		else
			myfile.open("level1_2.txt");
	}
	else if (level == 2)
	{
		if (n == 0)
			myfile.open("level2_1.txt");
		else
			myfile.open("level2_2.txt");
	}
	else if (level == 3)
	{
		if (n == 0)
			myfile.open("level3_1.txt");
		else
			myfile.open("level3_2.txt");
	}
	else if (level == 4)
	{
		if (n == 0)
			myfile.open("level4_1.txt");
		else
			myfile.open("level4_2.txt");
	}
	else if (level == 5)
	{
		if (n == 0)
			myfile.open("level5_1.txt");
		else
			myfile.open("level5_2.txt");
	}
	if (!myfile.is_open()) {
		cout << "Error";
		return;
	}
	getline(myfile, matrix);
	myfile.close();
}

void print(char** field, unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			cout << "[" << field[i][j] << "] ";
		cout << endl << endl;
	}
}

void printNumbersAboveNonogram(unsigned int** numbers, int maxrows, int columns, int maxcolumns)
{
	for (size_t i = 0; i < maxrows; i++)
	{
		for (size_t i = 0; i < maxcolumns; i++)
		{
			cout << "  ";
		}
		for (size_t j = 0; j < columns; j++)
		{
			if (numbers[i][j] == 0) cout << "    ";
			else
			{
				if(numbers[i][j] > 9) cout << ' ' << numbers[i][j] << " ";
				else if (numbers[i][j]) cout << ' ' << numbers[i][j] << "  ";
			}
				
		}
		cout << endl;
	}
	cout << endl;
}

void printNumbersLeftOfNonogram( unsigned int** numbers, int rows, int maxcolumns)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < maxcolumns; j++)
		{
			if (numbers[i][j] == 0) cout << ' ';
			else
				cout << numbers[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void countNumbersInRows(char** nonogram, unsigned int size, unsigned int**& numbers, int& rows, int& maxcolumns)
{
	int columns = 0;
	unsigned int counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (nonogram[i][j] == '0')
			{
				if (counter != 0)
				{
					numbers[rows][columns] = counter;
					columns++;
					counter = 0;
				}
			}
			if (nonogram[i][j] == '1')
			{
				counter++;
			}
			if (j == size - 1 && counter != 0)
			{
				numbers[rows][columns] = counter;
				columns++;
			}
		}
		if (maxcolumns < columns) maxcolumns = columns;
		rows++;
		columns = 0;
		counter = 0;
	}
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < maxcolumns; j++)
		{
			if (numbers[i][j] < 0 || numbers[i][j] > size)
				numbers[i][j] = 0;
		}
	}
}

void countNumbersInColumns(char** nonogram, unsigned int size, int& maxcolumns, unsigned int**& numbers,int& rows,int& columns,int& maxrows)
{
	unsigned int counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (nonogram[j][i] == '0')
			{
				if (counter != 0)
				{
					numbers[rows][columns] = counter;
					rows++;
					counter = 0;
				}
			}
			if (nonogram[j][i] == '1')
			{
				counter++;
			}
			if (j == size - 1 && counter != 0)
			{
				numbers[rows][columns] = counter;
				rows++;
			}
		}
		if (maxrows < rows) maxrows = rows;
		columns++;
		rows = 0;
		counter = 0;
	}
	for (size_t i = 0; i < maxrows; i++)
	{
		for (size_t j = 0; j < columns; j++)
		{
			if (numbers[i][j] < 0 || numbers[i][j] > size ) 
				numbers[i][j] = 0;
		}
	}
}

void print2(char** field, unsigned int size,  unsigned int** numbersInRows, unsigned int** numbersInColums, int rows, int maxcolumns, int maxrows, int columns)
{
	printNumbersAboveNonogram(numbersInColums, maxrows, columns, maxcolumns);
	for (int i = 0; i < size; i++)
	{
		for (size_t j = 0; j < maxcolumns; j++)
		{
			if (numbersInRows[i][j] == 0) cout << "  ";
			else
			{
				if (numbersInRows[i][j] > 9) cout << numbersInRows[i][j];
				else if (numbersInRows[i][j]) cout << numbersInRows[i][j] << " ";
			}
		}
		for (int j = 0; j < size; j++)
			if ((field[i][j] != '*') && (field[i][j] != '-'))
			{
				cout << "[" << ' ' << "] ";
			}
			else
				cout << "[" << field[i][j] << "] ";
		cout << endl << endl;
	}
}

bool isValid(unsigned int x, unsigned int y, unsigned int size)
{
	return x >= 0 && y >= 0 && x < size&& y < size;
}

bool isValid(char symbol)
{
	return symbol == '-' || symbol == '*';
}

bool isLevelValid(unsigned int level)
{
	return (level >= MIN_LEVEL && level <= MAX_LEVEL);
}

void levelInput(unsigned int& level)
{
	cout << "Enter a level (between 1 and 5): ";
	cin >> level;
	while (!isLevelValid(level))
	{
		cout << "Wrong input! Please enter level between 1 and 5!: ";
		cin >> level;
	}
}

bool isFree(char** field, unsigned int x, unsigned int y)
{
	return (field[x][y] != '*' && field[x][y] != '-');
}

void userInput(char** field, unsigned int& x, unsigned int& y, char& current_symbol, unsigned int size)
{
	cout << "Enter x, y and symbol('*' to fill the cell, '-' to mark as empty): ";
	cin >> x >> y >> current_symbol;
	while (!isValid(x, y, size) || !isFree(field, x, y) || !isValid(current_symbol))
	{
		if (!isValid(x, y, size))
			cout << "You have entered wrong coordinates (please enter coordinates between 0 and " << size << ")! Try again : ";
		
		else if (!isFree(field, x, y))
			cout << "This cell is already opened! Try again: ";
		
		else if(!isValid(current_symbol))
			cout << "You have entered wrong symbol! (please enter '*' to fill the cell or '-'to mark as empty)! Try again: ";

		cin >> x >> y >> current_symbol;			
	}
}

bool areAllFilledCellsInTheRowOpened(char** nonogram, int row, unsigned int size)
{
	for (size_t j = 0; j < size; j++)
	{
		if (nonogram[row][j] == '1') return false;
	}
	return true;
}

bool areAllFilledCellsInTheColumnOpened(char** nonogram, int column, unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (nonogram[i][column] == '1') return false;
	}
	return true;
}

void openCellsInRow(char** nonogram, unsigned int r, unsigned int size)
{
	for (size_t j = 0; j < size; j++)
	{
		if (nonogram[r][j] == '0') nonogram[r][j] = '-';
	}
}

void openCellsInColumn(char** nonogram, unsigned int c, unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (nonogram[i][c] == '0') nonogram[i][c] = '-';
	}
}

void openEmptyCells(char** nonogram, unsigned int i, unsigned int j, unsigned int size)
{
	if (areAllFilledCellsInTheRowOpened(nonogram, i, size))
	{
		openCellsInRow(nonogram, i, size);
	}
	if (areAllFilledCellsInTheColumnOpened(nonogram, j, size))
	{
		openCellsInColumn(nonogram, j, size);
	}
}

bool isWinner(char** matrix, unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (matrix[i][j] == '1') return false;
		}
	}
	return true;
}

bool isWinner2(char** matrix, unsigned int x, unsigned y, unsigned int& mistakes, char symbol, unsigned int size)
{
	if (symbol == '*')
	{
		if (matrix[x][y] == '0')
		{
			matrix[x][y] = '-';
			mistakes++;
		}
		else
		{
			matrix[x][y] = '*';
		}
	}
	else
	{
		if (matrix[x][y] == '1')
		{
			matrix[x][y] = '*';
			mistakes++;
		}
		else
		{
			matrix[x][y] = '-';
		}
	}
	openEmptyCells(matrix, x, y, size);

	return (isWinner(matrix, size));
}

void myStrCopy(const char* source, char* dest)
{
	if (source == nullptr || dest == nullptr)
		return;

	while (*source != '\0')
	{
		*dest = *source;
		dest++;
		source++;
	}
	*dest = '\0';
}

size_t myStrlen(const char* str)
{
	if (str == nullptr)
		return 0;

	size_t count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

void findMatrix(int level, char**& nonogram, unsigned int& size)
{
	if (level == 1)
	{
		size = 5;
		nonogram = createMatrix(size);
	}
	else if (level == 2)
	{
		size = 6;
		nonogram = createMatrix(size);
	}
	else if (level == 3)
	{
		size = 10;
		nonogram = createMatrix(size);
	}
	else if (level == 4)
	{
		size = 15;
		nonogram = createMatrix(size);
	}
	else if (level == 5)
	{
		size = 20;
		nonogram = createMatrix(size);
	}
}

void play(unsigned int level, unsigned int**& numbersInColumns, unsigned int**& numbersInRows)
{
	unsigned int x, y, mistakes = 0, size = 0;
	char current_symbol;

	string matrix;
	char** nonogram;
	int maxcolumns = 0, rows = 0, maxrows = 0, columns = 0;

	findMatrix(level, nonogram, size);
	printSourceCode(level, matrix, size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			nonogram[i][j] = matrix[j + i * size];
		}
	}
	numbersInColumns = createMatrix(size, size);
	numbersInRows = createMatrix(size, size);

	countNumbersInColumns(nonogram, size, maxcolumns, numbersInColumns, rows, columns, maxrows);
	countNumbersInRows(nonogram, size, numbersInRows, rows, maxcolumns);
	print2(nonogram, size, numbersInRows, numbersInColumns, rows, maxcolumns, maxrows, columns);

	while (true)
	{
		userInput(nonogram, x, y, current_symbol, size);
		if (isWinner2(nonogram, x, y, mistakes, current_symbol, size))
		{
			cout << "You won!\n";
			cout << "You have reached level "<< ++level << " !\n\n";
			play(level, numbersInColumns, numbersInRows);
		}

		if (mistakes == MAX_MISTAKES)
		{
			cout << "You lost!\n";
			break;
		}
		print2(nonogram, size, numbersInRows, numbersInColumns, rows, maxcolumns, maxrows, columns);
		cout << "Mistakes: " << mistakes << endl;
	}

}

int main()
{
	unsigned int level;
	string username, password;
	bool account_exists;

	cout << "Do you have an account? (1 - yes, 0 - no): ";
	cin >> account_exists;

	if (account_exists)
	{
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		if (!existingAccounts(username, password))
		{
			cout << "Wrong password!";
			return 0;
		}
	}
	else
	{
		cout << "Create an account!\n";
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		createAccount(username, password);
	}

	unsigned int** numbersInColumns = {0};
	unsigned int** numbersInRows = {0};
	levelInput(level);
	play(level, numbersInColumns, numbersInRows);
	return 0;
}

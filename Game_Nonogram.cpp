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
	//cout << matrix << endl;
	/*
	string line;
	unsigned int maxlength = 0;

	unsigned int numbers[5][5];
	//finding the max length
	for (size_t i = 0; i < size; i++)
	{
		getline(myfile, line);
		const int length = line.length();

		char* char_array = new char[length + 1];
		strcpy(char_array, line.c_str());

		for (size_t i = 0; i < length; i++)
		{
			u
		}
		for (int i = 0; i < length; i++)
		{
			std::cout << char_array[i];
		}
		cout << endl;
		delete[] char_array;
	}

	unsigned int** numbers = createMatrix(maxlength, size);

	for (size_t i = 0; i < maxlength; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			cout << numbers[i][j];
		}
	}

	*/

	/*
	int numbers[MAX_COUNT_OF_NUMBERS];
	string line;
	for (size_t i = 0; i < size; i++)
	{
		getline(myfile, line);
		numbers[i] = stoi(line);
		cout << numbers[i];
	}
	cout << matrix << endl;
	myfile.close();*/
}

void readCharArrayWithSpaces()
{
	std::ofstream out("test.txt");
	out << "free" << endl;
	out.close();
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

void printNumbersAboveNonogram( unsigned int** numbers, int maxrows, int columns, int maxcolumns)
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
				cout << ' ' << numbers[i][j] << "  ";
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
	//printNumbersLeftOfNonogram(numbers, rows, maxcolumns);
	//delete[] numbers;
	
}

void countNumbersInColumns(char** nonogram, unsigned int size, int& maxcolumns, unsigned int**& numbers,int& rows,int& columns,int& maxrows)
{
	//unsigned int** numbers = createMatrix(size, size);
	//int rows = 0, columns = 0, maxrows = 0;
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
	//printNumbersAboveNonogram(numbers, maxrows, columns, maxcolumns);
	//delete[] numbers;
}

void print2(char** field, unsigned int size,  unsigned int** numbersInRows, unsigned int** numbersInColums, int rows, int maxcolumns, int maxrows, int columns)
{
	//int rows = 0, maxcolumns = 0;
	
	
	//countNumbersInRows(field, size, numbersInRows, rows, maxcolumns);
	//countNumbersInColumns(field, size, maxcolumns, numbersInColums);

	/*for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			if ((field[i][j] != '*') && (field[i][j] != '-'))
			{
				cout << "[" << ' ' << "] ";
			}
			else
				cout << "[" << field[i][j] << "] ";
		cout << endl << endl;
	}*/

	printNumbersAboveNonogram(numbersInColums, maxrows, columns, maxcolumns);
	for (int i = 0; i < size; i++)
	{
		for (size_t j = 0; j < maxcolumns; j++)
		{
			if (numbersInRows[i][j] == 0) cout << "  ";
			else
				cout << numbersInRows[i][j] << ' ';
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

	/*for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < maxcolumns; j++)
		{
			if (numbers[i][j] == 0) cout << ' ';
			else
				cout << numbers[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;*/
	//delete[] numbersInRows;
}

bool isValid(unsigned int x, unsigned int y, char symbol, unsigned int size)
{
	return x >= 0 && y >= 0 && x < size&& y < size && (symbol == '-' || symbol == '*');
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
	while (!isValid(x, y, current_symbol, size) || !isFree(field, x, y))
	{
		cout << "This cell is already opened! Try again: ";
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

/*/
void convertInMatrix(string matrix, char* nonogram[][])
{
	unsigned int matrix_size = sqrt(myStrlen(nonogram));
	for (size_t i = 0; i < matrix_size; i++)
	{
		for (size_t j = 0; j < matrix_size; j++)
		{
			nonogram[i][j] = matrix[j + i * matrix_size];
		}
	}

	for (size_t i = 0; i < matrix_size; i++)
	{
		for (size_t j = 0; j < matrix_size; j++)
		{
			cout << nonogram[i][j] << " ";
		}
		cout << endl;
	}
}*/

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

/*
void play(unsigned int level, char**& nonogram, unsigned int size, string matrix, int& rows, int& columns, int& maxrows, int& maxcolumns)
{

	findMatrix(level, nonogram, size);
	printSourceCode(level, matrix, size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			nonogram[i][j] = matrix[j + i * size];
		}
	}
	unsigned int** numbersInColumns = createMatrix(size, size);
	unsigned int** numbersInRows = createMatrix(size, size);

	countNumbersInColumns(nonogram, size, maxcolumns, numbersInColumns, rows, columns, maxrows);
	countNumbersInRows(nonogram, size, numbersInRows, rows, maxcolumns);
	print2(nonogram, size, numbersInRows, numbersInColumns, rows, maxcolumns, maxrows, columns);
}*/

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
		cout << "Create an account!" << endl;
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		createAccount(username, password);
	}

	
	levelInput(level);
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
	unsigned int** numbersInColumns = createMatrix(size, size);
	unsigned int** numbersInRows = createMatrix(size, size);

	countNumbersInColumns(nonogram, size, maxcolumns, numbersInColumns, rows, columns, maxrows);
	countNumbersInRows(nonogram, size, numbersInRows, rows, maxcolumns);
	print2(nonogram, size, numbersInRows, numbersInColumns,rows, maxcolumns, maxrows, columns);

	
	while (true)
	{
		userInput(nonogram, x, y, current_symbol, size);
		if (isWinner2(nonogram, x, y, mistakes, current_symbol, size))
		{
			cout << "You won!/n";
			break;
		}

		if (mistakes == MAX_MISTAKES)
		{
			cout << "You lost!";
			break;
		}
		print2(nonogram, size, numbersInRows, numbersInColumns, rows, maxcolumns, maxrows, columns);
		cout << "Mistakes: " << mistakes << endl;
	}
}

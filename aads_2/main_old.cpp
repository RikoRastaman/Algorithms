#include <iostream>
#include <string>
#include "fstream"
#include <Windows.h>

/*
8. Выборы  старосты  в  группе  студентов  из   M   человек
организованы  по следующим правилам.  Задаются целые числа N и
K.  Студенты становятся по  кругу  в  соответствии  со  своими
номерами в журнале. Начиная от N-го студента отсчитывается K-й
студент.  Счет ведется циклически по возрастанию номеров. Этот
студент   выбывает  из  претендентов.  Начиная  со  следующего
студента,  процедура повторяется. Последний оставшийся студент
становится старостой.  Ввести значения M,  N,  K и найти номер
старосты (7).*/

using namespace std;

int main()
{

	string str;
	string fileName;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Enter input file name: ";
	cin >> fileName;
	// cout << "Enter the name of the file" << endl;
	//getline(cin, fileName);
	//cin >> fileName;

	// ifstream inputFile;
	// inputFile.open("input.txt");
	//inputFile.open("input.txt");
	// ofstream outputFile;
	// outputFile.open("output.txt ");
}

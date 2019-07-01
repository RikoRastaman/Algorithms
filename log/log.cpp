#include <iostream>
#include <limits>
#include <fstream>
#include <ostream>
#include <array>
/*
		3.5. Распил бруса (7)
	На пилораму привезли брус длиной L метров. Известны места, в которых необходимо сделать
	распилы. Стоимость одного распила равна длине распиливаемого бруса. Различный порядок
	распилов приводит к различным итоговым ценам. Например, брус длиной 10 метров, который
	нужно распилить на расстоянии 2, 4 и 7 метров можно пилить разными способами. Можно
	распилить сначала на отметке 2, потом 4 и потом 7. Стоимость будет 10+8+6=24. А если сначала
	распилить на отметке 4, потом 2 и затем 7, то стоимость составит 10+4+6=20. Требуется написать
	программу, которая определяла бы минимальную стоимость распила.
	Ввод из файла INPUT.TXT. В первой строке содержатся через пробел натуральные числа
	L и N (1 ≤ L ≤ 500, N &lt; L) – длина бруса и число разрезов. Вторая строка содержит N натуральных
	чисел C i (0&lt;C i &lt;L) через пробел, задающих в строго возрастающем порядке места, в которых
	нужно сделать распилы.
	Вывод в файл OUTPUT.TXT.. В единственной строке вывести минимальную стоимость
	распилов.

	Семеев Максим ПС-21
	Visual Studio 2017
*/
int main()
{
	std::ifstream inputFile;
	inputFile.open("INPUT.txt");
	std::ofstream outputFile;
	outputFile.open("OUTPUT.txt");
	if(!inputFile.is_open() || !outputFile.is_open())
	{
		std::cout << "Can not open file." << std::endl;
		return 1;
	}
		std::array< std::array <int, 502>, 502> costCutSegment;
		std::array<int, 502 > coordinatCut;

		int numberCut;
		int lenLog;
		inputFile >> lenLog >> numberCut;

		coordinatCut[0] = 0;
		for (int i = 1; i <= numberCut; i++)
		{
			inputFile >> coordinatCut[i];
		}
		coordinatCut[++numberCut] = lenLog;

		for (int i = 0; i <= numberCut; i++)
		{
			costCutSegment[i][i] = costCutSegment[i][i + 1] = 0;
		}

		int i;
		for (int m = 2; m <= numberCut; m++)
		{
			for (i = 0; i + m <= numberCut; i++)
			{
				int cost = coordinatCut[i + m] - coordinatCut[i];
				costCutSegment[i][i + m] = std::numeric_limits<int>::max();

				for (int j = 1; j < m; j++)
				{
					if (costCutSegment[i][i + m] > costCutSegment[i][i + j] + costCutSegment[i + j][i + m])
					{
						costCutSegment[i][i + m] = costCutSegment[i][i + j] + costCutSegment[i + j][i + m];
					}
				}

				costCutSegment[i][i + m] += cost;
			}
		}

		outputFile << costCutSegment[0][numberCut] << std::endl;
	
	return 0;
}

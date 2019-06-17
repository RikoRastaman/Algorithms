#include <iostream>
#include <limits>
#include <fstream>
#include <ostream>

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
		const int MAX_LENGTH_LOG = 502;
		int costCutSegment[MAX_LENGTH_LOG][MAX_LENGTH_LOG];
		int coordinatCut[MAX_LENGTH_LOG];

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
				int L = coordinatCut[i + m] - coordinatCut[i];
				costCutSegment[i][i + m] = std::numeric_limits<int>::max();

				for (int j = 1; j < m; j++)
				{
					if (costCutSegment[i][i + m] > costCutSegment[i][i + j] + costCutSegment[i + j][i + m])
					{
						costCutSegment[i][i + m] = costCutSegment[i][i + j] + costCutSegment[i + j][i + m];
					}
				}

				costCutSegment[i][i + m] += L;
			}
		}

		outputFile << costCutSegment[0][numberCut] << std::endl;
	
	return 0;
}

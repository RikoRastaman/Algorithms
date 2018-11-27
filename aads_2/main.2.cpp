#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <string>
#include <Windows.h>
/*
8. Выборы старосты в группе студентов из M человек
организованы по следующим правилам. Задаются целые числа N и
K. Студенты становятся по кругу в соответствии со своими
номерами в журнале. Начиная от N-го студента отсчитывается K-й
студент. Счет ведется циклически по возрастанию номеров. Этот
студент выбывает из претендентов. Начиная со следующего
студента, процедура повторяется. Последний оставшийся студент
становится старостой. Ввести значения M, N, K и найти номер
старосты (7).
*/

using namespace std;

int GetStudent(int n, int groupSize)
{

    if (groupSize > n)
    {
        return n;
    }
    int coef = (groupSize) / n;

    if (coef >= 1)
    {
        return n;
    }
    else
    {

        if ((n % groupSize) == 0)
        {
            return groupSize;
        }
        else
        {
            while (!(n < groupSize))
            {
                n = n - groupSize;
            }
            return n;
        }
    }
}

int GetBoss(int n, int k, int groupSize)
{
    // cout << "N in getboss=" << n << endl;
    // k;
    // groupSize;
    if (n + k - 1 > groupSize)
    {
        // int coef = ((n + k) / groupSize);
        int bossPosition = (n + k - 1);
        while (!(bossPosition < groupSize))
        {
            bossPosition = bossPosition - groupSize;
        }

        // int bossPosition = (n + k - 1) - groupSize * coef;
        return bossPosition;
    }
    else
    {
        // cout << n - 1 + k << endl;
        return n - 1 + k; // n-1 or n
    }
}

int main()
{
    int m = 0;
    int n = 0;
    int k = 0;
    int startStudent = 0;
    int temporaryStudent = 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    string inputFile;
    string outputFile = "output.txt";
    cout << "Enter input file name: ";
    cin >> inputFile;

    ifstream fileForInput(inputFile);
    ofstream fileForOutput(outputFile);
    if (!fileForInput.is_open())
    {
        cout << "File does not opened";
    }
    else
    {
        while (fileForInput >> m >> n >> k)
        {

            // cout << "Enter M: ";
            // cin >> m;
            // cout << "Enter N: ";
            // cin >> n;
            // cout << "Enter K: ";
            // cin >> k;

            vector<int>
                group = vector<int>(m);
            std::iota(std::begin(group), std::end(group), 1); // Fill with 1, ..., 99.

            fileForOutput << "CLASS: ";
            for (std::vector<int>::const_iterator i = group.begin(); i != group.end(); ++i)
                fileForOutput << *i << ' ';

            fileForOutput << endl;
            startStudent = GetStudent(n, group.size());
            while (group.size() != 1)
            {
                cout << "[size OF CLASS] : " << group.size() << endl;

                // cout << GetBoss(GetStudent(n, group.size()), k, group.size()) << endl;

                cout << "StartST: " << startStudent << endl;
                cout << "GetBoss student: " << GetBoss(startStudent, k, group.size()) << endl;
                temporaryStudent = GetBoss(startStudent, k, group.size());

                group.erase(group.begin() + (GetBoss(startStudent, k, group.size()) - 1));

                startStudent = temporaryStudent; //or +1

                if (startStudent > group.size())
                {
                    startStudent = 1;
                }

                fileForOutput << "CLASS: ";
                for (std::vector<int>::const_iterator i = group.begin(); i != group.end(); ++i)
                    fileForOutput << *i << ' ';
                fileForOutput << endl;
            }
            fileForOutput << "Староста: " << group[0] << std::endl;
            //std::cout << group[1] << std::endl;
        }
    }
    return 0;
}
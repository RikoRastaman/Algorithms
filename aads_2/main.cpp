#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <string>
#include <Windows.h>
/*
8. ¬ыборы старосты в группе студентов из M человек
организованы по следующим правилам. «адаютс€ целые числа N и
K. —туденты станов€тс€ по кругу в соответствии со своими
номерами в журнале. Ќачина€ от N-го студента отсчитываетс€ K-й
студент. —чет ведетс€ циклически по возрастанию номеров. Ётот
студент выбывает из претендентов. Ќачина€ со следующего
студента, процедура повтор€етс€. ѕоследний оставшийс€ студент
становитс€ старостой. ¬вести значени€ M, N, K и найти номер
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
    if (n + k - 1 > groupSize)
    {
        int bossPosition = (n + k - 1);
        if ((bossPosition % groupSize) == 0)
        {
            return groupSize;
        }
        while (!(bossPosition < groupSize))
        {
            bossPosition = bossPosition - groupSize;
        }
        return bossPosition;
    }
    else
    {
        return n - 1 + k;
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
            if (m == 0 || n == 0 || k == 0)
            {
                fileForOutput << "ERROR: Input zero";
                break;
            }
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
                // fileForOutput << "StartST: " << startStudent << endl;
                // fileForOutput << "GetBoss student: " << GetBoss(startStudent, k, group.size()) << endl;
                temporaryStudent = GetBoss(startStudent, k, group.size());

                group.erase(group.begin() + (GetBoss(startStudent, k, group.size()) - 1));

                startStudent = temporaryStudent;

                if (startStudent > group.size())
                {
                    startStudent = startStudent - group.size();
                }

                fileForOutput << "CLASS: ";
                for (std::vector<int>::const_iterator i = group.begin(); i != group.end(); ++i)
                    fileForOutput << *i << ' ';
                fileForOutput << endl;
            }
            fileForOutput << "—тароста: " << group[0] << std::endl;
        }
    }
    return 0;
}
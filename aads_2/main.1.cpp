#include <iostream>
#include <vector>
#include <numeric>
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
    cout << "Group size in student" << groupSize << endl;
    if (groupSize > n) ///or -1
    {
        return n; // n-1 or n
    }
    int coef = (groupSize) / n;
    cout << "coef=>" << coef << endl;
    if (coef >= 1)
    {
        return n; // or * coef
    }
    else
    {
        cout << n % groupSize << "%%" << endl;
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
            // return n - groupSize;
        }
    }
}

int GetBoss(int n, int k, int groupSize)
{
    cout << "N in getboss=" << n << endl;
    k;
    groupSize;
    if (n + k > groupSize)
    {
        int coef = ((n + k) / groupSize);
        int bossPosition = (n + k) - coef * groupSize;
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
    cout << "Enter M: ";
    cin >> m;
    cout << "Enter N: ";
    cin >> n;
    cout << "Enter K: ";
    cin >> k;

    vector<int> group = vector<int>(m);
    std::iota(std::begin(group), std::end(group), 1); // Fill with 1, ..., 99.

    for (std::vector<int>::const_iterator i = group.begin(); i != group.end(); ++i)
        std::cout << *i << ' ';
    while (group.size() != 1)
    {
        // cout << GetBoss(GetStudent(n, group.size()), k, group.size()) << endl;
        group.erase(group.begin() + GetBoss(GetStudent(n, group.size()), k, group.size()));
    }
    std::cout << group[1] << std::endl;
    return 0;
}
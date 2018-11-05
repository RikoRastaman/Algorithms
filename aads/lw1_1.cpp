#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <clocale>
using namespace std;

/*
   10. Имеется текстовый файл с некоторым описанием. Переносов
слов нет.  Требуется каждые 3 предложения выделить в отдельный
абзац.  Каждое   предложение   может   заканчиваться   точкой,
вопросительным либо восклицательным знаком (6).

вывод в файл, перенос после конца строки
*/

bool checkMultiDots(string &strWithDots, int i)
{
    if (i + 2 < strWithDots.length())
    {
        return (strWithDots[i] == '.' && strWithDots[i + 1] == '.' && strWithDots[i + 2] == '.');
    }
    return false;
}

void deleteSpacesFromBegin(string &strWithSpaces)
{
    int i = 0;
    while (strWithSpaces[i] == ' ' && i < strWithSpaces.length())
    {
        i++;
    }
    strWithSpaces.erase(strWithSpaces.begin(), strWithSpaces.begin() + i);
}

void deleteSpacesFromEnd(string &strWithSpaces)
{
    int i = strWithSpaces.length() - 1;
    while (strWithSpaces[i] == ' ' && i != 0)
    {
        i--;
    }
    strWithSpaces.erase(strWithSpaces.begin() + i + 1, strWithSpaces.end());
}

int main()
{
    setlocale(LC_ALL, "1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string str;
    string fileName;
    string outputFile;
    cout << "Enter input file name: ";
    cin >> fileName;
    
    
    ifstream file(fileName);
    ofstream fileOutput(outputFile);
    if (!file.is_open())
    {
        cout << "File does not opened";
    }
    else
    {
        while (!file.eof())
        {
            getline(file, str);
            deleteSpacesFromBegin(str);
            deleteSpacesFromEnd(str);
            int counter = 0;
            for (int i = 0; i < str.length(); ++i)
            {
                if (checkMultiDots(str, i))
                {
                    fileOutput << str[i] << str[i + 1] << str[i + 2];
                    i += 2;
                    counter++;
                    continue;
                }

                // if (str[i] == '\n')
                // {
                //     cout << str[i] << endl;
                // }
                fileOutput << str[i];

                if (str[i] == '.' || str[i] == '!' || str[i] == '?')
                {
                    ++counter;
                    if (counter == 3)
                    {
                        fileOutput << endl;
                        counter = 0;
                        if (i != str.length() && str[i + 1] == ' ')
                        {
                            ++i;
                        }
                    }
                }
            }
            fileOutput << endl;
        }
    }
    return 0;
}
